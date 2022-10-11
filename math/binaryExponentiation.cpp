//Program to compute kth power of n in O(logk) using binary exponentiation
//Author: Krzysztof Hałubek
#include <iostream>
static inline long long power_fast(long long a, long long pow)noexcept
{
	long long i;
	long long result = 1;
	long long x = a;
	for (i = 1; i <= pow; i <<= 1)
	{
		if ((pow & i) != 0) result *= x;
		x *= x;
	}
	return result;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  long long n, k;
  std::cin>>n>>k;
  std::cout<<power_fast(n, k);
}
