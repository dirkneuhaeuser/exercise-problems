#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
#define FORS(i, n) for(; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/templates/debug.h"
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
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*b,m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
const int MOD = 1000000007;

int N;
vector<int> E[10];
//int l[10], r[10];
int visited[10], cookie;
vector<int> l(10, -1), r(10, -1);
int cnt_x[10], cnt_y[10];

int dfs(int node) {
	if(node == -1) return 1; // not been visited: use as match
	if(visited[node] == cookie) return 0; //alrady been visited, can't be used to match
	visited[node] = cookie;

	for(int i = 0; i < E[node].size(); ++i)
		if(dfs(l[E[node][i]])) {//for given x value (node) check if there is a y value
			l[E[node][i]] = node; // node is x value and E[node][i] is y value
			r[node] = E[node][i];
			return 1;
		}

	return 0;
}

void matching(void) {
    int m=0;
	for(int i = 1; i <= 10; ++i) {
		++cookie;
		m += dfs(i);
	}
    cout << "matching: " << m << endl;
}

void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/competitve/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/competitve/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/competitve/output.txt", "w", stdout); 
    #endif 
    
    int t=1; 
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{

	scanf("%d", &N);

	for(int i = 0; i < N; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		++cnt_x[x]; ++cnt_y[y];
		E[x].push_back(y);
	}

	//memset(l, -1, sizeof l);
	//memset(r, -1, sizeof r);

	matching();
    dbg(l);dbg(r);

	for(int i = 1; i <= 10; ++i) {
		if(cnt_x[i] > 0 && r[i] == -1){printf("Mirko\n"); return;} 
		if(cnt_y[i] > 0 && l[i] == -1){printf("Mirko\n"); return;}
    }



	printf("Slavko\n");

}

