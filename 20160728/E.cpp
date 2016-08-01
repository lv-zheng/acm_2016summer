#include <algorithm>
#include <iostream>
#include <iomanip>

typedef long double ldb;

int a, b;

const ldb eps = 1e-10;

void work()
{
	ldb pa = 0, pb = 0;
	int baka = a, bakb = b;
	ldb pp = 1;
	ldb ans = 0;
	if (a == 0 || b == 0) {
		ans = 0;
		pa = a != 0 ? 1.0 : 0.0;
		goto finish;
	}
	for (int t = 0; t < 100; ++t) {
		pp *= 0.5L;
		if (a > b) {
			pa += pp;
			int delta = std::min(a, b);
			b += delta;
			a -= delta;
		ans += pp * (t + 1);
		} else if (a < b) {
			pb += pp;
			int delta = std::min(a, b);
			b -= delta;
			a += delta;
		ans += pp * (t + 1);
		} else if (a == b) {
			pa += pp;
			pb += pp;
		ans += 2 * pp * (t + 1);
			break;
		}
	}
finish:
	std::cout
		<< std::fixed << std::setprecision(6) << ans + eps << ' '
		<< std::fixed << std::setprecision(6) << pa + eps << std::endl;
}

int main()
{
	std::ios::sync_with_stdio(false);
	int t;
	std::cin >> t;
	for (int i = 1; i <= t; ++i) {
		std::cin >> a >> b;
		std::cout << "Case " << i << ": ";
		work();
	}
	return 0;
}
