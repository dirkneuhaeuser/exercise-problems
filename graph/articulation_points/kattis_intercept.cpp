#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef tuple<long long, long long, long long> tll;
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
const ll INF = 1ll<<60;


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

vector<vector<pii>> AL;
vector<vector<pii>> ALRev;
vector<ll> dis, disRev;
vector<ll> counter;



void solve() 
{
    // 1. reduce graph to only shortest paths (from end to begin, to have the differences left)
    // 2. On that graph, pretend you have an undirected graph(thats ok, as all possible ways (apart of backwards are shortest paths) and find articulation points
    // does not work :(

    int n, m; cin >> n >> m;
    AL.assign(n, vector<pii>());
    ALRev.assign(n, vector<pii>());
    FOR(i, m){
        int a, b;
        ll w; 
        cin >> a >> b >> w;
        AL[a].push_back({b, w});
        ALRev[b].push_back({a, w});
        //if(a == 0) cout <<i <<  " " << b << endl;
    }
    //dbg(AL);
    ll start, end; cin >> start >> end;
    //cout << start << " " << end << endl;

    dis.assign(n, INF);
    disRev.assign(n, INF);
    map<ll, ll> counter, counterRev;

    priority_queue<tll, vector<tll>, greater<tll>> pq;
    pq.push({0, start, 1});
    while(pq.size()){
        auto[wCur, cur, a] = pq.top(); pq.pop();
        while(pq.size()){
            auto [ww, cc, aa] =pq.top();
            if(cc == cur){
                a+=aa;
                pq.pop();
            }else{
                break;
            }
        }
        if(dis[cur] < wCur) continue;
        //cout << cur << endl;
        counter[cur] += a;
        if(dis[cur] == wCur)continue;
        dis[cur] = wCur;
        for(auto [next, wNext]: AL[cur]){
            if(wNext + wCur <= dis[next]){
                pq.push({wNext+wCur, next, a});
            }
        }
    }
    priority_queue<tll, vector<tll>, greater<tll>> pqRev;
    pqRev.push({0, end, 1});
    while(pqRev.size()){
        auto[wCur, cur, a] = pqRev.top(); pqRev.pop();
        while(pqRev.size()){
            auto [ww, cc, aa] =pqRev.top();
            if(cc == cur){
                a+=aa;
                pqRev.pop();
            }else{
                break;
            }
        }
        if(disRev[cur] < wCur) continue;
        //cout << cur << endl;
        counterRev[cur] += a;
        if(disRev[cur] == wCur)continue;
        disRev[cur] = wCur;
        for(auto [next, wNext]: ALRev[cur]){
            if(wNext + wCur <= disRev[next]){
                pqRev.push({wNext+wCur, next, a});
            }
        }
    }

    ll allShortestPaths = counter[end];
    set<ll> all;
    for(auto [k, v]: counter){
        if(k == start || k == end ||((v*counterRev[k] == allShortestPaths) &&  (dis[k] + disRev[k]) == dis[end])){
            all.insert(k);
        }
    }
    bool first = true;
    for(ll a: all){
        if(!first)cout << " ";
        cout << a;
        first = false;
    }
    //dbg(all);


}

