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
bool isCreeper(string s){
    if(s.size()<8)return false;
    if(s[0] =='5'){
        bool check1 = s.substr(s.size()-4) == "7777";
        bool check2 = s.substr(0, 4) == "5566";
        bool check4 = s.substr(4, s.size()-4-4) == string(s.size()-4-4, '6');
        return check1&&check2&&check4;
    }else if(s[0] == '1'){
        bool check1 = s.substr(s.size()-4) == "4444";
        bool check2 = s.substr(0, 4) == "1233";
        bool check4 = s.substr(4, s.size()-4-4) == string(s.size()-4-4, '3');
        return check1&&check2&&check4;
    }else{
        return false;
    }
}
string f(string s){
    string ret;
    int offset = 0;
    for(int i=0; i<s.size(); ++i){
        int a = s[i]-'0';
        int b = s[s.size() - 1 - i]-'0';
        //cout << s[i] << " " << a << " " << s[s.size() - 1 - i] << " " << b << endl;
        int ans = a + b + offset;
        int concat = ans%10;
        offset = ans/10;
        if(concat != 0){
            char concatChar = '0' + concat;
            ret +=  concatChar;
            //cout << concatChar << " " << concatChar <<endl;
        }
    }
    if(offset){
        char concatChar = '0' + offset;
        ret +=  concatChar;
    }

    sort(ret.begin(), ret.end());
    return ret;

}
void solve() 
{
    int cur, m;
    string start;
    cin >> cur >> m>> start;
    string t = start;
    unordered_set<string> alr;
    int idx = 1;
    while(idx < m && !isCreeper(t) && !alr.count(t)){
        alr.insert(t);
        t = f(t);
        //cout << t << endl;
        //dbg(alr);
        idx++;
    }
    if(alr.count(t)){
        cout << cur << " R " << idx;
    }else if(isCreeper(t)){
        cout << cur << " C " << idx;
    }else{
        cout << cur << " " <<  t;
    }

}

