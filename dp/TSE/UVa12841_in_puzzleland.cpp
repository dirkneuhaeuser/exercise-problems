#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
// 2**6 =  64                           // 4!  = 24                       
// 2**8 =  256                          // 5!  = 120                      
// 2**10 = 1,024                        // 6!  = 720
// 2**15 = 32,768                       // 7!  = 5,040
// 2**20 = 1,048,576                    // 8!  = 40,320
// 2**25 = 33,554,432                   // 9!  = 362,880
// 2**30 = 1,073,741,824                // 10! = 3,628,800
// 2**32 = 4,294,967,296                // 12! = 479,001,600
                                        // 14! = 87,178,291,200
// int up to  2*10^9 (2^31-1)           // 16! = 20,922,789,888,000
// ll up to   9*10^18 (2^63 -1)         // 18! = 6,402,373,705,728,000
// ull up to 18*10^18 (2^64-1)/         // 20! = 2,432,902,008,176,640,000                                                                    
// ld up to  10*10^307
ll smod(ll a, ll m){return((a%m) +m) %m;}
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*smod(b, m),m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
const int MOD = 1000000007;
const int INF = 1<<30;


void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/output.txt", "w", stdout); 
    #endif 
    
    int t=1; 
    cin >> t;
    int count = 1;
    while(t--) 
    { 
        cout<<"Case " << count++ << ": ";
        solve(); 
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
int memo[16][(1<<16)-1];

int LSOne(int x){
    return x&(-x);
}


int dp(int cur, int mask, int end, vector<vector<bool>> &am){
    int &ans = memo[cur][mask];
    if(ans != -1) return ans;
    if(cur  == end){
        if(mask == 0){
            return ans = 1;
        }
        return ans = 0;
    }
    int m = mask;
    while(m){
        int v = LSOne(m);
        int next = __builtin_ctz(v);
        if(am[cur][next] && dp(next, mask^v, end, am)==1){
            return ans = 1;
        }
        m^=v;
    }
    return ans = 0;
}

void retrieve_solution(int cur, int mask, int end, vector<vector<bool>> &am, vector<int> &ret){
    ret.push_back(cur);
    int m = mask;
    while(m){
        int v = LSOne(m);
        int next = __builtin_ctz(v);
        if(am[cur][next] && memo[next][mask^v]==1){
            retrieve_solution(next, mask^v, end, am, ret);
        }
        m^=v;
    }
    return;
}

void solve() 
{
    // Hemiltonian Path Problem. 
    // Find the lexicographically smallest solution, therefore, sort the bitmask, such that first bit(from right) stands
    // for the smalles lexicographically value and when passing through the mask int the top-down held-karp algorithm we
    // get the first set bit with LSOne, which aotmatically is the smallest possible lexicographically value for the current mask. 
    // Then just check if it is indead possible to go that way or aboard. Also retrieve the solution afterwards.
    int n, m; cin >> n >> m;
    vector<char> lets(n);
    FOR(i,n){
        cin >> lets[i];
    }
    char cStart = lets[0];
    char cEnd = lets.back();
    sort(lets.begin(), lets.end());
    vector<vector<bool>> am(n, vector<bool>(n, false));
    FOR(j, m){
        char a, b; cin >> a >> b;
        int idxA = find(lets.begin(), lets.end(), a) - lets.begin();
        int idxB = find(lets.begin(), lets.end(), b) - lets.begin();
        am[idxA][idxB] = true;
        am[idxB][idxA] = true;
    }
    int start = find(lets.begin(), lets.end(), cStart) - lets.begin();
    int end = find(lets.begin(), lets.end(), cEnd) - lets.begin();
    int mask = (1<<n) -1;
    memset(memo, -1, sizeof memo);
    int ans = dp(start, mask ^ (1<<start), end, am);
    if(ans == 1){
        vector<int> ret;
        retrieve_solution(start, mask ^ (1<<start), end, am, ret);
        FOR(i, ret.size()){
            cout << lets[ret[i]];
        }
        cout << endl;
    }else{
        cout <<"impossible" << endl;
    }

}

