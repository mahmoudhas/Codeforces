#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
#define fr first
#define sc second
#define mp make_pair

const int MAXN = 200010;
const int MAXA = 1000010;

int n, q;
int s;
int ar[MAXN];
int cnt[MAXA];

ll cur = 0;
void add(int i)
{
    int x = ar[i];
    cur -= 1LL * cnt[x]*cnt[x] * x;
    cnt[x]++;
    cur += 1LL * cnt[x]*cnt[x] * x;
}
void rem(int i)
{
    int x = ar[i];
    cur -= 1LL * cnt[x]*cnt[x] * x;
    cnt[x]--;
    cur += 1LL * cnt[x]*cnt[x] * x;
}

struct query
{
    int l, r;
    int ind;
    query() {}
    query(int a, int b, int c) { l = a; r = b; ind = c; }
};

bool cmp(query a, query b)
{
    if (a.l / s != b.l / s)
        return a.l < b.l;
    return a.r > b.r;
}

int main()
{
    scanf("%d%d", &n, &q);
    s = sqrt(n);
    for (int i = 0; i < n; i++)
        scanf("%d", ar + i);
    vector<query> qrs(q);
    vector<ll>    ans(q);
    for (int i = 0; i < q; i++)
    {
        scanf("%d%d", &qrs[i].l, &qrs[i].r);
        qrs[i].l--;
        qrs[i].r--;
        qrs[i].ind = i;
    }
    sort(qrs.begin(), qrs.end(), cmp);
    int l = 0, r = 0;
    add(0);
    for (int i = 0; i < q; i++)
    {
        while (l > qrs[i].l)
            add(--l);
        while (l < qrs[i].l)
            rem(l++);
        while (r < qrs[i].r)
            add(++r);
        while (r > qrs[i].r)
            rem(r--);
        ans[qrs[i].ind] = cur;
    }
    for (int i = 0; i < q; i++)
        printf("%I64d\n", ans[i]);
}
