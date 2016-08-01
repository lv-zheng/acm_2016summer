#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 111;

struct node {
	int cap, time, now;
	double v;
} a[N];

int chps, n, q;
const double eps = 1e-9;

double work(int x) {
	double l = 0, r = 111111, mid;
	while (r - l >= eps) {
		mid = (l + r) / 2.0;
		double s = x * chps * mid;
		for (int i = 1; i <= n; ++i) {
			s -= max(0.0, a[i].v * mid - a[i].now);
		}
		if (s <= eps) {
			r = mid;
		} else {
			l = mid;
		}
	}
	return mid;
}

int main() {
	int T = 0;
	while (scanf("%d%d", &n, &q) != EOF && n && q) {
		scanf("%d", &chps);
		printf("Case %d:\n", ++T);
		double s = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d", &a[i].cap, &a[i].time, &a[i].now);
			s += (a[i].v = (double)a[i].cap / (double)a[i].time);
		}
		int t = (int) s / chps;
		if (t * chps < s) {
			++t;
		}
		printf("%d\n", t);
		for (int i = 1; i <= q; ++i) {
			int x;
			scanf("%d", &x);
			double ans = work(x);
			if (ans > 100000) {
				ans = -1;
			}
			printf("%.3f\n", ans);
		}
	}
}
