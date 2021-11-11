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
ll smod(ll a, ll m){return((a%m) +m) %m;}
ll modPow(ll b, ll p, ll m){if(p == 0){return 1;}ll a=modPow(b,p/2,m);a=smod(a*a,m);if(p&1)a=smod(a*smod(b, m),m);return a;}
ll invFerm(ll a, ll m){ return modPow(a, m-2,m);}
ll eea(ll a, ll n, ll &s, ll &t){ll xx = t = 0; ll yy = s = 1;while(n){ll q = a/n;ll u = n; n =a%n; a=u; u = xx; xx = s-q*xx; s = u;u = yy; yy = t-q*yy; t = u;}return a;}
ll invEea(ll b, ll m){ll s, t; ll d = eea(b, m, s, t); if(d!=1) return -1; return smod(s,m);}
const int MOD = 1000000007;
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
    
    int t=1; 
    cin >> t;
    while(t--) 
    { 
        solve(); 
        cout<<"\n";    
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 
int dijkstra(vector<pii> &bottles, int mliters){ // O(E * log(V))
    // Instead of PQ use a set to update nodes once you see a lower value. The complexity lower but in Big O still the same
    // DOES NOT WORK WITH NEGATIVE WEIGHT CYCLES
    int m = bottles.size();
    int ret =0;
    set<pii> pq;
    pii start = {0, 0};
    pq.emplace(start);
    while(pq.size()){
        auto [curStart, curEnd] = *pq.begin(); // intotal O(V * log(V))
        pq.erase(pq.begin());
        for(auto [minV, maxV]: bottles){
            int nextMin = curStart + minV;
            if(nextMin > mliters) continue;
            int nextMax = min(curEnd + maxV, mliters);
            if(nextMax == mliters) return mliters;
            pii newWindow = {nextMin, nextMax};
            auto it = pq.lower_bound(newWindow);
            auto itBelowCheck = it;
            while(itBelowCheck != pq.begin()){
                itBelowCheck--;
                pii prev = *itBelowCheck;
                if(prev.second >= newWindow.first){
                    newWindow.first = min(prev.first, newWindow.first);
                    newWindow.second = max(prev.second, newWindow.second);
                    itBelowCheck = pq.erase(itBelowCheck); // you can decrement a erased iterator
                }else{
                    break;
                }
            }
            auto itAfterCheck = pq.lower_bound(newWindow);
            if(itAfterCheck != pq.end()){
                itAfterCheck++;
                while(itAfterCheck != pq.end()){
                    pii after = *itAfterCheck;
                    if(after.first <= newWindow.second){
                        newWindow.first = min(after.first, newWindow.first);
                        newWindow.second = max(after.second, newWindow.second);
                        itAfterCheck = pq.erase(itAfterCheck);
                    }else{
                        break;
                    }
                }
            }
            pii oldWindow = {curStart, curEnd};
            if(newWindow != oldWindow){
                ret = max(ret, newWindow.second);
                pq.insert(newWindow);
            }
        }
    }
    return ret;
}





void solve() 
{
    // Subset-Sum/Knapsack with reducing the search-space
    // Alternative: PQ/Dijkstra with reducing the search-space (I dont feel it is fitting here, but in CP4 its recommended as weighted shortest path.
    // However, I think it is faster, as we just compute selected/needed elements and do not go over all elements like in knapsack)
    //
    // Main way to reduce the search space:
    // Consider only one bottle with minCap and maxCap, then it will cover the this space: [minCap, maxCap], [2*minCap, 2*maxCap], ... [i*minCap, i*maxCap],...
    // At one point we will have: i*maxCap >= (i+1)*minCap, and so there is no space more inbetween. Fix this i, lets call it maxBottles.
    // Now we know for sure, that we can reduce any mili-liter query > maxBottles*maxCap to 0.
    //
    // Learnings:
    // -if empty container -> begin and end equal
    // -else: end iterator points right to the last element, while begin iterator points to the first element
    // -when erasing elements by using the iterator, it always returns the next valid iterator and only this can be used. The previous once cannot be increased/decreased
    int liters, m; cin >> liters >> m;
    vector<pii> bottles;
    int mLiters = liters*1000;
    ll limit = INF;
    FOR(i, m){
        int a, b;cin >> a >> b;
        bottles.push_back({a, b});
        ll div = (b-a);
        if(div == 0) continue;
        limit = min(limit, (ll)b*a/div);
    }
    if(mLiters>limit){
        cout << 0;
        return;
    }
    int possible = dijkstra(bottles, mLiters);
    cout << mLiters-possible;

}

