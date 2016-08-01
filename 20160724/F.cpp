#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <math.h>

using namespace std;
typedef long long LL;                   

const LL MODULO = 1000000007;
const int INF = 1<<30;

const int N = 100010;

vector<int> g[N];
int dfs_clock,dfn[N],low[N];
bool isCut[N];
LL wei[N];
LL gans[N];
LL bans[N];
int color[N];
LL cans[N];

int clock2, dft[N];

int n, m;

void init()
{
    dfs_clock = 0;
	clock2 = 0;
    for(int i=0; i<=n; ++i) {
        isCut[i] = wei[i] = gans[i] = bans[i] = cans[i] = color[i] = dft[i] = dfn[i] = low[i] = 0;
		g[i].clear();
	}
}


LL fdfs(int node, int par, LL parprod) {
	if (dft[node])
		return -1;
	dft[node] = ++clock2;
	//printf("%d    %lld\n", node, parprod);

	LL npp = parprod * wei[node] % MODULO;

	if (isCut[node]) {
		std::vector<LL> chld;
		LL sigma = 0;
		for (int i = 0; i < (int) g[node].size(); ++i) {
			if (dft[g[node][i]])
				continue;
			//printf("+ %d %lld\n", g[node][i], cans[g[node][i]]);
			sigma += cans[g[node][i]];
			sigma %= MODULO;
		}
		//printf("SIGMA %d %lld\n", node, sigma);

		LL ans = 0;
		LL myprod = 1;

		if (par != -1)
			ans += parprod;

		for (int i = 0; i < (int) g[node].size(); ++i) {
			if (g[node][i] == par)
				continue;
			LL c = fdfs(g[node][i], node, npp * (sigma - cans[g[node][i]]));
			if (c != -1) {
				ans += c;
				myprod = (myprod * c) % MODULO;
				//chld.push_back(c);
			}
		}
		gans[node] = ans;
		myprod = (myprod * wei[node]) % MODULO;
		return myprod;
	}

	LL myprod = 1;
	if (par == -1 && g[node].size() == 0) {
		gans[node] = 0;
		return wei[node];
	}

	for (int i = 0; i < (int) g[node].size(); ++i) {
		if (g[node][i] == par)
			continue;
		LL c = fdfs(g[node][i], node, npp);
		if (c != -1) {
			myprod = (myprod * c) % MODULO;
			//chld.push_back(c);
		}
	}

	gans[node] = myprod * parprod;

	myprod = (myprod * wei[node]) % MODULO;
	return myprod;
}

//重边对割点没有影响，且该算法对有向图同样适用
void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++dfs_clock;
    int child = 0;
    for(int i=0; i<(int)g[u].size(); ++i)
    {
        int v = g[u][i];
        if(v==fa) continue;//如果是树枝边的反向访问，则不能用来更新low[u]
        if(dfn[v]==0) {
            tarjan(v,u);
        	child++;
        	low[u] = min(low[u],low[v]);//用树枝边，或者后向边来跟新low[u]
			if(low[v] >= dfn[u])
				isCut[u] = true;
		} else {
			low[u] = min(low[u], dfn[v]);
		}
    }
    if(fa==-1 && child==1) isCut[u] = false;
}

LL colorize(int node, int c){
	if (color[node])
		return -1;
	color[node] = c;
	LL ans = 1;
	for (int i = 0; i < (int) g[node].size(); ++i) {
		if (color[g[node][i]])
			continue;
		LL ch = colorize(g[node][i], c);
		if (ch != -1)
			ans = (ans * ch) % MODULO;
	}
	return cans[node] = (ans * wei[node]) % MODULO;
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int kase = 0; kase < t; ++kase) {
    	scanf("%d%d",&n,&m);
        init();
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", wei + i);
		}
        for(int i=0; i<m; ++i)
        {
			int u, v;
            scanf("%d%d",&u,&v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
		LL sigma = 0;
		for (int i = 1; i <= n; ++i) {
			LL co = colorize(i, i);
			if (co != -1) {
				sigma += (bans[i] = co);
				sigma %= MODULO;
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (dfn[i])
				continue;
			tarjan(i, -1);
			fdfs(i, -1, 1);
		}
#if 0
		for (int i = 1; i <= n; ++i) {
			if (isCut[i])
				printf("C %d\n", i);
		}
#endif
		LL fans = 0;
		for (int i = 1; i <= n; ++i) {
			//printf("%lld\n", gans[i]);
			fans = (fans + i * (gans[i] + sigma - bans[color[i]])) % MODULO;
		}
		printf("%lld\n", fans);
    }
    return 0;
}
