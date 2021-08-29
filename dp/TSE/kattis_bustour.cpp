#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
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

int LSOne(int num){
    return (num)&(-num);
}
int memoToStart[19][(1<<18)];
int memoToEnd[19][(1<<18)];

int dp(int start, int end, int mask, vector<vector<int>> &am){
    int &ans = (end ==0)? memoToStart[start][mask]:memoToEnd[start][mask];
    if(ans != -1){
        return ans;
    }
    if(mask == 0){
        return ans = am[start][end];
    }
    ans = INF;
    int m = mask;
    whilr(m){
        int v = LSOne(m);
        int next = __builtin_ctz(v)+1;
        ans = min(ans, am[start][next] + dp(next, end, mask^v, am));
        m ^= v;
    }
    return ans;
}

vector<int> dijkstra(int start, vector<vector<pii>> graph){ // O(E * log(V))
    // SSSP idea: Always take the next node with minimial distance
    // once taken a node with minimial distance, you can't correct it, as a detour over others will make it worse
    // graph is given like a vector of pii, where first is targetNode, and second is weight.
    priority_queue<pii> q;
    vector<int> distances(graph.size(), INF);
    priority_queue<pii, vector<pii>, ::greater<pii>> nodes;
    nodes.push({0, start});
    while(nodes.size()){
        pii node = nodes.top();
        nodes.pop(); // intotal O(V * log(V))
        int nodeIdx = node.second;
        if(distances[nodeIdx] < INF) continue; // you have that node already 
        int nodeDistance = node.first;
        distances[nodeIdx] = nodeDistance;
        for(int i = 0; i<graph[nodeIdx].size(); ++i){
            int adjNode = graph[nodeIdx][i].first;
            if(distances[adjNode] == INF){
                nodes.push({nodeDistance + graph[nodeIdx][i].second, adjNode}); // In total O(E * log(V))
            }
        }

    }
    return distances;
}



void solve() 
{
    // more suffisicated TSP. The first half of the hotels need to be also in the first half on way back.
    //
    // Try all combinations for n/2 hotels in the first half (on the way towards the destination); 18 choose 9  = 48K -> mask
    //
    // Now we need to split the round into 4 different paths: 
    // 1. First n/2 hotls on the way towards destination
    // 2. Second n/2 hotls on the way towards destination
    // 1. First n/2 hotls on return
    // 2. Second n/2 hotls on return
    //
    // NOTE: In order to use memo, the destination of the current path always needs to be same. Here the roads are bidrectional, so we structure the four paths in that way, that the 
    // destination is alywas either the start 0, or the destination n-1;
    //
    // NOTE: A good way to get permutations: use permutations of an 0-1 vector.
    //
    // NOTE: To get the full AM, we need to calculate APSP (I used several times dijsktra here, instead of floyed);
    //
     int n, m; 
    int count = 1;
    while(cin >> n >> m){
        vector<vector<int>> am;
        vector<vector<pii>> aj(n, vector<pii>());
        FOR(j, m){
            int a, b, c; cin >> a >> b >> c;
            aj[a].push_back({b, c});
            aj[b].push_back({a, c});
        }
        FOR(i, n){
            vector<int> dis = dijkstra(i, aj);
            am.push_back(dis);
        }
        int newN = n-2;
        vector<int> used(newN, 0);
        FOR(i, newN/2){
            used[i] = 1;
        }
        memset(memoToStart, -1, sizeof memoToStart);
        memset(memoToEnd, -1, sizeof memoToEnd);
        int minE = INF;
        do{
            int fstMask = 0, sndMask =0;
            FOR(i, used.size()){
                if(used[i] == 1){
                    fstMask ^= (1<<i);
                }else{
                    sndMask ^= (1<<i);
                }
            }
            FOR(i, newN){
                if(!sndMask & (1 << i)){
                    continue;
                }
                FOR(j, newN){
                    if(!sndMask & (1 << j)){
                        continue;
                    }
                    int ret1 = dp(i+1, 0, fstMask^(1<<i), am);
                    int ret2 = dp(i+1, n-1, sndMask^(1<<i), am);
                    int ret3 = dp(j+1, 0, sndMask^(1<<j), am);
                    int ret4 = dp(j+1, n-1, fstMask, am);
                    int ret = ret1+ret2+ret3+ret4;


                    if(ret < minE){
                        minE = min(ret, minE);
                    }
                }
            }

        }while (prev_permutation(used.begin(), used.end()));
        cout << "Case" << " " << count++ << ": " << minE << endl;
    }

}

