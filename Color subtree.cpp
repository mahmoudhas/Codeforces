#include <bits/stdc++.h>

using namespace std;

const long long inf = (1LL << 62);
typedef long long ll;
typedef pair<int, int> ii;
#define fr first
#define sc second
#define mp make_pair
#define bits(x) __builtin_popcountll(x)
#define left (index << 1)
#define right ((index << 1) + 1)
#define mid ((l + r) / 2)

const int MAXN = 4*100000 + 100;

int n, q;
vector<int> adj[MAXN];
int ar[MAXN];
int conv[MAXN];
int to[MAXN];

int dfs(int u, int cur, int par)
{
    conv[u] = cur;
    int ret = cur;
    for (auto v : adj[u]) if (v != par)
    {
        ret = dfs(v, ret + 1, u);
    }
    to[conv[u]] = ret;
    return ret;
}

///Segment Tree
int cl[MAXN];
ll st[5*MAXN];
ll lazy[5*MAXN];

inline void fix(int index, int l, int r)
{
    if (lazy[index] == 0)
        return;
    st[index] = lazy[index];
    if (l != r)
    {
        lazy[left] = lazy[index];
        lazy[right] = lazy[index];
    }
    lazy[index] = 0;
}
void build(int index, int l, int r)
{
    if (l == r)
    {
        st[index] = 1LL << cl[l];
    }
    else
    {
        build(left, l, mid);
        build(right, mid + 1, r);
        st[index] = st[left] | st[right];
    }
}
void update(int index, int l, int r, int ql, int qr, int x)
{
    fix(index, l, r);
    if (l > qr || r < ql)
        return;
    if (l >= ql && r <= qr)
    {
        lazy[index] = (1LL << x);
        fix(index, l, r);
    }
    else
    {
        update(left, l, mid, ql, qr, x);
        update(right, mid + 1, r, ql, qr, x);
        st[index] = st[left] | st[right];
    }
}
ll query(int index, int l, int r, int ql, int qr)
{
    fix(index, l, r);
    if (l > qr || r < ql)
        return 0;
    if (l >= ql && r <= qr)
    {
        return st[index];
    }
    ll a = query(left, l, mid, ql, qr);
    ll b = query(right, mid + 1, r, ql, qr);
    return a | b;
}
inline void build()
{
    dfs(0, 0, -1);
    for (int i = 0; i < n; i++)
    {
        cl[conv[i]] = ar[i];
    }
    build(1, 0, n - 1);
}
inline void update(int ql, int x)
{
        ql = conv[ql];
    int qr = to[ql];
    update(1, 0, n - 1, ql, qr, x);
}
inline int ans(int ql)
{
        ql = conv[ql];
    int qr = to[ql];
    return bits(query(1, 0, n - 1, ql, qr));
}
///

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", ar + i);
    }
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build();
    while (q--)
    {
        int t;
        scanf("%d", &t);
        if (t == 1)
        {
            int r, c;
            scanf("%d%d", &r, &c);
            r--;
            update(r, c);
        }
        else
        {
            int r;
            scanf("%d", &r);
            r--;
            printf("%d\n", ans(r));
        }
    }
}
