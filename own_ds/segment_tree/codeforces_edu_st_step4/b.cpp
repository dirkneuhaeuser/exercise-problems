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
int MOD = 1000000007;
const int INF = 1<<30;

int smod(int a, int m=MOD){return((a%m) +m) %m;}


// DP speed up with matrix multiplication
vector<vi> matMul(const vector<vi> &a,const vector<vi> &b){
    vector<vi> ret(2, vi(2, 0));
    //memset(ret.mat, 0, sizeof ret.mat);
    for(int i=0; i<2; ++i){
        for(int k=0; k<2; ++k){
            if(a[i][k]==0) continue;
            for(int j = 0; j<2; ++j){
                ret[i][j] += smod(a[i][k], MOD) * smod(b[k][j], MOD);
                ret[i][j] = smod(ret[i][j], MOD);
            }
        }
    }
    return ret;
}

bool isPowerOfTwo(ll x){
    return (x&(x-1)) == 0;
}



class SegmentTree{
private:
    int n;
    vector<vector<vi>> A, st;
    int l(int p){return p<<1;}
    int r(int p){return (p<<1) +1;}

    // O(n) as O(1+2+4+..+ 2**logn) = O(2n). Note the advantage of build is that each segment is computed only once, if we apply n times update we also need to update the inner nodes each time, leading to O(n log n)
    void build(int p, int L, int R, vector<vector<vi>> &init){
        if (L == R){
            st[p] = init[L];
        } else{
            int m = (L+R)/2;
            build(l(p), L, m, init);
            build(r(p), m+1, R, init);
            st[p] = matMul(st[l(p)], st[r(p)]);
        }
    }
    void del(){
        current[0][0]=0;
        current[1][1]=0;
        current[1][0]=0;
        current[0][1]=0;
    }

    // DP speed up with matrix multiplication
    void contr(const vector<vi> &b){
        cp = current;
        del();
        for(int i=0; i<2; ++i){
            for(int k=0; k<2; ++k){
                if(cp[i][k]==0) continue;
                for(int j = 0; j<2; ++j){
                    current[i][j] += smod(cp[i][k], MOD) * smod(b[k][j], MOD);
                    current[i][j] = smod(current[i][j], MOD);
                }
            }
        }
    }



    void query(int p, int L, int R, int i, int j){ // O(logn)
        //cout << p << " " << L << " " << R << " " << i << " " << j <<  endl;
        if(i<=L && j>=R){ // with == would be sufficent
            contr(st[p]);
            return;
        }
        int m = (L+R)/2;
        if(m+1>j){
            query(l(p), L, m, i, j);
            return;
        }
        if(m < i){
            query(r(p), m+1, R, i, j);
            return;
        }
        query(l(p), L, m, i, j);
        query(r(p), m+1, R, i, j);
    }
public:
    vector<vi> current, cp;
    SegmentTree(int size) : n(size) {
        current.assign(2, vi(2, 0));
        cp.assign(2, vi(2, 0));
        current[0][0]=1;
        current[1][1]=1;
        if(isPowerOfTwo(size)){
            st.resize(2*size); // 4 = 2*2. First 2: to make n a factor of two [actualy 2 * upper(log_2(n))], and second 2 for the inner nodes of the tree
        }else{
            st.resize(4*size); // 4 = 2*2. First 2: to make n a factor of two [actualy 2 * upper(log_2(n))], and second 2 for the inner nodes of the tree
        }
    }
    SegmentTree(vector<vector<vi>> &initA): SegmentTree(initA.size()) {
        build(1, 0, n-1, initA);
    } 
    void query(int i, int j){
        // queries [i,..j]
        current[0][0]=1;
        current[1][1]=1;
        current[1][0]=0;
        current[0][1]=0;
        query(1, 0, n-1, i, j);
    }
};

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
void solve() 
{

    // problem: https://codeforces.com/edu/course/2/lesson/4/4/practice/contest/274684/problem/C
    // about: Segment-tree with matrix-multiplicationstate. Matrix multiplication is associative and thus we can use it in a ST. Here the time restrictions are very tight though..
    int n, m;// cin >> MOD >> n >> m;
    scanf("%d %d %d", &MOD, &n, &m);
    vector<vector<vi>>init(n,vector<vi>(2, vi(2, 0)));
    FOR(i, n){
        int a, b, c, d; // cin >> a >> b >> c >> d;
        scanf(" %d %d %d %d", &init[i][0][0], &init[i][0][1], &init[i][1][0], &init[i][1][1]);
    }
    SegmentTree st(init);
    FOR(i, m){
        int l, r; // cin >> l >> r;
        scanf(" %d %d", &l, &r);
        st.query(l-1, r-1);
        FOR(i, 2){
            FOR(j, 2){
                printf("%d ",st.current[i][j]);
                //cout << ans.val.mat[i][j] << " ";
            }
            printf("\n");
            //cout << endl;
        }
        printf("\n");
        //cout << endl;
    }


    

}

