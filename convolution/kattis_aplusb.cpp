#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first

// int up to 2*10^9 (2^31-1)
#define ll long long  // up to 9*10^18 (2^63 -1)
#define ull unsigned long long // up to 18*10^18 (2^64-1)
#define ld long double
#define FOR(i, n) for(int i=0; i<n; i++)
#define FORS(i, n) for(; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/templates/debug.h"
#endif

const int MOD = 1000000007;
using namespace std; 
void solve(); 

typedef complex<double> cd;
const double PI = acos(-1.0);

int reverseBit(int num, int log2n){
    int ret = 0;
    for(int i=0;i<log2n;++i){
        if(num & (1 << i)) ret |= (1 << (log2n-1-i));
    }
    return ret;
}

// Fast Fourier Transformation
void FFT(vector<cd> &A){ // O(n log(n)) 
    // Given A, a vector of coefficents, FFT will evaluate the polynomial at n different positions in place
    //
    // Main Idea (D&C): A(x) = A_0(x**2) + x*A_1(x**2), where A_0 are all the even indicies of A, and A_1 all the odds
    // A is always halved, at each iteration, we want to get A.size() evaluation. 
    // Fast way: Use the nth-root, as the the square of the n-th root of unity can complety be reduced to the the n/2-root of unity
    // 
    // In other words, it will calculate y in W*a = y
    // W is the matrix of (kth element from the nth root of unity) x (it exponential, from 0 to (n-1))
    //
    // w^k = the kth element from nth root of unity = exp(i*2*PI*k/n)
    //
    // W = w^0 w^0 ... w^0
    //     w^0 w^-1    w^-(n-1)
    //     w^0 w^-2    w^-2(n-1)
    //     ...
    //     w^0 w^-(n-1)    w^-(n-1)(n-1)
    int n=1;
    int log2n=0;
    while(n<A.size()){
        n <<= 1;
        log2n++;
    }
    A.resize(n);
    // sorting forst even than odd over and over again is equal to bit-reversal-order
    for (int k=0; k < A.size(); ++k ){
        if (k < reverseBit(k , log2n) ){
            swap(A[k], A[reverseBit(k, log2n)]);
        }
    }
    const complex<double> J(0, 1);
    for (int s = 1; s <= log2n; ++s) {
        int m = 1 << s; // 2 power s
        int m2 = m >> 1; // m2 = m/2 -1
        cd w(1, 0);
  
        // principle root of nth root of unity. (exp(i*2*PI/n))
        cd wm = exp(J * (PI / m2)); 
        for (int j = 0; j < m2; ++j) {
            for (int k = j; k < n; k += m) {
                cd t = w * A[k + m2]; 
                cd u = A[k];
                A[k] = u + t; 
                A[k + m2] = u - t; 
            }
            w *= wm;
        }
    }
}

// Inverse FFT
void IFFT(vector<cd> &Y){
    // FFT calcualtes n different points WA = Y, now reverse and calcualte W^-1*Y = A
    // So after fast multiplication we can go back from point-value-representation to coefficient representation
    // can be shown: W^-1_ij = 1/n (1/w_ij), in polar coordinates is that just scaling and conjugation
    // y_j * exp(-i*theta) = conj(conj(y_j) * exp(i*theta)) 
    // As exp(i*theta) is used also in FFT, we can use it here as well
    for(auto &p:Y)p=conj(p);
    FFT(Y);
    //for(auto &p:Y)p = conj(p); // conjugate here acutally not neccessary, as we only need real unitys in our problems
    for(auto &p:Y)p /= Y.size();
}

// Fast point-value multiplication
vector<ll> multiply(vector<ll> &p1, vector<ll> &p2){ // O(n*log(n))
    // pi = 3 + 4x^1 + 2x^2 -> [3, 4, 2]
    // in order to specify a degree m polynom, we need m+1 different data observations
    // new degree d = p1.size() + p2.size()- 1
    // 1. receive n point-value representation from FFT (resize each pi to length n>d - a power of two, as reverseBits needs it)
    // 2. fast multiply
    // 3. reverse back to coefficient representation
    int n = 1;
    while(n < p1.size() + p2.size() -1) n <<=1;
    vector<cd> A(p1.begin(), p1.end());
    vector<cd> B(p2.begin(), p2.end());
    A.resize(n);
    B.resize(n);
    FFT(A);
    FFT(B);
    vector<cd> mult(n);
    for(int i=0; i<n; ++i){
        mult[i] = A[i]*B[i];
    }
    IFFT(mult);
    vector<ll>ret;
    for(cd a: mult){
        ret.push_back(round(a.real()));
    }
    //cout << "size : " <<p1.size() + p2.size() -1 << endl;
    ret.resize(p1.size() + p2.size() -1);
    return ret;
}
//vector<int> a{1,2,3}; // 1 + 2x + 3x^2
//vector<int> b{1,2,3}; // 1 + 2x + 3x^2
//vector<int> ret = multiply(a, b); // 1 + 4x + 10x^2 + 12x^3 + 9x^4


int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/competitve/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/competitve/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/competitve/output.txt", "w", stdout); 
    #endif 
    
    int t=1; 
    while(t--) 
    { 
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    ll cnt0 = 0;
    int n;
    cin >> n;
    vector<ll>f(200008,0);
    vector<ll>nums;
    int offset = 50001;
    FOR(i,n){
        int num;
        cin >> num;
        nums.push_back(num+offset);
        if(num == 0){
            cnt0++;
        }
        f[num+offset]++;
    }

    vector<ll> f2 = f;
    vector<ll> ret = multiply(f, f2); // size:200003
    //dbg(ret);
    ll ans = 0;
    for(int num: nums){
        ret[num+num]--;
    }
    //dbg(ret);
    for(int num: nums){
            ans+= ret[num+offset];
        //cout << "i: " << i << "ans: " << ans << endl;
    }

    // take into account the number of times a number gets projected onto itself by 0 (a_i + 0 = a_i or 0 + a_i = a_i0
    ans -= (ll)2*cnt0*(n-1);

    cout << ans;



}

