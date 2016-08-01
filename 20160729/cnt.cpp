#include<map>
#include<string>
#include<cstdio>
#include<iostream>
using namespace std;

char s[100];
map<string, int>mp;
int main(){
	freopen("tmp.txt","r",stdin);
	freopen("out.txt","w",stdout);
	while(gets(s)){
		string t(s);
		mp[t] ++;
	}
	for(map<string, int> :: iterator it = mp.begin(); it != mp.end(); it ++)
		cout <<"mp[\"" << it -> first << "\"] = " << it -> second <<";" << endl;
	return 0;
}
