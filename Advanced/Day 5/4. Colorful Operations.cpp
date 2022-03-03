//https://codeforces.com/problemset/problem/1638/E
#include <bits/stdc++.h>
#define int long long
#define le node+node
#define ri node+node+1
#define mid (l+r)/2
using namespace std;
const int inf = 1e6+9,MX = 1e18+9;
int n,q,ColorUpdates[inf];
vector<pair<int,int> > AddUpdates[inf];

set<pair<int,pair<int,int> > > s;

int tree[inf<<2];
void update(int node,int l,int r,int x,int y,int val){
    if(l>r || r<x || l>y || x>y)
        return ;
    if(l>=x && r<=y)
        return void(tree[node] += val);

    update(le,l,mid,x,y,val);
    update(ri,mid+1,r,x,y,val);
}

int query(int node,int l,int r,int x){
    if(l == r)
        return tree[node];
    if(x <= mid)
        return tree[node] + query(le,l,mid,x);
    else
        return tree[node] + query(ri,mid+1,r,x);
}
//version is the index of the coloring query
int get_version(int x){
    auto it = s.upper_bound(make_pair(x,make_pair(inf,inf)));
    it--;
    return it->second.second;
}

int calc_increase(int color,int version){
    int idx = upper_bound(AddUpdates[color].begin(),AddUpdates[color].end(),make_pair(version,MX)) - AddUpdates[color].begin();
    idx--;
    return AddUpdates[color].back().second - AddUpdates[color][idx].second;
}

signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        AddUpdates[i].push_back(make_pair(0,0));

    s.insert(make_pair(1,make_pair(n,0)));
    ColorUpdates[0] = 1;

    for(int CurVersion=1;CurVersion<=q;CurVersion++){
        string type;
        int l,r,c,x;
        cin>>type;
        if(type == "Color"){
            cin>>l>>r>>c;
            ColorUpdates[CurVersion] = c;
            auto it = s.upper_bound( make_pair(l,make_pair(inf,inf)) );
            it--;
            vector<pair<int,pair<int,int> > > add;
            while(it != s.end()){
                pair<int,pair<int,int> > cur = *it;
                int x = cur.first,y = cur.second.first,v = cur.second.second;
                update(1,1,n,max(x,l),min(r,y), calc_increase(ColorUpdates[v],v) );
                if(x < l )
                    add.push_back(make_pair(x,make_pair(l-1,v)));
                if(y > r)
                        add.push_back(make_pair(r+1,make_pair(y,v)));
                it = s.erase(it);
                if( it == s.end() || (*it).first > r)
                    break;
            }
            for(auto o:add)
                        s.insert(o);

            s.insert(make_pair(l,make_pair(r,CurVersion)));
        }
        else if (type == "Add"){
            cin>>c>>x;
            int pre = AddUpdates[c].back().second;
            AddUpdates[c].push_back(make_pair(CurVersion,x));
            AddUpdates[c].back().second += pre;
        }
        else{
            cin>>x;
            int ans = query(1,1,n,x),version = get_version(x);
            int color = ColorUpdates[version];
            ans += calc_increase(color,version);

            cout<<ans<<endl;
        }
    }
}