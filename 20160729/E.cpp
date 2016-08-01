#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;

int n, p[20], b[20], a[20];
void exgcd(LL a, LL b, LL &d, LL &x, LL &y){
	if (!b) { d = a; x = 1; y = 0; }
	else {exgcd(b, a % b, d, y, x); y -= a/b * x;}
}

s
LL solve(LL x){
	LL t = x / 7, d, x, y;
	for(int i = 0; i < n; i ++){
		exgcd(7, p[i], d, x, y);
		while(x < 0){x += p[i], y -= 7;}
		a[i] = (t - x) / p[i];
	}
	LL ans = 0;
	for(int i = 0; i < n; i ++)
		f[1 << i] = a[i];
	ans = dfs((1 << n) - 1);
	return x - ans;
}
int main(){
	int T, cs = 0;;
	scanf("%d", &T);
	while(cs < T){
		printf("Case #%d: ", ++ cs);
		scanf("%d%lld%lld", &n, &x, &y);
		for(int i = 0; i < n; i ++) scanf("%d %d", &p[i], &b[i]);
		printf("%lld\n", solve(y) - solve(x - 1));
	}
	return 0;
}
