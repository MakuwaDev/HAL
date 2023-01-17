//Algorithm to calculate and print the suffix array of a given string (and also the rank array) in O(nlogn) using Karp-Rabin-Miller's algorithm
//Author: Krzysztof Hałubek
#include <iostream>
#include <vector>
#include <algorithm>

constexpr int MAXN = 1000000;
constexpr int MAXPOW = 21;

std::vector<std::pair<std::pair<int, int>, int>> pary;
int KMR[MAXN][MAXPOW];
std::vector<int> rank;
std::vector<int> suffixArray;

int log2(int x)
{
    int res = 0, pow = 1;
    while (x > pow)
    {
        pow *= 2;
        res++;
    }
    return res;
}

void bucketSort()
{
    std::vector<std::vector<std::pair<std::pair<int, int>, int>>> buckets;
    buckets.resize(27);
    for (auto& x : pary)
        buckets[x.first.first].push_back(x);
    pary.clear();
    for (int i = 0; i < 27; ++i)
        while (!buckets[i].empty())
        {
            pary.push_back(buckets[i].back());
            buckets[i].pop_back();
        }
}

void radixSort(int n)
{
    std::vector<std::vector<std::pair<std::pair<int, int>, int>>> buckets;
    buckets.resize(n + 1);
    for (auto& x : pary)
        buckets[x.first.second].push_back(x);
    pary.clear();
    for (int i = 0; i < buckets.size(); ++i)
        for (int j = 0; j < buckets[i].size(); ++j)
            pary.push_back(buckets[i][j]);
    for (int i = 0; i < buckets.size(); ++i)
        buckets[i].clear();
    for (auto& x : pary)
        buckets[x.first.first].push_back(x);
    pary.clear();
    for (int i = 0; i < buckets.size(); ++i)
        for (int j = 0; j < buckets[i].size(); ++j)
            pary.push_back(buckets[i][j]);
}

std::pair<int, int> identifier(int s, int l)
{
    int log = log2(l) - 1;
    if (log < 0) log = 0;
    return { KMR[s][log], KMR[s + l - (1 << log)][log] };
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, power = 1, log = 0, length = 2, id = 0;
    std::pair<int, int>pom;
    std::string s;
    std::cin >> n;
    std::cin >> s;
    for (int i = 0; i < n; ++i)
        pary.push_back({ {s[i] - 'a' + 1, s[i] - 'a' + 1}, i });
    for (int i = 0; i < n; ++i)
    {
        s.push_back(0);
        pary.push_back({ { 0, 0 }, i + n });
    }
    n = 2 * n;
    log = log2(n) - 1;
    if (log < 0) log = 0;
    bucketSort();
    pom = { -1, -1 };
    for (int i = 0; i < n; ++i)
    {
        if (pom != pary[i].first)
        {
            pom = pary[i].first;
            ++id;
        }
        KMR[pary[i].second][0] = id;
    }
    for (int l = 1; l <= log; ++l)
    {
        pary.clear();
        id = 0;
        for (int i = 0; i + length - 1 < n; ++i)
            pary.push_back({ {KMR[i][l - 1], KMR[i + length / 2][l - 1]}, i });
        radixSort(n);
        std::pair<int, int>pom = { -1, -1 };
        for (int j = 0; j < pary.size(); ++j)
        {
            if (pom != pary[j].first)
            {
                pom = pary[j].first;
                ++id;
            }
            KMR[pary[j].second][l] = id;
        }
        length = length << 1;
    }
    pary.clear();
    n = n / 2;
    rank.resize(n + 1);
    suffixArray.resize(n + 1);
    for (int i = 0; i <= n; ++i)
        pary.push_back({ identifier(i, n), i });
    radixSort(n + 1);
    pom = { -1, -1 };
    id = 0;
    for (auto& x : pary)
    {
        if (pom != x.first)
        {
            pom = x.first;
            ++id;
        }
        rank[x.second] = id - 1;
    }
    for (int i = 0; i < rank.size(); ++i)
        suffixArray[rank[i]] = i;
    for (auto x : suffixArray)
        std::cout << x << " ";
}
