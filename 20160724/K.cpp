#include<cstdio>

int n, a[100010];
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		int num = 0, sum = 0;
		for(int i = 1; i <= n; i ++){
			scanf("%d", &a[i]);
			if (a[i] & 1){
				a[i] --;
				num ++;
			}
			sum += a[i];
		}
		if (num) printf("%d\n", sum / 2 / num * 2 + 1);
		else printf("%d\n", sum);
	}
	return 0;
}
