#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 302;
int v1,v2,n, c[N], h[N];
bool must[N];
int f[2][502][52][2];

int main(){
	int T = 0;
	while(scanf("%d%d%d", &v1, &v2, &n) == 3 && n){
		for(int i = 1; i <= n; i ++)
			scanf("%d%d%d", &c[i], &h[i], &must[i]);
		memset(f, -1, sizeof f);
		f[0][0][0][0] = 0;
		int ans = -1;
		for(int i = 1; i <= n; i ++){
			int now = i & 1;
			memset(f[now], -1, sizeof f[now]);
			for(int j = 0; j <= v1; j ++)
				for(int k = 0; k <= v2; k ++)
					for(int l = 0; l < 2; l ++){
						f[now][j][k][l] = -1;
						int &tmp = f[now][j][k][l];
						if (must[i]){
							if (j >= c[i] && f[now ^ 1][j - c[i]][k][l] != -1) tmp = max(tmp, f[now ^ 1][j - c[i]][k][l] + h[i]);
							if (k >= c[i] && f[now ^ 1][j][k - c[i]][l] != -1) tmp = max(tmp, f[now ^ 1][j][k - c[i]][l] + h[i]);
							if (l && f[now ^ 1][j][k][0] != -1) tmp = max(tmp, f[now ^ 1][j][k][0] + h[i]);
						}else{
							tmp = max(tmp, f[now ^ 1][j][k][l]);
							if (j >= c[i] && f[now ^ 1][j - c[i]][k][l] != -1) tmp = max(tmp, f[now ^ 1][j - c[i]][k][l] + h[i]);
							if (k >= c[i] && f[now ^ 1][j][k - c[i]][l] != -1) tmp = max(tmp, f[now ^ 1][j][k - c[i]][l] + h[i]);
							if (l && f[now ^ 1][j][k][0] != -1) tmp = max(tmp, f[now ^ 1][j][k][0] + h[i]);
						}
						if (i == n) ans = max(ans, f[now][j][k][l]);
					}
		}
		printf("Case %d: %d\n\n",++ T, ans);
	}
	return 0;
}
