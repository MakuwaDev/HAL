//Algorithm to find and print the length of the side of the biggest square inside a square board which doesn't include the fields inputed as '1'
//author: Krzysztof Hałubek
#include <iostream>

constexpr int MAXN = (int)1e3 + 3; //insert the maximum length of the side of the square

int dp[MAXN][MAXN];

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, x, result;
    bool allones = true;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> x;
            if (x == 0) allones = false;
            if (x == 1) dp[i][j] = 0;
            else dp[i][j] = 1;
        }
    }
    if (allones)
    {
        std::cout << "0";
        return 0;
    }
    for (int i = 1; i < n; i++)
        for (int j = 1; j < n; j++)
            if (dp[i][j] != 0) dp[i][j] = std::min(std::min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result = std::max(result, dp[i][j]);
    std::cout << result;
    return 0;
}
