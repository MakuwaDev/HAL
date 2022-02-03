//Algorithm to calclulate the sum of the fields on any rectangle on a rectangle board in O(1) with O(n^2) preprocessing (two dimensional partial sum)
//author: Krzysztof Hałubek
#include <iostream>

constexpr size_t MAXN = (size_t)1e4 + 4; //insert the maximum length of the side of the rectangle

int t[MAXN + 1][MAXN + 1];

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin.tie(nullptr);
    int n, m, q, a1, b1, a2, b2;
    std::cin >> n >> m;
    for (int i = 0; i <= n; i++)
        t[i][0] = 0;
    for (int i = 0; i <= m; i++)
        t[0][i] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            std::cin >> t[i][j];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            t[i][j] = t[i][j] + t[i - 1][j] + t[i][j - 1] - t[i - 1][j - 1];
    }
    std::cin >> q;
    for (int i = 0; i < q; i++)
    {
        std::cin >> a1 >> b1 >> a2 >> b2;
        std::cout << t[a2][b2] - t[a1 - 1][b2] - t[a2][b1 - 1] + t[a1 - 1][b1 - 1] << "\n";
    }
}
