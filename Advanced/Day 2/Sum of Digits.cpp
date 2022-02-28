//https://www.spoj.com/problems/CPCRC1C/
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int inf=1e3+9,I=22;
ll dp[I][inf][2];
vector<ll> cur;
 
ll solve(ll pos,ll sum,bool smaller){
 
    if(pos==cur.size())
        return sum;
 
    ll &ret=dp[pos][sum][smaller];
    if(ret!=-1)
        return ret;
 
    ret=0;
    for(ll i=0;i<=(smaller?9:cur[pos]);i++)
        ret+=solve(pos+1,sum+i,smaller|(i<cur[pos]));
 
    return ret;
}
 
ll rec(ll x){
    cur.clear();
    while(x)
        cur.push_back(x%10),x/=10;
 
    cur.push_back(0);
    reverse(cur.begin(),cur.end());
    memset(dp,-1,sizeof(dp));
 
    return solve(1,0,0);
}
 
int main(){
 
    while(1){
        ll a,b;
        cin>>a>>b;
        if(a==-1)
            return 0;
        if(a==0)
            a++;
 
        cout<<rec(b)-rec(a-1)<<endl;
    }
} 