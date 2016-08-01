#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;

const int N=20010;
int T,n,m,p,q,v,sum;
int root,tot,k[18];
short f[N];
int g[N];
bool flag;
char c[100];
char s[500];

int find(int k){
    if(f[k] != k){
        find(f[k]);
        g[k] = g[k] ^ g[f[k]];
        f[k] = f[f[k]];
    }
    return f[k];
}

void Change(int p, int q, int v){
    if(v==-1){
        if(root==-1){
            root=find(p);
            tot=g[p]^q;
        }
        else{
            static int tmp;
            tmp=find(p);
            if(tmp==root){
                if((g[p]^q)!=tot){
                    flag=true;
                    printf("The first %d facts are conflicting.\n",sum);
                    return ;
                }
            }
            else{
                f[tmp]=root;
                g[tmp]=tot^q^g[p];
            }
        }
    }
    else{
        static int x,y;
        x = find(p);
        y = find(q);
        //printf("%d:%d-->%d:%d\n",p,x,q,y);
        if(x == y){
            if(v!=(g[p]^g[q])){
                flag=true;
                printf("The first %d facts are conflicting.\n",sum);
                return ;    
            }
        }
        else{
            f[x]=y;
            g[x]=g[p]^g[q]^v;
        }
    }
}

void Query(int len){
    static int ans;
    ans=0;
    static bool now;
    now=true;
    for(int i=1;i<= len ;++i){
        find(k[i]);
        ans=ans^g[k[i]];
        k[i]=f[k[i]];
    }
    static int pos,cnt;
    pos = 0;
    sort(k+1,k + len + 1);
    while(pos < len){
        pos++;
        cnt=1;
        while(pos<len&&k[pos]==k[pos+1]){
            pos++;  cnt++;
        }
        if(cnt&1){
            if(k[pos]==root)    ans=ans^tot;
            else{
                now=false;   break;
            }
        }
    }
    if(now){
        printf("%d\n",ans);
    }
    else{
        printf("I don't know.\n");
    }
}

void work(){
    sum=0;
    tot = 0; root=-1;
    flag=false;
    for(int i=0;i<n;++i){
        f[i]=i;
        g[i]=0;
    }
    for(int i=1;i<=m;++i){
        scanf("%s",c);
        p=-1;   q=-1;   v=-1;
        k[0]=-1;
        if(c[0]=='I'){
            sum++;
            gets(s);
            sscanf(s,"%d%d%d",&p,&q,&v);
			if (!flag) Change(p, q, v);
        }
        else{
			static int len = 0;
            scanf("%d",&len);  k[len+1]=-1;
            for(int j=1;j<=len;++j)   scanf("%d",&k[j]);
			if (!flag) Query(len);
        }
    }
}

int main(){
    T=0;
    while(1){
        scanf("%d%d",&n,&m);
        if(n==0&&m==0)  break;
        printf("Case %d:\n",++T);
        work();
        printf("\n");
    }
}
