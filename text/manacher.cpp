//Algorithm to find palindromes in a given (first, last) compartment. Returns a vector of both odd and even palindromes (in a spliced manner: odd/even/odd/even...)
//Authors: Jakub Bachurski and Krzysztof Hałubek
#include <vector>
#include <limits>
#include <iterator>

template<typename Iterator, typename T = typename std::iterator_traits<Iterator>::value_type>
std::vector<size_t> manacher(Iterator first, Iterator last, T leaf = std::numeric_limits<T>::max())
{
    size_t n = distance(first, last);
    std::vector<T> S(2 * n + 1);
    for(size_t i = 0; i < n; ++i, ++first)
        S[2 * i] = leaf, S[2 * i + 1] = *first;
    S[2 * n] = leaf;
    n = 2 * n + 1;
    std::vector<size_t> R(n);
    size_t m = 0;
    for(size_t i = 1; i + 1 < n; ++i)
    {
        if(i < 2 * m && i < m + R[m]) R[i] = std::min(R[2 * m - i], m + R[m] - i);
        while(i > R[i] && i + R[i] < n - 1 && S[i - R[i] - 1] == S[i + R[i] + 1])
            R[i]++;
        if(i + R[i] > m + R[m]) m = i;
    }
    for(size_t i = 0; i < n; ++i)
        R[i] = R[i];
    R.erase(R.begin());
    R.pop_back();
    return R;
}
