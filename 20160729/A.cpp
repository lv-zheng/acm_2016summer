#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int P = 1e9 + 7;
const int N = 100010;
char s[N], t[N];
int f[N], nxt[N], n, m;
bool yes[N];

void getnext(char *s, int n){
	int j = 1;
	nxt[1] = nxt[2] = 1;
	for(int i = 2; i <= n; i ++){
		while(s[i] != s[j] && j != 1 && j) j = nxt[j];
		if (s[i] == s[j]){
			nxt[i + 1] = j + 1;
			j ++;
		}else nxt[i + 1] = j;
	}
//	printf("nxt : "); for(int i = 1; i <= n; i ++) printf("%d ", nxt[i]);
}
int main(){
	int T, cs = 0;
	scanf("%d", &T);
	while(cs < T){
		printf("Case #%d: ", ++ cs);
		scanf("%s", s + 1); n = strlen(s + 1);
		scanf("%s", t + 1); m = strlen(t + 1);
		memset(yes, 0, sizeof yes);
		memset(nxt, 0, sizeof nxt);
		getnext(t, m);
		int j = 1;
		for(int i = 1; i <= n; i ++){
			while(s[i] != t[j] && j != 1 && j) j = nxt[j];
			if (s[i] == t[j]) j ++;
			if (j == m + 1) yes[i] = 1, j = nxt[j];
		}
		f[0] = 1;
		for(int i = 1; i <= n; i ++){
			f[i] = f[i - 1];
			if (yes[i]){
				f[i] += f[i - m];
				if (f[i] >= P) f[i] -= P;
			}
		}
		printf("%d\n", f[n]);
	}
	return 0;
}
