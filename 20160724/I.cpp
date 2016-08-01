#include<cstdio>
#include<cstring>
#include<cstdlib>

int gcd(int a, int b){return b ? gcd(b, a % b) : a;}
int n, m, a[110];
bool sign[110];

int main(){
	int T, x, y;
	scanf("%d", &T);
	while(T--){
		memset(a, 0, sizeof a);
		memset(sign, 0, sizeof sign);
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i ++){
			scanf("%d%d", &x, &y);
			sign[x] = 1;
			a[x] = y;
		}
		a[0] = 100; a[n + 1] = 0;
		for(int i = 1; i <= 2; i ++)
			if (!sign[i]) a[i] = a[i - 1];
		for(int i = n; i >= 3; i --)
			if (!sign[i]) a[i] = a[i + 1];
//		for(int i = 1; i <= n; i ++) printf("%d ",a[i]); puts("");
		int sum = 0;
		for(int i = 1; i <= n; i ++)
			sum += a[i];
		int ans = a[1] + a[2], d = gcd(ans, sum);
//		printf("%d %d %d\n",ans, sum, d);
		printf("%d/%d\n", ans / d, sum / d);
	}
	return 0;
}
