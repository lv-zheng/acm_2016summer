#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 20010;
int n, m, num, rt, tot;
bool sign = 0;
int fa[N], g[N];
int getfa(int x){
	if (fa[x] == x) return fa[x];
	getfa(fa[x]);
	g[x] ^= g[fa[x]];
	fa[x] = fa[fa[x]];
	return fa[x];
}

void change(int p, int q, int v){
	if (v == -1) {
		if (rt == -1){
			rt = getfa(p);
			tot = g[p] ^ q;
		}else{
			if (getfa(p) == rt){
				if (g[p] ^ q != tot){
					sign = 1;
					printf("The first %d facts are confilicting.\n",num);
					return;
				}
			}else{
				fa[getfa(p)] = rt;
				g[getfa(p)] = tot ^ g[p] ^ q;
			}
		}
	}else{
		int fx = getfa(p), fy = getfa(q);
		if (fx == fy){
			if (v != (g[fx] ^ g[fy])){
				sign = 1;
				printf("The first %d facts are confilicting.\n",num);
				return;
			}
		}else{
			fa[fx] = fy;
			g[x] = g[p] ^ g[q] ^ v;
		}
	}
}

int tmp[100], k[100];
void query(int len){
	int ans = 0;
	for(int i = 1; i <= len; i ++){
int main(){
	int T = 0;
	while(scanf("%d", &n, &m) == 2 && n && m){
		rt = -1; num = 0;
		tot = 0;
		sign = 0;
		for(int i = 1; i <= m; i ++){
			scanf("%s", opt);
			int len = 0;
			if (opt[0] == 'I'){
				num ++;
				v = -1;
				gets(opt);
				sscanf(opt, "%d%d%d", &p, &q, &v);
				if (!sign) change(p, q, v);
			}else{
				scanf("%d", &len);
				for(int j = 1; j <= k; j ++)
					scanf("%d", &k[j]);
				if (!sign) query(len);
			}
		}
	}
	return 0;
}
