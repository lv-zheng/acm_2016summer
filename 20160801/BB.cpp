#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

int n, m, h[110], t[110], f[110][110];
bool check(int st, int r){
	int now = st;
	while(now < r){
		for(int i = 1; i <= n; i ++){
			if (h[now] < t[i]) return false;
			now ++;
			if (now == r) return 1;
		}
	}
	return 1;
}

int main(){
	while(scanf("%d", &n) == 1 && n){
		for(int i = 1; i <= n; i ++) scanf("%d", &t[i]);
		scanf("%d", &m);
		int x, y;
		for(int i = 1; i <= m; i ++) h[i] = 24;
		for(int i = 1; i <= m; i ++){
			scanf("%d%d", &x, &y);
			h[x] = min(h[x], y);
		}
		memset(f, 0x3f, sizeof f);
		f[1][1] = 0;
		for(int i = 2; i <= m; i ++){
			f[i][1] = f[i - 1][n];
			for(int j = 1; j < n; j ++)
				f[i][1] = min(f[i][1], f[i - 1][j] + 1);
			for(int j = 2; j <= n; j ++)
				if (h[i] >= t[j]) f[i][j] = f[i - 1][j - 1];
		}
		int ans = 10000;
		for(int i = 1; i <= n; i ++)
			ans = min(ans, f[m][i]);
		printf("%d\n", ans);
	}
	return 0;
}
