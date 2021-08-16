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

typedef complex<double> cd;
const double PI = acos(-1.0);

//int reverseBit(int num, int log2n){
//    int ret = 0;
//    for(int i=0;i<log2n;++i){
//        if(num & (1 << i)) ret |= (1 << (log2n-1-i));
//    }
//    return ret;
//}
//
//// Fast Fourier Transformation
//void FFT(vector<cd> &A){ // O(n log(n)) 
//    // Given A, a vector of coefficents, FFT will evaluate the polynomial at n different positions in place
//    //
//    // Main Idea (D&C): A(x) = A_0(x**2) + x*A_1(x**2), where A_0 are all the even indicies of A, and A_1 all the odds
//    // A is always halved, at each iteration, we want to get A.size() evaluation. 
//    // Fast way: Use the nth-root, as the the square of the n-th root of unity can complety be reduced to the the n/2-root of unity
//    // 
//    // In other words, it will calculate y in W*a = y
//    // W is the matrix of (kth element from the nth root of unity) x (it exponential, from 0 to (n-1))
//    //
//    // w^k = the kth element from nth root of unity = exp(i*2*PI*k/n)
//    //
//    // W = w^0 w^0 ... w^0
//    //     w^0 w^-1    w^-(n-1)
//    //     w^0 w^-2    w^-2(n-1)
//    //     ...
//    //     w^0 w^-(n-1)    w^-(n-1)(n-1)
//    int n=1;
//    int log2n=0;
//    while(n<A.size()){
//        n <<= 1;
//        log2n++;
//    }
//    A.resize(n);
//    // sorting forst even than odd over and over again is equal to bit-reversal-order
//    for (int k=0; k < A.size(); ++k ){
//        if (k < reverseBit(k , log2n) ){
//            swap(A[k], A[reverseBit(k, log2n)]);
//        }
//    }
//    const complex<double> J(0, 1);
//    for (int s = 1; s <= log2n; ++s) {
//        int m = 1 << s; // 2 power s
//        int m2 = m >> 1; // m2 = m/2 -1
//        cd w(1, 0);
//  
//        // principle root of nth root of unity. (exp(i*2*PI/n))
//        cd wm = exp(J * (PI / m2)); 
//        for (int j = 0; j < m2; ++j) {
//            for (int k = j; k < n; k += m) {
//                cd t = w * A[k + m2]; 
//                cd u = A[k];
//                A[k] = u + t; 
//                A[k + m2] = u - t; 
//            }
//            w *= wm;
//        }
//    }
//}


