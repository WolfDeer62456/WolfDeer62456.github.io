#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int Read() {
    int x = 0, f = 1; char ch = getchar();
    while(!isdigit(ch) && ch != '-')  ch = getchar();
    if(ch == '-')  f = -1, ch = getchar();
    while(isdigit(ch))  x = x * 10 + ch - '0', ch = getchar();
    return x * f;  
}
int first[5005], nxt[10005], to[10005], tot;
void Add(int x, int y) {
    nxt[++tot] = first[x];
    first[x] = tot;
    to[tot] = y;
}
const int Mod = 998244353;
int n, f[5005], g[5005], a[5005], cov[5005], pw2[5005] = {0};
int suf[5005], pre[5005], ff[5005];

void dfs(int u, int fa) {
    f[u] = 0;
    if(!cov[u]) {
        f[u] = 1, g[u] = 0;
        return;
    }
    int cnt = 0;
    for (int e = first[u]; e; e = nxt[e]) {
        int v = to[e];
        if(v == fa)
            continue;
        dfs(v, u);
    }
    //一定要dfs完再进行计算，否则后面dfs的时候会覆盖suf和pre中的内容 
    for (int e = first[u]; e; e = nxt[e]) {
        int v = to[e];
        if(v == fa)
            continue;
        ++cnt;
        int tmp = f[v] << 1;
        if(tmp >= Mod)
            tmp -= Mod;
        tmp += g[v];
        if(tmp >= Mod)
            tmp -= Mod;
        suf[cnt] = pre[cnt] = tmp;
        ff[cnt] = f[v];
    }
    suf[cnt + 1] = pre[0] = 1;
    for (int i = 1; i <= cnt; i++)
        pre[i] = 1ll * pre[i] * pre[i - 1] % Mod;
    for (int i = cnt; i >= 1; i--)
        suf[i] = 1ll * suf[i] * suf[i + 1] % Mod;
    for (int i = 1; i <= cnt; i++)
        f[u] = (f[u] + 1ll * ff[i] * pre[i - 1] % Mod * suf[i + 1]) % Mod;
    g[u] = suf[1];
}

signed main() {
    n = Read();
    for (int i = 1; i < n; i++) {
        int x = Read(), y = Read();
        Add(x, y), Add(y, x);
    }
    for (int _ = 1; _ < n; _++) {
        int val = Read();
        cov[val] = 1;
        memset(f, -1, sizeof(f));
        memset(g, 0, sizeof(g));
        int ans = 1;
        for (int i = 1; i <= n; i++) {
            if(f[i] == -1 && cov[i]) {
                dfs(i, 0);
                ans = 1ll * ans * f[i] % Mod;
            }
        }
        printf("%d\n", ans);
    }
        return 0;
}
