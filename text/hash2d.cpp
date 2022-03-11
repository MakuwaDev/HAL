//Program to find every occurrence of a given array in another, bigger given array using 2d hashing algorithm. The output consists of the number of found occurrences followed by a list of pairs (x, y) representing the coordinates of an upper left corner of each found occurrence (indexing starts at 1). The output is guaranteed to be ordered, first by line and then by column
//Author: Krzysztof Hałubek
#include <iostream>
#include <vector>

constexpr size_t MAXN = 810;
constexpr long long p1 = 997;
constexpr long long p2 = 1009;
constexpr long long MOD = 694202137;

long long pot1[MAXN];
long long pot2[MAXN];
long long t1[MAXN][MAXN];
long long t2[MAXN][MAXN];
std::vector<std::pair<size_t, size_t>> res;

void init()
{
	pot1[0] = pot2[0] = 1;
	for (size_t i = 1; i < MAXN; i++)
	{
		pot1[i] = (pot1[i - 1] * p1) % MOD;
		pot2[i] = (pot2[i - 1] * p2) % MOD;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	init();
	size_t n1, m1, n2, m2;
	long long val = 0, curr;
	std::string s;
	std::cin >> n1 >> m1;
	for (size_t i = 1; i <= n1; ++i)
	{
		std::cin >> s;
		for (size_t j = 1; j <= m1; ++j)
			t1[i][j] = s[j - 1];
	}
	std::cin >> n2 >> m2;
	for (size_t i = 1; i <= n2; ++i)
	{
		std::cin >> s;
		for (size_t j = 1; j <= m2; ++j)
			t2[i][j] = s[j - 1];
	}
	for (size_t i = 1; i <= n1; ++i)
		for (size_t j = 1; j <= m1; ++j)
		{
			val += ((t1[i][j] * pot1[i]) % MOD) * pot2[j] % MOD;
			val %= MOD;
			val += MOD;
			val %= MOD;
		}
	for (size_t i = 1; i <= n2; ++i)
		for (size_t j = 1; j <= m2; ++j)
		{
			t2[i][j] = ((t2[i][j] * pot1[i]) % MOD) * pot2[j] % MOD;
			t2[i][j] %= MOD;
			t2[i][j] += MOD;
			t2[i][j] %= MOD;

		}
	for (size_t i = 1; i <= n2; ++i)
		for (size_t j = 1; j <= m2; ++j)
		{
			t2[i][j] = (t2[i][j] + t2[i - 1][j] + t2[i][j - 1] - t2[i - 1][j - 1]) % MOD;
			t2[i][j] %= MOD;
			t2[i][j] += MOD;
			t2[i][j] %= MOD;
		}
	for(size_t i = n1; i <= n2; ++i)
		for (size_t j = m1; j <= m2; ++j)
		{
			curr = (t2[i][j] - t2[i - n1][j] - t2[i][j - m1] + t2[i - n1][j - m1]) % MOD;
			curr %= MOD;
			curr += MOD;
			curr %= MOD;
			if (curr == (((val * pot1[i - n1]) % MOD) * pot2[j - m1]) % MOD) res.push_back({ i - n1 + 1, j - m1 + 1});
		}
	std::cout << res.size() << "\n";
	for (auto x : res)
		std::cout << x.first << " " << x.second << "\n";
	std::cout.flush();
}
