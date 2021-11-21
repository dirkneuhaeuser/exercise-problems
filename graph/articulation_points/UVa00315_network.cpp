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

enum {VISITED=-2, UNVISITED=-1};

int nodeIdx, rootChildren, root;
vector<int> dfsNum, dfsLow, articulationPoints, parents, vis;

void dfsArticulationPoints(int curIdx, vector<set<int>> &al){
    vis[curIdx] = VISITED;
    dfsNum[curIdx] = nodeIdx++;
    dfsLow[curIdx] = dfsNum[curIdx];

    for(int next: al[curIdx]){
        if (vis[next] == UNVISITED){
            parents[next] = curIdx;
            if(curIdx == root) rootChildren++;

            dfsArticulationPoints(next, al);

            if(dfsNum[curIdx] <= dfsLow[next]){
                articulationPoints[curIdx] = true;
            }
            dfsLow[curIdx] = min(dfsLow[curIdx], dfsLow[next]);
        }else{
            if(parents[curIdx] != next){
                //very important we only want the exact number here. Otherwise we might make it too low(even still is a articulationPoint)
                dfsLow[curIdx] = min(dfsLow[curIdx], dfsNum[next]); 
            }
        }
    }


}



void solve() 
{
    int n;
    while(cin >> n && n){
        vector<set<int>> al(n, set<int>());
        string line;getline(cin, line);
        while(getline(cin, line)){
            if(line == "0") break;
            stringstream ss; ss<<line;
            int start; ss >> start;
            --start;
            int end;
            while(ss >> end){
                --end;
                al[start].insert(end);
                al[end].insert(start);;
            }
        }
        nodeIdx = 0;
        dfsNum.assign(n, 0);
        dfsLow.assign(n, INF);
        parents.assign(n, -1);
        articulationPoints.assign(n, false);
        vis.assign(n, UNVISITED);
        for(int i=0; i<n; ++i){
            if(vis[i] == UNVISITED){
                rootChildren = 0;
                root = i;
                dfsArticulationPoints(i, al);
                articulationPoints[i]=rootChildren>1; // override, as for the root this algorithm doesn't work (children of root can never have lower dfsLow.
            }
        }

        int numberOfFlags = accumulate(articulationPoints.begin(), articulationPoints.end(), 0);
        cout << numberOfFlags << endl;
    }
}

