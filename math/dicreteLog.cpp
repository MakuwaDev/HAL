//Algorithm to find x such that a^x = b (mod m) for given a, b, m in O(sqrt(m))
//Author: Krzysztof Hałubek
#include <iostream>
#include <unordered_map>
#include <cmath>

long long gcd(long long a, long long b)
{
	long long h;
	while (b != 0)
	{
		h = b;
		b = a % b;
		a = h;
	}
	return a;
}

long long power_fast(long long a, long long pow, long long mod)
{
	long long i;
	long long result = 1;
	long long x = a;
	for (i = 1; i <= pow; i <<= 1)
	{
		if ((pow & i) != 0) result = (result * x) % mod;
		x = (x * x) % mod;
	}
	return result % mod;
}

long long discreteLog(long long a, long long b, long long m)
{
	a %= m;
	b %= m;
	std::unordered_map<long long, long long> vals;
	long long k = 1, add = 0, g, n = std::sqrt(m) + 1, an = 1;
	while ((g = gcd(a, m)) > 1)
	{
		if (b == k) return add;
		if (b % g != 0) return -1;
		b /= g;
		m /= g;
		++add;
		k = (k * a / g) % m;
	}
	an = power_fast(a, n, m);
	for (long long q = 0, cur = b; q <= n; ++q) 
	{
		vals[cur] = q;
		cur = (cur * a) % m;
	}
	for (long long p = 1, cur = k; p <= n; ++p)
	{
		cur = (cur * an) % m;
		if(vals.count(cur) != 0) return (n * p - vals[cur] + add);
	}
	return -1;
}
