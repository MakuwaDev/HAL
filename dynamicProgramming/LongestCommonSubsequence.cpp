//Algorithm to find the Longest Common Subsequence of two given sequences, and print it's length and the elements involved
//author: Krzysztof Hałubek
#include <iostream>
#include <vector>

constexpr size_t MAXN = 1000; //insert the maximum length of the sequences

long long A[MAXN], B[MAXN], dp[MAXN][MAXN], from[MAXN][MAXN];

int main() 
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m;
	std::cin >> n >> m;
	for (int i = 0; i < n; i++) 
		std::cin >> A[i];
	for (int i = 0; i < m; i++)
		std::cin >> B[i];
	for (int j = 0; j < m; j++) 
	{
		dp[0][j] = 0;
		from[0][j] = j;
		if (A[0] == B[j]) dp[0][j] = 1;
	}
	for (int i = 1; i < n; i++) 
	{
		int wynik = 0, last = -1;
		for (int j = 0; j < m; j++) 
		{
			dp[i][j] = dp[i - 1][j];
			from[i][j] = j;
			if (A[i] == B[j] and wynik >= dp[i - 1][j]) 
			{
				dp[i][j] = wynik + 1;
				from[i][j] = last;
			}
			if (A[i] > B[j] and dp[i][j] > wynik) 
			{
				wynik = dp[i][j];
				last = j;
			}
		}
	}
	int wynik = 0, indeks, indeks2 = n - 1;
	for (int i = 0; i < m; i++) 
	{
		if (wynik < dp[n - 1][i]) 
		{
			wynik = dp[n - 1][i];
			indeks = i;
		}
	}
	std::cout << wynik << '\n';
	std::vector<int>res;
	while (wynik != 0) 
	{
		while (indeks2 >= 0 and from[indeks2][indeks] == indeks) indeks2--;
		res.push_back(B[indeks]);
		if (indeks2 < 0)break;
		indeks = from[indeks2][indeks];
		wynik--;
	}
	for (auto a = res.rbegin(); a != res.rend(); a++)
		std::cout << *a << ' ';
}
