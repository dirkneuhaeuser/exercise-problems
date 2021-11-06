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

ld euclid(int ai, int aj, int bi, int bj){
    return powl(powl(abs((ld)bi-ai), (ld)2) + powl(abs((ld)bj-aj), (ld)2), 0.5);
}


void solve() 
{
    // Basic SSSDSP, but there are O(n^2) adjacent fields, but only 1000 potential fields -> Don't check all adjacent fields but all potential fields
    int stepE, stepF; cin >> stepE >> stepF;
    int n, m; cin >> n >> m;
    vector<vector<char>> grid (n, vector<char>(m, 'c'));
    vector<vector<int>> disE(n, vector<int>(m, INF));
    vector<vector<int>> disF(n, vector<int>(m, INF));
    queue<pii> qE, qF;
    vector<pii> toCheckE, toCheckF;
    int iG, jG;
    FOR(i, n){
        FOR(j, m){
            cin >> grid[i][j];
            if(grid[i][j] == 'S'){
                disE[i][j] = 0;
                disF[i][j] = 0;
                qE.push({i, j});
                qF.push({i, j});
            }else if(grid[i][j] != 'B'){
                toCheckE.push_back({i, j});
                toCheckF.push_back({i, j});
            }
            if(grid[i][j] == 'G'){
                iG = i;
                jG = j;
            }
        }
    }
    while(qE.size()){
        auto [i, j] = qE.front(); qE.pop();
        vector<pii> newCheck;
        for(auto [potI, potJ]: toCheckE){
            ld d = euclid(i, j, potI, potJ);
            if(d-0.000001 <= stepE){
                disE[potI][potJ]  = disE[i][j]+1;
                qE.push({potI, potJ});
            }else{
                newCheck.push_back({potI, potJ});
            }
        }
        toCheckE = newCheck;
    }
    while(qF.size()){
        auto [i, j] = qF.front(); qF.pop();
        vector<pii> newCheck;
        for(auto [potI, potJ]: toCheckF){
            if((potI == i && abs(potJ - j) <= stepF) || (potJ == j && abs(potI - i) <= stepF) ) {
                disF[potI][potJ]  = disF[i][j]+1;
                qF.push({potI, potJ});
            }else{
                newCheck.push_back({potI, potJ});
            }
        }
        toCheckF = newCheck;
    }
    if(disE[iG][jG] < disF[iG][jG]){
        cout << "GO FOR IT";
    }else if(disE[iG][jG] == disF[iG][jG] && disE[iG][jG] == INF){
        cout << "NO WAY";
    }else if(disE[iG][jG] == disF[iG][jG]){
        cout << "SUCCESS";
    }else if(disE[iG][jG] > disF[iG][jG]){
        cout << "NO CHANCE";
    }


}

