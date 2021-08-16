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

//18,446,744,073,709,551,615
//9,827,655,926,262,173,984

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
    vector<ull> faqs(1,1);
    for(int i=1;i<=12; ++i){
        faqs.push_back(faqs.back()*i);
    }
    int n;
    while(cin >> n){
        if(n==0)break;
        vector<ull> nums;
        unordered_map<ull,ull>vals;
        for(int i=0;i<n;++i){
            ld num; cin >> num;
            nums.push_back(num);
            vals[num]++;
        }
        ull red = 1; // mulitnomial reduction if repeats
        for(auto kv: vals){
            red*=faqs[kv.second];
        }
        ull ret = 0;
        for(int j = 0; j<n; ++j){ // number
            ull dec = 1;
            ull bnum = nums[j];
            for(int i=0; i<n; ++i){//dec
                ret += dec*bnum;
                dec*=10;
            }
        }
        ull d = __gcd(faqs[n-1], red);
        // (n-1)! and the reduction red dont have to be int, its not possible to: faqs[n-1]/red as fractional digits ignored
        ret = ret *(faqs[n-1]/d)/(red/d);

        cout << ret << endl;


    }

}

