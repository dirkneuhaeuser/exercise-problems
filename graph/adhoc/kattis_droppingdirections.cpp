#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int, int> tiiii;
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

set<pair<int, int>> seen;

void mark(int from, int to, vector<tiiii> &e){
    //cout << from <<  " " << to << endl;
    auto [a,b,c,d] = e[to];
    if(from < to){
        seen.insert({from, to});
    }else{
        seen.insert({to, from});
    }
    int next = -1;
    if(from == a) next = c;
    if(from == b) next = d;
    if(from == c) next = a;
    if(from == d) next = b;
    //cout << from << " " << to << endl;
    if(a<next){
        if(seen.count({to, next}) == 0){
            mark(to, next, e);
        }
    }else{
        if(seen.count({next, to}) == 0){
            mark(to, next, e);
        }
    }



}


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
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    // Just count all cycles, but do not count the intial 1-2 cycles which go thorugh the goal
    int n, goal; cin >> n >> goal;

    goal--;
    vector<tiiii>e;
    FOR(i, n){
        int a,b,c,d; cin >> a >> b >>c >> d;
        a--; b--; c--; d--;
        e.push_back({a, b, c, d});
    }
    seen.clear();

    auto [ag,bg,cg,dg] = e[goal];
    mark(ag, goal, e);
    mark(bg, goal, e);


    int ret = 0;
    FOR(i, n){
        auto [a,b,c,d] = e[i];
        // opt1:
        if(i < c){
            if(seen.count({i, c}) == 0){
                ret++;
                mark(i, c, e);
            }
        }else{
            if(seen.count({c, i}) == 0){
                ret++;
                mark(i, c, e);
            }
        }
        // opt2:
        if(i < d){
            if(seen.count({i, d}) == 0){
                ret++;
                mark(i, d, e);
            }
        }else{
            if(seen.count({d, i}) == 0){
                ret++;
                mark(i, d, e);
            }
        }

    }
    cout << ret;
    

}

