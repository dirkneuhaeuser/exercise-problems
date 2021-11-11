#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
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

int idx;
unordered_map<string, int> name2idx;
vector<string> idx2name;
vector<vector<pll>> AL;

void addName(string name){
    if(name2idx.count(name) ==0){
        name2idx[name] = idx++;
        idx2name.push_back(name);
        AL.push_back({});
    }
}




vector<ll> faster_dijkstra(ll start, vector<vector<pll>> &AL, vector<int> &par){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHTS (normal one does work with negative weights)
    ll n = AL.size();
    vector<ll> dist(AL.size(), INF);
    dist[start] = 0;
    set<pll> pq;
    pq.emplace(dist[start], start);
    while(pq.size()){
        auto [cost, cur] = *pq.begin(); // intotal O(V * log(V))
        pq.erase(pq.begin());
        for(auto [next, w]: AL[cur]){
            if(dist[cur] + w-1 >= dist[next]) continue;
            auto it = pq.find({dist[next], next});
            if(it != pq.end()){
                pq.erase(it); // O(E * log(V));
            }
            par[next]=cur;
            dist[next] = dist[cur] + w -1;
            pq.emplace(dist[next], next);

        }
    }
    return dist;
}



void solve() 
{
    // Weighted SSSDSP. Major issue is converting the names. With Reconstruction.
    string startName, endName;
    while(cin >> startName >> endName){
        int lines;cin >> lines;
        name2idx.clear();
        idx2name.clear();
        idx = 0;
        AL.clear();
        addName(startName);
        addName(endName);

        string line;
        getline(cin, line);
        
        FOR(i, lines){
            getline(cin, line);
            stringstream ss; ss << line;
            vector<string> names;
            string name;
            while(ss >> name){
                names.push_back(name);
                addName(name);
            }
            int nClass = names.size();
            FOR(ii, nClass){
                int a = name2idx[names[ii]];
                for(int jj = ii+1; jj<nClass; ++jj){
                    int b = name2idx[names[jj]];
                    AL[a].push_back({b, nClass});
                    AL[b].push_back({a, nClass});
                }
            }
        }
        int n = idx2name.size();
        vector<int> par(n); FOR(i, n) par[i]=i;
        vector<ll> dist = faster_dijkstra(0, AL, par);
        int idxEnd = name2idx[endName];
        ll ret = dist[idxEnd];
        if(ret == INF){
            cout << "impossible" <<endl;
        }else{
            cout << ret-1;
            int cur = 1;
            vector<string> toTraverse;
            while(true){
                toTraverse.push_back(idx2name[cur]);
                if(cur == par[cur])break;
                cur = par[cur];
            }
            FOR(i, toTraverse.size()){
                cout << " " << toTraverse[toTraverse.size() - 1 - i];
            }
            cout << endl;
        }
    }

}

