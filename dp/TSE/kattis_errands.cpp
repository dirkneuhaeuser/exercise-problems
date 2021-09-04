#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
typedef pair<ld, ld> pld;
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
unordered_map<string, pld> coords;
ld memo[12][(1<<10)];


void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/output.txt", "w", stdout); 
    #endif 
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

ld distance(string &a, string &b){
    ld fst = pow(coords[a].first - coords[b].first, 2);
    ld snd = pow(coords[a].second - coords[b].second, 2);
    ld ret =sqrt(fst + snd);
    return ret;
}

int LSOne(int x){
    return x&-x;
}

ld dp(int cur, int mask, vector<string> &locs){
    ld &ans = memo[cur][mask];
    if(ans != -1) return ans;
    if(mask == 0){
        return ans = distance(locs[cur], locs.back());
    }
    ans = DBL_MAX;
    int m = mask;
    while(m){
        int v = LSOne(m);
        int next = __builtin_ctz(v) + 1;
        ans = min(ans, distance(locs[cur], locs[next]) + dp(next, mask^v, locs));
        m ^= v;
    }
    return ans;
}

void backtrack(int cur, int mask, vector<string> &locs, vector<string> &sol){
    sol.push_back(locs[cur]);
    if(mask == 0){
        return;
    }
    ld &ans = memo[cur][mask];
    int m = mask;
    while(m){
        int v = LSOne(m);
        int next = __builtin_ctz(v) + 1;
        if(ans == distance(locs[cur], locs[next]) + dp(next, mask^v, locs)){
            return backtrack(next, mask^v, locs, sol);

        }
        m ^= v;
    }
    return;
    
}


void solve() 
{
     
    // Basic hamiltonian path.
    int n; cin >> n;
    FOR(i, n){
        string name; cin >> name;
        ld a, b; cin >> a >> b;
        coords[name] = {a, b};
    }
    string line;
    while(getline(cin, line)){
        if(line == "") continue;
        stringstream ss; ss << line;
        string location; 
        vector<string> locations;
        locations.push_back("work");
        while(ss >> location){
            locations.push_back(location);
        }
        locations.push_back("home");
        fill_n(&memo[0][0], 12*(1<<10), -1);
        int mask = (1<<(locations.size() - 2))-1;
        ld ret = dp(0, mask, locations);

        vector<string> sol;
        backtrack(0, mask, locations, sol);
        for(int i=1;i<sol.size();++i){
            cout << sol[i];
            if(i< sol.size()-1){
                cout << " ";
            }
        }
        cout << endl;

        
    }


}
