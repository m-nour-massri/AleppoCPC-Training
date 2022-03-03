//https://cses.fi/problemset/task/1143
#include <bits/stdc++.h>
#define le node+node
#define ri node+node+1
#define mid (l+r)/2
using namespace std;
const int inf = 2e5+9;
int n,q,h[inf],tree[inf*4];

int merge(int Left,int Right){
    return max(Left,Right);
}

void build(int node,int l,int r){
    if(l == r){
        tree[node] = h[l];
    }
    else {
        build(le,l,mid);
        build(ri,mid+1,r);
        tree[node] = merge(tree[le],tree[ri]);
    }
}

int queryupdate(int node,int l,int r,int val){
    if(l == r){
        tree[node] -= val;
        return l;
    }
    int ret;
    if(tree[le] >= val)
        ret = queryupdate(le,l,mid,val);
    else
        ret = queryupdate(ri,mid+1,r,val);

    tree[node] = merge(tree[le],tree[ri]);
    return ret;
}

int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>h[i];
    build(1,1,n);
    while(q--){
        int x;
        cin>>x;
        if(x > tree[1])
            cout<<0<<" ";
        else
            cout<<queryupdate(1,1,n,x)<<" ";
    }
}


