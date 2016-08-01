#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int dx[] = {1, 0, -1, 0},
	      dy[] = {0, 1, 0, -1};

const int N = 32;
int n, m, num[N][N], a[N][N], b[N][N];
bool yes = 0;
int id(int x, int y){
	return (x - 1) * m + y;
}
void check(){
	if (yes) return;
	for(int j = 1; j <= m; j ++)
		if (a[n][j]) return;
	int ans = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			ans += num[i][j];
	printf("%d\n", ans);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			for(int k = 1; k <= num[i][j]; k ++)
				printf("%d %d\n", i, j);
	yes = 1;
}

inline void zha(int x, int y, int times){
	if (times == 0 || times == 3) return;
	num[x][y] = (num[x][y] + times) % 3;
	a[x][y] = (a[x][y] + 2 * times) % 3;
	int tx, ty;
	for(int i = 0; i < 4; i ++){
		tx = x + dx[i], ty = y + dy[i];
		if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
		a[tx][ty] = (a[tx][ty] + times) % 3;
	}
}
void dfs(int x, int y){
	if (yes) return;
	if (x == n + 1){
		check();
		return;
	}
	if (x <= 1 && a[x][y] != 0){
		for(int i = 0; i < 3; i ++){
//		for(int i = 2; i >= 0; i --){ 
			zha(x, y, i);
			if (y < m) dfs(x, y + 1);
			else dfs(x + 1, 1);
			zha(x, y, 3 - i);
			if (yes) return;
		}
	}else{
		if (a[x - 1][y] == 0){
			if (y < m) dfs(x, y + 1);
			else dfs(x + 1, 1);
			if (yes) return;
		}else if (a[x - 1][y] == 1){
			zha(x, y, 2);
			if (y < m) dfs(x, y + 1);
			else dfs(x + 1, 1);
			zha(x, y ,1);
			if (yes) return;
		}else if (a[x - 1][y] == 2){
			zha(x, y, 1);
			if (y < m) dfs(x, y + 1);
			else dfs(x + 1, 1);
			zha(x, y, 2);
			if (yes) return;
		}
	}
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				scanf("%d", &a[i][j]);
		yes = 0;
		dfs(1, 1);
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++) a[i][j] = num[i][j] = 0;
	}
	return 0;
}
