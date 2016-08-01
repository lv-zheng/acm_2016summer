#include <cstdio>
#include <cstring>
#include <cmath>

typedef long double ldb;
const ldb eps = 1e-12;

int n;

int arr[356];
int occ[300];

ldb eval(int s, int a, int c)
{
	std::memset(occ, 0, sizeof(occ));
	int r = s;
	r = (a * r + c) % 256;
	for (int i = 0; i < n; ++i) {
		int ch = (arr[i] + r) % 256;
		++occ[ch];
		r = (a * r + c) % 256;
	}
	ldb ans = 0;
	for (int i = 0; i < 256; ++i) {
		if (occ[i] == 0)
			continue;
		ans += (ldb) occ[i] / n * log((ldb) occ[i] / n);
	}
	return -ans;
}

void work()
{
	for (int i = 0; i < n; ++i) {
		scanf("%d", arr + i);
	}
	int anss = -1;
	int ansa = -1;
	int ansc = -1;
	ldb anse = 1e200L;
	for (int s = 0; s < 16; ++s) {
		for (int a = 0; a < 16; ++a) {
			for (int c = 0; c < 16; ++c) {
				ldb v = eval(s, a, c);
				//printf("%d %d %d = %.15lf\n", s, a, c, (double) v);
				if (s + a + c == 0 || v + eps < anse) {
					anss = s;
					ansa = a;
					ansc = c;
					anse = v;
				}
			}
		}
	}
	printf("%d %d %d\n", anss, ansa, ansc);
}

int main()
{
	while (~scanf("%d", &n) && n) {
		work();
	}
	return 0;
}
