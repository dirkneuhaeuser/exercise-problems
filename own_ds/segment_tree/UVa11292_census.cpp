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
    
    solve();
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl; 
    return 0; 
} 

class SegmentTree2D{
private:
    ll NO_VALUE;
    ll n, m;
    vector<vi> A, st;
    ll l(ll p){return p<<1;}
    ll r(ll p){return (p<<1) +1;}
    bool maxType;

    // the conq method decides the problem which is being solved: here min
    ll conq(ll a, ll b){
        if (a==NO_VALUE) return b; // edge case (happens in invalid subtree in query); sometimes its enough to just use a neutral value for NO_VALUE
        if (b==NO_VALUE) return a;
        if(maxType){
            return max(a,b);
        }else{
            return min(a,b);
        }
    }

    // Second-Dimension: O(m) as O(1+2+4+..+ 2^log m) = O(2m)
    void build_y(ll px, ll Lx, ll Rx, ll py, ll Ly, ll Ry){
        // 2nd stage
        if (Ly == Ry){
            if(Lx == Rx){
                st[px][py] = A[Lx][Ly];
            }else{
                // now as the 2nd stage is equal, but the first stage differ, we separate and build it (note, as build_x is kind of postorder, we have that computed already)
                st[px][py] = conq(st[l(px)][py], st[r(px)][py]);
            }
        } else{
            ll mid = (Ly+Ry)/2;
            build_y(px, Lx, Rx, l(py), Ly, mid);
            build_y(px, Lx, Rx, r(py), mid+1, Ry);
            st[px][py] = conq(st[px][l(py)], st[px][r(py)]);
        }
    }

    // Combined with 2nd-Dimension O(n*m)
    void build_x(ll px, ll Lx, ll Rx){
        // 1st stage
        if(Lx != Rx){
            ll mid = (Lx+Rx)/2;
            build_x(l(px), Lx, mid);
            build_x(r(px), mid+1, Rx);
        }
        build_y(px, Lx, Rx, 1 , 0, m-1);

    }


    // point-update: O(log(m))
    void update_y(ll px, ll Lx, ll Rx, ll py, ll Ly, ll Ry, ll pointX, ll pointY, ll newVal){
        // 2nd stage
        if (Ly == Ry){
            if(Lx == Rx){
                st[px][py] = newVal;
            }else{
                // now as the 2nd stage is equal, but the first stage differ, we separate and build it (note, as build_x is kind of postorder, we have that computed already)
                st[px][py] = conq(st[l(px)][py], st[r(px)][py]);
            }
        } else{
            ll mid = (Ly+Ry)/2;
            if(pointY <= mid){
                update_y(px, Lx, Rx, l(py), Ly, mid, pointX, pointY, newVal);
            }else{
                update_y(px, Lx, Rx, r(py), mid+1, Ry, pointX, pointY, newVal);
            }
            st[px][py] = conq(st[px][l(py)], st[px][r(py)]);
        }
    }

    // point-update combined with second stage: O(log n * log m)
    void update_x(ll px, ll Lx, ll Rx, ll pointX, ll pointY, ll newVal){
        // 1st stage
        if(Lx != Rx){
            ll mid = (Lx+Rx)/2;
            if(pointX <= mid){
                update_x(l(px), Lx, mid, pointX, pointY, newVal);
            }else{
                update_x(r(px), mid+1, Rx, pointX, pointY, newVal);
            }
        }
        update_y(px, Lx, Rx, 1 , 0, m-1, pointX, pointY, newVal);
    }

    // second-dimenson: O(2 log n), this is the case as only the left and right border might go down all the way, the inner nodes will return there result right away.
    ll query_y(ll px, ll py, ll Ly, ll Ry, ll queryLy, ll queryRy){
        if(Ly > queryRy || Ry < queryLy) return NO_VALUE;
        if(Ly >= queryLy && Ry <= queryRy){
            return st[px][py];
        }
        ll mid = (Ly + Ry)/2;
        return conq(query_y(px, l(py), Ly, mid, queryLy, queryRy), query_y(px, r(py), mid+1, Ry, queryLy, queryRy));

    }

