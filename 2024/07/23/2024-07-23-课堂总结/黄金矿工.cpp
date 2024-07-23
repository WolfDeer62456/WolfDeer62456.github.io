#include<bits/stdc++.h>
#define f(i,x,y) for(int i=x;i<=y;i++)
#define df(i,x,y) for(int i=x;i>=y;i--)
using namespace std;
const int N=2e6+9,B=80;
int n,m,k,x[N],v[N],y,f[N],g[N],op[N],q[N],ct[N],da[N],di[N];
void A(int t)
{
	y=x[t],t=v[t];
	if(y<=B)df(i,k,y*t)f[i]=max(f[i-y*t]+t,f[i]);
	else df(i,k/B,t)g[i]=min(g[i-t]+y*t,g[i]);
}
signed main()
{
	freopen("x.txt","r",stdin);//freopen("miner.in","r",stdin);freopen("miner.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	f(i,1,n)scanf("%d%d",&x[i],&v[i]);
	f(i,1,k/B)g[i]=N;
	f(i,1,m)scanf("%d%d",&op[i],&q[i]),di[q[i]]+=(op[i]==1);
	f(i,1,n)if(!di[i]&&x[i]>6e3)if(ct[v[i]]*v[i]>=k/6e3)di[i]=1;else ++ct[v[i]];
	f(i,1,n)if(!di[i])A(i);
	df(i,m,1)
	if(op[i]==1)A(q[i]);
	else df(j,k/B,0)if(g[j]<=q[i])da[i]=max(j+f[q[i]-g[j]],da[i]);
	f(i,1,m)if(op[i]==2)cout<<da[i]<<'\n';
	return 0;
}
