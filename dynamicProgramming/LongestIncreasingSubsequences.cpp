//Algorithm to calculate and print the amount of Longest Increasing Subsequences (not neccesarily coherent) of a sequence, out of the technical reasons, the result is printed modulo 'mod' which is inputed along the subsequence
//author: Krzysztof Hałubek
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#define MAXN 500005

typedef std::pair<long long, long long> para;

long long t[MAXN];
std::vector <para> dp[MAXN];

const bool inline compare(const std::vector <para>& a, const std::vector <para>& b)
{
	return (*(a.rbegin())).first < (*(b.rbegin())).first;
}

const bool inline compare2(const para& a, const para& b)
{
	return a.first > b.first;
}

int main(int argc, char* argv[])
{
	std::ios_base::sync_with_stdio(NULL);
	std::cin.tie(0);
	std::cout.tie(0);
	long long n, mod;
	std::cin >> n >> mod;
	for (int i = 0; i < n; i++)
		std::cin >> t[i];
	for (int i = 0; i <= n; i++)
	{
		dp[i].push_back(std::make_pair(LLONG_MAX, 0));
	}
	dp[0].push_back(std::make_pair(LLONG_MIN, 1));
	std::vector <para>* start;
	std::vector <para>* last;
	std::vector <para> z;
	z.push_back(std::make_pair(LLONG_MAX, 0));
	for (int i = 0; i < n; i++)
	{
		z[0] = std::make_pair(t[i], 0);
		start = std::lower_bound(dp, dp + n + 1, z, compare);
		last = start;
		last--;
		std::vector<para>::iterator it = std::lower_bound((*last).begin(), (*last).end(), std::make_pair(t[i], 0), compare2);
		it--;
		long long val = ((*((*start).rbegin())).second + (*((*last).rbegin())).second - (*it).second) % mod;
		(*start).push_back(std::make_pair(t[i], val));
		if ((*((*start).rbegin())).second < 0) {
			(*((*start).rbegin())).second += mod;
		}
	}
	z[0] = std::make_pair(LLONG_MAX, 0);
	std::vector<para>* wynik = std::lower_bound(dp, dp + n, z, compare);
	wynik--;
	std::cout << (*((*wynik).rbegin())).second << '\n';
}
