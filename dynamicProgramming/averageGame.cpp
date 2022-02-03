//Algorithm to compute the maximum outcome of such problem: given a sequence of n elemets take any two adjacent elements and replace them with one element equal to their arithmetic average, then repeat until only one element remains
//author: Krzysztof Hałubek
#include <iostream>
#include <iomanip>

constexpr size_t MAXN = (size_t)1e3 + 3;

long double dp[MAXN][MAXN];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout << std::fixed << std::setprecision(7);
	size_t n;
	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> dp[i][i];
	for (size_t length = 2; length <= n; length++)
	{
		for (size_t start = 1; start + length - 1 <= n; start++)
		{
			size_t end = start + length - 1;
			long double maks = -1;
			for (size_t i = start; i < end; i++)
			{
				maks = std::max(dp[start][i] + dp[i + 1][end], maks);
			}
			dp[start][end] = maks / 2;
		}
	}
	std::cout << dp[1][n];
	return 0;
}
