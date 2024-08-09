#include <bits/stdc++.h>
using namespace std;
const int N = 3000;
vector<pair<int, int>> graph[N + 5];
bool vis[N + 5];
int dis[N + 5];
bool spfa(int u)
{
    vis[u] = 1;
    for (auto i : graph[u])
        if (dis[i.first] > dis[u] + i.second)
        {
            dis[i.first] = dis[u] + i.second;
            if (vis[i.first] || !spfa(i.first))
                return 0;
        }
    vis[u] = 0;
    return 1;
}
int main()
{
    int n, q, a, b, c;
    scanf("%d%d", &n, &q);
    //s_i:1~i中左括号减去右括号的数量 
    //s_0=0
    for (int i = 1; i <= n; i++)
        graph[i].emplace_back(0, 0);
    //s_i>=0,s_i-s_0>=0
    for (int i = 0; i < n; i++)
    {
        graph[i + 1].emplace_back(i, 1);
        graph[i].emplace_back(i + 1, 1);
    }
    //-1<=s_i-s_{i-1}<=1
    graph[0].emplace_back(n, 0);
    graph[n].emplace_back(0, 0);
    //s_n=0,s_n-s_0=0
    while (q && q--)
    {
        scanf("%d%d%d", &a, &b, &c);
        graph[a - 1].emplace_back(b, c);
        graph[b].emplace_back(a - 1, -c);
        //s_r-s_{l-1}=c
    }
    memset(dis, 0x3f, sizeof(dis));
    dis[0] = 0;
    if (!spfa(0))
    {
        printf("?");
        return 0;
    }
    printf("! ");
    for (int i = 1; i <= n; i++)
        if (dis[i - 1] < dis[i])
            printf("(");
        else
            printf(")");
    return 0;
}