    // combined with 2nd-Dimension: O(2 log n * 2 log m),
    ll query_x(ll px, ll Lx, ll Rx, ll queryLx, ll queryRx, ll queryLy, ll queryRy){
        if(Lx > queryRx || Rx < queryLx) return NO_VALUE;
        if(Lx >= queryLx && Rx <= queryRx) {
            return query_y(px, 1, 0, m-1, queryLy, queryRy);
        }
        ll mid = (Lx + Rx)/2;
        return conq(query_x(l(px), Lx, mid, queryLx, queryRx, queryLy, queryRy), query_x(r(px), mid+1, Rx, queryLx, queryRx, queryLy, queryRy));
    }

public:
    SegmentTree2D(ll sizeX, ll sizeY, bool _maxType) : n(sizeX), m(sizeY), maxType(_maxType) {
        if(maxType){
            NO_VALUE = 0;
        }else{
            NO_VALUE = INF;
        }
        st.assign(4*sizeX, vi(4*sizeY, NO_VALUE));
    }
    SegmentTree2D(const vector<vi> &initA, bool _maxType): SegmentTree2D(initA.size(), initA[0].size(), _maxType) {
        A = initA;
        build_x(1, 0, n-1);
    } 

    // All idx's i,j from 0 to n-1
    // point update
    void update(ll pointX, ll pointY, ll val) {
        // updates [i,..j]
        update_x(1, 0, n-1, pointX, pointY, val);
    }
    // range query
    ll query(ll queryLx, ll queryRx, ll queryLy, ll queryRy){
        // queries [i,..j]
        return query_x(1, 0, n-1, queryLx, queryRx, queryLy, queryRy);
    }
};

void solve() 
{
    // problem: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2272
    // about: 2D Segment-Tree or Quad-Tree. Dynamic Min/Max Queries on 2D Grid. Here we use a 2D Segment-Tree. It is basically the same as the 1D version, but each segment itself again contains a Segment-Tree. So at first we forgot about the 2 dimension and just focus on the the first. We called it the x-Dimension (We use it for the rows here). Therefore we use build_x, update_x and query_x. But whenever we want to read or update st[px] (this is the case when the current segment is coverd completly by update-X-points or query-X-interval), we instead go one dimension deeper and also try to find segments to be covered by our update-Y-points or query-Y-interval (to update or query). Note for me at least it feels that build_x and build_y is a bit sophisicated as the first dimension is a kind of a post-order, making sure that later nodes are already computed. When updaing/building the second dimension we also access these kids of the frist dimension to build/update the current segment (px,py).
    // reference: https://cp-algorithms.com/data_structures/segment_tree.html
    // note: only works with point updates -> no lazy updates (Probably not even possible with 2D Segment-Trees)
    // note: ST is all about defining update and query (and if needed going for lazy propagation and build function). Most often the value of each segment is just an integer (max or min of the segment, or even sum). Sometimes it makes sense to define a new struct  (e.g. Node) if there are more values defined. For example, when merging the segments is a bit more sophisticated.
    int n; cin >> n;
    vector<vi> grid(n, vi(n, 0));
    FOR(i, n){
        FOR(j, n){
            cin >> grid[i][j];
        }
    }
    // O(n*m)
    SegmentTree2D stMax(grid, true);
    SegmentTree2D stMin(grid, false);
    int q; cin >> q;
    FOR(i, q){
        char type; cin >> type;
        if(type == 'q'){
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            x1--; x2--; y1--; y2--;
            // O(log n * log m)
            ll ansMax = stMax.query(x1, x2, y1, y2);
            ll ansMin = stMin.query(x1, x2, y1, y2);
            cout << ansMax << " " << ansMin<< endl;
        }else{
            int pointX, pointY, val; cin >> pointX >> pointY >> val;
            pointX--; pointY--;
            // O(log n * log m)
            stMax.update(pointX, pointY, val);
            stMin.update(pointX, pointY, val);
        }


    }
    
}

