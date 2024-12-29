#include <bits/stdc++.h>
using namespace std;
inline int read(){
    char ch=getchar();int i=0,f=1;
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){i=(i<<1)+(i<<3)+ch-'0';ch=getchar();}
    return i*f;
}
const int N=1e6+50;
int n,a[N],l[N],r[N],st[N],pos[N],top,diff_l[N],diff_r[N],mx[35];
int mxpos[35];

int main(){
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
    n=read(); 
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++){
        while(top&&st[top]<=a[i])top--;
        l[i]=pos[top]+1;
        st[++top]=a[i];pos[top]=i;
    }
    top=0; pos[top]=n+1;
    for(int i=n;i>=1;i--){
        while(top&&st[top]<a[i]) top--;
        r[i]=pos[top]-1;
        st[++top]=a[i];pos[top]=i;
    }
    for(int i=1;i<=n;i++){
        int p=0;
        for(int j=0;(1ll<<j)<=a[i];j++){
            if((1ll<<j)&a[i])mx[j]=max(mx[j],i);
            else p=max(p,mx[j]);
        }
        diff_l[i]=p;
    }
    fill(mx,mx+32+1,n+1);
    for(int i=n;i>=1;i--) {
        int p=n+1;
        for(int j=0;(1ll<<j)<=a[i];j++) {
            if((1ll<<j)&a[i]) mx[j]=min(mx[j],i);
            else p=min(p,mx[j]);
        }
        diff_r[i]=p;
    }
    long long ans=0;
    for(int i=1;i<=n;i++) {
        if(diff_l[i]>=l[i])
            ans+=1ll*(diff_l[i]-l[i]+1)*(r[i]-i+1);
        if(diff_r[i]<=r[i])
            ans+=1ll*(r[i]-diff_r[i]+1)*(i-l[i]+1);
        if(diff_l[i]>=l[i]&&diff_r[i]<=r[i])
            ans-=1ll*(r[i]-diff_r[i]+1)*(diff_l[i]-l[i]+1);
    }
    cout<<ans<<endl;
}

