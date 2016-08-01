#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
int to[N << 1], nxt[N << 1], head[N], cnt;
void add(int x, int y){
	to[++ cnt] = y; nxt[cnt] = head[x]; head[x] = cnt;
	to[++ cnt] = x; nxt[cnt] = head[y]; head[y] = cnt;
}

int leaves, n, m, ans, size[N], child[N];
bool vis[N];
void dfs(int x){
	vis[x] = 1;
	for(int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]){
			dfs(to[i]);
			child[x] ++;
		}
	if (child[x] == 0){
		leaves ++;
		size[x] = 1;
	}
}

bool yes = 0;
int f[N][2][3];
void dp(int x){
	vis[x] = 1;
	for(int i = head[x]; i; i = nxt[i])
		if (!vis[to[i]]){
			dp(to[i]);
			size[x] += size[to[i]];
		}
	if (size[x] > 1 && !yes) {
		size[x] --;
		yes = 1;
	}
	if (x == 1) return;
	size[x] &= 1;
	if (size[x] == 0) size[x] += 2;
	ans += size[x];
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		memset(head, 0, sizeof head); cnt = 0;
		memset(child, 0, sizeof child);
		memset(size, 0, sizeof size);
		int x, y;
		for(int i = 1; i < n; i ++){
			scanf("%d%d", &x, &y);
			add(x, y);
		}
		leaves = ans = 0;
		memset(vis, 0, sizeof vis);
		dfs(1);
		memset(vis, 0, sizeof vis);
		if (leaves & 1){
			yes = 0;
		}else yes = 1;
		dp(1);
//		for(int i = 1; i <= n; i ++) printf("%d ", size[i]);
		printf("%d\n", ans);
	}
	return 0;
}
