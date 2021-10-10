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
        cout<<"Case #" << count++ << endl;
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 


//vector<int> hierholzer(int s, int n, vector<vector<int>> &AL){
//    vector<int> ret, stack, idx(n, 0);
//    stack.push_back(s);
//    while(stack.size()){
//        int cur = stack.back();
//        cout << cur << "-> ";
//        if(idx[cur] < AL[cur].size()){
//            stack.push_back(AL[cur][idx[cur]]);
//            idx[cur]++;
//        }else{
//            int justFinishedCycle = stack.back(); stack.pop_back();
//            ret.push_back(justFinishedCycle);
//        }
//    }
//    return ret;
//}
void eulerTour(int cur, vector<vector<int>> &AM){
    // this is similar to hierolzer: post order as well
    for(int i=0; i<50; ++i){
        if(AM[cur][i]){
            AM[cur][i]--;
            AM[i][cur]--;
            eulerTour(i, AM);
            cout << i+1 << " " << cur+1 << endl; // need postorder here because maybe in i+1 it ends, then we dont want to print it before
        }
    }

}


void solve() 
{
    // euler tour but on an undirected graph. With retrievel.
    int n;cin >> n;
    vector<int> colors(50, 0);
    vector<vector<int>> AM(50, vector<int>(50, 0));
    int start = -1;
    FOR(i, n){
        int a, b; cin >> a >> b;
        a--; b--;
        start = a;
        colors[a]++;
        colors[b]++;
        AM[a][b]++;
        AM[b][a]++;
    }
    int off = 0;
    FOR(i, 50){
        if(colors[i]&1){
            off++;
        }
    }
    if(off == 0){
        eulerTour(start, AM);

    }else{
        cout << "some beads may be lost" << endl;
    }

}

