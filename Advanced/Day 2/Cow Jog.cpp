//http://www.usaco.org/index.php?page=viewproblem2&cpid=496
#include <bits/stdc++.h>
#define mid (l+r)/2
#define le node+node
#define ri node+node+1
#define ll long long
using namespace std;
const ll inf=1e5+9;

ll n,t,cnt,ans;
ll tree[inf<<2],dp[inf];
pair<ll,ll> a[inf];
map<ll,ll> mp;

void update(ll node,ll l,ll r,ll idx,ll val){

    if(l==r)
        return void(tree[node]=max(tree[node],val) );
    if(idx<=mid)
        update(le,l,mid,idx,val);
    else
        update(ri,mid+1,r,idx,val);
    tree[node]=max(tree[le],tree[ri]);
}

ll query(ll node,ll l,ll r,ll x,ll y){

    if(l>r ||r<x || l>y || x>y)
        return 0;
    if(l>=x && r<=y)
        return tree[node];
    return max(query(le,l,mid,x,y),query(ri,mid+1,r,x,y));
}

int main(){

    freopen("cowjog.in","r",stdin);
    freopen("cowjog.out","w",stdout);

    cin>>n>>t;
    for(ll i=1;i<=n;i++)
        cin>>a[i].first>>a[i].second,mp[a[i].first+a[i].second*t];

    sort(a+1,a+1+n);//sort by starting position
    for(auto &o:mp)
        o.second=++cnt;

    for(ll i=1;i<=n;i++){
        ll val=a[i].first+a[i].second*t;
        dp[i]=query(1,1,cnt,mp[val],cnt)+1;
        update(1,1,cnt,mp[val],dp[i]);
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
}