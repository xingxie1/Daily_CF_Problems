#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
using i128 = __int128_t;
using vt = vector<int>;
using vd = vector<double>;
using vll = vector<long long>;
using vvt = vector<vector<int>>;
using vvd = vector<vector<double>>;
using vvll = vector<vector<long long>>;
using vvvt = vector<vector<vector<int>>>;
using vvvll = vector<vector<vector<long long>>>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<double,double>;
using vpii = vector<pair<int,int>>;
using vpll = vector<pair<ll,ll>>;
using vpdd = vector<pair<double,double>>;
using vvpii = vector<vector<pair<int,int>>>;
using vvpll = vector<vector<pair<ll,ll>>>;
using tri = tuple<int,int,int>;
using trl = tuple<ll,ll,ll>;
using vtri = vector<tuple<int,int,int>>;
using vtrl = vector<tuple<ll,ll,ll>>;
#define YES cout << "YES" << endl
#define Yes cout << "Yes" << endl
#define NO cout << "NO" << endl
#define No cout << "No" << endl
#define fi first
#define se second
#define umap unordered_map
#define uset unordered_set
#define pqueue priority_queue
#define mset multiset
// #define endl '\n'
//const int MOD = 998244353;
//const int MOD = (int)1e9+7;

void solve()
{
    int n;
    cin >> n;
    vt pre(n);
    auto cal = [&]()
    {
        vll dp(1 << n);
        dp[0] = 1;
        for (int mask = 0;mask < 1 << n;mask++)
        {
            for (int i = 0;i < n;i++)
            {
                if (mask >> i & 1) continue;
                if ((pre[i] & mask) == pre[i])
                {
                    dp[mask | 1 << i] += dp[mask];
                }
            }
        }
        return dp[(1 << n) - 1];
    };
    auto get = [&](int f) 
    {
        vt deg(n);
        vvt g(n);
        for (int u = 0;u < n;u++)
        {
            for (int v = 0;v < n;v++)
            {
                if (pre[u] >> v & 1) 
                {
                    g[v].push_back(u);
                    deg[u]++;
                }
            }
        }
        vt ans;
        if (f) 
        {
            pqueue<int,vt,greater<>> pq;
            for (int i = 0;i < n;i++) 
            {
                if (!deg[i]) pq.push(i);
            }
            while (!pq.empty())
            {
                int x = pq.top();
                ans.push_back(x + 1);
                pq.pop();
                for (int y : g[x])
                {
                    deg[y]--;
                    if (!deg[y]) pq.push(y);
                }
            }
        }
        else 
        {
            pqueue<int> pq;
            for (int i = 0;i < n;i++) 
            {
                if (!deg[i]) pq.push(i);
            }
            while (!pq.empty())
            {
                int x = pq.top();
                ans.push_back(x + 1);
                pq.pop();
                for (int y : g[x])
                {
                    deg[y]--;
                    if (!deg[y]) pq.push(y);
                }
            }
        }
        return ans;
    };
    ll s = 1;
    for (int i = 1;i <= n;i++) s = s * i;
    while (1)
    {
        char op;
        cin >> op;
        if (op == '?')
        {
            int i,j;
            cin >> i >> j;
            i--;j--;
            pre[j] |= 1 << i;
            ll ns = cal();
            if (ns >= s - ns) 
            {
                s = ns;
                cout << "<" << endl;
            }
            else 
            {
                pre[j] ^= 1 << i;
                pre[i] |= 1 << j;
                s = s - ns;
                cout << ">" << endl;
            }
        }
        else 
        {
            vt a(n);
            for (int i = 0;i < n;i++) cin >> a[i];
            auto ans = get(0);
            cout << "! ";
            if (a != ans)
            {
                for (int x : ans) cout << x << " ";
                cout << endl;
            }
            else 
            {
                ans = get(1);
                for (int x : ans) cout << x << " ";
                cout << endl;
            }
            break;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(15);
    int _ = 1;
    // cin >> _;
    while (_ --) solve();

    return 0;
}