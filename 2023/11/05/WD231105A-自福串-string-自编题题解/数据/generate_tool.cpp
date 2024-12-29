#include<bits/stdc++.h>
#define For(i,l,r) for(int i=l;i<=r;i++)
#define Rof(i,l,r) for(int i=l;i>=r;i--)
using namespace std;
inline int input(){int x;return cin>>x,x;}
const int N = 1012345;
int n,a[N];
signed main(){
	ios::sync_with_stdio(false);
	srand(time(NULL));
	freopen("string.in","w",stdout);
	cout<<(n=(999999))<<'\n';
//	For(i,1,n) cout<<i<<' ';	
	For(i,1,n){
		a[i]=rand()%((int)1e9)+1;
		cout<<a[i]<<' ';
	}return 0;
}
