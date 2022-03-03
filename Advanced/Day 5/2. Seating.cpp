//http://www.usaco.org/index.php?page=viewproblem2&cpid=231
//USACO 2013 January Contest, Gold
//Problem 3. Seating
//fingers search
#include <bits/stdc++.h>
#define le node+node
#define ri node+node+1
#define mid (l+r)/2
using namespace std;
const int inf=5e5+9;
struct N{
    int mx,l,r,sz,lazy;
}tree[inf<<2];

int n,q,ans;

N merge(N Left,N Right){

    N ret;
    ret.mx=max(Left.r+Right.l,max(Left.mx,Right.mx));
    ret.l=Left.l+Right.l*(Left.l==Left.sz);
    ret.r=Right.r+Left.r*(Right.r==Right.sz);
    ret.sz=Left.sz+Right.sz;
    ret.lazy=-1;
    return ret;
}

void push(int node,int l,int r){

    if(tree[node].lazy==-1)
        return ;
    tree[node].mx=tree[node].l=tree[node].r=(r-l+1)*tree[node].lazy;
    if(l!=r)
        tree[le].lazy=tree[ri].lazy=tree[node].lazy;//,push(le,l,mid),push(ri,mid+1,r);
    tree[node].lazy=-1;
}

void build(int node,int l,int r){

    if(l==r)
        return void(tree[node]={1,1,1,1,-1});

    build(le,l,mid);
    build(ri,mid+1,r);
    tree[node]=merge(tree[le],tree[ri]);
}

void update(int node,int l,int r,int x,int y,int val){

    push(node,l,r);
    if(l>r || r<x || l>y)
        return ;

    if(l>=x && r<=y){
        tree[node].lazy=val;
        push(node,l,r);
        return;
    }
    update(le,l,mid,x,y,val);
    update(ri,mid+1,r,x,y,val);
    tree[node]=merge(tree[le],tree[ri]);
}

int query(int node,int l,int r,int val){

    push(node,l,r);
    if(l> r)
        return 1e9+9;
    if(tree[node].mx<val)
        return 1e9+9;

    if(tree[node].mx==val && val==tree[node].sz==val)
        return l;

    int ret;
    //to get the correct information of the left and the right childs
    push(le,l,mid);
    push(ri,mid+1,r);

    if(tree[le].mx>=val)
        ret = query(le,l,mid,val);

    else if(tree[le].r+tree[ri].l>=val )
             ret=mid-tree[le].r+1;
    else
        ret= query(ri,mid+1,r,val);

    tree[node]=merge(tree[le],tree[ri]);
    return ret;
}

int main(){

    freopen("seating.in","r",stdin);
    freopen("seating.out","w",stdout);

    cin>>n>>q;
    build(1,1,n);

    while(q--){
        char type;
        int x,y;
        cin>>type;
        if(type=='A'){
            cin>>x;
            int cur=query(1,1,n,x);
            //cout<<cur<<endl;
            if(cur>1e9)
                ans++;
            else
                update(1,1,n,cur,cur+x-1,0);
        }
        else {
            cin>>x>>y;
            update(1,1,n,x,y,1);
        }
    }
    cout<<ans<<endl;
}