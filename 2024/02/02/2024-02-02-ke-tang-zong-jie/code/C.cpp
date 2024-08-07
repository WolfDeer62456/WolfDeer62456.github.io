#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
int Read() {
	int x = 0, f = 1; char ch = getchar();
	while(!isdigit(ch) && ch != '-')  ch = getchar();
	if(ch == '-')  f = -1, ch = getchar();
	while(isdigit(ch))  x = x * 10 + ch - '0', ch = getchar();
	return x * f;  
}

const int N = 1e5 + 5, Mod = 998244353;

struct SegTree {
	int sum[N << 2], mulv[N << 2];
	void pushup(int o) {
		sum[o] = sum[o << 1] + sum[o << 1 | 1];
		if(sum[o] >= Mod)
			sum[o] -= Mod;
	}
	void pushr(int o, int val) {
		sum[o] = 1ll * sum[o] * val % Mod;
		mulv[o] = 1ll * mulv[o] * val % Mod;
	}
	void pushdown(int o) {
		pushr(o << 1, mulv[o]);
		pushr(o << 1 | 1, mulv[o]);
		mulv[o] = 1;
	}
	void build(int o, int l, int r) {
		mulv[o] = 1, sum[o] = 0;
		if(l == r)
			return;
		int mid = (l + r) >> 1;
		build(o << 1, l, mid);
		build(o << 1 | 1, mid + 1, r);
	}
	void modify_mul(int o, int l, int r, int nl, int nr) {
		if(nl <= l && r <= nr)
			return pushr(o, 2);
		int mid = (l + r) >> 1;
		pushdown(o);
		if(nl <= mid)
			modify_mul(o << 1, l, mid, nl, nr);
		if(mid < nr)
			modify_mul(o << 1 | 1, mid + 1, r, nl, nr);
		pushup(o);
	}
	void modify_add(int o, int l, int r, int pos, int val) {
		if(l == r)
			return sum[o] += val, void();
		int mid = (l + r) >> 1;
		pushdown(o);
		if(pos <= mid)
			modify_add(o << 1, l, mid, pos, val);
		else
			modify_add(o << 1 | 1, mid + 1, r, pos, val);
		pushup(o);
	}
	int query(int o, int l, int r, int nl, int nr) {
		if(nl > nr)
			return 0;
		if(nl <= l && r <= nr)
			return sum[o];
		int mid = (l + r) >> 1, res = 0;
		pushdown(o);
		if(nl <= mid)
			res = res + query(o << 1, l, mid, nl, nr);
		if(mid < nr)
			res = res + query(o << 1 | 1, mid + 1, r, nl, nr);
		return (res >= Mod) ? res - Mod : res;
	}
}s[2];

vector<array<int, 3>> seg;

bool cmp(array<int, 3> x, array<int, 3> y) {
	return x[1] < y[1];
}

signed main() {
	int T = Read();
	while(T--) {
		int n = Read();
		s[0].build(1, 1, n + 1);
		s[1].build(1, 1, n + 1);
		seg.resize(n + 1);
		for (int i = 1; i <= n; i++)
			seg[i][0] = Read(), seg[i][1] = Read(), seg[i][2] = Read();
		sort(seg.begin() + 1, seg.end(), cmp);
		s[0].modify_add(1, 1, n + 1, 1, 1);
		s[1].modify_add(1, 1, n + 1, 1, 1);
		//初始化不选是一种 
		int Ans = 1;
		for(int i = 1; i <= n; i++) {
			int l = 1, r = i - 1, ans = 0;
			while(l <= r) {
				int mid = (l + r) >> 1;
				if(seg[mid][1] < seg[i][0])
					ans = mid, l = mid + 1;
				else
					r = mid - 1;
			}
			//找到最后一个满足r_j<l_i的线段
			s[seg[i][2] ^ 1].modify_mul(1, 1, n + 1, 1, ans + 1);
			int val = s[seg[i][2] ^ 1].query(1, 1, n + 1, 1, ans + 1);
			val = val * 499122177ll % Mod;
			//除以2 
			s[seg[i][2]].modify_add(1, 1, n + 1, i + 1, val);
			Ans = Ans + val;
			if(Ans >= Mod)
				Ans -= Mod;
		}
		printf("%d\n", Ans);
	}
	return 0;
}
