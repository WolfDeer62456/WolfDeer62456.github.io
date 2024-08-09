#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<vector>
#define _for(i,n) for(int i=1;i<=n;i++)
#define N 1012345
#define int long long
using namespace std;
inline int input(){
	char c;bool f=false;while(!isdigit(c=getchar()))f=c=='-';int x=c^48;
	while(isdigit(c=getchar())){x=(((x<<2)+x)<<1)+(c^48);}return f?-x:x;
} 
int n,a[N],ans;

#define ls p<<1
#define rs p<<1|1
struct TR{
	int max,huo,pos;
}tr[N<<2|3];

void pushup(int p){
	tr[p].max=max(tr[ls].max,tr[rs].max);
	tr[p].huo=tr[ls].huo|tr[rs].huo;
	tr[p].pos=tr[ls].max==tr[p].max?tr[ls].pos:tr[rs].pos;
}

void build(int p,int l,int r){
	if(l==r){
		tr[p].max=tr[p].huo=a[l];
		tr[p].pos=l;
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(p);
}

struct B{
	int x,id;
	bool operator<(const B y)const{return x<y.x;}
}b[N];
inline B ask_max(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R) return {tr[p].max,tr[p].pos};
	B res={0,0};
	int mid=(l+r)>>1;
	if(L<=mid){
		B s=ask_max(ls,l,mid,L,R);
		if(s.x>res.x) res=s;
	}	
	if(R>mid){
		B s=ask_max(rs,mid+1,r,L,R);
		if(s.x>res.x) res=s;
	}
	return res;
}

inline int ask_huo(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R) return tr[p].huo;
	int mid=(l+r)>>1;
	int res=0;
	if(L<=mid) res=(res|ask_huo(ls,l,mid,L,R));
	if(R>mid) res=(res|ask_huo(rs,mid+1,r,L,R));
	return res;
}

void search(int L,int R){
	if(L>=R) return;
	//找到区间最大值位置 
	B maxnum=ask_max(1,1,n,L,R);
	int l=maxnum.id,r=maxnum.id;
	int pos=maxnum.id;
//	printf("maxnum=a[%d]=%d\n",pos,maxnum.x);
//	printf("%d %d %d\n",L,R,pos);
	//寻找左侧首个满足 g(T)>f(T) 的位置
	for(int i=24;i>=0;i--){
		if(l-(1<<i)<L) continue;
		if(ask_huo(1,1,n,l-(1<<i),pos)>maxnum.x) continue;
		else l=l-(1<<i);
	}
	//寻找右侧首个满足 g(T)>f(T) 的位置
	for(int i=24;i>=0;i--){
		if(r+(1<<i)>R) continue;
		if(ask_huo(1,1,n,pos,r+(1<<i))>maxnum.x) continue;
		else r=r+(1<<i);
	}
	ans+=(l-L)*(R-pos+1)+(R-r)*(pos-L+1)-(R-r)*(l-L);
	search(L,pos-1);search(pos+1,R);
}

void solve(){
	_for(i,n) b[i]={a[i],i};
	sort(b+1,b+n+1);
	search(1,n);
}

signed main(){
	freopen("string.in","r", stdin);
	freopen("string.out", "w", stdout);
	n=input();
	_for(i,n) a[i]=input();
	build(1,1,n);
	solve();
	printf("%lld",ans);
	return 0;
}
