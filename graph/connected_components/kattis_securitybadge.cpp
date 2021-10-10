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


void solve() 
{
    // using apsp (TLE);
    int n, l, b; cin >> n >> l >> b;
    int s, d; cin >> s >> d;
    s--; d--;
    vector<vector<vector<pii>>> AM (n, vector<vector<pii>>(n, vector<pii>()));
    FOR(j, l){
        int a, b, x, y; cin >> a >> b >> x >> y;
        a--; b--;
        pii t{x, y};
        vector<pii> newE{t};
        AM[a][b] = combine(AM[a][b], newE);
    }
    for(int k=0; k<n; ++k){
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                AM[i][j] = combine(AM[i][j], intersection(AM[i][k], AM[k][j]));
            }
        }
    }
    int ret = 0;
    for(int i=0; i<AM[s][d].size(); ++i){
        ret += AM[s][d][i].second - AM[s][d][i].first +1;
    }
    cout << ret;

}

