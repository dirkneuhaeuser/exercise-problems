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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

vector<pii> combine(const vector<pii> &a, const vector<pii> &b){
    vector<pii> ret;
    int ptB = 0;
    if(b.size() == 0) return a;
    if(a.size() == 0) return b;
    int i =0;
    int last = a[i].second;
    int first = a[i].first;
    
    while(i<a.size()){
        if(a[i].first > last){
            if(first != -1 && last != -1){
                ret.push_back({first, last});
            }
            last = a[i].second;
            first = a[i].first;
        }else{
            last = max(last, a[i].second);
        }
        while(ptB < b.size() && b[ptB].first <= last){
            if(b[ptB].second < first){ // b is before current
                ret.push_back(b[ptB]);
                ptB++;
            }else if(b[ptB].second > last){ // b only starts in current
                first = min(first, b[ptB].first);
                last = b[ptB].second;
                ptB++;
            }else{
                first = min(first, b[ptB].first);
                ptB++;
            }
        }
        i++;
    }
    if(last != -1 && first != -1){
        ret.push_back({first, last});
    }
    if(ptB < b.size()){
        ret.insert(ret.end(), b.begin()+ptB, b.end());
    }
    return ret;
}

vector<pii> intersection(const vector<pii> &a, const vector<pii> &b){
    vector<pii> ret;
    int i = 0, j = 0;
    while(j < b.size() && i < a.size()){
        int f = a[i].first;
        int s = a[i].second;
        if(b[j].first >= f && b[j].second <= s){ // completly covered by a
            ret.push_back(b[j]);
            j++;
        }else if(b[j].first >= f && b[j].first <= s &&b[j].second > s){  // only starts in a
            ret.push_back({b[j].first, s});
            i++;
        }else if(b[j].first < f && b[j].second >= f && b[j].second <= s){ // only ends in a
            ret.push_back({f, b[j].second});
            j++;
        }else if(b[j].first <= f && b[j].second >= s){ // covers a completely
            ret.push_back(a[i]);
            i++;
        }else if(b[j].second < f){
            j++;
        }else if(b[j].first > s){
            i++;
        }
    }
    return ret;
}

vector<pii> onlyCoveredByB(vector<pii> &a, vector<pii> &b){
    vector<pii> ret;
    int i = 0, j = 0;
    int bStart = -1;
    while(j < b.size() && i < a.size()){
        int bf = bStart > b[j].first? bStart:b[j].first;
        int bs = b[j].second;
        int af = a[i].first;
        int as = a[i].second;
        if(bf < af && bs >= af && bs <= as){ // b ends in a
            ret.push_back({bf, af-1});
            j++;
        }else if(bf < af && bs < af){ // b ends before a
            ret.push_back({bf, bs});
            j++;
        }else if(bf < af && bs > as){ // b covers a
            ret.push_back({bf, af-1});
            bStart = as+1;
            i++;
        }else if(bf >= af && bs >= af && bs <= as){ // b covered by a;
            j++;
        }else if(bf >= af && bs > as){ // b starts in a;
            bStart = af+1;
            i++;
        }else if(bf > as){
            i++;
        }
    }
    if(j<b.size()){
        int bf = bStart > b[j].first?bStart:b[j].first;
        ret.push_back({bf, b[j].second});
        j++;
    }
    ret.insert(ret.end(), b.begin()+j, b.end());
    return ret;

}

vector<pii> newKeys(vector<pii> &a, pii &b){
    vector<pii> nb{b};
    vector<pii> inters = onlyCoveredByB(a, nb);
    return inters;
}

vector<bool> endReachable;
void dfs(int cur, vector<vector<int>> &ALR){
    endReachable[cur] = 1;
    for(int next: ALR[cur]){
        if(endReachable[next] != 1){
            dfs(next, ALR);
        }
    }
}


vector<vector<pii>> visited; // n -> visited pii
queue<int> q;
set<int> inQ;
vector<vector<pii>> pending;

void bfs(int start, vector<vector<tuple<int, int, int>>> &AL){
    vector<pii> windows{make_pair(1, 1000000000)};
    pending[start] = windows;
    q.push(start);
    while(q.size()){
        int cur = q.front(); q.pop();
        inQ.erase(cur);
        vector<pii> window = pending[cur];
        if(window.size() == 0){
            return;
        }
        visited[cur] = combine(visited[cur], window); //not sure
        for(auto [next, a, b]: AL[cur]){
            if(!endReachable[next])continue;
            pii edgeWindow{a, b};
            vector<pii> edgeWindowV{edgeWindow};
            vector<pii> newKeys = intersection(window, edgeWindowV); // # O(window)
            vector<pii> onlyCoveredByNewKeys = onlyCoveredByB(visited[next], newKeys); // O(window + visited[next])
            if(onlyCoveredByNewKeys.size()){
                pending[next] = combine(pending[next], onlyCoveredByNewKeys);
                if(inQ.count(next) == 0){
                    inQ.insert(next);
                    q.push(next);
                }
            }
        }
    }
}


void solve() 
{
    // using a bfs -> tle in last 3 test cases :( Maybe meet in middle?
    int n, l, b; cin >> n >> l >> b;
    int s, d; cin >> s >> d;
    s--; d--;
    vector<vector<tuple<int, int, int>>> AL (n, vector<tuple<int, int, int>>());
    vector<vector<int>> ALR (n, vector<int>());
    FOR(j, l){
        int a, b, x, y; cin >> a >> b >> x >> y;
        a--; b--;
        tuple<int, int, int> t {b, x, y};
        AL[a].push_back(t);
        ALR[b].push_back(a);

    }
    visited.assign(n, vector<pii>());
    pending.assign(n, vector<pii>());
    endReachable.assign(n, false);
    dfs(d, ALR);

    bfs(s, AL);
    int ret = 0;
    for(int i=0; i<visited[d].size(); ++i){
        ret += visited[d][i].second - visited[d][i].first +1;
    }
    cout << ret;

}

