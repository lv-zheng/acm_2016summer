#include<cstdio>
#include<cstring>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int INF = 1e9;
const int N = 11010;
const int M = 100010;
struct edge{
	int to;
	LL v;
}E[M << 1];
int head[N], nxt[M << 1], cnt;
void add(int x, int y, LL z){
	E[++ cnt] = (edge){y, z}; nxt[cnt] = head[x]; head[x] = cnt;
	E[++ cnt] = (edge){x, 0}; nxt[cnt] = head[y]; head[y] = cnt;
}
int S, T, cur[N], d[N], Q[N];
bool mklevel(){
	for(int i = 0; i <= T; i ++) d[i] = -1;
	d[S] = 0;
	int l = 0, r = -1;
	Q[++ r] = S;
	while(l <= r){
		int x = Q[l ++];
		for(int i = head[x]; i; i = nxt[i])
			if (E[i].v && d[E[i].to] == -1){
				d[E[i].to] = d[x] + 1;
				Q[++ r] = E[i].to;
			}
	}
	return d[T] != -1;
}
LL dfs(int x, LL a){
	if (x == T || a == 0) return a;
	LL flow = 0;
	for(int &i = cur[x]; i; i = nxt[i])
		if (E[i].v && d[E[i].to] == d[x] + 1){
			LL f = dfs(E[i].to, min(a - flow, E[i].v));
			E[i].v -= f;
			E[i ^ 1].v += f;
			flow += f;
			if (a == flow) break;
		}
	if (!flow) d[x] = -1;
	return flow;
}
LL Dinic(){
	LL ans = 0;
	while(mklevel()){
		for(int i = 0; i <= T; i ++) cur[i] = head[i];
		ans += dfs(S, INF);
	}
	return ans;
}

int num[15], a[110], b[110], w[110][110], n;
char s[110];
void init(){
	memset(head, 0, sizeof head); cnt = 1;
	scanf("%d", &n);
	scanf("%s", s + 1);
	for(int i = 1; i <= 10; i ++) scanf("%d%d", &a[i], &b[i]);
	memset(num, 0, sizeof num);
	for(int i = 1; i <= n; i ++)
		num[s[i] - '0' + 1] ++;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			scanf("%d", &w[i][j]);
	S = 0, T = n * n + n + 11;
	LL sum = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++){
			add((i - 1) * n + j, n * n + i, INF);
			if (i != j) add((i - 1) * n + j, n * n + j, INF);
			add(S, (i - 1) * n + j, w[i][j]);
			sum += w[i][j];
		}
	for(int i = 1; i <= n; i ++){
		add(n * n + i, T, a[s[i] - '0' + 1]);
		add(n * n + i, n * n + n + (s[i] - '0' + 1), INF);
	}
	for(int i = 1; i <= 10; i ++)
		add(n * n + n + i, T, b[i] - a[i]);
	printf("%lld\n", sum - Dinic());
}

int main(){
	int T, cs = 0;
	scanf("%d", &T);
	while(cs < T){
		printf("Case #%d: ", ++ cs);
		init();
	}
	return 0;
}
