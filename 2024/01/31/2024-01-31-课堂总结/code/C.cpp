#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
long long Read() {
    long long x = 0, f = 1; char ch = getchar();
    while(!isdigit(ch) && ch != '-')  ch = getchar();
    if(ch == '-')  f = -1, ch = getchar();
    while(isdigit(ch))  x = x * 10 + ch - '0', ch = getchar();
    return x * f;  
}

const int N = 5e5 + 5;
int n, a[N];
long long k, sum, sum1, sum2;
multiset<int> s1, s2;

void getmid() {
    while(s1.size() > s2.size() + 1) {
        auto it = s1.end();
        --it;
        int val = *it;
        sum1 -= val, sum2 += val;
        s2.insert(val);
        s1.erase(it);
    }
    while(s2.size() >= s1.size() + 1) {
        auto it = s2.begin();
        int val = *it;
        sum1 += val, sum2 -= val;
        s1.insert(val);
        s2.erase(it);
    }
    //动态维护中位数 
    if(!s1.size())
        return sum = 0, void();
    auto it = s1.end();
    --it;
    int mid = *it;
    sum = 1ll * mid * s1.size() - sum1 + sum2 - 1ll * mid * s2.size();
}

void Add(int val) {
    if(s2.empty() || val < *s2.begin())
        s1.insert(val), sum1 += val;
    else
        s2.insert(val), sum2 += val;
    getmid();
}

void Del(int val) {
    auto it = s1.find(val);
    if(it != s1.end())
        s1.erase(it), sum1 -= val;
    else
        s2.erase(s2.find(val)), sum2 -= val;
    getmid();
}

signed main() {
    int T = Read();
    while(T--) {
        sum = sum1 = sum2 = 0;
        s1.clear(), s2.clear();
        n = Read(), k = Read();
        int ans = 0;
        for (int i = 1; i <= n; i++)
            a[i] = Read() - i;
        int l = 1;
        for (int r = 1; r <= n; r++) {
            Add(a[r]);
            while(sum > k)
                Del(a[l++]);
            ans = max(ans, r - l + 1);
        }
        cout << ans << endl;
    }
    return 0;
}
