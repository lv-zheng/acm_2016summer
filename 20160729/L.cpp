#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int N=100010;
int T,n,f[N],t[N],ans[N];

int lowbit(int k){
    return k&(-k);
}

void ADD(int k){
    while(k<=n){
        t[k]++;
        k+=lowbit(k);
    }
}

int Qsum(int k){
    int sum=0;
    while(k>0){
        sum+=t[k];
        k-=lowbit(k);
    }
    return sum;
}

void work(){
    memset(t,0,sizeof(t));
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",&f[i]);
    }
    int tmp;
    for(int i=n;i>=1;--i){
        tmp=Qsum(f[i]);
        //printf("%d-->%d\n",f[i],tmp);
        ans[f[i]]=max(tmp,i+tmp-f[i]);
        ADD(f[i]);
    }
    for(int i=1;i<=n;++i)   printf(" %d",ans[i]);
}

int main(){
    scanf("%d",&T);
    for(int i=1;i<=T;++i){
        printf("Case #%d:",i);
        work();
        printf("\n");
    }
}
