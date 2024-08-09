#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <functional>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;
namespace FastIO {
    char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf;
    int p, p3 = -1;
    void read() {}
    void print() {}
    inline int getc() { return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++; }
    inline void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
    template <typename T, typename... T2>
    inline void read(T &x, T2 &...oth) {
        int f = 0;
        x = 0;
        char ch = getc();
        while (!isdigit(ch)) {
            if (ch == '-') f = 1;
            ch = getc();
        }
        while (isdigit(ch)) {
            x = x * 10 + ch - 48;
            ch = getc();
        }
        x = f ? -x : x;
        read(oth...);
    }
    template <typename T, typename... T2>
    inline void print(T x, T2... oth) {
        if (p3 > 1 << 20)
            flush();
        if (x < 0)
            buf2[++p3] = 45, x = -x;
        do {
            a[++p] = x % 10 + 48;
        } while (x /= 10);
        do {
            buf2[++p3] = a[p];
        } while (--p);
        buf2[++p3] = '\n';
        print(oth...);
    }
}
using FastIO::flush;
using FastIO::print;
using FastIO::read;
const int N = 1e5 + 5, M = 2e3 + 5;
struct line {
    int val, pos, l, r;
    bool operator < (line A) const {
        return pos < A.pos;
    }
}l[N << 1];
struct node {
    int l, r;
    bool operator < (node A) const {
        return l < A.l;
    }
};
vector<node> vec;
struct query {
    int id, l, r;
    bool operator < (query A) const {
        return l < A.l;
    }
} q[N];
int n, m, cnt, L[M][M], R[M][M], ans[N];
struct Segtree1 {
    priority_queue<int> mxin[M << 2], mxout[M << 2];
    priority_queue<int, vector<int>, greater<int>> mnin[M << 2], mnout[M << 2];
    int maxn[M << 2], minn[M << 2];
    void Insert(int o, int l, int r, int nl, int nr, int val) {
        if(nl <= l && r <= nr) {
            if(val < 0) {
                mxout[o].emplace(-val);
                mnout[o].emplace(-val);
                //懒删除标记 
            }
            else {
                mxin[o].emplace(val);
                mnin[o].emplace(val);
            }
            while(mxin[o].size() && mxout[o].size() && mxin[o].top() == mxout[o].top()) {
                mxin[o].pop();
                mxout[o].pop();
                //删除操作 
            }
            while(mnin[o].size() && mnout[o].size() && mnin[o].top() == mnout[o].top()) {
                mnin[o].pop();
                mnout[o].pop();
                //删除操作 
            }
            if(mnin[o].size()) {
                minn[o] = mnin[o].top();
                maxn[o] = mxin[o].top();
                //维护覆盖这个区间的矩形的出现时间的最早和最晚值 
            }
            return;
        }
        int mid = (l + r) >> 1;
        if(nl <= mid)
            Insert(o << 1, l, mid, nl, nr, val);
        if(mid < nr)
            Insert(o << 1 | 1, mid + 1, r, nl, nr, val);
    }
    void Query(int o, int l, int r, int id, int ll, int rr) {
        if(mnin[o].size()) {
            ll = min(ll, minn[o]);
            rr = max(rr, maxn[o]);
            //对线段树进行dfs，维护从根到叶子的max和min 
        }
        if(l == r) {
            L[id][l] = ll, R[id][l] = rr;
            return;
        }
        int mid = (l + r) >> 1;
        Query(o << 1, l, mid, id, ll, rr);
        Query(o << 1 | 1, mid + 1, r, id, ll, rr);
    }
}S1;
struct Segtree2 {
    int lowbit(int x) { return x & (-x); }
    int c[N], sum;
    void modify(int pos) {
        ++sum;
        for(int i = pos; i <= n; i += lowbit(i))
            ++c[i];
    }
    int query(int pos) {
        int res = 0;
        for(int i = pos; i >= 1; i -= lowbit(i))
            res += c[i];
        return sum - res;
    }
} S2;
int sl[N], sr[N];
signed main() {
    read(n, m);
    for (int i = 1; i <= n; i++) {
        int X1, Y1, X2, Y2;
        read(X1, Y1, X2, Y2);
        ++X1, ++Y1;
        l[++cnt] = (line){i, Y1, X1, X2};
        l[++cnt] = (line){-i, Y2 + 1, X1, X2};
    }
    sort(l + 1, l + cnt + 1);
    int nw = 1;
    for(int i = 1; i <= M - 5; i++) {
        while(nw <= cnt && l[nw].pos == i) {
            S1.Insert(1, 1, M - 5, l[nw].l, l[nw].r, l[nw].val);
            ++nw;
        }
        S1.Query(1, 1, M - 5, i, n + 1, 0);
    }
    for(int i = 1; i <= M - 5; i++)
        for (int j = 1; j <= M - 5; j++)
            if(L[i][j] <= R[i][j]) {
                vec.push_back((node){L[i][j], R[i][j]});
                ++sl[L[i][j] + 1], ++sr[R[i][j] - 1];
            }
    for(int i = 1; i <= n; i++)
        sl[i] += sl[i - 1];
    for(int i = n; i >= 1; i--)
        sr[i] += sr[i + 1];
    for (int i = 1; i <= m; i++) {
        q[i].id = i;
        read(q[i].l, q[i].r);
        ans[i] += sl[q[i].l];
        ans[i] += sr[q[i].r];
    }
    sort(vec.begin(), vec.end());
    nw = 0;
    sort(q + 1, q + m + 1);
    //对格子和询问进行排序 
    for(int i = 1; i <= m; i++) {
        while(nw < vec.size() && vec[nw].l < q[i].l) {
            S2.modify(vec[nw].r);
            ++nw;
        }
        ans[q[i].id] -= S2.query(q[i].r);
    }
    for(int i = 1; i <= m; i++)
        print(ans[i]);
    flush();
    return 0;
}
