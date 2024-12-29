#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
string a[1000005],b[1000005];
struct Hash{
    vector <long long> pre1,pre2,fac1,fac2;
    long long mod1=1e9+9,mod2=998244353,base=129;
    int n;
    void init(int len,string &s){
        n=len;
        pre1.resize(n+2),pre2.resize(n+2),fac1.resize(n+2),fac2.resize(n+2);
        fac1[0]=fac2[0]=1,pre1[0]=pre2[0]=0;
        for(int i=1;i<=n;i++) fac1[i]=fac1[i-1]*base%mod1,fac2[i]=fac2[i-1]*base%mod2;
        for(int i=1;i<=n;i++) pre1[i]=(pre1[i-1]*base+s[i-1])%mod1,pre2[i]=(pre2[i-1]*base+s[i-1])%mod2;
    }
    long long query(int l,int r){
        long long val1=((pre1[r]-pre1[l-1]*fac1[r-l+1])%mod1+mod1)%mod1;
        long long val2=((pre2[r]-pre2[l-1]*fac2[r-l+1])%mod2+mod2)%mod2;
        return val1*2000000000LL+val2;
    }
}ha[1000005],hb[1000005];
long long va1[1000005],va2[1000005],vb1[1000005],vb2[1000005];
int ida[1000005],idb[1000005],n,m,pa,pb,in[2000005],out[2000005];
vector <int> can;
unordered_map <long long,int> mp1,mp2;
vector <pair<int,int>> v[2000005];
void dfs(int x,int fr){
	//找欧拉回路 
    while(v[x].size()) {
        auto temp = v[x].back();
        v[x].pop_back();
        dfs(temp.first, temp.second);
    }if(fr) can.push_back(fr);
}
int check(int pos){
	//对于偏移量pos查询是否存在欧拉回路 
    mp1.clear(),mp2.clear();
    int c1=0,c2=0;
    for(int i=1;i<=n;i++){
        va1[i]=ha[i].query(1,pos),va2[i]=ha[i].query(pos+1,m);
        if(!mp1.count(va1[i])) mp1[va1[i]]=++c1;
        //计算出每个子串的哈希值并放到map中 
    }
    c2=c1;
    for(int i=1;i<=n;i++) if(!mp2.count(va2[i])) mp2[va2[i]]=++c2;
    for(int i=1;i<=c2;i++) v[i].clear(),in[i]=out[i]=0;
    for(int i=1;i<=n;i++) v[mp1[va1[i]]].push_back({mp2[va2[i]],i}),out[mp1[va1[i]]]++,in[mp2[va2[i]]]++;
    //连边 
    for(int i=1;i<=n;i++){
        vb1[i]=hb[i].query(1,m-pos),vb2[i]=hb[i].query(m-pos+1,m);
        if(!mp2.count(vb1[i])) return 0;
        if(!mp1.count(vb2[i])) return 0;
        v[mp2[vb1[i]]].push_back({mp1[vb2[i]],i+n}),out[mp2[vb1[i]]]++,in[mp1[vb2[i]]]++;
        //连边 
    }
    for(int i=1;i<=c2;i++) if(in[i]!=out[i]) return 0;
    //判断是否存在欧拉回路 
    pa=0,pb=0,can.clear(),dfs(1,0);
    if(can.size()!=n*2) return 0;
    while(can.size()){
        if(can.back()<=n) ida[++pa]=can.back();
        else idb[++pb]=can.back()-n;
        can.pop_back();
    }
    //找到欧拉回路并存储 
    return 1;
}
void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i],ha[i].init(m,a[i]),ida[i]=i;
    for(int i=1;i<=n;i++) cin>>b[i],hb[i].init(m,b[i]),idb[i]=i;
    for(int i=1;i<=n;i++) va1[i]=ha[i].query(1,m),vb1[i]=hb[i].query(1,m);
    sort(ida+1,ida+n+1,[&](int x,int y){
        return va1[x]<va1[y];
    });
    sort(idb+1,idb+n+1,[&](int x,int y){
        return vb1[x]<vb1[y];
    });
    int fl=1;
    for(int i=1;i<=n;i++) if(va1[ida[i]]!=vb1[idb[i]]) fl=0;
    if(fl){
        for(int i=1;i<=n;i++) cout<<ida[i]<<" ";
        cout<<'\n';
        for(int i=1;i<=n;i++) cout<<idb[i]<<" ";
        cout<<'\n';
        return;
    }
    for(int i=1;i<m;i++){
        if(check(i)){
            for(int j=1;j<=n;j++) cout<<ida[j]<<" ";
            cout<<'\n';
            for(int j=1;j<=n;j++) cout<<idb[j]<<" ";
            cout<<'\n';
            return;
        }
    }
    cout<<"-1\n";
}
int main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int T = 1, kase = 0;
    cin >> T;
    while (T--) solve();
    return 0;
}
