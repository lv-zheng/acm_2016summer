#include <cstring>
#include <iostream>
#include <queue>
#include <utility>

const int N = 6;

struct pii {
	int x, y;
	bool operator == (const pii& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
};

struct pos {
	pii a, b;
	int comp() {
		return a.x * 1000 + a.y * 100 + b.x * 10 + b.y;
	}
	bool operator == (const pos& rhs) const {
		return a == rhs.a && b == rhs.b;
	}
};

inline pos decomp(int c) {
	int ax, ay, bx, by;
	ax = c / 1000;
	c %= 1000;
	ay = c / 100;
	c %= 100;
	bx = c / 10;
	c %= 10;
	by = c;
	return {{ax, ay}, {bx, by}};
}

int maze[N + 2][N + 2];
pii as, at;
int mbze[N + 2][N + 2];
pii bs, bt;

void initmbze()
{
	for (int i = 0; i < N + 2; ++i) {
		for (int j = 0; j < N + 2; ++j) {
			mbze[i][j] = 0x0f;
		}
	}
}

void inputmbze()
{
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			std::cin >> mbze[i][j];
			if (mbze[i][j] & 0x20)
				bs = {i, j};
			if (mbze[i][j] & 0x40)
				bt = {i, j};
		}
	}
}

bool vis[20000];
int from[20000];
int act[20000];

bool valid(int (*mcze)[N + 2], pii p)
{
	return mcze[p.x][p.y] & 0x10;
}

bool valid(pos p)
{
	return valid(maze, p.a) && valid(mbze, p.b);
}

pii gom(int (*mcze)[N + 2], pii p, int dir)
{
	int x = p.x, y = p.y;
	if (dir == 0) {
		// D
		if (!(mcze[x][y] & 0x02))
			++x;
	} else if (dir == 1) {
		// L
		if (!(mcze[x][y] & 0x01))
			--y;
	} else if (dir == 2) {
		// R
		if (!(mcze[x][y] & 0x04))
			++y;
	} else if (dir == 3) {
		// U
		if (!(mcze[x][y] & 0x08))
			--x;
	}
	return {x, y};
}

char actstr[] = "DLRU";

void solve()
{
	std::memset(vis, 0, sizeof(vis));
	std::queue<pos> q;
	q.push({as, bs});
	vis[pos{as, bs}.comp()] = true;
	bool found = false;
	while (!q.empty()) {
		pos p = q.front();
		q.pop();
		if (p.a == at && p.b == bt) {
			found = true;
			break;
		}
		pos npos;

		for (int i = 0; i < 4; ++i) {
			npos.a = gom(maze, p.a, i);
			npos.b = gom(mbze, p.b, i);
			if (valid(npos) && !vis[npos.comp()]) {
				q.push(npos);
				vis[npos.comp()] = true;
				from[npos.comp()] = p.comp();
				act[npos.comp()] = i;
			}
		}
	}
	if (!found) {
		std::cout << -1 << std::endl;
		return;
	}
	std::vector<char> ans;
	pos p = {at, bt};
	while (!(p == pos{as, bs})) {
		ans.push_back(actstr[act[p.comp()]]);
		p = decomp(from[p.comp()]);
	}
	for (int i = (int) ans.size() - 1; i >= 0; --i) {
		std::cout << ans[i];
	}
	std::cout << std::endl;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int t;
	std::cin >> t;
	initmbze();
	inputmbze();
	std::memcpy(maze, mbze, sizeof(maze));
	as = bs;
	at = bt;
	for (int i = 1; i < t; ++i) {
		inputmbze();
		solve();
		std::memcpy(maze, mbze, sizeof(maze));
		as = bs;
		at = bt;
	}
	return 0;
}
