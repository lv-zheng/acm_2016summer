#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

const int N = 2500010;
int t[N], n, m, a[1010], cnt;
struct Rec{
	int x1, y1, x2, y2;
}rec[N];
struct ques{
	int l, r, y, rank, id;
}q[N];
bool operator < (const ques &a, const ques &b){
	return a.y < b.y || (a.y == b.y && a.rank < b.rank);
}

void build(){
	cnt = 0;
	int sm[2];
	for(int i = 0; i < n; i ++){
		sm[0] = sm[1] = 0;
		++ cnt;
		rec[cnt].x1 = rec[cnt].x2 = rec[cnt].y1 = rec[cnt].y2 = 0;
		if (i > 0){
			if (i & 1) rec[cnt].x2 += a[i - 1];
			else rec[cnt].y2 += a[i - 1];
		}
		if (i < n){
			if (i & 1) rec[cnt].y2 += a[i];
			else rec[cnt].x2 += a[i];
		}
		for(int j = i; j < n; j ++){
			sm[j & 1] += a[j];
			cnt ++;
			rec[cnt].x2 = rec[cnt].x1 = sm[0];
			rec[cnt].y2 = rec[cnt].y1 = sm[1];
			if (i > 0){
				if (i & 1) rec[cnt].x2 += a[i - 1];
				else rec[cnt].y2 += a[i - 1];
			}
			if (j < n - 1){
				if (j & 1) rec[cnt].x2 += a[j + 1];
				else rec[cnt].y2 += a[j + 1];
			}
		}
	}
	for(int i = 1; i <= cnt; i ++){
		q[m + i] = (ques){rec[i].x1, rec[i].x2 + 1, rec[i].y1, 1, 0};
		q[m + cnt + i] = (ques){rec[i].x1, rec[i].x2 + 1, rec[i].y2, 3, 0};
	}
	cnt = cnt * 2 + m;
}

int v[N], num;
bool ans[500010];
inline int lowbit(int x){return x & (-x);}
void add(int x, int v){
	for(int i = x; i <= num; i += lowbit(i)) t[i] += v;
}
int sum(int x){
	int r = 0;
	for(int i = x; i; i -= lowbit(i)) r += t[i];
	return r;
}
void solve(){
	num = 0;
	for(int i = 1; i <= cnt; i ++){
		v[++ num] = q[i].l;
		if (q[i].rank != 2) v[++ num] = q[i].r;
	}
	sort(v + 1, v + num + 1);
	num = unique(v + 1, v + num + 1) - v - 1;
	for(int i = 1; i <= cnt; i ++){
		q[i].l = lower_bound(v + 1, v + num + 1, q[i].l) - v;
		if (q[i].rank != 2)
			q[i].r = lower_bound(v + 1, v + num + 1, q[i].r) - v;
		else q[i].r = 0;
	}
	sort(q + 1, q + cnt + 1);
	for(int i = 1; i <= cnt; i ++){
		if (q[i].rank == 1){
			add(q[i].l, 1);
			add(q[i].r, -1);
		}else if (q[i].rank == 2){
			ans[q[i].id] = (sum(q[i].l) > 0);
		}else{
			add(q[i].l, -1);
			add(q[i].r, 1);
		}
	}
	for(int i = 1; i <= m; i ++) printf("%d", ans[i]);
	puts("");
}
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i ++) scanf("%d", &a[i]);
		for(int i = 1; i <= m; i ++){
			scanf("%d%d", &q[i].l, &q[i].y);
			q[i]. rank = 2; q[i].id = i;
		}
		build();
		solve();
	}
	return 0;
}
