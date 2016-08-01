#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
using namespace std;

int cnt,ans;
int f[10],g[10],d[10];
char c[10][25];
set<int> s;

int change(int k[]){
    int sum=0;
    for(int i=1;i<=8;++i){
        sum*=10;
        sum+=k[i];
    }
    return sum;
}

void rot_z(){
    d[1]=g[2];  d[2]=g[6];  d[6]=g[5];  d[5]=g[1];
    d[3]=g[4];  d[4]=g[8];  d[8]=g[7];  d[7]=g[3];
    for(int i=1;i<=8;++i)   g[i]=d[i];
}

void rot_y(){
    d[1]=g[3];  d[3]=g[4];  d[4]=g[2];  d[2]=g[1];
    d[5]=g[7];  d[7]=g[8];  d[8]=g[6];  d[6]=g[5];
    for(int i=1;i<=8;++i)   g[i]=d[i];
}

bool judge(){
    for(int i=1;i<=8;++i)   g[i]=f[i];
    for(int i=1;i<=4;++i){
        rot_z();
        for(int j=1;j<=4;++j){
            rot_y();
            if(s.count(change(g)))  return false;
        }
    }
    g[1]=f[3];  g[3]=f[7];  g[7]=f[5];  g[5]=f[1];
    g[2]=f[4];  g[4]=f[8];  g[8]=f[6];  g[6]=f[2];
    for(int i=1;i<=4;++i){
        rot_y();
        if(s.count(change(g)))  return false;
    }
    g[1]=f[5];  g[5]=f[7];  g[7]=f[3];  g[3]=f[1];
    g[2]=f[6];  g[6]=f[8];  g[8]=f[4];  g[4]=f[2];
    for(int i=1;i<=4;++i){
        rot_y();
        if(s.count(change(g)))  return false;
    }
    return true;
}

void work(){
    cnt=0;  ans=0;
    for(int i=1;i<=8;++i){
        f[i]=0;
        for(int j=1;j<i;++j){
            if(strcmp(c[i],c[j]) == 0)  f[i]=f[j];
        }
        if(f[i]==0) f[i]=++cnt;
    }
    if(cnt==1){
        printf("1\n");  return ;
    }
	sort(f+1, f+9);
    s.insert(change(f));
    while(next_permutation(f+1,f+9)){
        if(judge())    s.insert(change(f));
    }
    ans=s.size();
    s.clear();
    printf("%d\n",ans);
}

int main(){
    while(scanf("%s",c[1])!=EOF){
        for(int i=2;i<=8;++i)   scanf("%s",c[i]);
        work();
    }
}
