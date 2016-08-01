#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int T,n,h[110],t[110],f[110][110];

int main(){
    while(1){
        scanf("%d",&T);
        if(T==0)    break;
        for(int i=1;i<=T;++i){
            scanf("%d",&t[i]);
        }
        scanf("%d",&n);
        int x,y;
        for(int i=1;i<=n;++i)   h[i]=24;
        for(int i=1;i<=n;++i){
            scanf("%d%d",&x,&y);
            h[x]=min(h[x],y);
        }
        memset(f,0x3f,sizeof(f));
        f[1][1]=0;
        for(int i=2;i<=n;++i){
            f[i][1]=f[i-1][T];
            for(int j=1;j<T;++j){
                f[i][1]=min(f[i][1],f[i-1][j]+1);
            }
            for(int j=2;j<=T;++j){
                if(h[i]>=t[j])   f[i][j]=f[i-1][j-1];
            }
        }
        int ans=10000;
        for(int i=1;i<=T;++i)   ans=min(ans,f[n][i]);
        printf("%d\n",ans);
    }
    return 0;
}
