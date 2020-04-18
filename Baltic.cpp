/*
 * first let's learn how to add a value x on the path from a to b , lets have an array sum[node] -> sum[a] ++ , sum [b] ++ , sum [lca(a,b)] -= 2 , now we run a dfs calculating the value of every edge using prifx sum 
 * let's have an array ord[node] = the order of that node in the dfs , let's build lca table 
 * now we can sort every query according to its order, add 1 between every two adjacent nodes in the query vector & the last and the first node also
 * in this way every edge between those nodes are increased by 2 , 
 * we print the edges with value >= k 
*/ 
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 547
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ld pai=acos(-1);
int n , q , k ;
vpi v[100009];
int sum[100009] , val[100009] , ord[100009] , timer , dp[100009][20] , w[100009] ;
bool cmp ( int i , int j ) {
    return ord[i] < ord[j] ;
}
void dfs ( int node , int p ) {
    ord [ node ] = timer ++ ;
    dp [node][0] = p ;
    w [node] = w [ p ] + 1 ;
    for ( auto u : v [ node ] ) {
        if ( u.fi == p ) C ;
        dfs ( u.fi , node ) ;
    }
}
int lca ( int a , int b ) {
    int l = w[a] - w[b] ;
    for ( int i = 0 ; i < 20 ; i ++ ) {
        if ( ( l & ( 1<<i ) ) ) {
            a = dp[a][i] ;
        }
    }
    if ( a == b ) return a ;
    for ( int i = 19 ; i >= 0 ; i -- ) {
        if ( dp[a][i] != dp[b][i] ) {
            a = dp[a][i] ;
            b = dp[b][i] ;
        }
    }
    return dp[a][0] ;
}
void solve ( int a , int b ) {
    if ( w[a] < w[b] ) swap ( a , b ) ;
    int c = lca ( a , b ) ;
    sum [a] ++ ;
    if ( b == c ) {
        sum [b] -- ;
        return ;
    }
    sum [b] ++ ;
    sum [c] -=2;
}
void dfs_calc ( int node , int p ) {
    for ( auto U : v[node] ) {
        int u = U.fi ;
        int id= U.se ;
        if ( u == p ) C ;
        dfs_calc ( u , node ) ;
        sum [node] += sum[u] ;
        val [id]  = sum[u] ;
    }
}
int main () {
    cin >> n >> q >> k ;
    k *= 2 ;
    for ( int i = 0 ; i < n-1 ; i ++ ) {
        int a , b ;
        cin >> a >> b ;
        a -- , b -- ;
        v[a].pb ( { b , i } ) ;
        v[b].pb ( { a , i } ) ;
    }
    dfs ( 0 , 0 ) ;
    for ( int j = 1 ; j < 20 ; j ++ ) {
        for ( int i = 0 ; i < n ; i ++ ) {
            dp [i][j] = dp [ dp [i][j-1] ][j-1] ;
        }
    }
    while ( q -- ) {
        int N ;
        cin >> N ;
        vi ret ; 
        for ( int i = 0 ; i < N ; i ++ ) {
            int x ;
            cin >> x ;
            x -- ; 
            ret .pb ( x ) ;
        }
        sort ( ret.begin() , ret.end() , cmp ) ;
        for ( int i = 0 ; i < ret.size() -1 ; i ++ ) solve ( ret[i] , ret[i+1] ) ;
        solve ( ret.back() , ret[0] ) ;
    }
    dfs_calc ( 0 , 0 ) ;
    vi ans ;
    for ( int i = 0 ; i < n-1 ; i ++ ) {
        if ( val [i] >= k ) {
            ans .pb ( i + 1 ) ; 
        }
    }
    cout << ans .size() << endl ;
    for ( auto u : ans ) cout << u << " " ;
    cout << endl ; 
}
