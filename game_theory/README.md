# Game Theory

Solvable with Backtracking or DP. Sometimes there is no need to compute all states: use mathematical trick (only consider reduced cases - other will automatically reduce to them anyway)
If you need all states: bottom up from final state
if you can skip many cases: top down/ backtracking (without memo)


Often: 
	1. check if opponent loses
	2. observe how the opponent uses the rest

Bottom-Up (check if opponent loses):
```
for(int mask=65534; mask>=0; mask--){ //O(65524 * 48 pins)
    for(int pin: pins){
        if(dp[mask^pin] == 0){ // if you have the possibilty that next guy (opponent loses), then you take it and win
            dp[mask] = 1;
        }
    }
}
```

Top-Down (check if opponent loses)
```
bool bt(ll n, ll m){
    if(n<m) swap(n,m);
    if(m == 0) return false;
    ll times = n/m;
    if(times>1){
        if(!bt(n-(times - 1) * m, m)){
            return true;
        }
    }
    if(!bt(n-times * m , m)){
        return true;
    }
    return false;
}
```

Note, that you could also use the player information, but this is usually not as smooth




Bottum-Up (observe how the opponent uses the rest)
```
for(int dis = 1;dis<n; ++dis){
    for(int i = 0;i<2*n; ++i){
        int j = i+dis;
        f[i][j] = max(f[i][i] - f[i+1][j], f[j][j] - f[i][j-1]);
    }
}
```

Top-Down (observe how the opponent uses the rest)
Hier mit Backtrack
```
ll dp(vector<ll> nums){
    ll ret = NINF;
    for(int j=0; j<15; ++j){
        if(nums[j] ==  0) continue;
        for(int i =0 ; i<g[j].size(); ++i){
            ll f = g[j][i].first;
            ll s = g[j][i].second;
            ll mult = nums[j] * nums[f];
            swap(nums[j], nums[s]);
            ll cache = nums[f];
            nums[f] = 0;
            ret = max(ret, mult - dp(nums));
            swap(nums[j], nums[s]);
            nums[f] = cache;
        }
    }
    return ret
}
```



