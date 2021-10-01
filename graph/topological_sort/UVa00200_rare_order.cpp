#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                          // ld up to  10*10^307
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

// building adjacency list
void buildingAdjacencyList(int startIdx, vector<set<int>> &al, vector<string> &words){
    for(int i=0; i<words.size(); ++i){
        if(words[i].size() <= startIdx) continue;
        char cur = words[i][startIdx];
        int curI = words[i][startIdx] - 'A';
        for(int j=i+1; j<words.size(); ++j){
            if(words[j].size() <= startIdx) continue;
            if(cur == words[j][startIdx]) continue;
            int nextI = words[j][startIdx] - 'A';
            al[curI].insert(nextI);
        }
    }
    // now put all which had the same character in this round into separate list;
    char cur = '!';
    vector<string> newWords;
    for(int i=0; i<words.size(); ++i){
        if(words[i].size() <= startIdx){
            if(newWords.size() > 1){
                buildingAdjacencyList(startIdx+1, al, newWords);
            }
            newWords = vector<string>();
        }else if(words[i][startIdx] == cur){
            newWords.push_back(words[i]);
        }else if(words[i][startIdx] != cur){
            if(newWords.size() > 1){
                buildingAdjacencyList(startIdx+1, al, newWords);
            }
            newWords = vector<string>();
            newWords.push_back(words[i]);
            cur = words[i][startIdx];
        }
    }
    // check if there is still sth in the list:
    if(newWords.size() > 1){
        buildingAdjacencyList(startIdx+1, al, newWords);
    }

}

enum {VISITED = -1, UNVISITED = -2};

void topSort(int curIdx, vector<int> &v, vector<set<int>> &al, vector<int> &order){
    v[curIdx] = VISITED;
    for(int next: al[curIdx]){
        if(v[next] == UNVISITED){
            topSort(next, v, al, order);
        }
    }
    order.push_back(curIdx);
}


void addToUsed(vector<bool> &used, string &word){
    FOR(i, word.size()){
        int charIdx = word[i] - 'A';
        used[charIdx] = true;
    }
}

void solve() 
{
    // more advanced topological sort problem. Convert the given list of words into a adjacency list and then use topological sort to find the order of the alphabet
    string word;
    while(cin >> word){
        vector<bool> used (26, false);
        addToUsed(used, word);
        vector<string> words{word};
        while(cin >> word){
            if(word != "#"){
                words.push_back(word);
                addToUsed(used, word);
            }else{
                break;
            }
        }
        
        vector<set<int>> al(26, set<int>()); // idx -> [idxs] means idx comes before each element in [idxs]
        buildingAdjacencyList(0, al, words);
        vector<int> inDegree(26, 0);

        FOR(i, 26){
            for(int after: al[i]){
                inDegree[after]++;
            }
        }
        int startIdx = -1;

        FOR(i, 26){
            if(used[i] && inDegree[i] == 0){
                startIdx = i;
            }
        }
        vector<int> visited(26, UNVISITED);
        vector<int> order;
        topSort(startIdx, visited, al, order);
        for(int i=order.size()-1; i>=0; --i){
            char let = order[i] + 'A';
            cout << let; 
        }
        cout << endl;
    }

}
