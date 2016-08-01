#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int N=100010;
struct line{
    int to,next;
}   l[N];
struct tree{
    int l,r,val;
}   t[4*N];
int n,q,sum,cnt;
long long ans=0;
int g[N],st[N],en[N],dep[N];
char c[2];

void ADD(int x,int y){
//printf("ADD:%d-->%d\n",x,y);
    sum++;  l[sum].to=y;
    l[sum].next=g[x];   g[x]=sum;
}

void DFS(int x,int v){
    cnt++;  st[x]=cnt;  dep[x]=v;
    for(int y=g[x];y;y=l[y].next){
        int z=l[y].to;
        DFS(z,v+1);
    }
    en[x]=cnt;
}

void build(int k,int L,int R){
    t[k].l=L;   t[k].r=R;   t[k].val=0;
    if(L==R)    return ;
    int mid=(L+R)/2;
    build(k<<1,L,mid);
    build(k<<1|1,mid+1,R);
}

void change(int k,int L,int R,int pos){
    //printf("%d-->%d:%d:::%d\n",k,L,R,pos);
    if(t[k].l==L&&t[k].r==R){
        if(t[k].val==0||dep[t[k].val]<dep[pos]){
            t[k].val=pos;
        }
        return ;
    }
    int mid=(t[k].l+t[k].r)/2;
    if(L>mid){
        change(k<<1|1,L,R,pos);
        return ;
    }
    if(R<=mid){
        change(k<<1,L,R,pos);
        return ;
    }
    change(k<<1,L,mid,pos);
    change(k<<1|1,mid+1,R,pos);
}

int Qsum(int k,int tmp){
    if(t[k].l==t[k].r)  return t[k].val;
    int mid,now,pos;
    mid=(t[k].l+t[k].r)/2;
    pos=t[k].val;
    if(tmp<=mid)    now=Qsum(k<<1,tmp);
    else    now=Qsum(k<<1|1,tmp);
    if(dep[now]>dep[pos])   pos=now;
    return pos;
}

void work(){
    int tmp;
    sum=0;
    cnt=0;
    ans=0;
    memset(g,0,sizeof(g));
    for(int i=2;i<=n;++i){
        scanf("%d",&tmp);
        ADD(tmp,i);
    }
    DFS(1,1);
    /*for(int i=1;i<=n;++i){
        printf("%d:%d-->%d\n",i,st[i],en[i]);
    }*/
    build(1,1,n);
    change(1,1,n,1);
    for(int i=1;i<=q;++i){
        scanf("%s%d",c,&tmp);
        if(c[0]=='M'){
            change(1,st[tmp],en[tmp],tmp);
        }
        else{
            ans+=Qsum(1,st[tmp]);
        }
    }
    cout<<ans<<endl;
}

int main(){
    while(1){
        scanf("%d%d",&n,&q);
        if(n==0&&q==0){
            break;
        }
        work();
    }
}

