#include <bits/stdc++.h>
#define MAXN ((int) 1e5)
#define INF ((long long) 1e18)
using namespace std;
typedef pair<int, long long> pil;

int n, q;
long long A[MAXN + 10];

struct Magic {
    long long A[MAXN + 10], sm;
    set<pil> st;

    void clear() {
        memset(A, 0, sizeof(long long) * (n + 3));
        sm = 0;
        st.clear(); st.insert(pil(1, 0)); st.insert(pil(n + 1, INF));
    }

    // A[x] += v
    void update(int x, long long v) {
        A[x] += v;
        // 尝试将操作结果插入 set 中
        auto it = prev(st.upper_bound(pil(x, INF)));
        // 如果插入位置的前一个元素都比操作结果大，那么本次操作无影响
        if (it->second >= A[x]) return;
        sm -= (next(it)->first - it->first) * it->second;
        sm += (x - it->first) * it->second + (next(it)->first - x) * A[x];
        it = st.insert(pil(x, A[x])).first;
        // 将插入位置后面比操作结果小的元素都移除
        while (next(it)->second <= A[x]) {
            sm -= (next(it)->first - x) * A[x] + (next(next(it))->first - next(it)->first) * next(it)->second;
            st.erase(next(it));
            sm += (next(it)->first - x) * A[x];
        }
    }
} f, g;

void solve() {
    scanf("%d", &n);
    long long mx = 0, sm = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &A[i]);
        mx = max(mx, A[i]); sm += A[i];
    }

    // g 的维护其实只要把序列 A 倒过来，剩下的操作和 f 的维护都是一样的
    f.clear(); g.clear();
    for (int i = 1; i <= n; i++) f.update(i, A[i]), g.update(n + 1 - i, A[i]);

    scanf("%d", &q);
    while (q--) {
        int x, v; scanf("%d%d", &x, &v);
        A[x] += v;
        mx = max(mx, A[x]); sm += v;
        f.update(x, v); g.update(n + 1 - x, v);
        printf("%lld\n", f.sm + g.sm - n * mx - sm);
    }
}

int main() {
    int tcase; scanf("%d", &tcase);
    while (tcase--) solve();
    return 0;
}
