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

vector<vector<int>> bincofs(9, vector<int>(9, 1));

// combinations of putting r elements in  k bins
// total number of combinations: ((r+k-1)Cr)
vector<vector<int>> combBins(int k, int r){
    vector<vector<int>> combinations;
    if(r==0) return combinations; //edge case
    vector<int> bins(k,0);  
    bins[0] = r;
    while (true){ 
        combinations.push_back(bins);
        int i=0;
        for (; bins[i] == 0; i++); // Look for smallest value
        if (i == k-1) break; // Done
        bins[i+1]++; // Increase value of one die with smallest value by one
        bins[0] = bins[i]-1; // Turn others into ones
        if (i > 0){
            bins[i] = 0;
        }
    }
    return combinations;
}
//int r = 8; // the number of dices
//int k = 6; // each dice could fall onto 1...6
//vector<vector<int>> ret = combBins(k, r); //[[8, 0, 0, 0, 0, 0], [7, 1, 0, 0, 0, 0], ...]


vector<vector<vector<int>>> outcomes;
vector<ll> facs = {1}; // factorials





void solve(); 
int main() 
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/competitve/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/competitve/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/competitve/output.txt", "w", stdout); 
    #endif 

    for(ll i =1; i <= 13; ++i){
        facs.push_back(facs.back()*i);
    }

    for(int i=1; i<9; ++i){
        vector<vector<int>> o = combBins(6, i); // combinations putting i elements in 6 bins
        int bc1 = 6 + i - 1;
        ll poss = facs[bc1]/facs[bc1 - i] / facs[i];
        outcomes.push_back(o);
    }

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
int n;
vector<vector<vector<ld>>> dp;

ld dpRec(int mask, int totalSum, int dicesLeft){
    if(dp[mask][totalSum][dicesLeft]!=-1) return dp[mask][totalSum][dicesLeft];
    if((mask & (1<<5))){
        if(totalSum >= n) return dp[mask][totalSum][dicesLeft] = 1;
    }
    if(dicesLeft == 0) return 0;
    ld ret = 0;
    // calculate all ((6+dicesLeft - 1) C dicesLeft) outcomes
    for(vector<int> o: outcomes[dicesLeft-1]){
        ld maxE =0;
        ll weightFactor = facs[dicesLeft];
        for(int i =0; i<o.size(); ++i){
            weightFactor /= facs[o[i]];
            if(o[i] == 0 || (mask & (1<<i)) != 0) continue;
            if(i==5){
                maxE = max(maxE, dpRec(mask^(1<<i), totalSum + i*o[i], dicesLeft - o[i]));
            }else{
                maxE = max(maxE, dpRec(mask^(1<<i), totalSum + (i+1)*o[i], dicesLeft - o[i]));
            }
        }
        ret += maxE* weightFactor;
    }
    ld prob = ret/powl(6.0, dicesLeft);
    return dp[mask][totalSum][dicesLeft] = prob;
}
void solve() 
{
    // note, bottom-up would not be feasible as it would calculate also for elements which might never really be used
    while(cin >>n){
        int mask = 1<<6;
        int totalSum = 5*8;
        dp = vector<vector<vector<ld>>>(mask,vector<vector<ld>>(totalSum + 1, vector<ld>(9, -1)));
        cout << setprecision(6) << fixed<< dpRec(0, 0, 8) << endl;
    }

}

