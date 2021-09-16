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

void dfsGetCost(int cur, int price, vector<vector<pii>> &al, vector<int> &dis){
    dis[cur] = price;
    for(int i=0; i<al[cur].size(); ++i){
        dfsGetCost(al[cur][i].first, price + al[cur][i].second, al, dis);
    }
}

int memo[100001];

int hasSubtreeFriend(int cur, vector<vector<pii>> &al, vector<int> &friends){
    int &ans = memo[cur];
    if(ans != -1)return ans;
    int pos = lower_bound(friends.begin(), friends.end(), cur) - friends.begin();
    if(pos != friends.size() && friends[pos] == cur) return ans = 1;
    for(int i=0; i<al[cur].size(); ++i){
        if(hasSubtreeFriend(al[cur][i].first, al, friends)) return ans = 1;
    }
    return ans = 0;
}

int dfsVisistFriend(int cur, vector<vector<pii>> &al, vector<int> &friends){
    int ans = 0;
    for(int i=0; i<al[cur].size(); ++i){
        if(hasSubtreeFriend(al[cur][i].first, al, friends)){
            ans += al[cur][i].second + dfsVisistFriend(al[cur][i].first, al, friends);
        }
    }
    return ans;
}





void solve() 
{
    // dfs problem. Before we go to a certain child and add the cost towards it, wee need to know wether there is indead a friend in this subtree.
    // As the hasSubtreeFriend function is maybe called often, we will memo it.
    int n, f; 
    while(cin >> n >> f){
        vector<vector<pii>> al(n, vector<pii>());
        FOR(i, n-1){
            int a, b, c;
            cin >> a >> b >> c;
            a--; b--;
            al[a].push_back({b, c});
        }
        vector<int> friends;
        FOR(i, f){
            int a; cin >> a;
            a--;
            friends.push_back(a);
        }
        sort(friends.begin(), friends.end());
        vector<int> distances(n);
        dfsGetCost(0, 0, al, distances);
        memset(memo, -1, sizeof memo);
        int ret = dfsVisistFriend(0, al, friends);
        int maxE = 0;
        FOR(i, friends.size()){
            maxE = max(maxE, distances[friends[i]]);
        }
        cout << ret - maxE << endl;
    }
}

