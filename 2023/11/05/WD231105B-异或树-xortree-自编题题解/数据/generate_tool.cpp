#include<bits/stdc++.h>
#include<random>
#define For(i,l,r) for(int i=l;i<=r;i++)
#define Rof(i,l,r) for(int i=l;i>=r;i--)
#define rd(l,r) (rd1()%(r-l+1)+l)
using namespace std;
#define int long long
inline int input(){int x;return cin>>x,x;}
const int N = 100000;
int n,m,a[N],fa[N],R=10000;

signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	freopen("xortree10.in","w",stdout);
	mt19937_64 rd1(time(0));

	cout<<(n=100000)<<'\n';
	For(i,1,n) cout<<(rd(1,100000))<<' ';cout<<'\n';
	For(i,2,n) cout<<(rd(1,i-1))<<' ';cout<<'\n';
	cout<<(m=100000)<<'\n';
	while(m--){
		int k=rd(1,5);cout<<k<<' ';
		if(k==1){
			cout<<(rd(1,n))<<'\n';
		}else
		if(k==2){
			cout<<(rd(1,n))<<' '<<(rd(1,n))<<' '<<(rd(1,100000))<<'\n';
		}else
		if(k==3){
			cout<<(rd(1,n))<<' '<<(rd(1,100000))<<'\n';
		}else
		if(k==4){
			cout<<(rd(1,n))<<' '<<(rd(1,n))<<'\n';
		}else
		if(k==5){
			cout<<(rd(1,n))<<'\n';
		}
	}
	return 0;
}
