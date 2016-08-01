#pragma GCC optimize("O2")

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>

const int N = 600;
const int M = 62000;

int n, m;

int head[N];

bool hasedge[N][N];

struct Edge {
	int next, dest;
} edge[M];

int ne;
int timer;

struct Tarjan {
	int idx, low;
	bool onst;
} tar[N];

int st[N];
int stp;
int scc[N];
int sccc;

bool adde(int x, int y)
{
	if (hasedge[x][y])
		return false;
	hasedge[x][y] = true;
	++ne;
	edge[ne].next = x[head];
	x[head] = ne;
	edge[ne].dest = y;
	return true;
}

void tarjan(int node)
{
	tar[node].idx = tar[node].low = ++timer;
	st[stp++] = node;
	tar[node].onst = true;
	for (int e = node[head]; e; e = edge[e].next) {
		int son = edge[e].dest;
		if (!tar[son].idx) {
			tarjan(son);
			tar[node].low = std::min(tar[node].low, tar[son].low);
		} else if (tar[son].onst) {
			tar[node].low = std::min(tar[node].low, tar[son].idx);
		}
	}

	if (tar[node].low == tar[node].idx) {
		int next;
		++sccc;
		do {
			next = st[--stp];
			tar[next].onst = false;
			scc[next] = sccc;
		} while (node != next);
	}
}

void initall()
{
	ne = 0;
	std::memset(head, 0, sizeof(head));
	//std::memset(edge, 0, sizeof(edge));
	std::memset(hasedge, 0, sizeof(hasedge));
}

int a[M], b[M], c[M];

bool validate(int mm)
{
	initall();
	for (int i = 0; i < mm; ++i) {
		bool ad;
		if (c[i] == 0) {
			ad = adde(a[i] << 1, (b[i] << 1) + 1);
			ad = adde(b[i] << 1, (a[i] << 1) + 1);
		} else if (c[i] == 1) {
			ad = adde(a[i] << 1, b[i] << 1);
			ad = adde(b[i] << 1, a[i] << 1);
			ad = adde((a[i] << 1) + 1, (b[i] << 1) + 1);
			ad = adde((b[i] << 1) + 1, (a[i] << 1) + 1);
		} else {
			ad = adde((a[i] << 1) + 1, b[i] << 1);
			ad = adde((b[i] << 1) + 1, a[i] << 1);
		}
	}

	std::memset(tar, 0, sizeof(tar[0]) * (n * 2 + 10));
	std::memset(scc, 0, sizeof(scc[0]) * (n * 2 + 10));
	stp = 0;
	timer = sccc = 0;
	for (int i = 0; i < n * 2; ++i) {
		if (!tar[i].idx)
			tarjan(i);
	}
	for (int i = 0; i < n; ++i) {
		if (scc[i << 1] == scc[(i << 1) + 1])
			return false;
	}
	return true;
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; ++i) {
		scanf("%d%d", &n, &m);
		initall();
		for (int i = 0; i < m; ++i) {
			scanf("%d%d%d", &a[i], &b[i], &c[i]);
		}
		int l = 0, r = m,mid, ans = 0;
		while(l <= r){
			mid = (l + r) >> 1;
			if (validate(mid)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", ans);
#if 0
			for (int i = 0; i < 5; ++i) {
				std::cout << i << "  ";
				for (int e = i[head]; e; e = edge[e].next) {
					std::cout << edge[e].dest << ' ';
				}
				std::cout << std::endl;
			}
			for (int i = 0; i < 5; ++i) {
				std::cout << scc[i] << ' ';
			} std::cout << std::endl;
			for (int i = 0; i < 5; ++i) {
				std::cout << tar[i].idx << ' ' << tar[i].low << std::endl;;
			}
			std::cout << std::endl;
#endif

	}
	return 0;
}
