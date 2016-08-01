#include<iostream>
#include<cstdio>
#include<string>
#include<map>
using namespace std;

int T;
char s[100];
map<string,int> mp;

int main(){
    scanf("%d",&T); getchar();
    mp["Baltimore Bullets"] = 1;
    mp["Boston Celtics"] = 17;
    mp["Chicago Bulls"] = 6;
    mp["Cleveland Cavaliers"] = 1;
    mp["Dallas Mavericks"] = 1;
    mp["Detroit Pistons"] = 3;
    mp["Golden State Warriors"] = 2;
    mp["Houston Rockets"] = 2;
    mp["L.A. Lakers"] = 11;
    mp["Miami Heat"] = 3;
    mp["Milwaukee Bucks"] = 1;
    mp["Minneapolis Lakers"] = 5;
    mp["New York Knicks"] = 2;
    mp["Philadelphia 76ers"] = 2;
    mp["Philadelphia Warriors"] = 2;
    mp["Portland Trail Blazers"] = 1;
    mp["Rochester Royals"] = 1;
    mp["San Antonio Spurs"] = 5;
    mp["Seattle Sonics"] = 1;
    mp["St. Louis Hawks"] = 1;
    mp["Syracuse Nats"] = 1;
    mp["Washington Bullets"] = 1;
    for(int i=1;i<=T;++i){
        gets(s);
        string t(s);
//        cout << t << endl;
        printf("Case #%d: ",i);
        printf("%d\n",mp[t]);
    }
    return 0;
}
