#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>

const int N = 110000;
int n;
std::vector<int> sons[N];

typedef std::pair<int, int> pii;

bool marked[N];
int stree[4 * N];
int dfn;
pii dfo[N];
int rdfo[N];

void dfs(int node)
{
	++dfn;
	dfo[node].first = dfn;
	rdfo[dfn] = node;
	for (unsigned i = 0; i < sons[node].size(); ++i) {
		int son = sons[node][i];
		dfs(son);
	}
	dfo[node].second = dfn;
}

int stree_get(int node, int first, int last, int q)
{
	if (first == q && last == q) {
	//printf("q node %d = %d\n", node, stree[node]);
		return stree[node];
	}
	int mid = first + (last - first) / 2;
	if (mid >= q)
		return std::max(stree[node], stree_get(node * 2, first, mid, q));
	else
		return std::max(stree[node], stree_get(node * 2 + 1, mid + 1, last, q));
}

int query(int node)
{
	return rdfo[stree_get(1, 1, n, dfo[node].first)];
}

void stree_update(int node, int first, int last, int ql, int qr, int v) {
	//printf("REC %d, %d, %d, %d, %d.\n", node, first, last, ql, qr);
	if (first >= ql && last <= qr) {
		//printf("UPD node %d = %d\n", node, v);
		stree[node] = std::max(stree[node], v);
		return;
	}
	int mid = first + (last - first) / 2;
	if (ql <= mid)
		stree_update(node * 2, first, mid, ql, qr, v);
	if (qr > mid)
		stree_update(node * 2 + 1, mid + 1, last, ql, qr, v);
}

void mark(int node)
{
	//if (marked[node])
	//	return;
	//marked[node] = true;
	stree_update(1, 1, n, dfo[node].first, dfo[node].second, dfo[node].first);
}

int main()
{
	int q;
	while (~scanf("%d%d", &n, &q) && n) {
		std::memset(stree, 0, sizeof(stree));
		std::memset(marked, 0, sizeof(marked));
		dfn = 0;
		for (int i = 0; i <= n; ++i) {
			sons[i].clear();
		}
		for (int i = 2; i <= n; ++i) {
			int x;
			scanf("%d", &x);
			sons[x].push_back(i);
		}
		dfs(1);
		long long ans = 0;
		mark(1);
		for (int i = 0; i < q; ++i) {
			char ch;
			do {
				ch = std::getchar();
			} while (std::isspace(ch));
			int node;
			scanf("%d", &node);
			if (ch == 'Q')
				ans += query(node);
			else
				mark(node);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
