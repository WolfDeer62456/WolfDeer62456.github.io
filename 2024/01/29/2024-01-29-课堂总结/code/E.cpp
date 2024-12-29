#include"bits/stdc++.h"
using namespace std;
int fa[1000006];
int finds(int u);
void unin(int u,int v)//并查集合并操作
{
    fa[finds(v)]=finds(u);
}
int finds(int u)//查找集合编号操作
{
    if(fa[u]!=u)fa[u]=finds(fa[u]);
    return fa[u];
}
void init(int n)//并查集初始化
{
    for(int i=0;i<=n;i++)fa[i]=i;
}
int a[500005],b[500005];
long long c[500005];
int x[500005],y[500005],ans[500005];
int main()
{
    int n,m,q;
    long long v;
    cin>>n>>m>>q>>v;
    for(int i=0;i<m;i++)scanf("%d%d%lld",&a[i],&b[i],&c[i]);
    for(int i=0;i<q;i++)scanf("%d%d",&x[i],&y[i]);
    int t=62;
    while(t--)
    {
        init(n);
        for(int i=0;i<m;i++)if((c[i]&v)==v)unin(a[i],b[i]);
        //如果满足必须是1的位置都是1 
        for(int i=0;i<q;i++)if(finds(x[i])==finds(y[i]))ans[i]=1;
        v=v+(v&-v);
        //每次让v的最后的1变成0 
        if(v==0)break;
    }
    for(int i=0;i<q;i++)if(ans[i])printf("Yes\n");
    else printf("No\n");
    return 0;
}
