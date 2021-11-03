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

const int maxn = 10001;

bitset<maxn> p;
void sieve(){
    p.set();
    p[1] = false;
    for(int i=2; i*i<maxn; ++i){
        if(p[i]){
            for(int j=i*i; j<maxn; j+=i){
                p[j]=0;
            }
        }
    }
}
bool isPrime(int num){
    return p[num];
}


void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/output.txt", "w", stdout); 
    #endif 
    
    sieve();
    solve();

    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    // Unweigted SSSDSP: Level bfs
    // Major Problem: the bfs works on the 1D number, but to know which other number is adjacent to it, we need to recunstruct the Prime Spiral 
    // and alongside a mapping from number to coordinates and coordintes to number
    map<pii, int> coord2num;
    vector<pii> num2coord{{0, 0},{0, 0}};
    coord2num[{0, 0}] = 1;
    int num = 2;
    int steps = 0;
    int curI = 0, curJ = 0;
    while(num <= 10000){
        for(int i=0; i<4 && num <= 10000; ++i){
            if((i%2)==0)steps++;
            for(int j=0; j<steps && num <= 10000; ++j){
                if(i == 0)curJ++;
                if(i == 1)curI--;
                if(i == 2)curJ--;
                if(i == 3)curI++;
                pii c{curI, curJ};
                coord2num[c] = num++;
                num2coord.push_back(c);
            }
        }
    }
    int x, y; 
    vector<pii> dir{{1,0}, {-1, 0}, {0, 1}, {0, -1}};
    int cnt = 1;
    while(cin >> x >> y){
        cout << "Case " << cnt++ << ": ";
        pii c1 = num2coord[x];
        pii c2 = num2coord[y];
        int shortestPath = 0;
        vector<int> seen(maxn, false);
        vector<int> q{x};
        seen[x] = true;
        bool poss = false;
        while(q.size()){
            vector<int> nq;
            for(int cur: q){
                if(cur == y){
                    poss = true;
                    cout << shortestPath;
                    break;
                }
                auto [i, j] = num2coord[cur];
                for(auto [di, dj]: dir){
                    int nextI = i+di;
                    int nextJ = j+dj;
                    pii next{nextI, nextJ};
                    if(coord2num.count(next)){
                        int nextNum = coord2num[next];
                        if(seen[nextNum]==false){
                            seen[nextNum] = true;
                            if(isPrime(nextNum)) continue;
                            nq.push_back(nextNum);
                        }
                    }
                }
            }
            shortestPath++;
            if(poss) break;
            q = nq;
        }
        if(!poss){
            cout << "impossible";
        }
        cout << endl;
    }


}

