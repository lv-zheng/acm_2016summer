//#pragma GCC optimize("O2")
#include<iostream>
#include<cstdio>
#include <queue>
#include <cmath>
using namespace std;

const int N = 100010;

int T,n,m;
long long f[100010],g[100010];

struct BBB {
	long long a, b, c;
	int pos;
	bool operator < (const BBB& rhs) const {
		return pos < rhs.pos;
	}
};


bool judge(long long val){
	std::priority_queue<BBB> pq;
	long long a = 0, b = 0, c = 0;
	int cnt = 0;
    for(long long i=n;i>=1;--i){
		while (!pq.empty() && pq.top().pos == i) {
			a -= pq.top().a;
			b -= pq.top().b;
			c -= pq.top().c;
			pq.pop();
		}
		long long hit = a * i * i + b * i + c;
		if (hit > f[i])
			continue;
		long long times = (f[i] - hit) / val + 1;
		cnt += times;
		long long dc = times * (val - i * i);
		long long db = times * 2 * i;
		long long da = -1 * times;
		c += dc;
		b += db;
		a += da;
		long long endpos = i - std::sqrt(val);
		if (endpos > 0)
			pq.push(BBB{da, db, dc, (int) endpos});

		if (cnt > m)
			return false;
#if 0
        k=0;    g[i]=0;
        for(long long j=i+1;j<=n;++j) {
			long long fac = (val-(j-i)*(j-i));
			if (fac <= 0)
				break;
            k+=g[j]*fac;
		}
        if(k>f[i])  continue;
        g[i]=(f[i]-k)/val+1;
        tot+=g[i];
        if(tot>m)   return false;
#endif
    }
    return true;
}

void work(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%lld",&f[i]);
    }
    long long l=1,r=5e9,mid;
    while(l<r){
        mid=(l+r)/2;
        if(judge(mid))  r=mid;
        else    l=mid+1;
    }
    printf("%lld\n",r);
}

int main(){
    scanf("%d",&T);
    for(int i=1;i<=T;++i){
        work();
    }
}
