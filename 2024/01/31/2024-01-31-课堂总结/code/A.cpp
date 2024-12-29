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
const int N = 2e6 + 5;
int n, a[N];
template<int base, int Mod>
struct Hash {
    int pw[N], val[N];
    void init() {
        pw[0] = 1;
        for (int i = 1; i <= n; i++) {
            pw[i] = 1ll * pw[i - 1] * base % Mod;
            val[i] = (1ll * val[i - 1] * base + a[i]) % Mod;
        }
    }
    int query(int l, int r) {
        int p = (val[r] - 1ll * val[l - 1] * pw[r - l + 1]) % Mod;
        if(p < 0)
            p += Mod;
        return p;
    }
    int Get(int l, int r, int k) {
    	//[1,l-1]合法且[1,r]不合法，二分找第一个产生不合法的位置 
        int L = l;
        int ans = r + 1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            int val1 = query(L, mid) - query(L - k, mid - k), val2 = query(k + 1, mid - L + 1 + k) - query(1, mid - L + 1);
            if(val1 < 0)
                val1 += Mod;
            if(val2 < 0)
                val2 += Mod;
            if(val1 != val2)
                ans = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        return ans;
    }
    int solve(int k) {
    	//检查每一段是否满足条件 
        int las = query(k + 1, 2 * k), diff = las - query(1, k);
        if(diff < 0)
            diff += Mod;
        for (int i = 3 * k; i <= n; i += k) {
            int l = i - k + 1, r = i;
            int nw = query(l, r);
            if((nw - las - diff) % Mod != 0)
                return Get(l, r, k);
            las = nw;
        }
        //检查最后剩下的长度不足k的一段 
        return Get((n / k) * k + 1, n, k);
    }
};

Hash<2333, 1000000009> H;

int NUM(int x) {
    if(x >= '0' && x <= '9')
        return x - '0';
    if(x >= 'a' && x <= 'z')
        return x - 'a' + 10;
    if(x >= 'A' && x <= 'Z')
        return x - 'A' + 36;
}
char s[55];
int ans[N];
signed main() {
    n = Read();
    for (int i = 1; i <= n; i++) {
        scanf("%s", s);
        int len = strlen(s);
        for (int j = 0; j < len; j++)
            a[i] = a[i] * 62 + NUM(s[j]);
    }
    H.init();
    for (int k = 1; 2 * k + 1 <= n; k++) {
        int r = H.solve(k);
        ++ans[2 * k + 1], --ans[r];
    }
    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
        if(ans[i])
            putchar('1');
        else
            putchar('0');
    }
    return 0;
}
