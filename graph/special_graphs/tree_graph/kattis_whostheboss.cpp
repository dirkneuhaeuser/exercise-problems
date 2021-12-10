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
    
    //int t; cin >> t;
    //FOR(i, t)
        solve();

    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

vi cntSub;
int dfs(int cur, vector<vi> &sub){ // dp O(n)
    if(cntSub[cur] != -1) return cntSub[cur];
    int ret = sub[cur].size();
    for(int pre: sub[cur]){
        ret += dfs(pre, sub);
    }
    cntSub[cur] = ret;
    return ret;
}

struct P{
    int h, id;
    P(int _h,int _id):h(_h), id(_id){
    };

    friend bool operator <(const P& lhs, const P& rhs) //friend claim has to be here
    {
       return lhs.h<rhs.h;
    }
};

void solve() 
{
    // problem: https://open.kattis.com/problems/whostheboss
    // about: Ad-hoc problem. Sort by salary, now loop through the persons. Maintain a set for all persons without boss yet. Consider person i, now delete all elements in the set, which are smaller/equal (height), as these automatically have smaller salary (because of the sort). We can be greedy here, as we won't find any boss with a smaller salary (as now only even higher saleries will be processed). Save parent and subordient and finally do dfs/dp to get for one person all the subordients. Not the grahp is a tree, as a person can only have one boss (DAG -> dp);
    // salary O(10KK)
    // height O(2.5KK)
    // n O(100K)
    int n, q; cin >> n >> q;
    vi ids;
    vector<tiii> persons;
    cntSub.assign(1'000'000, -1);
    vi par(1'000'000, -1);
    vector<vi> sub(1'000'000);
    FOR(i, n){
        int id, salary, height;
        cin >> id >> salary >> height;
        ids.push_back(id);
        persons.push_back({salary, height, id});
    }
    sort(persons.begin(), persons.end()); // O(n log n)
    set<P> setHeightId; // only elements without parent
    for(auto [s, h, id]: persons){ // O(n log n)
        P newEntry(h, id);
        auto it = setHeightId.upper_bound(newEntry);
        while(it != setHeightId.begin()){
            it--;
            P prev = *it;
            sub[id].push_back(prev.id);
            par[prev.id] = id;
            it = setHeightId.erase(it);
        }
        setHeightId.insert(newEntry);
    }

    FOR(i, q){
        int id; cin >> id;
        int subs = dfs(id, sub);
        int boss = 0;
        if(par[id] != -1){
            boss = par[id];
        }
        cout << boss  << " " << subs << endl;
    }

}

