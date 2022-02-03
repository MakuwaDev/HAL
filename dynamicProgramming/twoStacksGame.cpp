//Algorithm to calculate the best possible outcome to such problem: two players, two stacks, in each round one of the players takes one element out of either of the two stacks, your task is to maximalize the sum of elements taken from the stacks by you, your opponent uses the best strategy possible for him, you start
//author: Krzysztof Hałubek
#include <iostream>

constexpr size_t MAXN = (size_t)1e4 + 4; //insert the maximum amount of elements in one stack

int a[MAXN + 1], b[MAXN + 1], dp[MAXN + 1][MAXN + 1];

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    a[0] = b[0] = dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    for (int i = 1; i <= m; i++)
        std::cin >> b[i];
    for (int i = 1; i <= n; i++)
    {
        int akt = 0;
        for (int k = i; k > 0; k -= 2)
            akt += a[k];
        dp[i][0] = akt;
    }
    for (int j = 1; j <= m; j++)
    {
        int akt = 0;
        for (int k = j; k > 0; k -= 2)
            akt += b[k];
        dp[0][j] = akt;
    }
    for (int i = 1; i <= n; i++)
        a[i] += a[i - 1];
    for (int i = 1; i <= m; i++)
        b[i] += b[i - 1];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            dp[i][j] = a[i] + b[j] - std::min(dp[i - 1][j], dp[i][j - 1]);
    }
    std::cout << dp[n][m];
}
