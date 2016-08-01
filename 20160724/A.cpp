#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

struct Number{
    long long a,b;
}   p[100010],w[100010],ave,ans;
int t,n;

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

Number ADD(Number x,Number y){
    Number z;
    long long k=GCD(x.b,y.b);
    z.a=x.b/k*y.a+y.b/k*x.a;
    z.b=x.b/k*y.b;
    k=GCD(z.a,z.b);
    z.a/=k;
    z.b/=k;
    return z;
}

Number MULT(Number x,Number y){
    Number z;
    z.a=x.a*y.a;
    z.b=x.b*y.b;
    long long k=GCD(z.a,z.b);
    z.a/=k;
    z.b/=k;
    return z;
}

void work(){
    scanf("%d",&n);
    ave.a=0;
    ave.b=n;
    for(long long i=1;i<=n;++i){
        scanf("%lld",&w[i].a);
        w[i].a=abs(w[i].a);
        ave.a-=w[i].a;
        w[i].b=1;
    }
    long long k=GCD(ave.a,ave.b);
    ave.a/=k;
    ave.b/=k;
    ans.a=0;
    ans.b=1;
    for(long long i=1;i<=n;++i){
        p[i]=ADD(ave,w[i]);
        p[i]=MULT(p[i],p[i]);
        ans=ADD(ans,p[i]);
    }
    printf("%lld/%lld\n",ans.a,ans.b);
}

int main(){
    scanf("%d",&t);
    for(long long i=1;i<=t;++i){
        work();
    }
}
