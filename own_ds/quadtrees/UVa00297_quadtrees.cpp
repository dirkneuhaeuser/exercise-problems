#include"bits/stdc++.h" // using "" instead of <>, so it will search locally for the precompiled version first
using namespace std; 
                                                // int up to 2*10^9 (2^31-1)
typedef long long ll;                           // ll up to 9*10^18 (2^63 -1)
typedef unsigned long long ull;                 // ull up to 18*10^18 (2^64-1)
typedef long double ld;                         // ld up to  10*10^307
typedef pair<long long, long long> pll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<ll> vi;
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

struct Node{
    char val;
    int ans;
    Node* upLeft;
    Node* upRight;
    Node* downLeft;
    Node* downRight;
    Node(){
        ans = 0;
        upLeft = nullptr;
        upRight = nullptr;
        downLeft = nullptr;
        downRight = nullptr;
    };
};

Node* build(string &s, int &curIdx, int factor){
    if(curIdx >= s.size()) return nullptr;
    Node* nn = new Node();
    nn->val = s[curIdx];
    if(s[curIdx] == 'p'){
        nn->upRight = build(s, ++curIdx, factor/4);
        if(nn->upRight != nullptr)nn->ans += nn->upRight->ans;
        nn->upLeft = build(s, ++curIdx, factor/4);
        if(nn->upLeft != nullptr)nn->ans += nn->upLeft->ans;
        nn->downLeft = build(s, ++curIdx, factor/4);
        if(nn->downLeft != nullptr)nn->ans += nn->downLeft->ans;
        nn->downRight = build(s, ++curIdx, factor/4);
        if(nn->downRight != nullptr)nn->ans += nn->downRight->ans;
    }else{
        if(s[curIdx] == 'f'){
            nn->ans = factor;
        }
    }
    return nn;
}

void del(Node* cur){
    if(cur == nullptr){
        return;
    }
    del(cur->upLeft);
    del(cur->upRight);
    del(cur->downLeft);
    del(cur->downRight);
    delete(cur);
}

Node* merge(Node* n1, Node* n2){
    if(n1 == nullptr) return n2;
    if(n2 == nullptr) return n1;
    if(n1->val == 'f' || n2->val == 'e') {
        del(n2);
        return n1;
    }
    if(n2->val == 'f' || n1->val == 'e') {
        del(n1);

        return n2;
    }
    // both are p
    Node* ret = new Node();
    ret->ans =0;
    ret->upRight = merge(n1->upRight, n2->upRight);
    if(ret->upRight != nullptr)ret->ans += ret->upRight->ans;
    ret->upLeft = merge(n1->upLeft, n2->upLeft);
    if(ret->upLeft != nullptr)ret->ans += ret->upLeft->ans;
    ret->downRight = merge(n1->downRight, n2->downRight);
    if(ret->downRight != nullptr)ret->ans += ret->downRight->ans;
    ret->downLeft = merge(n1->downLeft, n2->downLeft);
    if(ret->downLeft != nullptr)ret->ans += ret->downLeft->ans;
    delete(n1);
    delete(n2);
    return ret;
}


void solve() 
{
    // problem: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=233
    // about: quadtree problem. Note normally 2D ST is preferred, as with Master-theorem, we can proof, if N = n*n, the number of cells in our grid, then for query and update functions we would have recursive term as T(m) = 4*T(m/4) + t(m) , where t(m) = O(1), this means our crit_value = m^(log_4(4)) = m and thus t(m) also O(crit_value) -> crit dominates -> query and update are O(m).
    // implementations with querys and updates: https://codeforces.com/blog/entry/57498
    string s1, s2; cin >> s1 >> s2;
    int curIdx1=0, curIdx2=0;
    Node * quadtree1 = build(s1, curIdx1, 1024);
    Node * quadtree2 = build(s2, curIdx2, 1024);
    Node * combined = cmp(quadtree1, quadtree2);
    cout << "There are " << combined->ans << " black pixels.";

}

