//Algorithm to calculate and print the amount of possible routes from upper left corner to lower right corner of a square whith obstacles (inputed as '1')
//author: Krzysztof Hałubek
#include <iostream>

constexpr size_t MAXN = 1000; // insert the maximum length of the side of the square

long long tab[MAXN][MAXN];

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t n;
    long long a, x;
    std::cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            std::cin >> a;
            if (a == 1) tab[i][j] = 0;
            else tab[i][j] = 1;
        }
    x = 1;
    for (int i = 1; i < n; i++)
    {
        if (tab[0][i] == 0) x = 0;
        tab[0][i] = x;
    }
    x = 1;
    for (int i = 1; i < n; i++)
    {
        if (tab[i][0] == 0) x = 0;
        tab[i][0] = x;
    }
    for (int i = 1; i < n; i++)
        for (int j = 1; j < n; j++)
            if (tab[j][i] != 0) tab[j][i] = tab[j - 1][i] + tab[j][i - 1];
    std::cout << tab[n - 1][n - 1];
}
