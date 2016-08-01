#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

int c[100010], n;
int main(){
	while(scanf("%d", &n) == 1){
		for(int i = 1; i <= n; i ++) scanf("%d", &c[i]);
		if (n == 1){
			printf("%.6f\n", (double)c[1]);
			continue;
		}
		double ans = 0.0;
		ans += 0.5 * (c[1] + c[n]);
		int tmp = 0;
		for(int i = 2; i < n; i ++) tmp += c[i];
		ans += 1.0 / 3.0 * tmp;
		printf("%.6f\n", ans);
	}
	return 0;
}
