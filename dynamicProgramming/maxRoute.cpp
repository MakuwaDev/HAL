//Algorithm to calculate the maximum sum of values from visited fields on a n x m rectangle going from upper left corner to lower right corner
//author: Krzysztof Hałubek
#include <iostream>

constexpr int MAXN = 1e3 + 10; //insert the maximum length of one of the rectangles' sides
constexpr int MAXM = 1e3 + 10; //insert the maximum length of the other of the rectangle's sides

long long dp[MAXN][MAXN];
int n, m;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            std::cin >> dp[i][j];
    for (int i = 2; i <= n; i++)
        dp[i][1] += dp[i - 1][1];
    for (int i = 2; i <= m; i++)
        dp[1][i] += dp[1][i - 1];
    for (int i = 2; i <= n; i++)
        for (int j = 2; j <= m; j++)
            dp[i][j] += std::max(dp[i - 1][j], dp[i][j - 1]);
    std::cout << dp[n][m];
}
