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

vector<ull> facs(2,1);


void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/competitve/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/competitve/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/competitve/output.txt", "w", stdout); 
    #endif 
    for(int i =2; i<=20; ++i){
        facs.push_back(facs.back()*i);
    }
    
    int t=1; 
    cin >> t;
    int count = 1;
    while(t--) 
    { 
        cout<<"Case " << count++ << ": ";
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
void solve() 
{
    // idea: use faculties to determine current char, but as prefix is not listed in current suffix, you need to adjust the order
    string s;
    ull k;
    cin >> s >> k;
    k--;
    int n = s.size();
    vector<int> alphOrder(26, 22);
    for(int i=0;i<n;++i){
        ull d = facs[n-1-i];
        ull order = k/d;
        ull adj_order = order;
        vector<int> orderCheck = alphOrder;
        int level = 20;

        // adjusting the order: while there are already characters lower in the order (in prefix) we need to ajdust for that
        while(level){
            for(int i=0; i<orderCheck.size(); ++i){
                if(orderCheck[i] <= adj_order){
                    adj_order++;
                    orderCheck[i] = 20;
                }
            }
            level--;
        }
        alphOrder[s[i]-'a'] = (int)adj_order;
        k-= order * (facs[n-1-i]);
    }
    for(int i=0; i<n; ++i){
        for(int j=0; j<26; ++j){
            if(alphOrder[j]==i){
                cout << (char)('a' + j);
            }
        }
    }


}

