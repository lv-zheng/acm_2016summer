#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <queue>


const int N = 32;

#define short int

int n, m;

struct Location {
	short x, y;
};

struct Status {
	Location q, a;
	short qfirst;
	Status(Location _q, Location _a, short _qf):
		q(_q), a(_a), qfirst(_qf)
	{ }
};

short board[N][N];
Location exits[N * N];
Location queen, army;
int ne;

short degree[N][N][N][N][2];
short dp[N][N][N][N][2];
bool fini[N][N][N][N][2];

const short dir[5][2] = {
	{-1,  0},
	{ 1,  0},
	{ 0, -1},
	{ 0,  1},
	{ 0,  0}
};

void work()
{
	std::memset(board, -1, sizeof(board));
	std::memset(degree, 0, sizeof(degree));
	std::memset(dp, 0, sizeof(dp));
	std::memset(fini, 0, sizeof(fini));
	ne = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			char ch;
			do {
				ch = std::getchar();
			} while (std::isspace(ch));
			if (ch == '#') {
				board[i][j] = -1;
			} else {
				if (ch == 'E') {
					exits[ne++] = (Location) {i, j};
				} else if (ch == 'A') {
					army = (Location) {i, j};
				} else if (ch == 'Q') {
					queen = (Location) {i, j};
				}
				board[i][j] = 0;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (board[i][j] == 0) {
				int dg = 1;
				for (int d = 0; d < 4; ++d)
					if (board[i + dir[d][0]][j + dir[d][1]] == 0)
						++dg;
				for (int k = 1; k <= n; ++k) {
					for (int l = 1; l <= m; ++l) {
						if (board[k][l])
							continue;
						degree[i][j][k][l][1] = dg;
						degree[k][l][i][j][0] = dg;
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (board[i][j])
				continue;
			for (int k = 1; k <= n; ++k) {
				for (int l = 1; l <= m; ++l) {
					if (board[k][l])
						continue;
					dp[i][j][k][l][0] = 1;
					dp[i][j][k][l][1] = -1;
				}
			}
		}
	}

	std::queue<Status> q;
	for (int e = 0; e < ne; ++e) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (board[i][j])
					continue;
				if (exits[e].x == i && exits[e].y == j)
					continue;
				//std::cout << "EXIT " << exits[e].x << ' ' << exits[e].y << ' ' << i << ' ' << j << std::endl;
				degree[exits[e].x][exits[e].y][i][j][1] = 0;
				fini[exits[e].x][exits[e].y][i][j][1] = true;
				dp[exits[e].x][exits[e].y][i][j][1] = 1;
				q.push(Status((Location) {exits[e].x, exits[e].y}, (Location) {i, j}, 1));
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (board[i][j])
				continue;
			degree[i][j][i][j][0] = 0;
			degree[i][j][i][j][1] = 0;
			fini[i][j][i][j][0] = true;
			fini[i][j][i][j][1] = true;
			dp[i][j][i][j][0] = -1;
			dp[i][j][i][j][1] = -1;
			q.push(Status((Location) {i, j}, (Location) {i, j}, 1));
			q.push(Status((Location) {i, j}, (Location) {i, j}, 0));
		}
	}
	while (!q.empty()) {
		Status s = q.front();
		q.pop();

		int qx = s.q.x;
		int qy = s.q.y;
		int ax = s.a.x;
		int ay = s.a.y;
		//std::cout << qx << ' ' << qy << ' ' << ax << ' ' << ay << ' ' << s.qfirst << std::endl;

		if (s.qfirst) {
			for (int d = 0; d < 5; ++d) {
				int nax = ax + dir[d][0];
				int nay = ay + dir[d][1];
				if (board[nax][nay])
					continue;
				if (fini[qx][qy][nax][nay][0])
					continue;
				dp[qx][qy][nax][nay][0] = std::min(dp[qx][qy][nax][nay][0], dp[qx][qy][ax][ay][1]);
				//std::cout << "FLUS " << nqx << ' ' << nqy << ' ' << ax << ' ' << ay << ' ' << 0 << ' ' << dp[nqx][nqy][ax][ay][0] << std::endl;
				if (dp[qx][qy][nax][nay][0] == -1 || --degree[qx][qy][nax][nay][0] == 0) {
					fini[qx][qy][nax][nay][0] = true;
					q.push(Status((Location) {qx, qy}, (Location) {nax, nay}, 0));
					//std::cout << "FINI " << nqx << ' ' << nqy << ' ' << ax << ' ' << ay << ' ' << 0 << ' ' << dp[nqx][nqy][ax][ay][0] << std::endl;
				}
			}
		} else {
			for (int d = 0; d < 5; ++d) {
				int nqx = qx + dir[d][0];
				int nqy = qy + dir[d][1];
				if (board[nqx][nqy])
					continue;
				if (fini[nqx][nqy][ax][ay][1])
					continue;
				dp[nqx][nqy][ax][ay][1] = std::max(dp[nqx][nqy][ax][ay][1], dp[qx][qy][ax][ay][0]);
				//std::cout << "FLUS " << qx << ' ' << qy << ' ' << nax << ' ' << nay << ' ' << 1 << ' ' << dp[qx][qy][nax][nay][1] << std::endl;
				if (dp[nqx][nqy][ax][ay][1] == 1 || --degree[nqx][nqy][ax][ay][1] == 0) {
					fini[nqx][nqy][ax][ay][1] = true;
					q.push(Status((Location) {nqx, nqy}, (Location) {ax, ay}, 1));
					//std::cout << "FINI " << qx << ' ' << qy << ' ' << nax << ' ' << nay << ' ' << 1 << ' ' << dp[qx][qy][nax][nay][1] << std::endl;
				}
			}
		}
	}
	if (!fini[queen.x][queen.y][army.x][army.y][1]) {
		puts("Queen can not escape and Army can not catch Queen.");
	} else {
		if (dp[queen.x][queen.y][army.x][army.y][1] > 0) {
			puts("Queen can escape.");
		} else if (dp[queen.x][queen.y][army.x][army.y][1] < 0) {
			puts("Army can catch Queen.");
		} else {
			puts("Queen can not escape and Army can not catch Queen.");
		}
	}
}

signed main()
{
	while (~scanf("%d%d", &m, &n) && n && m) {
		work();
	}
	return 0;
}
