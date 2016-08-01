#include <algorithm>
#include <cstdio>

typedef double ldb;

const ldb eps = 1e-8;
const ldb epshalf = eps / 2;

int n;

const int N = 10010;

ldb arg[N][3];

ldb eval(ldb x)
{
	ldb ans = -1e20;
	for (int i = 0; i < n; ++i) {
		ldb v = arg[i][0] * x * x + arg[i][1] * x + arg[i][2];
		ans = std::max(ans, v);
	}
	return ans;
}

void work()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%lf%lf%lf", arg[i] + 0, arg[i] + 1, arg[i] + 2);
	}
	ldb lo = 0;
	ldb hi = 1000;

	//ldb evall = eval(lo);
	//ldb evalh = eval(hi);

	ldb el = 0;
	ldb er = 1;
	//int cnt = 0;
	while (hi - lo > epshalf || std::abs(el - er) > epshalf) {
		ldb left = lo + (hi - lo) * 0.45;
		ldb right = hi - (hi - lo) * 0.45;
		el = eval(left);
		er = eval(right);
		//printf("l %.10lf = %.10lf\n", left, el);
		//printf("r %.10lf = %.10lf\n", right, er);
		if (el < er) {
			hi = right;
			//evalh = er;
		} else {
			lo = left;
			//evall = el;
		}
		//++cnt;
	}
	//printf("%d\n", cnt);
	printf("%.4lf\n", eval(lo) + eps);
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; ++i) {
		work();
	}
}
