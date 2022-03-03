//
//#include <bits/stdc++.h>
//using namespace std;
//int a[1234];
//
//bool cmp(pair<int,int> x,pair<int,int> y){//decreasing
//    //first decreasing
//    //second increasing
//
//    if(x.first > y.first)
//        return 1;
//    else if(x.first < y.first)
//        return 0;
//    else {
//
//    }
//}
//
//int main(){
//    int n;
//    cin>>n;
//    for(int i=0;i<n;i++)
//        cin>>a[i];
//    sort(a,a+n,cmp);
//    for(int i=0;i<n;i++)
//        cout<<a[i]<<" ";
//    cout<<endl;
//}


#include <bits/stdc++.h>
#define le node+node
#define ri node+node+1
#define mid (l+r)/2
using namespace std;
const int inf = 1e5+9;
int n,q,tree[inf*4],lazy[inf*4],a[inf];

int merge(int Left,int Right){
    return Left+Right;
}

void build(int node,int l,int r){
    lazy[node] = 0;
    if(l == r){
          tree[node] = a[l];
    }
    else {
        build(le,l,mid);
        build(ri,mid+1,r);
        tree[node] = merge(tree[le] ,tree[ri]);
    }
}

void push(int node,int l,int r){
    if(lazy[node] == 0)
        return ;
    //resolve
    int add = lazy[node];
    tree[node] += (r-l+1)*add;

    //push
    if(l != r){
        lazy[le] += lazy[node];
        lazy[ri] += lazy[node];
    }
    lazy[node] = 0;
}

void update(int node,int l,int r,int x,int y,int add){
    push(node,l,r);

    if(y < l || x>r)
        return ;
    if(l>=x && r<=y){
        lazy[node] += add;
        push(node,l,r);
        return ;
    }
    update(le,l,mid,x,y,add);
    update(ri,mid+1,r,x,y,add);
        tree[node] = merge(tree[le] ,tree[ri]);
}

int query(int node,int l,int r,int x,int y){

  push(node,l,r);
    if(y < l || x>r)
        return 0;
    if(l>=x && r<=y){
        return tree[node];
    }
    else {
        int ret =  merge(query(le,l,mid,x,y),query(ri,mid+1,r,x,y));
        tree[node] = merge(tree[le] ,tree[ri]);
        return ret;
    }
}

int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    while(q--){
        int type,l,r,x;
        cin>>type;
        if(type == 1){//update
            cin>>l>>r>>x;
            update(1,1,n,l,r,x);
        }
        else {//query
             cin>>l>>r;
            cout<<query(1,1,n,l,r);
        }
    }
}
