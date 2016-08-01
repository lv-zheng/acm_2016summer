#include <cstdio>
#include <cstring>

char buf[1000];
int meetcnt[256];

void work()
{
	std::memset(meetcnt, 0, sizeof(meetcnt));
	int n, k;
	scanf("%d%d%s", &n, &k, buf);
	int ans = 0;
	for (int i = 0; buf[i]; ++i) {
		if (i - k - 1 >= 0)
			--meetcnt[buf[i - k - 1]];
		char ch = buf[i];
		if (meetcnt[ch])
			++ans;
		++meetcnt[ch];
	}
	printf("%d\n", ans);
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; ++i) {
		printf("Case %d: ", i);
		work();
	}
}
