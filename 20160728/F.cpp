#include <cstdio>
#include <cstring>

using namespace std;

const int N = 40;
const int Q = 1200;
const int ROW = 20;
const int COL = 48;

int n, q;

int mapping[256];
char whole[N];
char board[N][ROW][COL];

char query[N];

int occ[ROW][COL];

int main()
{
	scanf("%d%d", &n, &q);
	scanf("%s", whole);
	for (int i = 0; i < n; ++i) {
		mapping[whole[i]] = i;
		for (int r = 0; r < 17; ++r) {
			scanf("%s", board[i][r]);
		}
	}
	for (int p = 0; p < q; ++p) {
		printf("Query %d: ", p + 1);
		scanf("%s", query);
		memset(occ, 0, sizeof(occ));
		int ql = strlen(query);
		for (int i = 0; i < ql; ++i) {
			int which = mapping[query[i]];
			for (int x = 0; x < 16; ++x) {
				for (int y = 0; y < 43; ++y) {
					if (board[which][x][y] == '*')
						++occ[x][y];
				}
			}
		}
		for (int i = 0; i < ql; ++i) {
			int which = mapping[query[i]];
			bool flag = false;
			for (int x = 0; x < 16; ++x) {
				for (int y = 0; y < 43; ++y) {
					if (occ[x][y] == 1 && board[which][x][y] == '*') {
						flag = true;
						goto finish;
					}
				}
			}
finish:
			putchar(flag ? 'Y' : 'N');
		}
		putchar('\n');
	}
	return 0;
}
