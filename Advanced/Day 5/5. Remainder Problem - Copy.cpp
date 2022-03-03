//https://codeforces.com/problemset/problem/1207/F
#include <bits/stdc++.h>
using namespace std;
const int inf = 5e5+9,sqr = 709;
 
int a[inf],q,cnt[sqr+5][sqr+4];
 
int main(){
 
    scanf("%d",&q);
    while(q--){
        int type,x,y;
        scanf("%d%d%d",&type,&x,&y);
        if(type == 1){
            for(int i=1;i<=sqr;i++)
                cnt[ i ][x%i] += y;
            a[x] += y;
        }
        else {
            if(x <= sqr)
                printf("%d\n",cnt[x][y]);
            else{
                int ret = 0;
                for(int i = y;i<inf;i += x)
                    ret += a[i];
                printf("%d\n",ret);
            }
        }
    }
}