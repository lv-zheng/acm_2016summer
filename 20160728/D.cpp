#include <cmath>
#include <iomanip>
#include <iostream>

const int N = 110;

typedef double ldb;

int n, q;

int Chps;

struct PC {
	ldb cur;
	ldb rate;
} pc[N];

const ldb eps = 1e-8;

int calcmin(ldb sigmarate)
{
	return std::ceil(sigmarate / Chps) + eps;
}

ldb calc(int x, ldb rem, ldb drate)
{
	int crate = Chps * x;
	ldb ccrate = drate - crate;
	if (ccrate < eps)
		return -1.0L;
	ldb ans = rem / ccrate;
	if (ans > 100000)
		return -1;
	else
		return ans;
}

void work()
{
	std::cin >> Chps;
	ldb sigmarema = 0;
	ldb sigmarate = 0;
	int zeros = 0;
	for (int i = 0; i < n; ++i) {
		int x, y, z;
		std::cin >> x >> y >> z;
		pc[i].cur = z;
		if (z == 0)
			++zeros;
		pc[i].rate = (ldb) x / y;
		sigmarema += z;
		sigmarate += pc[i].rate;
	}

	int mc = std::max(calcmin(sigmarate), 0);//zeros);
	std::cout << mc << std::endl;

	for (int i = 0; i < q; ++i) {
		int x;
		std::cin >> x;
		if (x == 0 || (sigmarema == 0 && sigmarate >= Chps * x))
			std::cout << "0.000" << std::endl;
		else if (x >= mc) 
			std::cout << "-1.000" << std::endl;
		//else if (x < zeros)
		//	std::cout << "0.000" << std::endl;
		else
			std::cout << std::fixed << std::setprecision(3) << calc(x, sigmarema, sigmarate) << std::endl;;
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	int kase = 0;
	while (std::cin >> n >> q && n) {
		++kase;
		std::cout << "Case " << kase << ":" << std::endl;
		work();
	}
	return 0;
}
