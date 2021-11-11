#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
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
    // Unweigted SSMDSP: For all important station do a level bfs, and get the one with lowest average
    int n, s; cin >> n >> s;
    string line; getline(cin, line);
    vector<set<int>> AL(n, set<int>());
    unordered_set<int> seen;
    set<int> important;
    FOR(i, s){
        getline(cin, line);
        stringstream ss;
        ss << line;
        int prev = - 1;
        int station;
        unordered_set<int> seenCur;
        while(ss >> station){
            if(station == 0) break;
            station--;
            if(seen.count(station)){
                important.insert(station);
            }
            seenCur.insert(station);
            if(prev != -1){
                AL[prev].insert(station);
                AL[station].insert(prev);
            }
            prev = station;
        }
        for(int cur: seenCur){
            seen.insert(cur);
        }
    }
    int ret = INF;
    int idx = -1;
    for(int imp: important){
        vector<bool> seen(n, false);
        vector<int> dist(n, -1);
        int shortestPath = 0;
        vector<int> q{imp};
        seen[imp] = true;
        while(q.size()){
            vector<int> nq;
            for(int cur: q){
                dist[cur] = shortestPath;
                for(int next: AL[cur]){
                    if(seen[next] == false){
                        seen[next] = true;
                        nq.push_back(next);
                    }
                }
            }
            shortestPath++;
            q = nq;
        }
        int ans = 0;
        for(int check: important){
            ans += dist[check];
        }
        if(ans < ret){
            ret = ans;
            idx = imp;
        }
    }
    cout << "Krochanska is in: " << idx+1;

}

