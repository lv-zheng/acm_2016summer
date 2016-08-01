#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const double INF = 1e9;
double f[100000][2], P[7][35];
int v[100000][2];
int U, n, m;
struct aid
{
	int a[5];
	int id()
	{
		int tmp = 0;
		for (int i = 0; i < n; ++ i) tmp = tmp * U + a[i];
		return tmp;
	}
};
bool req[35];
double dfs(int que, aid &x, int correct)
{
	if (que == m)
	{
		int MAX = 0, MIN = U;
		for (int i = 0; i < n; ++ i)
		{
			MAX = max(MAX, x.a[i]);
			MIN = min(MIN, x.a[i]);
		}
		if (MAX - MIN <= 1) return 0.;
		return -INF;
	}
	int id = x.id();
	int &vis = v[id][correct];
	double &ans = f[id][correct];
	if (vis) return ans;
	vis = 1;
	ans = -INF;
	for (int i = 0; i < n; ++ i)
	{
		//if (!x.a[i]) continue;
		if (x.a[i] >= U - 1) continue;
		double tmp;
		x.a[i] ++;
		if (correct || !req[que])
		{
			tmp = (1 + dfs(que + 1, x, 1)) * P[i][que] + dfs(que + 1, x, 0) * (1. - P[i][que]);
		}
		else
		{
			tmp = dfs(que + 1, x, 0);
		}
		if (tmp < 0) tmp = -INF;
		ans = max(ans, tmp);
		x.a[i] --;
	}
	return ans;
}
int main()
{
	int T, zzz = 0;
	scanf("%d", &T);
	while (T --)
	{
		int q;
		scanf("%d%d", &n, &m);
		memset(req, 0, sizeof(req));
		scanf("%d", &q);
		for (int i = 0; i < q; ++ i)
		{
			int x;
			scanf("%d", &x);
			req[x - 1] = 1;
		}
		memset(v, 0, sizeof(v));
		for (int i = 0; i < n; ++ i)
		{
			for (int j = 0; j < m; ++ j) scanf("%lf", & P[i][j]);
		}
		int a1 = m / n, b1 = a1 + 1;
		U = b1 + 1;
		double ans = 0;
		/*for (int mask = 0; mask < (1 << n); ++ mask)
		{
			aid x;
			memset(x.a, 0, sizeof(x.a));
			int cnt = 0;
			for (int i = 0; i < n; ++ i)
			{
				x.a[i] = (mask >> i & 1) ? a1 : b1;
				cnt += x.a[i];
			}*/
			//if (cnt != m) continue;
			//for (int i = 0; i < n; ++ i) printf("%d ", x.a[i]); puts("");
			/*for (int i = 1; i <= m; ++ i)
			{
				//double f1 = dfs(m - 1, x, i, 1);
				//double f2 = dfs(m - 1, x, i, 0);
				//printf("%d : %.2f %.2f\n", i, f1, f2);
				double f = dfs(0, x, i, 1);
				printf("%d : %.2f\n", i, f);
				ans += i * f;
			}*/
		aid x;
		memset(x.a, 0, sizeof(x.a));
			ans = max(ans, dfs(0, x, 1));
		//}
		printf("Case %d: %.4f\n", ++ zzz, ans);
	}
}
