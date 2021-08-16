#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 

// 2**6 =  64
// 2**8 =  256
// 2**10 = 1,024
// 2**15 = 32,768
// 2**20 = 1,048,576
// 2**25 = 33,554,432
// 2**30 = 1,073,741,824
// 2**32 = 4,294,967,296

// int up to  2*10^9 (2^31-1)
// ll up to   9*10^18 (2^63 -1)
// ull up to 18*10^18 (2^64-1)/

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

const int MOD = 1000000007;


// max number FFFFF  FFFFF = 16**10 - 1
// to check if prime:you need primes up to sqrt(16**10) = 16**5 = 1,048,576 
const int s = 1048577;
vector<int>primes;
bitset<s> p;
void sieve(){
    p.set();
    for(ll i = 2; i<s; ++i){
        if(p[i]){
            primes.push_back(i);
            for(ll j=i*i; j<s; j+=i){
                p[j]=0;
            }
        }
    }
}

vector<ll> convert(string s){
    // 2 base

    int n = s.size();
    vector<ll>ret;
    ll ans =0;
    FOR(i, s.size()){
        if(s[i] != '1' && s[i]!= '0'){
            goto base8;
        }
    }
    ret.push_back(stoll(s, NULL, 2));
    base8:
    FOR(i, s.size()){
        if((int)(s[i]-'0') > 7 ){
            goto base10;
        }
    }
    ret.push_back(stoll(s, NULL, 8));
    base10:
    FOR(i, s.size()){
        if((int)(s[i]-'0') > 9 ){
            goto base16;
        }
    }
    ret.push_back(stoll(s));
    base16:
    ret.push_back(stoll(s, NULL, 16));
    return ret;

}

bool isPrime(ll x){
    for(int i=0; i<primes.size() && primes[i]*primes[i]<=x; ++i ){
        if(x%primes[i]==0) return false;
    }
    return true;
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
    sieve();
    
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
void reduce(int& top, int& bot) {
    if(top == 0) {
        bot = 1;
        return;
    }

    int gcd = __gcd(top, bot);
    top /= gcd;
    bot /= gcd;

}
void solve() 
{
    int ret=0;
    string a; cin >> a;
    vector<ll> con = convert(a);
    for(ll num:con){
        if(num!=0 && num!= 1 && isPrime(num)){
            ret++;
        }
    }
    int b=con.size();
    reduce(ret, b);
    cout << ret << "/" << b;

}

