#include<cstdio>
#include<ctime>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int dx[] = {1, 0, -1, 0},
	      dy[] = {0, 1, 0, -1};

int a[32][32], n, m;
int num[32][32];
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

int main(){
	freopen("D.in","w",stdout);
	srand(time(0));
	puts("1");
	n = 30, m = 30;
	printf("%d %d\n", n, m);
	int k = 1000;
	for(int i = 1; i <= 40; i ++){
		int x = rand() % n + 1, y = rand() % m + 1;
		zha(x, y, 1);
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++) printf("%d ", a[i][j]);
		puts("");
	}
	return 0;
}
