#include <cstdio>
#include <algorithm>
#include <vector>


using namespace std;

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; ++i) {
		int n, m;
		scanf("%d%d", &n, &m);
		std::vector<int> v;
		for (int i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			v.push_back(x);
		}
		std::sort(v.begin(), v.end());
		for (int i = 0; i < m; ++i) {
			int x;
			scanf("%d", &x);
			int ans = v[0];
			for (int i = 1; i < (int) v.size(); ++i) {
				if (__builtin_popcount(v[i] ^ x) < __builtin_popcount(ans ^ x))
					ans = v[i];
			}
			printf("%d\n", ans);
		}
	}
}
