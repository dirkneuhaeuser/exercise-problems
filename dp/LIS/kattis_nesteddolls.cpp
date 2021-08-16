#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<long, long> pll;
typedef pair<int, int> pii;
#define FOR(i, n) for(int i=0; i<n; i++)
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
const int MOD = 1000000007;
const int INF = 1<<30;


struct compare {
    bool operator()(const pair<ll,ll>& p1, const pair<ll,ll>& p2) const { // second > *second || second==*second && first >= first
        if(p1.second == p2.second) {
            return p1.first < p2.first;
        }
        return p1.second < p2.second;
    }
};

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
void solve() 
{
    // idea: Problem, we don't want to know the LIS, but the max. numbter of threads (or dolls, wenn as many smaller ones are in bigger ones).
    //
    // In LIS, we binary search for the first bigger or equal one to substitute and try to expand our LIS when possible (if new eleement becomes head)
    // Here, we binary search to the biggest thread end, which is still strictly smaller than the current doll to eat. No overwide an array but delete/insert from multiset
    // Completely different, but the way you the first dimension is sorted ASC and the second DSC remains
    // 
    // Consider each element in the multiset as a new thread, when first processing smaller dolls, you can delete small doll-thread if you have a current bigger doll, as you can fit the smaller in the bigger one. However, you still insert a new thread (for the bigger one).
    int m; cin >> m;
    vector<pii> dolls;
    FOR(i, m){
        int w, h; cin >> w >> h;
        dolls.push_back({w, h});
    }
    sort(dolls.begin(), dolls.end(), [](auto &a, auto &b){ // first Dimension ASC, second DSC
            return ((a.first < b.first) || ((a.first == b.first) && (a.second > b.second)));
                    });

    multiset<pii, compare> ms; // ASC in Second, ASC in First
    FOR(i, m){ // first dimension is always <= than the first dimension of already checked
        pii current = {dolls[i].first -1, dolls[i].second -1}; // find strictly smaller dolls-thread, to 'eat'
        
        // Moreover, we let the multiset look at the second dimension first, because, we know that all previous processed elements are already smaller in first dimension.
        // If they are in first dimension equal, we process first the ones which are bigger in second dimension, such they cannnot eat each other
        // When subtracting 1 from each dimension of the query, we find strictly smaller dolls in both dimensions.



        auto it = ms.upper_bound(current); // the first which is bigger than strictly smaller
        if(it != ms.begin()){ 
            advance(it, -1); // the last strictly smaller
            ms.erase(it);
        }
        ms.insert({dolls[i].first, dolls[i].second});
    }
    cout << ms.size();


}

