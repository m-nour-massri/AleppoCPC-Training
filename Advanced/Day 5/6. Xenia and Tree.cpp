//https://codeforces.com/problemset/problem/342/E
 
#include <bits/stdc++.h>
using namespace std;
const int inf=1e5+9,lg=20,sqr=322;
int n,q;
int level[inf],sparse[lg][inf],ans[inf];
vector<int> v[inf],temp;
 
void dfs(int node,int par){
 
    sparse[0][node]=par;
    level[node]=level[par]+1;
    for(auto o:v[node])
        if(o!=par)
            dfs(o,node);
}
 
void build(){
 
    memset(ans,21,sizeof(ans));
    dfs(1,0);
    for(int j=1;j<lg;j++)
        for(int i=1;i<=n;i++)
            sparse[j][i]=sparse[j-1][sparse[j-1][i]];
}
 
int LCA(int x,int y){
 
    if(level[x]>level[y])
        swap(x,y);
    int diff=level[y]-level[x];
    for(int i=lg-1;i>=0;i--)
        if(diff&(1<<i))
            y=sparse[i][y];
 
    for(int i=lg-1;i>=0;i--)
        if(sparse[i][x] != sparse[i][y])
            x=sparse[i][x],y=sparse[i][y];
 
    return (x==y?y:sparse[0][y]);
}
 
int dis(int x,int y){
    return level[x]+level[y]-2*level[LCA(x,y)];
}
 
void bfs(){
    bool vis[inf]={0};
    queue<int> q;
 
    for(auto o:temp)
        q.push(o),ans[o]=0;
    temp.clear();
 
    while(!q.empty()){
        int node=q.front();
        q.pop();
        if(vis[node])
            continue;
        vis[node]=1;
        for(auto o:v[node])
            if(ans[o]>ans[node]+1)
                ans[o]=ans[node]+1,q.push(o);
    }
 
}
 
int main(){
 
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    build();
    temp.push_back(1);
    while(q--){
        int type,node;
        cin>>type>>node;
        if(type==1)
           temp.push_back(node);
        else{
            int result=ans[node];
            for(auto o:temp)
               result=min(result,dis(node,o));
            cout<<result<<endl;
        }
        if(temp.size()==sqr)
            bfs();
    }
}