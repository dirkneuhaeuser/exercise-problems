#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 

// 2**6 =  64                           // 5!  = 120                        
// 2**8 =  256                          // 10! = 3,628,800
// 2**10 = 1,024                        // 12! = 479,001,600
// 2**15 = 32,768                       // 14! = 87,178,291,200
// 2**20 = 1,048,576                    // 16! = 20,922,789,888,000
// 2**25 = 33,554,432                   // 18! = 6,402,373,705,728,000
// 2**30 = 1,073,741,824                // 20! = 2,432,902,008,176,640,000
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


// testing:
//    set<int> quads;
//    for(int i =0; i<10000; ++i){
//        quads.insert(i*i);
//    }
//
//    for(int i =0; i<100; i+=2){
//        for(int q:quads){
//            if(quads.find(q+i) != quads.end()){
//                goto next;
//            }
//        }
//        cout << i  <<endl;
//        next:
//        ;
//    }

    // Note: this didn't get AC. Task is too unclear. Which number to print first, are numbers allowed to be the same? Also not a mod arithmetic task

    ll maxN = (1ll <<31) - 1;
    string line;
    while(getline(cin, line)){
        if(line.size()==0) break;
        stringstream ss; ss << line;
        int a, b;
        if(ss >> a >> b){
            if(a>b) swap(a,b);
            if(b<0) b=abs(b), a=abs(a);
            if(a<0){
                cout << (b+2)/4  + (a+2)/4;
            }else{
                a--;
                cout << (b+2)/4  - (a+2)/4  << endl;
            }
            continue;

        }else{
            bool zeroPossible = true;
            if(a<0){
                zeroPossible = true;
                a = abs(a);
            }
            // idea:
            // (a**2 - b**2) = (a+b)(a-b) = c*d -> use that instead, so that we only have to go till sqrt(n);
            // however you still have to maintain relatations: c+d = 2a and c-d = 2b
            for(int i=1; i<= sqrt(a); i++){
                if(a%i) continue;
                int c = i;
                int d = a/c;
                if(d>c) swap(d,c);
                if((c+d)%2==0 && (c-d)%2==0){
                    int maxE = max((c+d)/2, (c-d)/2);
                    int minE = min((c+d)/2, (c-d)/2);
                    cout << minE << " " << maxE << endl;
                    goto next;
                }
            }
            if(zeroPossible){
                if((int)sqrt(a)*(int)sqrt(a)==a){
                    cout << 0 << " " << sqrt(a) << endl;
                    goto next;
                }
            }

            if(a&1) cout << "Spinster Number." << endl;
            else cout << "Bachelor Number." << endl;
            next:
            ;
        }
    }

}

