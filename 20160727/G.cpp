//#pragma GCC optimize("O2")

#include <algorithm>
#include <cstdio>
#include <cstring>

#if 0
const int N = 384;
const int MV1 = 512;
const int MV2 = 64;
#else
const int N = 302;
const int MV1 = 502;
const int MV2 = 52;
#endif

int V1, V2, n;

struct Good {
	int wei, hap, must;
	bool operator < (const Good& rhs) const {
		return must > rhs.must;
	}
};

Good goods[N];

int mem_[2][2][MV1][MV2];

void clearall()
{
	std::memset(mem_, -1, sizeof(mem_));
}

#if 0
inline int& mem(which, int bonus, int v1, int v2)
{
	return mem_[which][bonus][v1][v2];
}

int bag(int which, int bonus, int v1, int v2)
{
	if (which == n)
		return 0;

	int& res = mem(which, bonus, v1, v2);
	if (res != -1)
		return res;

	int wei = goods[which].wei;
	int hap = goods[which].hap;
	int ans = -2;
	if (wei <= v1) {
		int chd = bag(which + 1, bonus, v1 - wei, v2);
		if (chd != -2)
			ans = std::max(ans, hap + chd);
	}
	if (wei <= v2) {
		int chd = bag(which + 1, bonus, v1, v2 - wei);
		if (chd != -2)
			ans = std::max(ans, hap + chd);
	}
	if (bonus) {
		int chd = bag(which + 1, 0, v1, v2);
		if (chd != -2)
			ans = std::max(ans, hap + chd);
	}

	if (!goods[which].must)
		ans = std::max(ans, bag(which + 1, bonus, v1, v2));

	return res = ans;
}
#endif

void work()
{
	//clearall();
	for (int i = 0; i < n; ++i) {
		scanf("%d%d%d", &goods[i].wei, &goods[i].hap, &goods[i].must);
	}
	std::sort(goods, goods + n);
	std::memset(mem_, -1, sizeof(mem_));
	mem_[1][0][0][0] = 0;
	for (int i = 0; i < n; ++i) {
		int wei = goods[i].wei;
		int hap = goods[i].hap;
		bool must = goods[i].must;
		int now = i & 1;
		//std::memset(mem_ + now, 0, sizeof (mem_[0]));
		int prev = now ^ 1;
		for (int b = 1; b >= 0; --b) {
			for (int p = V1; p >= 0; --p) {
				for (int q = V2; q >= 0; --q) {
					int& m = mem_[now][b][p][q];
					int ans;
					if (must)
						ans = -1;
					else
						ans = mem_[prev][b][p][q];
					if (p - wei >= 0) {
						int chd = mem_[prev][b][p - wei][q];
						if (chd != -1)
							ans = std::max(ans, chd + hap);
					}
					if (q - wei >= 0) {
						int chd = mem_[prev][b][p][q - wei];
						if (chd != -1)
							ans = std::max(ans, chd + hap);
					}
					if (b == 1) {
						int chd = mem_[prev][0][p][q];
						if (chd != -1)
							ans = std::max(ans, chd + hap);
					}
					m = ans;
				}
			}
		}
	}
	
	int bns = -1;
	for (int b = 0; b <= 1; ++b) {
		for (int p = 0; p <= V1; ++p) {
			for (int q = 0; q <= V2; ++q) {
				bns = std::max(bns, mem_[(n - 1) & 1][1][p][q]);
				bns = std::max(bns, mem_[(n - 1) & 1][0][p][q]);
			}
		}
	}
	//int ans = bag(0, 1, V1, V2);
	//printf("%d\n", ans == -2 ? -1 : ans);
	printf("%d\n", bns);
}


int main()
{
	int kase = 0;
	while (~scanf("%d%d%d", &V1, &V2, &n) && n) {
		++kase;
		printf("Case #%d: ", kase);
		work();
		puts("");
	}
	return 0;
}
