#include <cstring>
#include <iomanip>
#include <iostream>

const int N = 6;
const int M = 31;

typedef long double ldb;

int n, m;

ldb poss[N][M];
ldb mem_[1048576][2];

typedef ldb MEM[1048576][2];

struct mem_fuck {
	MEM& operator [] (int) {
		return mem_;
	}
} mem;

bool dep[M];

int per, maxo;

const ldb eps = 1e-9;

void decomp(int *a, int set)
{
	int cnt = 0;
	for (int i = 0; i < 5; ++i) {
		a[i] = set % 16;
		set /= 16;
		if (a[i] > per)
			++cnt;
	}
	a[5] = cnt;
}

int comp(const int *a)
{
	int ans = 0;
	for (int i = 4; i >= 0; --i) {
		ans = ans * 16 + a[i];
	}
	return ans;
}

void printset(int set)
{
	int s[6];
	decomp(s, set);
	for (int i = 0; i < n; ++i) {
		std::cout << s[i] << ' ';
	}
	std::cout << std::endl;
}

ldb dfs(int which, int set, int lastac)
{
		//std::cout << "M " << which << " SET ";
		//printset(set);

	if (which == m) {
		return 0;
	}

	if (mem[which][set][lastac] != -1)
		return mem[which][set][lastac];
	if (!dep[which] && !lastac)
		return dfs(which, set, 1);

	int status[6]; decomp(status, set);
	bool can_over = status[5] < maxo;
	ldb ans = 0;

	for (int i = 0; i < n; ++i) {
		if (status[i] == per + 1 || (status[i] == per && !can_over))
			continue;
		++status[i];
		int ns = comp(status);
		--status[i];
		//std::cout << "NS ";
		//printset(ns);

		if (lastac || !dep[which]) {
			ldb ac = dfs(which + 1, ns, 1);
			ldb wa = dfs(which + 1, ns, 0);
			ldb bns = poss[i][which] * (ac + 1) + (1 - poss[i][which]) * wa;
			ans = std::max(ans, bns);
		} else {
			ldb wa = dfs(which + 1, ns, 0);
			ans = std::max(ans, wa);
		}
	}
#if 0
	std::cout << "DFS " << which << ' ' << set << ' ' << lastac << std::endl;
	for (int i = 0; i < n; ++i) {
		std::cout << status[i] << ' ';
	}
	std::cout << std::endl << "ANS " << ans << ' ' << mppp << std::endl;
#endif
	return mem[which][set][lastac] = ans;
}

void clearall()
{
	std::memset(dep, 0, sizeof(dep));
	//for (int i = 0; i <= m; ++i) {
		for (int j = 0; j < 1048576; ++j) {
			for (int k = 0; k < 2; ++k) {
				mem_[j][k] = -1;
			}
		}
	//}
}

void work()
{
	std::cin >> n >> m;
	clearall();
	int k;
	std::cin >> k;
	for (int i = 0; i < k; ++i) {
		int x;
		std::cin >> x;
		dep[x - 1] = true;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin >> poss[i][j];
		}
	}
	per = m / n;
	maxo = m % n;
	//std::cout << per << ' ' << maxo << std::endl;
	ldb ans = dfs(0, 0, 1);
	std::cout << std::fixed << std::setprecision(4) << ans << std::endl;
}

int main()
{
	std::ios::sync_with_stdio(false);
	int t;
	std::cin >> t;
	for (int i = 1; i <= t; ++i) {
		std::cout << "Case " << i << ": ";
		work();
	}
	return 0;
}
