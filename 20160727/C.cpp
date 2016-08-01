#include<iostream>
#include<cstdio>
using namespace std;

int T,n,d;
int p,l,v;
double ans;

void work(){
    ans=d;
    for(int i=1;i<=n;++i){
        scanf("%d%d%d",&p,&l,&v);
        ans-=l;
        ans+=2*(double)l/(double)v;
    }
    printf("%.3lf\n\n",ans);
}

int main(){
    T=0;
    while(1){
        scanf("%d%d",&n,&d);
        if(n==0&&d==0)  break;
        T++;
        printf("Case %d: ",T);
        work();
    }
}