void FFT(vector<cd> &x){
    // This FFT is faster than the other, taken from https://rosettacode.org/wiki/Fast_Fourier_transform
    // DFT
    unsigned int N = x.size(), k = N, n;
    double thetaT = 3.14159265358979323846264338328L / N;
    cd phiT = cd(cos(thetaT), -sin(thetaT)), T;
    while (k > 1)
    {
        n = k;
        k >>= 1;
        phiT = phiT * phiT;
        T = 1.0L;
        for (unsigned int l = 0; l < k; l++)
        {
            for (unsigned int a = l; a < N; a += n)
            {
                unsigned int b = a + k;
                cd t = x[a] - x[b];
                x[a] += x[b];
                x[b] = t * T;
            }
            T *= phiT;
        }
    }
    // Decimate
    unsigned int m = (unsigned int)log2(N);
    for (unsigned int a = 0; a < N; a++)
    {
        unsigned int b = a;
        // Reverse bits
        b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
        b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
        b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
        b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
        b = ((b >> 16) | (b << 16)) >> (32 - m);
        if (b > a)
        {
            cd t = x[a];
            x[a] = x[b];
            x[b] = t;
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

// Fast point-value multiplication: FOR FREQUENCIES AND INTEGER POLYNOMIAL CONVOLUTION
vector<ll> multiply(vector<ll> p1, vector<ll> p2){ // O(n*log(n))
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
        ret.push_back(round(a.real()));  // rounding might be changed. When dealing with frequencies/integer-values this sould be ok!
    }
    ret.resize(p1.size() + p2.size() -1);
    return ret;
}
//vector<int> a{1,2,3}; // 1 + 2x + 3x^2
//vector<int> b{1,2,3}; // 1 + 2x + 3x^2
//vector<int> ret = multiply(a, b); // 1 + 4x + 10x^2 + 12x^3 + 9x^4



vector<ll> stringMatchingMultiply(vector<cd> p1, vector<cd> p2){
    // VERY SLIGHT MODIFCATION: Changes in the way we round the real values and different arguments
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
        ret.push_back((ll)(a.real() + .000000001)); // string matching works with doubles exp(i*2*PI*k/n) where we only want to carefully round up: 2.9999999999999999999991 should be 3, but not 2.72..
    }
    ret.resize(p1.size() + p2.size() -1);
    return ret;
}

vector<ll> stringMatching(string a, string query){
    // Only goof for checking if the COMPLETE query string is in a
    // Unlike KMP (better runtime), FFT is more versitile.
    // Idea: map literals to number (a->0, b->1,...) and for string a calculate exp(i*2*PI*k/n) where k is the characters value.
    // for string query calculuate exp(-i*2*PI*k/n) with minus. So when the same characters get matched the cancel out each other and lead to 1, anything else will be less than 1
    // Wildcards(here: '?')will automatically be set to 0 and don't effect the result
    // To see where the string matches,you have to find query.size() - #wildcards in the result array
    // As we want actualluy an alignment and not convolution, we need to REVERSE the query before
    const complex<double> im(0, 1);
    int n = 26; // 26 literals in alphabet
    vector<cd>  aTransformed, queryTransformed;
    FOR(i, a.size()){
        int literalValue = a[i] - 'a'; // a-> 0, b-> 1 ,...
        cd wm = exp(im * (2 * PI * literalValue / n)); 
        aTransformed.push_back(wm);
    }
    FOR(i, query.size()){
        if(query[i] == '?'){
            queryTransformed.push_back(0);
        }else{
            int literalValue = query[i] - 'a'; // a-> 0, b-> 1 ,...
            cd wm = exp(im * (-2 * PI * literalValue / n)); 
            queryTransformed.push_back(wm);
        }
    }
    reverse(queryTransformed.begin(), queryTransformed.end());
    return stringMatchingMultiply(aTransformed, queryTransformed);
}

//string str = "abcdefghijk";
//string pattern = "efg";
//vector<ll> matching = stringMatching(str, pattern); // [0, 0, 1, 2, 2, 2, 3, 2, 2, 2, 1, 0, 0] at position 6 str[6] = g the "efg" is matched
//string pattern2 = "e?g";
//vector<ll> matching = stringMatching(str, pattern2); // [0, 0, 1, 1, 1, 1, 2, 1, 1, 1, 1, 0, 0] at position 6 str[6] = g the "e?g" is matched


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
    int a1, a2, a3, a4;
    int b1, b2, b3, b4;
    cin >> a1 >> a2 >> a3 >> a4 >> b1 >> b2 >> b3 >> b4;
    int nom1 =0, denom1 = 0, nom2=0, denom2=0;



    // absolutley not neccessary n*log n solution with fft
    vector<ll>f1(101, 0), f2(101, 0), f3(101, 0), f4(101, 0);
    for(int i=a1; i<= a2; ++i){
        f1[i]++;
    }
    for(int i=a3; i<= a4; ++i){
        f2[i]++;
    }
    for(int i=b1; i<= b2; ++i){
        f3[i]++;
    }
    for(int i=b3; i<= b4; ++i){
        f4[i]++;
    }
    vector<ll> ret1 = multiply(f1,f2); 
    vector<ll> ret2 = multiply(f3, f4);
    FOR(i, ret1.size()){
        nom1 += i*ret1[i];
        denom1 += ret1[i];
    }
    FOR(i, ret2.size()){
        nom2 += i*ret2[i];
        denom2 += ret2[i];
    }


    // n^2 solution:
    //for(int i=a1; i<= a2; ++i){
    //    for(int j=a3; j<= a4; ++j){
    //        denom1++;
    //        nom1 += i+j;
    //    }
    //}
    //for(int i=b1; i<= b2; ++i){
    //    for(int j=b3; j<= b4; ++j){
    //        denom2++;
    //        nom2 += i+j;
    //    }
    //}
    ld e1 = (double) nom1 / (double) denom1;
    ld e2 = (double) nom2 / (double) denom2;
    if(e1 > e2){
        cout << "Gunnar";
    }else if(e1 < e2){
        cout << "Emma";
    }else{
        cout << "Tie";
    }


}

