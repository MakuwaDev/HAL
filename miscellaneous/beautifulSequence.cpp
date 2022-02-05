//Algorithm to find and print the subsequence of twice the given length, which fulfils these conditions: each number from 1 to n (input) occurs exactly two times and the distance between every pair of the same value equals the value
//author: Krzysztof Hałubek
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	size_t n, k, l;
	std::cin >> n;
	if (n % 4 == 2 || n % 4 == 3)
	{
		return -1;
	}
	else if (n % 4 == 0 && n != 4)
	{
		k = n / 2;
		l = n / 4;
		for (size_t i = 2 * k; i >= 2; i -= 2)
			std::cout << i << " ";
		std::cout << 2 * k - 1 << " ";
		for (size_t i = 2; i <= 2 * k; i += 2)
			std::cout << i << " ";
		std::cout << k - 1 << " ";
		for (size_t i = 2 * k - 3; i >= k + 1; i -= 2)
			std::cout << i << " ";
		for (size_t i = k - 3; i >= 3; i -= 2)
			std::cout << i << " ";
		std::cout << 2 * k - 1 << " " << k - 1 << " ";
		for (size_t i = 3; i <= k - 3; i += 2)
			std::cout << i << " ";
		std::cout << "1 1 ";
		for (size_t i = k + 1; i <= 2 * k - 3; i += 2)
			std::cout << i << " ";
	}
	else if (n % 4 == 1 && n != 5 && n != 1)
	{
    k = n / 2;
		l = n / 4;
		for (size_t i = 2 * k; i >= 2; i -= 2)
			std::cout << i << " ";
		std::cout << 2 * k + 1 << " ";
		for (size_t i = 2; i <= 2 * k; i += 2)
			std::cout << i << " ";
		std::cout << k - 1 << " ";
		for (size_t i = 2 * k - 1; i >= k + 1; i -= 2)
			std::cout << i << " ";
		for (size_t i = k - 3; i >= 3; i -= 2)
			std::cout << i << " ";
		std::cout << k - 1 << " " << 2 * k + 1 << " ";
		for (size_t i = 3; i <= k - 3; i += 2)
			std::cout << i << " ";
		std::cout << "1 1 ";
		for (size_t i = k + 1; i <= 2 * k - 1; i += 2)
			std::cout << i << " ";
	}
	else if (n == 4) std::cout << "4 2 3 2 4 3 1 1";
	else if (n == 5) std::cout << "1 1 3 4 5 3 2 4 2 5";
	else if (n == 1) std::cout << "1 1";
	std::cout.flush();
	_Exit(0);
}
