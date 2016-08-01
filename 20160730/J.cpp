#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int a,v1,v2;
double ans;

int main(){
    while(scanf("%d%d%d",&a,&v1,&v2)==3){
        if(v1<=v2){
            printf("Infinity\n");
        }
        else{
            ans=sqrt(v1*v1-v2*v2);
            ans=a/ans;
            printf("%.8lf\n",ans);
        }
    }
    return 0;
}
