//https://oj.uz/problem/view/BOI11_grow
#include <bits/stdc++.h>
#define ll long long
#define le node+node
#define ri node+node+1
#define mid (l+r)/2
using namespace std;
const ll inf = 1e5+9;
ll n,q,h[inf];
ll tree[inf<<2],lazy[inf<<2];
 
void build(ll node,ll l,ll r){
 
    if(l == r)
        return void(tree[node] = h[l]);
    build(le,l,mid);
    build(ri,mid+1,r);
    tree[node] = max(tree[le],tree[ri]);
}
 
void push(ll node,ll l,ll r){
    if(lazy[node] == 0)return;
    tree[node] += lazy[node];
    if(l != r)
        lazy[le] += lazy[node],lazy[ri] += lazy[node];
    lazy[node] = 0;
}
 
void update(ll node,ll l,ll r,ll x,ll y){
    push(node,l,r);
    if(l>r || r<x || l>y || x>y)
        return ;
    if(l>=x && r<=y){
        lazy[node] = 1;
        push(node,l,r);
        return ;
    }
    update(le,l,mid,x,y);
    update(ri,mid+1,r,x,y);
    tree[node] = max(tree[le],tree[ri]);
}
 
ll queryval(ll node,ll l,ll r,ll val){
    push(node,l,r);
    if(l == r)
        return l;
    int ret ;
    push(le,l,mid);
    push(ri,mid+1,r);
    if(tree[le] < val)
        ret = queryval(ri,mid+1,r,val);
    else
        ret = queryval(le,l,mid,val);
    tree[node] = max(tree[le],tree[ri]);
    return ret;
}
ll queryidx(ll node,ll l,ll r,ll idx){
 
    push(node,l,r);
    if(l == r)
        return tree[node];
    int ret;
    push(le,l,mid);
    push(ri,mid+1,r);
    if( idx > mid)
        ret = queryidx(ri,mid+1,r,idx);
    else
        ret = queryidx(le,l,mid,idx);
    tree[node] = max(tree[le],tree[ri]);
    return ret;
}
 
int main(){
    cin>>n>>q;
    for(ll i=1;i<=n;i++)
        cin>>h[i];
    sort(h+1,h+1+n);
    build(1,1,n);
    while(q--){
        char s;
        ll x,y;
        cin>>s>>x>>y;
        if(s == 'F'){
            swap(x,y);
            if(tree[1]<x)continue;
            ll l = queryval(1,1,n,x);
            ll r = min(n,l + y-1);
            if(r == n){
                update(1,1,n,l,r);
                continue;
            }
 
            ll valr = queryidx(1,1,n,r);
            ll d = queryval(1,1,n,valr);
            ll f = (tree[1] < valr+1?n+1:queryval(1,1,n,valr+1))-1;
            ll sz = r - d+1;
            ///cout<<l<<" "<<r<<" "<<d<<" "<<f<<"  "<<l<<" "<<d-1<<"    "<<f-sz+1<<" "<<f<<endl;
            update(1,1,n,l,d-1);
            update(1,1,n,f-sz+1,f);
        }
        else {
            if(tree[1] < x){
                cout<<0<<endl;
                continue;
            }
            ll l = queryval(1,1,n,x);
            ll r = (tree[1]<y+1?n+1:queryval(1,1,n,y+1));
            ///cout<<l<<" "<<r<<endl;
            cout<<r-l<<endl;
        }
    }
}
 