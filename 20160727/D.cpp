#include <functional>
#include <cstdio>
#include <queue>
#include <utility>

typedef double ldb;

int T, n, B;

void work()
{
	//using pfi = std::pair<ldb, int>;
	//std::priority_queue<pfi, std::vector<pfi>, std::greater<pfi> > pq;
	ldb ttl = 0;
	for (int i = 0; i < T; ++i) {
		ldb S;
		int P;
		scanf("%lf%d", &S, &P);
		//if (P != 100)
		//	pq.emplace(S, P);
		ttl += S * (100 - P) * 0.01;
	}
	printf("%.2lf\n", ttl / B);
#if 0
	std::priority_queue<ldb, std::vector<ldb>, std::greater<ldp> > q;
	while (1) {
		while (q.size() < n && pq.size()) {
			auto p = pq.top();
			pq.pop();
			q.insert(p.first * (100 - p.second) * 0.01);
		}
		if (q.size() == 0)
			break;
		int div = q.size();
		ldb s = q.top();
		q.pop();
		ttl += s / (S / div);
	}
#endif
}

int main()
{
	int kase = 0;
	while (~scanf("%d%d%d", &T, &n, &B) && T) {
		++kase;
		printf("Case %d: ", kase);
		work();
		putchar('\n');
	}
	return 0;
}
