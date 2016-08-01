#include <cstdio>
#include <cstring>

int t, n;

int sleep[32];
bool meeting[3000];

bool test(int start, int fini) {
	int c = start;
	while (c < fini) {
		for (int i = 0; i < t && c < fini; ++i) {
			for (int h = 0; h < 24 && c < fini; ++h) {
				if (meeting[c] && h < sleep[i])
					return false;
				++c;
			}
		}
	}
	return true;
}

void work()
{
	for (int i = 0; i < t; ++i) {
		scanf("%d", sleep + i);
	}
	scanf("%d", &n);
	std::memset(meeting, 0, sizeof(meeting));
	for (int i = 0; i < n; ++i) {
		int day, hour;
		scanf("%d %d", &day, &hour);
		meeting[(day - 1) * 24 + hour] = true;
	}
	int fini = n * 24;
	int ans = -1;
	while (fini > 0) {
		++ans;
		for (int i = 0; i < fini; i += 24) {
			if (test(i, fini)) {
				fini = i;
				//printf("OK %d\n", fini);
				break;
			}
		}
	}
	printf("%d\n", ans);
}

int main()
{
	while (~scanf("%d", &t) && t) {
		work();
	}
	return 0;
}
