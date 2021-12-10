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
    
    int t=1; 
    cin >> t;
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

int memoDP1[26];
int countDP(int cur, vector<set<int>> &AL){
    int &ans = memoDP1[cur];
    if(ans != -1) return ans;
    if(AL[cur].size() == 0) return ans = 1;
    int ret = 0;
    for(int next: AL[cur]){
        ret += countDP(next, AL);
    }
    return ans = ret;
}

int query(int idxS, vector<set<int>> &AL, string &s){
    if(idxS >= s.size() - 1)return 0;
    int aIdx = s[idxS] - 'A';
    int nextIdx = s[idxS+1] - 'A';
    int ret = 0;
    for(int next: AL[aIdx]){
        if(next < nextIdx){
            ret+=countDP(next, AL);
        }
    }
    ret += query(idxS+1, AL, s);
    return ret;

}

void solve() 
{
    // Counting Path on DAG: DP. when no more adj node -> endpoint.
    int n, m; cin >> n >> m;
    vector<set<int>> AL(n);
    FOR(j, m){
        char a, b; cin >> a >> b;
        int ai = a-'A';
        int bi = b-'A';
        AL[ai].insert(bi);
    }
    int q; cin >> q;
    memset(memoDP1, -1, sizeof memoDP1);
    FOR(j, q){
        string s; cin >> s;
        int ans = query(0, AL, s);
        cout << s << ": ";
        cout << ans+1 << endl;
    }


}

