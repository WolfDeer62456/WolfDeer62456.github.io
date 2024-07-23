#include<bits/stdc++.h>
#define For(i,l,r) for(int i=l;i<=r;i++)
#define Rof(i,l,r) for(int i=l;i>=r;i--)
using namespace std;
#define int long long
#define N 101234
bool ST;
vector<int> ft[N];
int n,m,a[N],root=1;

int son[N],siz[N],dep[N],fa[N];
void dfs_son(int x,int father){
	siz[x]=1,dep[x]=dep[father]+1,fa[x]=father;
	for(auto y:ft[x]){
		if(y==father) continue;
		dfs_son(y,x);
		siz[x]+=siz[y];
		son[x]=siz[son[x]]>=siz[y]?son[x]:y;
	}
}

int top[N],w[N],id[N],cnt;
void dfs_top(int x,int tp){
	top[x]=tp,id[x]=++cnt,w[cnt]=a[x];
	if(!son[x]) return;
	dfs_top(son[x],tp);
	for(auto y:ft[x]){
		if(y==fa[x]||y==son[x]) continue;
		dfs_top(y,y);
	}
}

#define mid (l+r>>1)
#define ls p<<1
#define rs p<<1|1
struct TR{
	int sum,add,siz;
}tr[N<<2|3];

void pushup(int p){tr[p].sum=tr[ls].sum+tr[rs].sum;}

void build(int p,int l,int r){
	tr[p]={0,0,r-l+1};
	if(l==r){tr[p].sum=w[l];return;}
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(p); 
}

void pushdown(int p){
	if(tr[p].add){
		tr[ls].sum+=tr[ls].siz*tr[p].add;
		tr[rs].sum+=tr[rs].siz*tr[p].add;
		tr[ls].add+=tr[p].add;
		tr[rs].add+=tr[p].add;
		tr[p].add=0;
	}
}

void update(int p,int l,int r,int L,int R,int k){
	if(L<=l&&r<=R){
		tr[p].sum+=tr[p].siz*k;
		tr[p].add+=k;return;
	}
	pushdown(p);
	if(L<=mid) update(ls,l,mid,L,R,k);
	if(R>mid) update(rs,mid+1,r,L,R,k);
	pushup(p);
}

inline int ask(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R) return tr[p].sum;
	pushdown(p);
	int res=0;
	if(L<=mid) res+=ask(ls,l,mid,L,R);
	if(R>mid) res+=ask(rs,mid+1,r,L,R);
	return res;
}

void update_path(int x,int y,int k){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,1,n,id[top[x]],id[x],k);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	update(1,1,n,id[y],id[x],k);
}

void update_tree(int x,int k){
	if(id[x]==id[root]) update(1,1,n,id[1],id[1]+siz[1]-1,k);else//x为根节点 
	if(id[x]<id[root]&&id[root]<=id[x]+siz[x]-1){//root在x子树中 
		update(1,1,n,id[1],id[1]+siz[1]-1,k);//先加上总数
		int y=root;//从root开始跳 
		while(fa[top[y]]!=x && top[y]!=top[x])y=fa[top[y]];
		if(fa[top[y]]==x) y=top[y];//root在x的轻链上 
		if(top[y]==top[x]) y=son[x];//root在x的重链上 
		update(1,1,n,id[y],id[y]+siz[y]-1,-k);
	}
	else{update(1,1,n,id[x],id[x]+siz[x]-1,k);}//root不在x子树中
}

int ask_path(int x,int y){
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res+=ask(1,1,n,id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	return res+ask(1,1,n,id[y],id[x]);
}

int ask_tree(int x){
	if(id[x]==id[root]) return ask(1,1,n,id[1],id[1]+siz[1]-1);else
	if(id[x]<=id[root]&&id[root]<=id[x]+siz[x]-1){
		int res=ask(1,1,n,id[1],id[1]+siz[1]-1); 
		int y=root;
		while(fa[top[y]]!=x && top[y]!=top[x])y=fa[top[y]];
		if(fa[top[y]]==x) y=top[y];
		if(top[y]==top[x]) y=son[x];
		return res-ask(1,1,n,id[y],id[y]+siz[y]-1);
	}else{return ask(1,1,n,id[x],id[x]+siz[x]-1);}
}

bool ED;
signed main(){
	string str("xortree10");
	freopen((str+".in").c_str(),"r",stdin);
	freopen((str+".out").c_str(),"w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cerr<<abs(&ST-&ED)/1024./1024.<<"MB\n";
	cin>>n;For(i,1,n) cin>>a[i];
	For(i,1,n-1){
		int x=i+1,y;cin>>y;
		ft[x].push_back(y);
		ft[y].push_back(x);
	}
	dfs_son(root,0);
	dfs_top(root,root);
	build(1,1,n);
	cin>>m;
	while(m--){
		int k;cin>>k;
		if(k==1){
			cin>>root;
		}else
		if(k==2){
			int x,y,v;cin>>x>>y>>v;
			update_path(x,y,v);
		}else
		if(k==3){
			int x,v;cin>>x>>v;
			update_tree(x,v); 
		}else
		if(k==4){
			int x,y;cin>>x>>y;
			cout<<ask_path(x,y)<<'\n';
		}else
		if(k==5){
			int x;cin>>x;
			cout<<ask_tree(x)<<'\n';
		}
	}
	return 0;
}
