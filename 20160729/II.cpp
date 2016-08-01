#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 110;
int a[N], b[N], w[110][110], num[14], n;
char s[N];
bool yes[N], out[N];

int ANS = -1e9;
void update(){
	bool ok = 0;
	memset(num , 0, sizeof num);
	for(int i = 1; i <= n; i++)
		if (yes[i]){
			num[s[i] - '0' + 1] ++;
			ok = 1;
		}
	int ans = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			if (yes[i] && yes[j]) ans += w[i][j];
	for(int i = 1; i <= 10; i ++)
		if (num[i]) ans -= a[i] * (num[i] - 1) + b[i];
	if (ans > ANS){
		for(int i = 1; i <= n; i ++) out[i] = yes[i];
		ANS = ans;
	}
}
void dfs(int x){
	if (x == n + 1){
		update();
		return;
	}
	for(int i = 0; i < 2; i ++){
		yes[x] = i;
		dfs(x + 1);
		yes[x] = 0;
	}
}
int main(){
	freopen("I.in","r",stdin);
	int T, cs = 0;;
	scanf("%d", &T);
	while(cs < T){
		printf("Case #%d: ", ++ cs);
		scanf("%d", &n);
		scanf("%s", s + 1);
		for(int i = 1; i <= 10; i ++) scanf("%d%d", &a[i], &b[i]);
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= n; j ++) scanf("%d", &w[i][j]);
		ANS = 0;
		dfs(1);
		printf("%d\n", ANS);
		for(int i = 1; i <= n; i ++) printf("%d ", out[i]); puts("");
	}
	return 0;
}
