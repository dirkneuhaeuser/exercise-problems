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

// lab1 first
int kahnLab1First(vector<int> inDegree, queue<int> lab1, queue<int> lab2, vector<vector<int>> &AL, vector<int> &labs){
    int ans = 0;
    int seen = 0;
    int n = labs.size();
    while((lab1.size() && lab2.size()) || n > seen){
        while(lab1.size()){
            int t = lab1.front(); lab1.pop();
            seen++;
            for(int next: AL[t]){
                inDegree[next]--;
                if(inDegree[next] == 0){
                    if(labs[next] == 1){
                        lab1.push(next);
                    }else{
                        lab2.push(next);
                    }
                }
            }
        }
        if(seen < n) ans++;
        while(lab2.size()){
            int t = lab2.front(); lab2.pop();
            seen++;
            for(int next: AL[t]){
                inDegree[next]--;
                if(inDegree[next] == 0){
                    if(labs[next] == 1){
                        lab1.push(next);
                    }else{
                        lab2.push(next);
                    }
                }
            }
        }
        if(seen < n) ans++;
    }
    return ans;
}

// lab2 first
int kahnLab2First(vector<int> &inDegree, queue<int> &lab1, queue<int> &lab2, vector<vector<int>> &AL, vector<int> &labs){
    int ans = 0;
    int seen = 0;
    int n = labs.size();
    while((lab1.size() && lab2.size()) || n > seen){
        while(lab2.size()){
            int t = lab2.front(); lab2.pop();
            seen++;
            for(int next: AL[t]){
                inDegree[next]--;
                if(inDegree[next] == 0){
                    if(labs[next] == 1){
                        lab1.push(next);
                    }else{
                        lab2.push(next);
                    }
                }
            }
        }
        if(seen < n) ans++;
        while(lab1.size()){
            int t = lab1.front(); lab1.pop();
            seen++;
            for(int next: AL[t]){
                inDegree[next]--;
                if(inDegree[next] == 0){
                    if(labs[next] == 1){
                        lab1.push(next);
                    }else{
                        lab2.push(next);
                    }
                }
            }
        }
        if(seen < n) ans++;
    }
    return ans;
}


void solve() 
{
    // topological order with kahn-algorithm to give priority to the same lab and not transport. Not that, we have to run the algorithm two times.
    // Once, for the first lab to begin, and once for the second lab to begin.
    int n, m; cin >> n >> m;
    vector<int> labs(n);
    FOR(i, n){
        cin >> labs[i];
    }
    vector<vector<int>> AL(n, vector<int>());
    vector<int> inDegree(n, 0);

    FOR(i, m){
        int a, b; cin >> a >> b;
        a--; b--;
        AL[a].push_back(b);
        inDegree[b]++;
    }
    queue<int> lab1, lab2;
    FOR(i, n){
        if(inDegree[i] == 0){
            if(labs[i]==1){
                lab1.push(i);
            }else{
                lab2.push(i);
            }
        }
    }
    int lab1First = kahnLab1First(inDegree, lab1, lab2, AL, labs);
    int lab2First = kahnLab2First(inDegree, lab1, lab2, AL, labs);
    cout << min(lab1First, lab2First);

}

