#include <bits/stdc++.h>
using namespace std;
typedef long double ldb;
typedef long long ll;
typedef pair<int, int> pii;
int read()
{
    char c = getchar();
    int x = 0, f = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}
int n, m, d[5005][5005], vis[5005], mi[5005];
queue<int> Q;
vector<int> G[5005];
void bfs(int x, int *dis)
{
    for (int i = 1; i <= n; i++)
        dis[i] = 1e7, vis[i] = 0;
    vis[x] = 1;
    dis[x] = 0;
    Q.push(x);
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (auto v : G[u])
        {
            if (!vis[v])
            {
                vis[v] = 1;
                dis[v] = dis[u] + 1;
                Q.push(v);
            }
        }
    }
}
ldb cal(int x, int k)
{
    if (x == 0)
        return 0;
    ldb s = 0;
    s += x * (1.0 / (k / x + 1));
    //一部分的路花k/x元 
    s += (k % x) * (1.0 / (k / x + 2) - 1.0 / (k / x + 1));
    //剩下的路花k/x+1元 
    return s;
}
ldb f(int mid, int a, int b, int k)
{
	//在a条非重合路径上画mid元，在b条重合路径上花k-mid元 
    return cal(a, mid) + cal(b, k - mid) * 2;
}
int main()
{
    n = read(), m = read();
    int k = read();
    for (int i = 1; i <= m; i++)
    {
        int a = read(), b = read();
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int i = 1; i <= n; i++)
        bfs(i, d[i]);
    //01bfs算距离 
    int s1 = read(), t1 = read(), s2 = read(), t2 = read();
    ldb ans = cal(d[s1][t1] + d[s2][t2], k);
    for (int i = 0; i <= n; i++)
        mi[i] = 1e7;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int b = d[i][j];
            if (b > n)
                continue;
            int a = d[s1][i] + d[s2][i] + d[j][t1] + d[j][t2];
            mi[b] = min(mi[b], a);
            a = d[s1][i] + d[t2][i] + d[j][t1] + d[j][s2];
            mi[b] = min(mi[b], a);
        }
    }
    //维护每种长度的重合路径对应的最短的非重合路径 
    for (int b = 0; b <= n; b++)
    {
        int a = mi[b];
        ll l = 0, r = k, lmid, rmid;
        //三分非重合路径上花多少钱 
        while (r - l > 4)
        {
            lmid = (l * 2 + r) / 3;
            rmid = (l + r * 2) / 3;
            if (f(lmid, a, b, k) > f(rmid, a, b, k))
                l = lmid;
            else
                r = rmid;
        }
        for (int t = l; t <= r; t++)
        {
            ans = min(ans, f(t, a, b, k));
        }
    }
    printf("%.15Lf\n", ans);
    return 0;
}
