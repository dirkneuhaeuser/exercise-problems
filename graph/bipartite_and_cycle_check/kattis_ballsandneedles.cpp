#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long, long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tii;
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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

enum {VISITED=-2, UNVISITED=-1, EXPLORED=-3};


template <class T>
bool existCycle(T cur, map<T, set<T>> &AL, map<T, int> &v, map<T, T> &parent){
    v[cur] = EXPLORED;
    for(T next: AL[cur]){
        if(next == cur) continue;
        if(v[next] == EXPLORED){
            // check if direckt parent
            if(parent[cur] == next) continue;
            return true;
        }else if(v[next] == UNVISITED){
            parent[next] = cur;
            if(existCycle(next, AL, v, parent)) return true;
        }
    }
    return false;

}



void solve() 
{
    // 3D cycle detetcion and 2D cycle detection.
    // Note that due to the loss of a dimension, some cycles (in height) are not longer cycles, 
    // and some none-cycles (because of differences in height) might have become cycles.
    int n; cin >> n;
    map<tii, set<tii>> AL;
    map<pii, set<pii>> ALS;
    FOR(i, n){
        int x, y, z, x1, y1, z1; cin >> x >> y >> z >> x1 >> y1 >> z1;
        tii t1{x, y, z};
        tii t2{x1, y1, z1};
        pii p1{x, y};
        pii p2{x1, y1};
        AL[t1].insert(t2);
        AL[t2].insert(t1);
        ALS[p1].insert(p2);
        ALS[p2].insert(p1);
    }
    bool cycleAir = false;
    bool cycleShadow = false;

    // air cycle
    map<tii, int>  v;
    map<tii, tii>  parent;
    for(auto [k, val]: AL){
        for(tii e: val){
            v[e] = UNVISITED;
            parent[e] = {0, 0, 0};
        }
    }
    for(auto [k, val]: AL){
        for(tii e: val){
            if(v[e] == UNVISITED){
                bool ans = existCycle(e, AL, v, parent);
                if(ans)cycleAir = true;
            }
        }
    }

    map<pii, int>  vS;
    map<pii, pii>  parentS;
    for(auto [k, val]: ALS){
        for(pii e: val){
            vS[e] = UNVISITED;
            parentS[e] = {0, 0};
        }
    }
    for(auto [k, val]: ALS){
        for(pii e: val){
            if(vS[e] == UNVISITED){
                bool ans = existCycle(e, ALS, vS, parentS);
                if(ans)cycleShadow = true;
            }
        }
    }
    if(cycleAir){
        cout << "True closed chains" <<endl;
    }else{
        cout << "No true closed chains" <<endl;
    }
    if(cycleShadow){
        cout << "Floor closed chains" <<endl;
    }else{
        cout << "No floor closed chains" <<endl;
    }



}

