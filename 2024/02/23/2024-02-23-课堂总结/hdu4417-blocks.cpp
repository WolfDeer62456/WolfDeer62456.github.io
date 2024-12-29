#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
int L[maxn],R[maxn],belong[maxn];
int a[maxn],temp[maxn],n,m;

void build()
{
    int t=sqrt(n);
    int num=n/t;
	if(n%num) num++;
    for(int i=1;i<=num;i++)
        L[i]=(i-1)*t+1,R[i]=i*t;
    R[num]=n;
    for(int i=1;i<=n;i++)
        belong[i]=(i-1)/t+1;
    for(int i=1;i<=num;i++)
        sort(temp+L[i],temp+1+R[i]);                            //Ã¿¿éÅÅÐò
}

int query(int l,int r,int h)
{
    int ans=0;
    if(belong[l]==belong[r])
	{
        for(int i=l;i<=r;i++)
            if(a[i]<=h) ans++;
    }
    else
	{
        for(int i=l;i<=R[belong[l]];i++)                         //×ó¶Ë 
            if(a[i]<=h) ans++;
        for(int i=belong[l]+1;i<belong[r];i++)                   //ÖÐ¼ä 
            ans+=upper_bound(temp+L[i],temp+R[i]+1,h)-temp-L[i];
        for(int i=L[belong[r]];i<=r;i++)                         //ÓÒ¶Ë 
            if(a[i]<=h) ans++;
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d",&T);
    for(int cas=1;cas<=T;cas++)
	{
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
		{
            scanf("%d",&a[i]);
            temp[i]=a[i];
        }
        build();
        printf("Case %d:\n",cas);
        while(m--)
		{
            int l,r,h; 
            scanf("%d%d%d",&l,&r,&h);
            printf("%d\n",query(++l,++r,h));
        }
    }
    return 0;
}
