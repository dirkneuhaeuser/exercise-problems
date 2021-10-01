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
    
    int t=1; 
    cin >> t;
    while(t--) 
    { 
        solve(); 
        if(t)cout<<"\n\n";    
        else cout <<"\n";
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

void backtrack(int curIdx, vector<bool>&usable, vector<set<int>> &al, vector<int> &inDegree, string& cur, int maxN, vector<string> &all){
    if(curIdx == maxN){
        all.push_back(cur);
    }
    FOR(i, 26){
        if(usable[i] && inDegree[i] == 0){
            usable[i] = 0;
            char thisChar = 'A' + i;
            cur[curIdx] = thisChar;
            for(int next: al[i]){
                inDegree[next]--;
            }
            backtrack(curIdx +1, usable, al, inDegree, cur, maxN, all);
            for(int next: al[i]){
                inDegree[next]++;
            }
            usable[i] = 1;
        }
    }
}

void solve() 
{
    // Backtracking. All possible alphabet orders given the contraints with backtracking. The topological order was controlled by indegree here, as it is more flexible 
    string line1;
    string line2;
    while(line1 == ""){
        getline(cin, line1);
    }
    getline(cin, line2);
    vector<set<int>> al(26, set<int>());
    vector<int> inDegree(26, 0);
    vector<bool> usable(26, 0);
    int n  = 0;
    FOR(i, line1.size()){
        if(line1[i] != ' '){
            n++;
            int charInt = line1[i]-'A';
            usable[charInt] = true;
        }
    }

    for(int i=0; i<line2.size(); i+=4){
        char first = line2[i];
        char snd = line2[i+2];
        int firstInt = first - 'A';
        int secondInt = snd - 'A';
        al[firstInt].insert(secondInt); // second after first;
        inDegree[secondInt]++;
    }

    string cur = string(n, ' ');
    vector<string> all;
    backtrack(0, usable, al, inDegree, cur, n, all);

    if(all.size() == 0){
        cout << "NO";
    }else{
        for(int i=0; i<all.size(); ++i){
            for(int j=0; j<all[i].size(); ++j){
                cout << all[i][j];
                if(j < all[i].size() - 1) cout << " ";
            }
            if(i < all.size() - 1) cout << endl;
        }

    }
}

