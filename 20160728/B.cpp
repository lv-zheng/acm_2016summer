#include <cstdio>
#include <cstring>
#include <stack>

char buf[256];
int degree[256];

void work()
{
	scanf("%s", buf);
	std::stack<char> st;
	std::memset(degree, 0, sizeof(degree));
	if (strlen(buf) == 2) {
		degree[buf[0]] = 1;
		goto finish;
	}
	for (char *p = buf; *p; ++p) {
		if (st.empty() || *p != st.top()) {
			//++degree[*p];
			if (!st.empty())
				++degree[st.top()];
			st.push(*p);
		} else {
			++degree[st.top()];
			st.pop();
		}
	}
	--degree[buf[0]];
finish:
	for (int i = 'A'; i <= 'Z'; ++i) {
		if (degree[i])
			printf("%c = %d\n", (char) i, degree[i]);
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; ++i) {
		printf("Case %d\n", i);
		work();
	}
	return 0;
}
