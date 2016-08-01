#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long LL;
LL x;
char s[1000];
int main(){
	while(scanf("%s", s) == 1){
		if (strlen(s) > 19){
			puts("TAT");
			continue;
		}
		sscanf(s, "%I64d", &x);
		if (x == 1){
			puts("0");
			continue;
		}
		bool yes = 0;
		for(int j = 1; j <= 5; j ++){
			x = sqrt(x);
			if (x == 1){
				printf("%d\n", j);
				yes = 1;
				break;
			}
		}
		if (!yes) puts("TAT");
	}
	return 0;
}
