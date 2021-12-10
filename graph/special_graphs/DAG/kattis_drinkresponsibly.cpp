#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef pair<ld, ld> pdd;
typedef pair<int, ld> pid;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
#define FOR(i, n) for(int i=0; i<n; i++)
#ifdef DIRK
#include "/Users/dirk/development/algorithms/algorithms/templates/debug.h"
#endif
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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

bool isClose(ld a, ld b){
    return abs(a-b) < 0.001;
}


struct Drink{
    string name;
    ld units;
    ld size;
    int cost;
};
map<pid, bool> memo;

bool dp(int leftMoney, ld leftUnits, vector<Drink> &drinks){
    pid param = {leftMoney, leftUnits};
    auto it = memo.find(param);
    if(it != memo.end()) return it->second;
    if(leftMoney == 0 && isClose(leftUnits, 0)) return memo[param] = true;
    if(leftMoney < 0 && leftUnits < 0) return memo[param] = false;
    for(Drink drink: drinks){
        if(leftMoney >= drink.cost && leftUnits >= drink.units - 0.000001 && dp(leftMoney - drink.cost, leftUnits - drink.units, drinks)){
            return memo[param] = true;
        }
    }
    return memo[param] = false;
}

void reconstruct(int leftMoney, ld leftUnits, vector<Drink> &drinks, map<string, int> &sol){
    for(Drink drink: drinks){
        if(leftMoney >= drink.cost && leftUnits >= drink.units - 0.000001 && dp(leftMoney - drink.cost, leftUnits - drink.units, drinks)){
            sol[drink.name]++;
            return reconstruct(leftMoney-drink.cost, leftUnits - drink.units, drinks, sol);
        }
    }
}


void solve() 
{
    // problem: https://open.kattis.com/problems/drinkresponsibly 
    // about: basic dp problem. The difficulty here is rather that the states are doubles and we need to transfer them to int, such that the memo actually helps. Note, it is sufficient to just transsfer money to int.
    string money; cin >> money;
    money.erase(money.size() -3,1);
    int moneyInt = stoi(money);
    ld units; cin >> units;
    int n; cin >> n;

    vector<Drink> drinks;
    FOR(i, n){
        string name; cin >> name;
        Drink drink;
        drink.name = name;
        int perc;  cin >> perc;
        string size; cin >> size;
        if(size == "1/1"){
            drink.size = 1;
        }else if(size == "1/2"){
            drink.size = 0.5;
        }else{
            drink.size = (ld)1/3;
        }
        drink.units = drink.size * perc;
        string cost; cin >> cost;
        cost.erase(cost.size() -3,1);
        int costInt = stoi(cost);
        drink.cost = costInt;
        if(costInt == 0 && isClose(drink.units, 0)) continue;
        drinks.push_back(drink);
    }
    bool poss = dp(moneyInt, units, drinks);
    if(poss){
        map<string, int> sol;
        reconstruct(moneyInt, units, drinks, sol);
        for(auto [k, v]: sol){
            cout << k << " " << v << endl;
        }

    }else{
        cout << "IMPOSSIBLE";
    }

}

