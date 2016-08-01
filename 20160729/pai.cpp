#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	int cs = 0;
	while(1){
		system("./gen > I.in");
		system("./I < I.in > I.out");
		system("./II < I.in > I.ans");
		if (system("diff I.out I.ans > NULL")){
			puts("WA!!!");
			break;
		}
		printf("AC : %d\n", ++ cs);
		if (cs == 1000) break;
	}
	return 0;
}
