//https://www.spoj.com/problems/NOCHANGE/
#include <bits/stdc++.h>
using namespace std;
const int inf=1e5+9;
bool dp[inf];
int val[12],sum[12];
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=k;i++)
        cin>>val[i],sum[i]=sum[i-1]+val[i];
 
 
    dp[0]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=k;j++)
            if(i>=sum[j])
                dp[i]|=dp[i-sum[j]];
 
    cout<<(dp[n]?"YES\n":"NO\n");
}
 
