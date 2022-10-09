//Program to calculate the binomial coefficient of given n over k mod p
//Author: Krzysztof Halubek
#include <iostream>

long long n, k, p;

static inline long long power_modulo_fast(long long a, long long pow, long long MOD)noexcept
{
	long long i;
	long long result = 1;
	long long x = a % MOD;
	for (i = 1; i <= pow; i <<= 1)
	{
		x %= MOD;
		if ((pow & i) != 0)
		{
			result *= x;
			result %= MOD;
		}
		x *= x;
	}
	return result % MOD;
}

static inline long long factorial(long long x)noexcept
{
    long long res = 1;
    for(long long i = 1; i <= x; ++i)
        res = (res * i) % p;
    return res;
}

static inline long long newton(long long k, long long n)noexcept
{
    return (factorial(n) * power_modulo_fast((factorial(k) * factorial(n - k)), p - 2, p)) % p;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin>>k>>n>>p;
    std::cout<<(newton(k, n) % p);
}
