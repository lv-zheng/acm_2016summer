#include<cstdio>
#include<map>
#include<bitset>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 110;
const int M = 4010;
const int INF = 1e9;
int ans, flow;
struct edge{int from, to, v, c;};

edge E[M];
int head[N], nxt[M], cnt;
void ins(int x, int y, int z, int c){
	E[++ cnt] = (edge){x, y, z, c};
	nxt[cnt] = head[x]; head[x] = cnt;
}
void add(int x, int y, int z, int c){
	ins(x, y, z, c); ins(y, x, 0, -c);
}
int from[N], Q[M], d[N], S, T;
bool inq[N];
bool spfa(){
	int l = 0, r = -1;
	for(int i = 0; i <= T; i ++) d[i] = INF;
	d[S] = 0; Q[++ r] = S; inq[S] = 1;
	while(l <= r){
		int x = Q[l ++];
		inq[x] = 0;
		for(int i = head[x]; i; i = nxt[i])
			if (E[i].v > 0 && d[x] + E[i].c < d[E[i].to]){
				d[E[i].to] = d[x] + E[i].c;
				from[E[i].to] = i;
				if (!inq[E[i].to]){
					Q[++ r] = E[i].to;
					inq[E[i].to] = 1;
				}
			}
	}
	return d[T] != INF;
}
void mcf(){
	int x = INF;
	for(int i = from[T]; i; i = from[E[i].from])
		x = min(x, E[i].v);
	for(int i = from[T]; i; i = from[E[i].from]){
		E[i].v -= x;
		E[i ^ 1].v += x;
	}
	flow += x;
	ans += x * d[T];
}

bitset<10010> t[30], w[30];
int n, k, m; 
map<short, short> mp;


void build(int n, int m, int k){
	S = 0; T = n + m + 1;
	memset(head, 0, sizeof head);
	cnt = 1;
	ans = flow = 0;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			add(i, n + j, 1, -(t[i] & w[j]).count() );
	for(int i = 1; i <= n; i ++)
		add(S, i, 1, 0);
	for(int i = 1; i <= m; i ++)
		add(n + i, T, 1, 0);
	while(spfa()) mcf();
	printf("%.4f\n",-1.0 * (double)ans/k);
}

char s[10];
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d", &n, &k, &m);
		mp.clear();
		int x, tot = 0;
		for(int i = 1; i <= 26; i ++) t[i] = 0;
		for(int i = 0; i < n; i ++){
			scanf("%s", s);
			x = s[0] - 'A';
			if (!mp[x]) mp[x] = ++ tot;
			x = mp[x];
			t[x][i] = 1;
		}
		for(int i = 1; i <= m; i ++){
			x = tot = 0;
			mp.clear();
			for(int j = 1; j <= 26; j ++) w[j] = 0;
			for(int j = 0; j < n; j ++){
				scanf("%s", s);
				x = s[0] - 'A';
				if (!mp[x]) mp[x] = ++ tot;
				x = mp[x];
				w[x][j] = 1;
			}
			build(k, tot, n);
		}
	}
	return 0;
}

