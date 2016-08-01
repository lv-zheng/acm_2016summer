#include <iostream>

template<int n, int a, int b, int c>
struct newton_sqrt {
	static constexpr int value = newton_sqrt<n, (a + n / a) / 2, a, b>::value;
};

template<int n, int a, int b>
struct newton_sqrt<n, a, b, a> {
	static constexpr int value = a > b ? b : a;
};

template<int n>
struct static_sqrt {
	static constexpr int value = newton_sqrt<n, 1, 0, 0>::value;
};

template<int n, int i>
struct is_prime_loop {
	static constexpr bool value = (n % i == 0 ? false : is_prime_loop<n, i - 1>::value);
};

template<int n>
struct is_prime_loop<n, 1> {
	static constexpr bool value = true;
};

template<int n>
struct is_prime {
	static constexpr bool value = is_prime_loop<n, static_sqrt<n>::value>::value;
};

template<int n>
struct prime_count {
	static constexpr int value = prime_count<n - 1>::value + (is_prime<n>::value ? 1 : 0);
};

template<>
struct prime_count<1> {
	static constexpr int value = 0;
};

template<int n>
struct display {
	static_assert(n != n, "");
};

display<prime_count<10000>::value> a;
