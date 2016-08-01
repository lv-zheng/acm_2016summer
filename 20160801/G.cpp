#include <cassert>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <iomanip>

typedef long double ldb;

const ldb eps = 1e-14;
const int N = 128;

int sign[N];
int route[N][N];
int dist[N][N];

const int inf = 0x3c3cdead;

#define fma dsfjsd
ldb fma[N][N];

int n, s, t;

void gauss(ldb a[N][N], int n){
	using namespace std;
	for(int i = 1; i <= n; i ++){
		int r = i;
		for(int j = i; j <= n; j ++)
			if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
		if (r != i) for(int j = 1; j <= n + 1; j ++) swap(a[i][j], a[r][j]);
		if (fabs(a[i][i]) < eps) continue;
		for(int j = 1; j <= n; j ++) if (i != j)
			for(int k = n + 1; k >= i; k --)
				a[j][k] -= a[j][i] / a[i][i] * a[i][k];
	}
}

void work()
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			fma[i][j] = 0;
		}
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", sign + i);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			int x;
			scanf("%d", &x);
			dist[i][j] = (x ? x : inf);
			route[i][j] = x;
		}
	}
	// Floyd
	for (int i = 1; i <= n; ++i) {
		dist[i][i] = 0;
	}
	for (int k = 1; k <= n; ++k) {
		for (int u = 1; u <= n; ++u) {
			for (int v = 1; v <= n; ++v) {
				if (dist[u][k] + dist[k][v] <= dist[u][v]) {
					dist[u][v] = dist[u][k] + dist[k][v];
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (i == t) {
			fma[i][i] = 1;
		} else if (dist[s][i] >= inf || dist[i][t] >= inf) {
			fma[i][n + 1] = 0;
			fma[i][i] = 1;
		} else if (!sign[i]) {
			int ndest = 0;
			for (int d = 1; d <= n; ++d) {
				if (route[i][d])
					++ndest;
			}
			assert(ndest);
			ldb consts = 0;
			for (int d = 1; d <= n; ++d) {
				if (route[i][d]) {
					fma[i][d] = (ldb) 1 / ndest;
					consts += route[i][d];
				}
			}
			fma[i][n + 1] = - (ldb) consts / ndest;
			fma[i][i] -= 1;
		} else {
			int ndest = 0;
			for (int d = 1; d <= n; ++d) {
				if (route[i][d] && dist[i][t] == route[i][d] + dist[d][t])
					++ndest;
			}
			assert(ndest);
			ldb consts = 0;
			for (int d = 1; d <= n; ++d) {
				if (route[i][d] && dist[i][t] == route[i][d] + dist[d][t]) {
					fma[i][d] = (ldb) 1 / ndest;
					consts += route[i][d];
				}
			}
			fma[i][n + 1] = - (ldb) consts / ndest;
			fma[i][i] -= 1;
		}
	}

	if (dist[s][t] >= inf) {
		std::cout << "impossible" << std::endl;
	} else {
		gauss(fma, n);
		ldb ans = fma[s][n + 1] / fma[s][s];
		std::cout << std::fixed << std::setprecision(12) << ans << std::endl;
	}

#if 0
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n + 1; ++j) {
			std::cout << std::fixed << std::setprecision(5) << std::setw(9) << fma[i][j];
		}
		std::cout << std::endl;
	}
#endif
}

int main()
{
	while (~scanf("%d%d%d", &n, &s, &t) && n) {
		work();
	}
	return 0;
}
