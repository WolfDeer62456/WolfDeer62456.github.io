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

const int N = 2005, Mod = 1e9 + 7;
int first[N], nxt[N << 1], to[N << 1], tot;
int n, sum, a[N], ans[N], p[N], sz[N], f[N][N], g[N][N];

void Add(int x, int y) {
    nxt[++tot] = first[x], first[x] = tot, to[tot] = y;
    nxt[++tot] = first[y], first[y] = tot, to[tot] = x;
}

int qpow(int x, int k) {
    int res = 1;
    while(k) {
        if(k & 1)
            res = 1ll * res * x % Mod;
        x = 1ll * x * x % Mod;
        k >>= 1;
    }
    return res;
}

int h[N][2];

void dfs(int u, int fa) {
    sz[u] = 1;
    f[u][1] = p[u];
    g[u][1] = a[u];
    for (int e = first[u]; e; e = nxt[e]) {
        int v = to[e];
        if(v == fa)
            continue;
        dfs(v, u);
        //树上背包，u枚举上界是sz[u]，v枚举上界是sz[v] 
        for (int i = 1; i <= sz[u] + sz[v]; i++)
            h[i][0] = h[i][1] = 0;
        //一定要用一个辅助数组，不能改变f和g里面的内容 
        for (int i = 1; i <= sz[u]; i++) {
            h[i][0] = (h[i][0] + 1ll * f[u][i] * (Mod + 1 - p[v])) % Mod;
            for (int j = 1; j <= sz[v]; j++)
                h[i + j][0] = (h[i + j][0] + 1ll * f[u][i] * f[v][j]) % Mod;
        }
        for (int i = 1; i <= sz[u]; i++) {
            h[i][1] = (h[i][1] + 1ll * g[u][i] * (Mod + 1 - p[v])) % Mod;
            for (int j = 1; j <= sz[v]; j++)
                h[i + j][1] = (h[i + j][1] + 1ll * f[u][i] * g[v][j]) % Mod;
        }
        for (int i = 1; i <= sz[u]; i++) {
            for (int j = 1; j <= sz[v]; j++)
                h[i + j][1] = (h[i + j][1] + 1ll * g[u][i] * f[v][j]) % Mod;
        }
        for (int i = 1; i <= sz[u] + sz[v]; i++)
            f[u][i] = h[i][0];
        for (int i = 1; i <= sz[u] + sz[v]; i++)
            g[u][i] = h[i][1];
        //更新sz[u] 
        sz[u] += sz[v];
    }
    for (int i = 1; i <= sz[u]; i++)
        ans[i] = (ans[i] + 1ll * g[u][i] * (Mod + 1 - p[fa])) % Mod;
}

signed main() {
    n = Read();
    for (int i = 1; i < n; i++)
        Add(Read(), Read());
    for (int i = 1; i <= n; i++) {
        a[i] = Read();
        int b = Read(), c = Read();
        p[i] = 1ll * b * qpow(c, Mod - 2) % Mod;
        sum += a[i];
    }
    for (int i = 1; i <= n; i++)
        a[i] = 1ll * a[i] * qpow(sum, Mod - 2) % Mod;
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    return 0;
}
