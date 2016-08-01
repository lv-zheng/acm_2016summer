#include <cstdio>
#include <cstring>
#include <tuple>

const int N = 3000;

const int RR = 120000;

int n, R;

typedef std::tuple<char, int, int> Rest;

Rest res[RR];

int seq[N];
int nseq;
bool onst[N];
bool fini[N];

int ghead[N];
int gnext[RR];
int gto[RR];
int gg;

void clearall()
{
	std::memset(seq, 0, sizeof(seq));
	nseq = 0;
	std::memset(onst, 0, sizeof(onst));
	std::memset(fini, 0, sizeof(fini));

	std::memset(ghead, 0, sizeof(ghead));
	gg = 0;
}

void adde(int x, int y)
{
	++gg;
	gnext[gg] = ghead[x];
	ghead[x] = gg;
	gto[gg] = y;
}

bool topodfs(int node)
{
	onst[node] = true;
	for (int e = ghead[node]; e; e = gnext[e]) {
		int son = gto[e];
		if (onst[son])
			return false;
		if (fini[son])
			continue;
		bool r = topodfs(son);
		if (!r)
			return false;
	}
	seq[nseq++] = node;
	onst[node] = false;
	fini[node] = true;
	return true;
}

bool topo()
{
	for (int i = 0; i < n * 2; ++i) {
		if (!fini[i]) {
			bool r = topodfs(i);
			if (!r)
				return false;
		}
	}
	return nseq == n * 2;
}

int result[3][N];

void clearresult()
{
	std::memset(result, 0, sizeof(result));
}

void collect(int p)
{
	for (int i = 0; i < n * 2; ++i) {
		result[p][seq[n * 2 - i - 1]] = i;
	}
}

void printresult(bool ok)
{
	if (!ok) {
		puts("IMPOSSIBLE");
		return;
	}
	puts("POSSIBLE");
	for (int i = 0; i < n; ++i) {
		printf("%d %d %d %d %d %d\n",
				result[0][i << 1],
				result[1][i << 1],
				result[2][i << 1],
				result[0][(i << 1) + 1],
				result[1][(i << 1) + 1],
				result[2][(i << 1) + 1]
		);
	}
}

void work()
{
	for (int i = 0; i < R; ++i) {
		 char ch = 0;
		 while (!std::isalpha(ch))
			 ch = getchar();
		 int x, y;
		 scanf("%d%d", &x, &y);
		 res[i] = Rest{ch, x - 1, y - 1};
	}

	clearresult();

	bool ok;

	// x
	clearall();
	for (int i = 0; i < n; ++i)
		adde(i << 1, (i << 1) + 1);
	for (int i = 0; i < R; ++i) {
		if (std::get<0>(res[i]) == 'I') {
			adde(std::get<1>(res[i]) << 1, (std::get<2>(res[i]) << 1) + 1);
			adde(std::get<2>(res[i]) << 1, (std::get<1>(res[i]) << 1) + 1);
		} else if (std::get<0>(res[i]) == 'X') {
			adde((std::get<1>(res[i]) << 1) + 1, std::get<2>(res[i]) << 1);
		}
	}
#if 0
	for (int i = 0; i < n * 2; ++i) {
		printf("%d", i);
		for (int e = ghead[i]; e; e = gnext[e])
			printf(" %d", gto[e]);
		puts("");
	}
#endif
	ok = topo();
	if (!ok)
		goto finish;
	collect(0);

	// y
	clearall();
	for (int i = 0; i < n; ++i)
		adde(i << 1, (i << 1) + 1);
	for (int i = 0; i < R; ++i) {
		if (std::get<0>(res[i]) == 'I') {
			adde(std::get<1>(res[i]) << 1, (std::get<2>(res[i]) << 1) + 1);
			adde(std::get<2>(res[i]) << 1, (std::get<1>(res[i]) << 1) + 1);
		} else if (std::get<0>(res[i]) == 'Y') {
			adde((std::get<1>(res[i]) << 1) + 1, std::get<2>(res[i]) << 1);
		}
	}
	ok = topo();
	if (!ok)
		goto finish;
	collect(1);

	// z
	clearall();
	for (int i = 0; i < n; ++i)
		adde(i << 1, (i << 1) + 1);
	for (int i = 0; i < R; ++i) {
		if (std::get<0>(res[i]) == 'I') {
			adde(std::get<1>(res[i]) << 1, (std::get<2>(res[i]) << 1) + 1);
			adde(std::get<2>(res[i]) << 1, (std::get<1>(res[i]) << 1) + 1);
		} else if (std::get<0>(res[i]) == 'Z') {
			adde((std::get<1>(res[i]) << 1) + 1, std::get<2>(res[i]) << 1);
		}
	}
	ok = topo();
	if (!ok)
		goto finish;
	collect(2);


finish:
	printresult(ok);
}

int main()
{
	int kase = 0;
	while (~scanf("%d%d", &n, &R) && n) {
		++kase;
		printf("Case %d: ", kase);
		work();
		puts("");
	}
	return 0;
}
