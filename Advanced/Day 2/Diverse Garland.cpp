//https://codeforces.com/contest/1108/problem/D
#include <bits/stdc++.h>
using namespace std;
const int inf=2e5+9;
int dp[inf][7],n,a[inf],par[inf][6];
map<char,int> mp;
string ss;
vector<int> v;
int solve(int pos,int last){
 
    if(pos==n+1)
        return 0;
 
    int &ret=dp[pos][last];
    if(ret!=-1)
        return ret;
        ret=1e9+9;
 
    for(int i=1;i<=3;i++){
        if(i==last)
            continue;
        int x=solve(pos+1,i)+(a[pos]!=i );
        if(x<ret)
            ret=x,par[pos][last]=i;
 
    }
    return ret;
}
 
void get(int pos,int last){
 
    if(pos==n+1)
        return ;
 
    v.push_back(par[pos][last]);
    get(pos+1,par[pos][last]);
}
 
int main(){
 
    cin>>n;
    cin>>ss;
 
    mp['G']=1,mp['R']=2,mp['B']=3;
    for(int i=1;i<=n;i++)
        a[i]=mp[ss[i-1]];
 
    memset(dp,-1,sizeof(dp));
    int ans=1e9+9,id;
    for(int i=1;i<=3;i++){
        int x=solve(2,i)+(a[1]!=i);
        if(x<ans)
            ans=x,id=i;
    }
 
    cout<<ans<<endl;
    v.push_back(id);
    get(2,id);
    for(auto o:v)
        if(o==1)
        cout<<'G';
        else if(o==2)
            cout<<'R';
        else cout<<'B';
    cout<<endl;
}
 