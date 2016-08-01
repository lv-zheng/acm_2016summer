#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

struct Vector{
    int x,y;
    double ord;
}   h[60];
int T,n,k,tot;
int f[2][60][2510];

bool comp(Vector a,Vector b){
    return a.ord>b.ord;
}

void work(){
    scanf("%d%d",&n,&k);
    tot=0;
    for(int i=1;i<=n;++i){
        scanf("%d%d",&h[i].x,&h[i].y);
        tot+=h[i].y;
        if(h[i].x==0)   h[i].ord=100.0;
        else    h[i].ord=(double)h[i].y/(double)h[i].x;
    }
    sort(h+1,h+1+n,comp);
    for(int i=1;i<=n;++i){
        //printf("%d:%d-->%d\n",i,h[i].x,h[i].y);
    }
    memset(f,-1,sizeof(f));
    f[0][0][0]=0;
    int now,tmp,ans;
    for(int i=1;i<=n;++i){
//        printf("%d-->\n",i);
        now=i&1;
        memset(f[now],-1,sizeof(f[now]));
        f[now][0][0]=0;
        for(int j=1;j<=k;++j){
            for(int l=1;l<=tot;++l){
                f[now][j][l]=f[now^1][j][l];
                tmp=l-h[i].y;
                if(tmp>=0&&f[now^1][j-1][tmp]!=-1){
                    tmp=f[now^1][j-1][tmp]+(tmp+l)*h[i].x;
                    //printf("tmp:%d\n",tmp);
                    if(tmp>f[now][j][l]){
                        f[now][j][l]=tmp;
                    }
                    //printf("-->%d-->%d:%d\n",j,l,f[now][j][l]);
                }
            }
        }
    }
    ans=0;
    for(int i=1;i<=tot;++i){
        ans=max(ans,f[n&1][k][i]);
    }
    printf("%d\n",ans);
}

int main(){
    scanf("%d",&T);
    for(int i=1;i<=T;++i){
        printf("Case %d: ",i);
        work();
    }
}
