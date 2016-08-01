#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 100010;
int n, a[N], f[N], len[N], num[N], cnt[N];
void init(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	int l, r, mid, ans, mx = 0;
	for(int i = 1; i <= n; i ++){
		if (a[i] != 0){
			l = 0; r = mx; ans = 0;
			while(l <= r){
				mid = (l + r) >> 1;
				if (f[mid] < a[i]) ans = mid, l = mid + 1;
				else r = mid - 1;
			}
			len[i] = ans + 1;
			f[ans + 1] = min(f[ans + 1], a[i]);
			mx = max(mx, ans + 1);
		}else{
			mx ++;
			for(int i = mx; i; i --) f[i] = min(f[i], f[i - 1] + 1);
			f[1] = 0;
		}
	}
	printf("%d\n", mx);
}
int main(){
	int T, cs = 0;;
	scanf("%d", &T);
	while(cs < T){
		printf("Case #%d: ", ++ cs);
		init();
	}
	return 0;
}
