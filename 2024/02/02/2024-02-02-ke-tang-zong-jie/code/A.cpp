#include <bits/stdc++.h>
#define fp(i, a, b) for (int i = a, i##_ = int(b); i <= i##_; ++i)
#define fd(i, a, b) for (int i = a, i##_ = int(b); i >= i##_; --i)

using namespace std;
using ll = long long;
const int N = 2e6 + 5, inf = 0x3f3f3f3f;
int n, k, ans, w[N], f[2][N];
vector<int> G[N];
void Clear() {
    fp(i, 1, n) G[i].clear();
    ans = 0;
}
void dfs(int p, int fa) {
    if (w[p] == 1) f[0][p] = -inf, f[1][p] = 1;
    else f[0][p] = w[p], f[1][p] = -inf;
    for (auto x : G[p]) if (x != fa) {
        dfs(x, p);
        int even = max({f[0][p], f[0][p] + f[0][x], f[1][p] + f[1][x]});
        int odd = max({f[1][p], f[0][p] + f[1][x], f[1][p] + f[0][x]});
        f[0][p] = even;
        f[1][p] = odd;
    }
    if (f[k % 2][p] >= k)
        ++ans, f[0][p] = f[1][p] = -inf;
}
void Solve() {
    scanf("%d%d", &n, &k);
    fp(i, 1, n) scanf("%d", w + i);
    int x, y;
    fp(i, 1, n - 1) {
        scanf("%d%d", &x, &y);
        G[x].push_back(y), G[y].push_back(x);
    }
    dfs(1, 1);
    printf("%d\n", ans);
}
int main() {
    int t = 1;
    scanf("%d", &t);
    while (t--) Solve(), Clear();
    return 0;
}
