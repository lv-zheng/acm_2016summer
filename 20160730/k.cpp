#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int N=200010;
int T,n,m;
int x[N],y[N];
bool f[N];

int ABS(int k){
    if(k<0) k=-k;
    return k;
}

void work(){
    memset(f,0,sizeof(f));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%d%d",&x[i],&y[i]);
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<i;++j){
            int tmp=ABS(x[i]-x[j])+ABS(y[i]-y[j]);
            //printf("%d:%d-->%d\n",i,j,tmp);
            if(f[tmp]){
                puts("YES");
                return ;
            }
            f[tmp]=1;
        }
    }
    puts("NO");
}

int main(){
    scanf("%d",&T);
    for(int i=1;i<=T;++i){
        work();
    }
}
