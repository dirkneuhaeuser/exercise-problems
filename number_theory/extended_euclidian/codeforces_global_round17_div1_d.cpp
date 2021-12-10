#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
const int MOD = 1000000007;
ll smod(ll a, ll m=MOD){return((a%m) +m) %m;}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m=MOD){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
ll modPow(ll b, ll p, ll m=MOD){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*smod(b, m),m);return a;}
ll invFerm(ll a, ll m=MOD){ return modPow(a, m-2,m);}
ll modAdd(ll a, ll b, ll m=MOD){return smod(a+b, m);};
ll modSub(ll a, ll b, ll m=MOD){return smod(a-b, m);};
ll modMul(ll a, ll b, ll m=MOD){return smod(a*b, m);};
ll modDiv(ll a, ll b, ll m=MOD){return smod(a*invEea(a, m), m);};
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
    // Combinatorics, Number Theory, Multivariate Diophantine Equationse
    // First Question: When is subsecence [k1, k2, ,... kn] good? (We consider it a subsequnece and therefore take all ki)
    //
    // With the first k1, we can get the following consecutive numbers:
    // 0, 1, 2,...(k1-1) and we can shift that to the right or left as we want and therefore we can add a multiple of ki to it.
    // Hence let x be any integer, then only with k1 we can have: k1*x + k1(k1-1)/2
    //
    // Including all the other ki, we therefore have SUM(ki*x_i + ki*(ki-1)/2) which needs to be 0;
    // Thus: SUM(k_i*x_i) = SUM(k_i*(k_i-1)/2)
    //
    // Basically, this is a multivariate diophantine equation sum(k_i * x_i) = c.
    // This only has a solution if GCD(k_1,..k_n) divides c.
    //
    // Lets define 
    //      c:= SUM(k_i*(k_i-1)/2)
    //      g:= GCD(k1,...kn)
    //
    // 1. Case g is odd
    //    Case 1.1: k_i is odd -> g | c
    //      When k_i is odd -> (k_i -1) is even. Theefore (k_i-1)/2 is ok and as g|k_i -> g|c
    //    Case 1.2 k_i is even -> g | c
    //      As k_i is even, k_i = 2 * X = g * Y -> k_i = g * 2 * Z -> Thus g|k_i
    //
    // 2. Case g is even
    //    When g is even, we might have a problem: (k_i -1) is odd and cannot divide 2. Therefore we need to see if g | (k_i/2).
    //    Therefore let l be the maxPower of 2 within g and X the corresponding conplement. So we can write g = 2^l*X.
    //    Now we know: Some k_i have exactly l as the highes power of 2, and some k_i have even more.
    //    When we have more: Perfect, k_i/2 still accounts for 2^l (and whatever is included in g). So when dividing c by g -> no remainder
    //    When we have only l: k_i/2 has only 2^(l-1) -> When dividing c by g, we have a remainder of 2^(l-1)*(k_i-1). 
    //    The right part is not important, as we don't get it to 0 anyway (at least not by dividing it by g).
    //    Thus, we can only have even numbers of k_i's which have exactly l as highes power of 2
    //
    // To solve the overall problem:
    // Add: 
    // (A1.) All subsequences which have at least one odd k_i;
    // (A2.) Go over all l - maxPowers of a potential GCD and multipy
    //          1. All subsequences which have even elements of these k_i's which maxPower == l. 
    //                  Lets donate X the amount of such k_i's. Then there are 2^(x-1) of such subsequences.
    //          2. All subsequences which contains only elements which higher maxPower >l
    int n; cin >> n;
    vector<int> nums(n);
    FOR(i, n){
        cin >> nums[i];
    }
    vi cnt(31, 0);
    FOR(i, n){
        int powerOfTwo=0;
        while(nums[i]>0 && ((nums[i]&1) == 0)){
            nums[i] = nums[i]/2;
            powerOfTwo++;
        }
        cnt[powerOfTwo]++;
    }
    int sum = n;
    ll ret = 0;
    // A1) odd
    ret = modAdd(ret, modSub(modPow(2, n), modPow(2, n-cnt[0]))); // All subsequences - all subsequences with only even elements
    sum -=cnt[0];
    // Now A2)
    for(int i=1; i<=30; ++i){
        if(cnt[i]){
            sum-=cnt[i];
            ll toAdd = modMul(modPow(2, cnt[i]-1)-1, modPow(2, sum));
            ret = modAdd(ret, toAdd);
        }
    }

    cout << ret;



}

