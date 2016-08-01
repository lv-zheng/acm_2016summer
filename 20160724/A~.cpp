#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int t,n;
long long sum,ansa,ansb;
long long w[100010];

long long GCD(long long x,long long y){
    x=abs(x);
    y=abs(y);
    if(x==0)    return y;
    if(x<=y){
        swap(x,y);
    }
    long long z=x%y;
    while(z){
        x=y;
        y=z;
        z=x%y;
    }
    return y;
}

void work(){
    scanf("%d",&n);
    sum=0;
    ansa=0;
    ansb=n;
    for(int i=1;i<=n;++i){
        scanf("%lld",&w[i]);
        w[i]=abs(w[i]);
        sum+=w[i];
        ansa+=w[i]*w[i];
    }
    ansa*=n;
    ansa-=sum*sum;
    long long k=GCD(ansa,ansb);
    ansa/=k;
    ansb/=k;
    printf("%lld/%lld\n",ansa,ansb);
}

int main(){
    scanf("%d",&t);
    for(int i=1;i<=t;++i){
        work();
    }
}
