
#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
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
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
vector<int> matchR, visitedL;

bool aum(int LEFT, vector<vector<int>> &al){
    if(visitedL[LEFT]) return false;
    visitedL[LEFT] = 1;
    for(int RIGHT: al[LEFT]){
        if(matchR[RIGHT] == -1  || aum(matchR[RIGHT], al)){
            matchR[RIGHT] = LEFT;
            return true; //current can be matched
        }
    }
    return false; // current cannot be matched
}

void solve() 
{
    // normal augmenting algorithm; O(V*E)
    int n, m; cin >> n >> m;
    matchR.assign(m, -1);
    visitedL.assign(n, 0);
    vector<vector<int>> al(n, vector<int>());
    FOR(i, n){
        FOR(j, m){
            int num; cin >> num;
            if(num==1){
                al[i].push_back(j);
            }
        }
    }
    FOR(i, n){
        visitedL.assign(n, 0);
        aum(i, al);
    }
    int ret=0;
    FOR(i, m){
        if(matchR[i] != -1){
            ret++;
        }
    }
    cout << "a maximum of " <<  ret << " nuts and bolts can be fitted together";



}

