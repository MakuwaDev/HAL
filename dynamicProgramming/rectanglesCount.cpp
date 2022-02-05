//Algorithm to count every rectangle that exists on an nxm board with k obstacles of integer coordinates in which there are no obstacles
//Author: Krzysztof Hałubek
#include <iostream>
#include <vector>

constexpr size_t MAXN = 1510; //insert the maximum length of the side of the board

bool t[MAXN][MAXN];
size_t height[MAXN][MAXN];
std::vector<std::pair<size_t, size_t>> stack;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	size_t n, m, k, x, y;
	long long res = 0;
	std::cin >> n >> m >> k;
	for (size_t i = 0; i < k; ++i)
	{
		std::cin >> x >> y;
		t[x][y] = true;
	}
	for (size_t i = 1; i <= m; ++i)
		if (!t[1][i]) height[1][i] = 1;
	for (size_t i = 2; i <= n; ++i)
		for (size_t j = 1; j <= m; ++j)
			if (!t[i][j]) height[i][j] = height[i - 1][j] + 1;
	for (size_t i = 1; i <= n; ++i)
	{
		stack.clear();
		stack.push_back({ 0, 0 });
		for (size_t j = 1; j <= m; ++j)
		{
			while (!stack.empty() && height[i][j] <= stack.back().first)
				stack.pop_back();
			stack.push_back({ height[i][j], j });
			for (size_t k = 1; k < stack.size(); ++k)
				res += ((long long)stack[k].second - (long long)stack[k - 1].second) * (long long)stack[k].first;
		}
	}
	std::cout << res;
	std::cout.flush();
	_Exit(0);
}
