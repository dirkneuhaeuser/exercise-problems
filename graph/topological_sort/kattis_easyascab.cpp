#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long, long> pll;
typedef pair<int, int> pii;
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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

// creates the AL[i] = [...j..] meaining in coms for j;
bool backtrack(vector<string> &words, vector<int> &subsetIdx, int start, vector<set<int>> &AL){
    if(subsetIdx.size() <= 1) return true;
    set<char> before;
    char last = '!';
    vector<int> curSubset;
    bool seenAlpha = false;
    for(int i: subsetIdx){
        if(start < words[i].size()){
            seenAlpha = true;
            if(words[i][start] != last){
                if(curSubset.size()>0){
                    if(!backtrack(words, curSubset, start + 1, AL)) return false;
                }
                curSubset = vector<int>();
            }
            for(char prev: before){
                int pInt = prev - 'a';
                int curInt = words[i][start] - 'a';
                if(pInt != curInt){
                    AL[pInt].insert(curInt);
                }
            }
            last = words[i][start]; 
            before.insert(words[i][start]);
            curSubset.push_back(i);
        }else if(seenAlpha){
            return false;
        }

    }
    if(curSubset.size()){
        if(!backtrack(words, curSubset, start + 1, AL)) return false;
    }
    return true;
}


enum {UNVISITED=-1, VISITED=-2, EXPLORED=-3};
vector<int> visited;

bool hasCycle(int cur, vector<set<int>> &AL){
    visited[cur] = EXPLORED;
    for(int next: AL[cur]){
        if(visited[next] == EXPLORED){
            return true;
        }
        if(visited[next] == UNVISITED && hasCycle(next, AL)){
            return true;
        }
    }
    visited[cur] = VISITED;
    return false;
}



void solve() 
{
    // Topologic Sorting with some pitfalls:
    // 1. detect improper orderings like, when a shorter prefix words is after the longer word (eg. aaaba is before aaab)  -> impossible
    // 2. use backtrack to generate the AL[i] = j, meaning the char i comes for char j
    // 3. detect cycles in the AL -> impossible
    // 4. Apply modified topological sort, if at any point there are more than one indegree == 0 -> ambigous
    char maxA; cin >> maxA;
    int n; cin >> n;
    int alphLen = maxA - 'a' + 1;
    vector<set<int>> AL(alphLen, set<int>());
    vector<string> words;
    FOR(i, n){
        string word; cin >> word;
        words.push_back(word);
    }

    // generating the AL
    vector<int> subset;
    FOR(i, words.size()) subset.push_back(i);
    bool consistent = backtrack(words, subset, 0, AL);
    if(!consistent){
        cout << "IMPOSSIBLE";
        return;
    }

    // checking if the graph has a cycle -> There are conflicting order, so order is impossible
    visited.assign(alphLen, UNVISITED);
    FOR(i, alphLen){
        if(visited[i] == UNVISITED){
            if(hasCycle(i, AL)){
                cout <<"IMPOSSIBLE" << endl;
                return;
            }
        }
    }
    
    // reconstruct the topological order 
    vector<int> inDegree(alphLen, 0);
    FOR(i, AL.size()){
        for(int next: AL[i]){
            inDegree[next]++;
        }
    }

    queue<int> q;
    FOR(i, alphLen){
        if(inDegree[i] == 0){
            q.push(i);
        }
    }

    vector<int> order;
    while(q.size()>0){
        if(q.size() > 1){ // when there are more then one way to go -> ambigious. This also checks the case if the graph has 2 or more ssc.
            cout << "AMBIGUOUS" << endl;
            return;
        }
        int cur = q.front(); q.pop();
        order.push_back(cur);
        for(int next: AL[cur]){
            inDegree[next]--;
            if(inDegree[next] == 0){
                q.push(next);
            }
        }
    }
    FOR(i, order.size()){
        char cur = order[i] + 'a';
        cout << cur;
        
    }



}

