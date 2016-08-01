#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long LL;
const int P = 1e9 + 7;
const int N = 1010;
struct Poi{
	int x, y, k;
	void read(){
		scanf("%d%d", &x, &y);
		k = 1;
	}
}a[N];
Poi operator - (const Poi &a, const Poi &b){
	return (Poi){a.x - b.x, a.y - b.y};
}
LL Cross(Poi a, Poi b){
	return 1LL * a.x * b.y - 1LL * a.y *b.x;
}
bool operator < (const Poi &a, const Poi &b){
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}
int K;
bool cmp(const Poi &x, const Poi &y){ 
	return Cross(x - a[K], y - a[K]) > 0;
}

int n, p[N];
int main(){
	p[0] = 1;
	for(int i = 1; i <= 1000; i ++)
		p[i] = (2LL * p[i - 1]) % P;
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		int ans = 0;
		for(int i = 1; i <= n; i ++)
			a[i].read();
		sort(a + 1, a + n + 1);
		int num = 1;
		for(int i = 2; i <= n; i ++)
			if (a[i].x == a[num].x && a[i].y == a[num].y) a[num].k ++;
			else a[++ num] = a[i];
		n = num;
		a[n + 1].k = 0;
		for(int i = 1; i <= n; i ++){
			K = i; int k = a[i].k;
			sort(a + i + 1, a + n + 1, cmp);
			int len = a[i + 1].k;
			for(int j = i + 2; j <= n; j ++)
				if (Cross(a[j] - a[i], a[j - 1] - a[i]) == 0) len += a[j].k;
				else{
					ans = (ans + (LL)(p[len] - 1) * (p[k] - 1) % P) % P;
					len = a[j].k;
				}
			ans = ((LL)ans + (LL)(p[len] - 1) * (p[k] - 1) % P + p[k] - k - 1 + P) % P;
			sort(a + i + 1, a + n + 1);
		}
		printf("%d\n", ans);
	}
	return 0;
}
