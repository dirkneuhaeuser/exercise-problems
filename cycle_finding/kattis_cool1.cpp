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
vector<vector<bool>> grid;
int nC;
string commands;
pii f(pii cur, int &idx){
    int i = cur.first, j = cur.second;
    char command = commands[idx];
    idx = (idx + 1) % nC;
    //cout << idx << " " << i << " " << j << endl;
    if(command == '<'){
        if(grid[i][j-1]) return {i, j-1};
        else return {i, j};
    }else if(command == '>'){
        if(grid[i][j+1]) return {i, j+1};
        else return {i, j};
    }else if(command == '^'){
        if(grid[i-1][j]) return {i-1, j};
        else return {i, j};
    }else{
        if(grid[i+1][j]) return {i+1, j};
        else return {i, j};
    } 

}
int countFreq(string &pat, string &txt)
{
    int M = pat.length();
    int N = txt.length();
    int res = 0;
   
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++)
    {
        /* For current index i, check for
           pattern match */
        int j;
        for (j = 0; j < M; j++)
            if (txt[i+j] != pat[j])
                break;
  
        // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        if (j == M) 
        {
           res++;
           j = 0;
        }
    }
    return res;
}
void solve() 
{
    // Note: this porgramm doesn't work, if you get the bug, tell me. :P
    int n; cin>> n;
    cin >> commands;
    nC = commands.size();
    grid = vector<vector<bool>>(n, vector<bool>(n, false));
    pair<int, int> cur;
    FOR(i, n){
        FOR(j, n){
            char c; cin >> c;
            if(c =='R'){
                cur = {i, j};
                grid[i][j] =true;
            }
            if(c == '.'){
                grid[i][j] =true;
            }
        }
    }
    //dbg(cur);
    int idxT =0, idxH=0;
    pii t = f(cur, idxT);
    pii h = f(cur, idxH);
    h = f(h, idxH);
    while( t != h || idxT != idxH){
        t = f(t, idxT);
        //dbg(t);
        h = f(h, idxH);
        h = f(h, idxH);
    }
    //cout << " qydewy" <<endl;
    // here check if stuck
    pii meet = t;
    pii check = t;
    for(int i=0; i<nC; ++i){
        int newI = (idxT + i) % nC;
        check = f(check, newI);
        if(check != meet){
            goto notStuck;
        }
    }
    cout << 1;
    return;

    notStuck:
    t = cur;
    int mu = 0;
    idxT = 0;
    while( t != h || idxT != idxH){
        mu++;
        t = f(t, idxT);
        h = f(h, idxH);
    }
    dbg(t);
    // now the cycle is within the en directins
    string commands1 = commands.substr(0, idxT);
    string commands2 = commands.substr(idxT);
    commands = commands2+commands1;
    dbg(commands);
    pii start = t;
    pii prev;
    string newCommands;
    for(int i =0; i<commands.size(); ++i){
        prev = t;
        int idx = i;
        t = f(t, idx);
        if(t != prev){
            newCommands += commands[i];
        }else{
            //dbg(t);
            //dbg(commands[i]);
        }
    }
    commands =newCommands;
    //dbg(commands);
    for(int i =2; i<=commands.size()/2; ++i){
        if(commands.size() % i != 0) continue;
        string pat = commands.substr(0,i);
        for(int j =i; j<commands.size(); j+= i){
            if(commands.substr(j, i) != pat ){
                goto next;
            }
        }
        cout << i << endl;
        return;
        next: 
        ;
    }
    //dbg(commands);
    cout << commands.size();

    
    



}

