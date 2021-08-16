#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first

#ifdef DIRK
#include "/Users/dirk/development/algorithms/templates/debug.h"
#endif

using namespace std;
typedef long long ll;

struct compare {
    bool operator()(const pair<ll,ll>& p1, const pair<ll,ll>& p2) const {
        if(p1.first == p2.first) {
            return p1.second > p2.second;
        }
        return p1.first > p2.first;
    }
};


const bool cmp(const pair<ll,ll>& p1, const pair<ll,ll>& p2) {
    if(p1.second == p2.second) {
        return p1.first > p2.first;
    }
    return p1.second < p2.second;
}

void solve() {
    ll n;
    cin >> n;
    vector<pair<ll,ll>> v(n);
    for(auto& i : v) {
        cin >> i.first >> i.second;
    }

    // first dsc, second dsc
    multiset<pair<ll,ll>, compare> s;

    // second asc, first dsc
    sort(v.begin(),v.end(),cmp); // todo check:

    // We know all inserted before us have a lower or same second val
    for(auto i : v) {
        // what happens: same second, and then ascending first
        // Remove smaller element from s if possible
        const pair<ll,ll> test = {i.first-1,i.second-1};
        auto it = s.lower_bound(make_pair(i.first-1,i.second-1)); // either <first-1 || <=first-1 and <=second-1 
        if(it != s.end()) {
            //cout << test.first << " " << test.second << " " << it->first << " " << it->second << endl;
            pair<ll,ll> p = *it;
            //if(p.first < i.first && p.second < i.second) {
            s.erase(it);
            //}
        }
        s.insert(i);
        //dbg(s);
    }

    cout << s.size() << endl;
}

int main() {

    ios_base::sync_with_stdio(false);cin.tie(NULL); 

    #ifdef DIRK 
    freopen("/Users/dirk/development/algorithms/competitve/input.txt", "r", stdin); 
    freopen("/Users/dirk/development/algorithms/competitve/error.txt", "w", stderr); 
    freopen("/Users/dirk/development/algorithms/competitve/output.txt", "w", stdout); 
    #endif 

    ll cases;
    cin >> cases;
    while(cases--) {
        solve();
    }
}
