#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>

void make(){
	int n = 10;
	printf("%d\n",n);
	for(int i = 1; i <= n; i ++) printf("%c", rand()%10 + '0');
	puts("");
	for(int i = 1; i <= 10; i ++) printf("%d %d\n", rand()% 1000, rand() % 1000);
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++) printf("%d ", rand()% 50);
		puts("");
	}
}

int main(){
	freopen("I.in","w",stdout);
	srand(time(0));
	int T = 10;
	printf("%d\n",T);
	
	while(T --){
		make();
	}
	return 0;
}
