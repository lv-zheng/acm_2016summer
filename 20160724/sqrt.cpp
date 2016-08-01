#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

int isqrt(int n)
{
	int a = 1, b = 0, c = 0;
	while (a != c) {
		c = b;
		b = a;
		a = (a + n / a) / 2;
	}
	return std::min(a, b);
}

float invSqrt(float x)  
{  
	float xhalf = 0.5f * x;  
	int i = *(int*)&x;          // get bits for floating value  
	i =  0x5f375a86 - (i>>1);    // gives initial guess  
	x = *(float*)&i;            // convert bits back to float  
	x = x * (1.5f - xhalf*x*x); // Newton step  
	x = x * (1.5f - xhalf*x*x); // Newton step  
	return 1 / x;
}

int main()
{
	int n = 1;
	int N = 160000;
	long ans = 0, bns = 0;
	for (int i = n; i <= N; ++i) {
		//ans += std::sqrt(i);
		double is = invSqrt(i);
		double ss = std::sqrt(i);
		if ((long) is != (long) ss) {
			std::cout << i << '\t' 
				<< std::fixed << std::setprecision(8) << is << '\t'
				<< std::fixed << std::setprecision(8) << ss << std::endl;
		}
		ans += is;
		bns += ss;
	}
	std::cout << ans << ' ' << bns << std::endl;
	return 0;
}
