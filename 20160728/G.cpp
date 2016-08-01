#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int N = 20010;
int n, m;
int to[N << 1], nxt[N << 1], head[N], cnt;
bool yes[N << 1];
int t[N << 1], nt[N << 1], hd[N], cnt2;
LL len[N << 1];
void add(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}
void ins(int x, int y, LL z){
	t[++ cnt2] = y; nt[cnt2] = hd[x]; hd[x] = cnt2; len[cnt2] = z;
	t[++ cnt2] = x; nt[cnt2] = hd[y]; hd[y] = cnt2; len[cnt2] = z;
}

int dfn[N], low[N], dfs_clock, fa[N], size[N], times, vis[N], belong[N];
LL val[N];
bool sign[N];
void tarjan(int x){
	dfn[x] = low[x] = ++dfs_clock;
	size[x] = 1;
	for(int i = head[x]; i; i = nxt[i])
		if (!dfn[to[i]]){
			tarjan(to[i]);
			size[x] += size[to[i]];
			low[x] = min(low[x], low[to[i]]);
			if (low[to[i]] > dfn[x]){
				sign[to[i]] = sign[x] = 1;
				val[to[i]] = 1LL * size[to[i]] * (n - size[to[i]]);
				ins(x, to[i], val[to[i]]);
				yes[i] = yes[i ^ 1] = 1;
			}
		}else low[x] = min(low[x], dfn[to[i]]);
}

int bcc;
void dfs(int x){
	belong[x] = bcc;
	if (sign[x]) ins(x, n + bcc, 0);
	for(int i = head[x]; i; i = nxt[i]){
		if (yes[i]) continue;
		if (!vis[to[i]]) dfs(to[i]);
	}
}
void rebuild(){
	memset(vis, 0, sizeof vis);
	for(int i = 1; i <= n; i ++)
		if (!vis[i]){
			bcc ++;
			dfs(i);
		}
}
void init(){
	bcc = times = 0;
	cnt = cnt2 = 1;
	memset(head, 0, sizeof head);
	memset(hd, 0, sizeof hd);
	memset(yes, 0, sizeof yes);
	memset(val, 0, sizeof val);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <
}
LL current[N], Lim;
bool treedp(int x){
	vis[x] = times;
	for(int i = hd[x]; i; i = nt[i])
		if (vis[t[i]] != times){
			if (!treedp[t[i]]) return false;
			if (current[t[i]] + len[i] > Lim) current[x] += len[i];
			if (current[x] > Lim) return false;
		}
	return current[x] <= Lim;
}

bool check(LL x){
	Lim = x;
	memset(current, 0, sizeof current);
	times ++;
	for(int i = 1; i <= n; i ++)
		if (vis[i] != times)
			if (!treedp(i)) return 0;
	return 1;
}
void work(){
	times ++;
	for(int i = 1; i <= n; i ++) if (vis[i] != times) tarjan(i);
	for(int i = 1; i <= n; i ++)
		printf("%lld\n",val[i]);
	rebuild();
	LL l = 0, r = 1e18, mid, ans = 0;
	while(l <= r){
		mid = (l + r) >> 1;
		if (check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%lld\n", ans);
}

int main(){
	int T, cs = 0;
	scanf("%d", &T);
	while(cs < T){
		cs ++;
		printf("Case %d: ", cs);
		init();
		work();
	}
	return 0;
}
