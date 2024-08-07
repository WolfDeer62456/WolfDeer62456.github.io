#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;
int Read() {
    int x = 0, f = 1; char ch = getchar();
    while(!isdigit(ch) && ch != '-')  ch = getchar();
    if(ch == '-')  f = -1, ch = getchar();
    while(isdigit(ch))  x = x * 10 + ch - '0', ch = getchar();
    return x * f;  
}
int rd[500005], cd[500005], first[500005], nxt[2000005], to[2000005], tot, vis[2000005], id[2000005];
void Add(int x, int y, int z) {
    nxt[++tot] = first[x]; first[x] = tot; to[tot] = y; vis[tot] = 0; id[tot] = z;
    nxt[++tot] = first[y]; first[y] = tot; to[tot] = x; vis[tot] = 0; id[tot] = z;
    ++rd[y]; ++cd[x];
}
struct node {
    int l, r, x, y;
}a[500005];
int dl[500005], num1, num2, Vis[500005], col[500005];
int stk[500005], ins[500005], dfn[500005], low[500005], cnt, tp, scc, mst2[500005];
void tarjan(int u) {
    Vis[u] = 1;
    low[u] = dfn[u] = ++cnt;
    stk[++tp] = u; ins[u] = 1;
    for(int e = first[u]; e; e = nxt[e]) {
        if(e % 2 == 1)  continue ;
        int v = to[e];
        if(!Vis[v])  tarjan(v), low[u] = min(low[u], low[v]);
        else if(ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        ++scc;
        while(stk[tp] != u) {
            col[stk[tp]] = scc;
            ins[stk[tp]] = 0;
            --tp;
        }
        col[stk[tp]] = scc;
        ins[stk[tp]] = 0;
        --tp;
    }
}
vector<pair<int, int> > edg[500005];
vector<int> insid[500005];

void dfs(int u) {
    Vis[u] = 1;
    for(int e = first[u]; e; e = nxt[e]) {
        int v = to[e];
        if(e % 2 == 1 || Vis[v] || col[u] != col[v])  continue ;
        insid[col[u]].push_back(id[e]);
        dfs(v);
    }
}

signed main() {
    int T = Read();
    while(T--) {
        int n = Read(), m = Read();
        memset(rd + 1, 0, sizeof(int) * n);
        memset(cd + 1, 0, sizeof(int) * n);
        memset(first + 1, 0, sizeof(int) * n);
        memset(Vis + 1, 0, sizeof(int) * n);
        memset(dl + 1, 0, sizeof(int) * m);
        memset(col + 1, 0, sizeof(int) * n);
        memset(mst2 + 1, 0, sizeof(int) * n);
        tot = 1, cnt = scc = 0;
        for(int i = 1; i <= m; i++)
            a[i].l = Read(), a[i].x = Read(), a[i].r = Read(), a[i].y = Read();
        num1 = 0, num2 = m + 1;
        for(int i = 1; i <= m; i++) {
            if(a[i].x == 1 && a[i].y == 1)  dl[++num1] = i;
            //全1，最先操作 
            if(a[i].x == 2 && a[i].y == 2)  dl[--num2] = i, mst2[a[i].l] = mst2[a[i].r] = 1;
            //全2，最后操作，并且把涉及到的位置全部标记为2 
            if(a[i].x == 1 && a[i].y == 2)  Add(a[i].l, a[i].r, i);
            if(a[i].x == 2 && a[i].y == 1)  Add(a[i].r, a[i].l, i);
            //1向2连边 
        }
        for(int i = 1; i <= n; i++)
            if(!Vis[i])
                tp = 0, tarjan(i);
        //求出强连通分量 
        for(int i = 1; i <= scc; i++)
            edg[i].clear(), insid[i].clear();
        unordered_map<long long, int> mp;
        memset(rd + 1, 0, sizeof(int) * scc);
        for(int i = 1; i <= n; i++)
            for(int e = first[i]; e; e = nxt[e])
                if(e % 2 == 0 && !vis[e]) {
                    int v = to[e];
                    if(col[i] != col[v] && !mp[1ll * col[i] * scc + col[v]]) {
                        mp[1ll * col[i] * scc + col[v]] = 1;
                        edg[col[i]].push_back(make_pair(col[v], id[e]));
                        mst2[v] = 1;
                        ++rd[col[v]];
                    }
                }
        //强连通分量之间连边 
        memset(Vis + 1, 0, sizeof(int) * n);
        for(int i = 1; i <= n; i++) {
            if(insid[col[i]].size() == 0 && mst2[i])
                dfs(i);
        }
        //对每个强连通分量内部进行搜索，优先从固定为2的点开始，搜出内部操作的顺序 
        for(int i = 1; i <= n; i++)
            if(insid[col[i]].size() == 0)
                dfs(i);
        queue<int> q;
        for(int i = 1; i <= scc; i++)
            if(rd[i] == 0)  q.push(i);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int i = 0; i < insid[u].size(); i++)
                dl[--num2] = insid[u][i];
            //根据拓扑序依次对强连通分量进行操作 
            for(auto v : edg[u]) {
                dl[--num2] = v.second;
                --rd[v.first];
                if(!rd[v.first])  q.push(v.first);
            }
        }
        memset(Vis + 1, 0, sizeof(int) * m);
        for(int i = 1; i <= m; i++)
            if(dl[i])  Vis[dl[i]] = 1;
        for(int i = 1; i <= m; i++)
            if(!Vis[i])  dl[++num1] = i;
        memset(col + 1, 0, sizeof(int) * n);
        for(int i = 1; i <= m; i++)
            col[a[dl[i]].l] = a[dl[i]].x, col[a[dl[i]].r] = a[dl[i]].y;
        //按顺序执行每个操作得到每个点最后的值 
        int res = 0;
        for(int i = 1; i <= n; i++)  res = res + col[i];
        printf("%d\n", res);
        for(int i = 1; i <= m; i++)
            printf("%d ", dl[i]);
        puts("");
    }
    return 0;
}
/*
1 1 2 2
2 1 3 2
1 2 3 1
3 1 4 2
4 1 5 2

5 1 6 2
4 2 6 1
7 1 8 2
8 1 9 2
7 2 9 1

5 2 9 1
8 2 10 2
1 1 10 1
*/
