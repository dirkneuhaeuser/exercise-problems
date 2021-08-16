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
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*smod(b, m),m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
int MOD;

//int mat_n = 2;

struct Matrix {
    vector<vector<ll>> mat;
    int mat_n;
    //ll mat[mat_n][mat_n];
    Matrix(int s):mat(s, vector<ll>(s,0)), mat_n(s){};
};

// DP speed up with matrix multiplication
Matrix matMul(Matrix a, Matrix b){
    //cout << MOD << endl;
    int mat_n = a.mat_n;
    Matrix ret(mat_n);
    //memset(ret.mat, 0, sizeof ret.mat);
    for(int i=0; i<mat_n; ++i){
        for(int k=0; k<mat_n; ++k){
            if(a.mat[i][k]==0) continue;
            for(int j = 0; j<mat_n; ++j){
                ret.mat[i][j] += smod(a.mat[i][k] , MOD) * smod(b.mat[k][j] , MOD);
                ret.mat[i][j] = smod(ret.mat[i][j] , MOD);
            }
        }
    }
    return ret;
}

Matrix modPowMat(Matrix base, ll pot){ // O(log p) iterative version 
    int mat_n = base.mat_n;
    Matrix ret(mat_n);
    //memset(ret.mat, 0, sizeof ret.mat);
    for(int i=0; i<mat_n; ++i){
        ret.mat[i][i] = 1;
    }
    while(pot){
        if(pot&1) ret = matMul(ret, base);
        base = matMul(base, base);
        pot >>= 1;
        //cout << pot << " " <<  MOD << endl;
        //dbg(ret.mat);
    }
    return ret;
}

// STEPS:
// 1. CHANGE MOD
// 2. SET UP TRANSITION MATRIX A (with recurrence equations)
// 3. SET UP INITIAL VECTOR y_0
// 4. Calculate: (A^t) * y_0 = y_t

// IMPORTANT: 
// Important: y_{t+1} is one step ahead of y_t and both have the same order 


// 1. EXAMPLE (RECURRSION EQUATION)
// (MOD)-fibonacci in O(2*log(i)), where i is the ith fib number:
// [1, 1][1, 0] * [fib(n+1), fib(n)] = [fib(n+2), fib(n+1)]
        
//Matrix A(2);
//A.mat[0][0] = 1;
//A.mat[0][1] = 1;
//A.mat[1][0] = 1;
//A.mat[1][1] = 0;
//
//Matrix ret = modPowMat(A, n);
//cout << ret.mat[0][1] << endl;  //the n-th fib number, modulo MOD in O(log n)


// 2. EXAMPLE (RECURRSION EQUATION)
// x_t = a0 + a1*x_{t-1} + a2*x_{t-2} + ... + an * x_{t-n}
// A:= [[1,0,0], [a0, a1, a2], [0, 1,0]
// y_0 = [1, x_1, x_0]
// => A^t = [1, x_t, x_{t-1}]
// Attention: only power the matrix, if t > degree


// 3. EXAMPLE (# Paths of Length L)
// The number of ways from a to b in an undirected graph of Length L
// matrix[i][j]:= number of ways to get from j to i (IMPORTANT: COL 2 ROW)
// Matrix ret = modPowMat(trans, L);
// cout << ret.mat[end][start] << endl;


// 4. EXAMPLE (AD-Hoc)
// Calculate a^n + b^n from 
// p := a + b
// q := a * b
//
// x_n := a^n + b^n 
// => playing around:
// xn = p * x_{n-1} - q * x_{n-2}
//
// Ax = b
// [[p, -q],[1, 0]]  *  [x_{n-1}, x_{n-2}] =  [x_n, x_{n-1}]


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
    //cin >> t;
    //int count = 1;
    while(t--) 
    { 
        //cout<<"Case #" << count++ << ": ";
        solve(); 
        //cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    ll deg;
    cin >> deg;
    Matrix trans(deg+1);
    trans.mat[0][0] = 1;
    for(int i=0; i<=deg; ++i){
        cin >> trans.mat[1][i];
    }

    for(int i=2; i<=deg; ++i){
        trans.mat[i][i-1] = 1;
    }
    vector<ll> x(deg+1);
    x[0] = 1;
    FOR(i, deg){
        cin >> x[deg-i];
    }

    int queries; cin >> queries;
    FOR(i, queries){
        ll t; cin >> t >> MOD;
        if(t<deg){
            // requested t is so low, we know this answer already: no need for any calcultions
            cout << x[deg-t] % MOD << endl;
            continue;
        }

        ll ans = 0;
        t -=(deg -1);
        // for higher t, calculate calcualte matrix^(diff), where diff := t - (deg - 1)
        Matrix ret = modPowMat(trans, t);
        FOR(k, deg+1){
            ans += smod((smod(ret.mat[1][k] , MOD )  * smod(x[k] ,MOD)) , MOD);
            ans = smod(ans, MOD);
        }
        cout << ans << endl;
    }








}

