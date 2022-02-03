//Algorithm to calculate and print the biggest possible sum of elements from a (N x 3) matrix on these conditions: you can use only one element out of every row and the element taken from row i cannot be in the same column as the element taken from row i - 1
//author: Krzysztof Hałubek
#include <iostream>

constexpr int MAXN = (int)2e5 + 5;

long long M[MAXN][3];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n;
	std::cin >> n;
	std::cin >> M[0][0] >> M[0][1] >> M[0][2];
	for (int i = 1; i < n; i++)
	{
		std::cin >> M[i][0] >> M[i][1] >> M[i][2];
		M[i][0] = std::max(M[i - 1][1], M[i - 1][2]) + M[i][0];
		M[i][1] = std::max(M[i - 1][0], M[i - 1][2]) + M[i][1];
		M[i][2] = std::max(M[i - 1][0], M[i - 1][1]) + M[i][2];
	}
	std::cout << std::max(std::max(M[n - 1][0], M[n - 1][1]), M[n - 1][2]);
	return 0;
}
