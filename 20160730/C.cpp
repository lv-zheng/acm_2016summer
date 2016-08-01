#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int dx[] = {1, 0, 1},
	  	  dy[] = {0, 1, 1};
int dp[1010][1010], n , m;
int queen[1010][1010];
//1 xianshou win
//0 ping
//-1 houshou win
int dfsking(int x, int y){
	if (x == n && y == m) return dp[x][y] = -1;
	if (dp[x][y] != -2) return dp[x][y];
	int win = 0, draw = 0, lose = 0, tmp;
	for(int i = 0; i < 3; i ++){
		if (x + dx[i] > n || y + dy[i] > m) continue;
		tmp = dfsking(x + dx[i], y + dy[i]);
		if (tmp == 1) win ++;
		if (tmp == 0) draw ++;
		if (tmp == -1) lose ++;
		if (lose) break;
	}
	if (lose) return dp[x][y] = 1;
	if (draw) return dp[x][y] = 0;
	if (win) return dp[x][y] = -1;
	return dp[x][y] = 0;
}

int dfsrook(int x, int y){
	if (x == n && y == m) return dp[x][y] = -1;
	if (dp[x][y] != -2) return dp[x][y];
	int win = 0, draw = 0, lose = 0, tmp;
	for(int i = x + 1; i <= n; i ++){
		tmp = dfsrook(i, y);
		if (tmp == 1) win ++;
		if (tmp == 0) draw ++;
		if (tmp == -1) lose ++;
		if (lose) break;
	}
	for(int j = y + 1; j <= m; j ++){
		tmp = dfsrook(x, j);
		if (tmp == 1) win ++;
		if (tmp == 0) draw ++;
		if (tmp == -1) lose ++;
		if (lose) break;
	}
	if (lose) return dp[x][y] = 1;
	if (draw) return dp[x][y] = 0;
	if (win) return dp[x][y] = -1;
	return dp[x][y] = 0;
}

const int kx[] = {1, 2},
	  	  ky[] = {2, 1};
int dfsknight(int x, int y){
	if (x == n && y == m) return dp[x][y] = -1;
	if (dp[x][y] != -2) return dp[x][y];
	int win = 0, draw = 0, lose = 0, tmp;
	for(int i = 0; i < 2; i ++){
		if (x + kx[i] > n || y + ky[i] > m) continue;
		tmp = dfsknight(x + kx[i], y + ky[i]);
		if (tmp == 1) win ++;
		if (tmp == 0) draw ++;
		if (tmp == -1) lose ++;
		if (lose) break;
	}
	if (lose) return dp[x][y] = 1;
	if (draw) return dp[x][y] = 0;
	if (win) return dp[x][y] = -1;
	return dp[x][y] = 0;
}

int dfsqueen(int x, int y){
	if (x == n && y == m) return dp[x][y] = -1;
	if (dp[x][y] != -2) return dp[x][y];
	int win = 0, draw = 0, lose = 0, tmp;
	for(int i = x + 1; i <= n; i ++){
		tmp = dfsqueen(i, y);
		if (tmp == 1) win ++;
		if (tmp == 0) draw ++;
		if (tmp == -1) lose ++;
		if (lose) break;
	}
	for(int j = y + 1; j <= m; j ++){
		tmp = dfsqueen(x, j);
		if (tmp == 1) win ++;
		if (tmp == 0) draw ++;
		if (tmp == -1) lose ++;
		if (lose) break;
	}
	for(int i = 1; x + i <= n && y + i <= m; i ++){
		if (x + i > n || y + i > m) break;
		tmp = dfsqueen(x + i, y + i);
		if (tmp == 1) win ++;
		if (tmp == 0) draw ++;
		if (tmp == -1) lose ++;
		if (lose) break;
	}

	if (lose) return dp[x][y] = 1;
	if (draw) return dp[x][y] = 0;
	if (win) return dp[x][y] = -1;
	return dp[x][y] = 0;
}

int have[1010];
int main(){
	int T;
	scanf("%d", &T);
	queen[0][0] = -1;
	int x = 1, y, now = 1;
	for(int i = 1; i <= 1000; i ++){
		x = now; y = x + i;
		queen[x][y] = queen[y][x] = -1;
		if (x > 1000 || y > 1000) break;
		have[x] = have[y] = 1;
		while(have[now] && now <= 1000) now ++;
	}
	while(T --){
		scanf("%d%d%d", &x, &n, &m);
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++) dp[i][j] = -2;
		int ans = -2;
		if (x == 1){
			if ((n & 1) && (m & 1)) ans = -1;
			else ans = 1;
		}
		else if (x == 2){
			if (n == m) ans = -1;
			else ans = 1;
		}
		else if (x == 3) ans = dfsknight(1, 1);
		else if (x == 4){
			if (queen[n - 1][m - 1] == -1) ans = -1;
			else ans = 1;
		}
		if (ans == 1) puts("B");
		else if (ans == -1) puts("G");
		else puts("D");
	}
	return 0;
}
