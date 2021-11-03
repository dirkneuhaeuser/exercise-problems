#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
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
void solve() 
{
    // Unweigted SSSDSP: basic level bfs
    // Note: In use vector for to save already computed values
    int current, code, b;
    int cnt = 1;
    while(cin >> current >> code >> b){
        if(current == 0 && code == 0 && b == 0)return;
        cout << "Case " << cnt++ <<": ";
        vector<int> nums;
        FOR(i,b){
            int num; cin>>num;
            nums.push_back(num);
        }
        vector<int> q{current};
        vector<bool> seen(10000, false);
        seen[current] = true;
        int times = 0;
        bool possible = false;
        while(q.size()){
            vector<int> nq;
            for(int c: q){
                if(c==code){
                    cout << times;
                    possible = true;
                    goto end;
                }
                for(int num: nums){
                    int next = c+num;
                    next = next % 10000;
                    if(seen[next] == false){
                        seen[next] = true;
                        nq.push_back(next);
                    }
                }
            }
            q = nq;
            times++;
        }
end:
        if(!possible){
            cout << "Permanently Locked";
        }
        cout << endl;

    }


}

