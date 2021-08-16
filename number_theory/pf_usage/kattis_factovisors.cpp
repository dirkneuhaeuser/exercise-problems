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

long long _sieve_size;
bitset<10000010> bs; // numbers up to 10^7, if bit set, number is prime
vector<long long> primes;
vector<long long> smallest_prime;

void sieve(long long limit){ // O(N * (1/2, 1/3, 1/5, .., 1/lastPrime)) = O(N * log log N)
    _sieve_size = limit + 1;
    smallest_prime = vector<long long>(_sieve_size, -1);
    bs.set(); // assume all numbers are prime
    bs[0] = bs[1] = 0;
    for(long long i = 2; i < _sieve_size; ++i) if(bs[i]) {
        smallest_prime[i]=i;
        for(long long j = i*i; j<_sieve_size; j+= i){
            bs[j] = 0;
            smallest_prime[j]=i;
        }
        primes.push_back(i);
    }
}

bool isPrime(long long N){ // works only for primes < sieve_size*sieve_size(10**14, if sieve_size = 10**7)
    if(N < _sieve_size){ return primes[N]; } // O(1) for small N < sieve_size
    for(int i =0; i<primes.size() && primes[i] * primes[i] <= N; i++){ // O(# primes) < O(Sqrt(N))
        if(N%primes[i] == 0){
            return false;
        }
    }
    return true; 
}
//sieve(10000000); // sieve of 10**7 is max -> else change bitset
//cout << isPrime(4398050705407) << endl; // big prime

// returns [2,2,2,2] for 16
vector<int> primeFactors(long long N){ // O(sqrt(N) * ln(sqrt(N))
    vector<int> factors;
    for(int i=0; i<(int)primes.size(); ++i){ // O(#primes) < O(sqrt(N))
        while(N%primes[i]==0){
            N /= primes[i];
            factors.push_back(primes[i]);
        }
    }
    if (N != 1) factors.push_back(N);
    return factors;
}
//sieve(10000007);
//vector<int> pf =primeFactors(142391208960); // [2, 2, 2,...2**10, 3**4 5, 7**4, 11, 13]

// get number of DIFFERENT pf for numbers [0,..N] (better than calling N times primeFactors())
vector<int> numDiffPFarr(long long N){ // O(N*log log N)
    vector<int> ret(N+1, 0);
    for(int i =2;i<= N;++i){
        if(ret[i]==0){
            for(int j=i; j<=N; j+=i){
                ret[j]++;
            }
        }
    }
    return ret;
}
//vector<int> pfs = numDiffPFarr(10); // [0, 0, 1, 1, 1, 1, 2, 1, 1, 1, 2]

// returns the number of different divisors of N 
int numDiv(long long N){ // O(sqrt(N) * ln(sqrt(N))
    // N falls down to is primefactors:
    // N = a**i * b**j * ... * c**k
    // you can take the first pf 0, 1, 2, .., or i times -> i+1 possibilities
    // ans = (i+1)*(j+1)*...*(k+1)
    int ans = 1;
    for(int i=0; i<(int)primes.size() && primes[i]*primes[i] <= N; ++i){
        int power = 0;
        while(N%primes[i]==0){
            N /= primes[i];
            power++;
        }
        ans *= (power + 1);
    }
    return (N!=1)?(2*ans):ans;
}
//sieve(10000007);
//int divs = numDiv(10); // divs=4, as divisors are [1, 2, 5, 10]

// returns the sum of all divisors of N
long long sumDiv(long long N){ // O(sqrt(N) * ln(sqrt(N))
    // if N has only one pf, e.g. N = a**i, the ans is a**0 + a**1 + a**2 +...+ a**i -> geometric sequence (a**i+1 - 1)/(a-1)
    // for different pf, multiply these results:
    long long ans = 1;
    for(int i=0; i< (int)primes.size() && primes[i] * primes[i] <= N; ++i){
        long long multiplier = 1;
        long long factor = 1;
        while(N % primes[i]==0){
            N /= primes[i];
            multiplier *= primes[i];
            factor += multiplier;
        }
        ans *= factor;
    }
    return N!=1?ans*(1 + N):ans;
}
//sieve(10000007);
//int sum = sumDiv(10); // sum=18, as divisors are [1, 2, 5, 10]

// returns the number of coprimes of N, which are smaller/equal than N
long long EulerPhi(long long N){  // O(sqrt(N) * ln(sqrt(N))
    // naive: check gcd of all N-1 numbers
    // better: euler-totient /w pf:N=a**i * b**j * ...* c**k  -> #coprimes(N) =  N*(1-1/a)*(1-1/b)*...*(1-1/c)
    long long ans = N;
    for(int i=0; (i<(int)primes.size()) && (primes[i]*primes[i]<=N) ;i++){
        if(N%primes[i]==0){
            ans -= ans/primes[i];
        }
        while(N%primes[i]==0){
            N /= primes[i];
        }
    }

    return (N != 1) ? ans-ans/N: ans;
}
//sieve(10000007);
//long long numberCoprimes = EulerPhi(10); // numberCoprimes=4, as [1, 3, 7, 9] have GCD(x, 10)==1


// returns for each number [0,..N] the # of coprimes
vector<int> EulerPhiArr(long long N){ // O(N loglogN)
    vector<int> ret(N+1, 0);
    for(int i=1; i<=N;i++) ret[i]=i;
    for(int i=2; i<=N;i++){
        if(ret[i]==i){ // i is prime
            for(int j=i;j<=N; j+=i){
                ret[j] = (ret[j]/i) * (i-1);
            }
        }
    }
    return ret;
}
//vector<int> euler = EulerPhiArr(10); // [0, 1, 1, 2, 2, 4, 2, 6, 4, 6, 4]


long long legendre(long long pf, long long n){
    // returns the support of the primefactor pf in n!
    // if a number m uses this pf with a higher power, then m does not divide n!
    long long support = 0;
    long long current = pf;
    while(pf <= n){
        support += floor(n/pf);
        pf *= current;
    }
    //dbg(support);
    return support;
}
// don't use sieve! as m might be very large: go pf from 2 up tp pf*pf <= m (or until tmp == 1), for each pf check its power in m and its support in n with legendre
// check afterwards if tmp > 1(temp itself is prime),



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
void solve(){
    ll n, m;
    while (scanf("%lld %lld", &n, &m) != EOF) {
        bool possible;
        if(m == 0){
            possible = false;
        }
        else if(m <= n){
            possible = true;
        }else{
            possible = true;
            ll pf = 2;
            ll tmp = m;
            while(possible && tmp != 1 && pf*pf <= m){
                ll cnt = 0;
                while(tmp % pf == 0){
                    cnt++;
                    tmp /= pf;
                }
                if(cnt && cnt > legendre(pf, n)){
                    possible = false;
                }
                pf++;
            }
            if(possible && tmp > 1){
                // tmp is prime it self
                possible = legendre(tmp, n)>=1;
            }

        }
        printf("%lld %s %lld!\n", m, possible ? "divides" : "does not divide", n);
    }

}

