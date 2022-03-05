//Algorithm to calculate the Z array of a given string
//author: Krzysztof Hałubek
#include <vector>

std::vector<size_t> buildZ(std::string& s)
{
	const size_t n = s.size();
	std::vector<size_t> Z(n);
	for (size_t i = 1, L = 0, R = 0; i < n; ++i)
	{
		if (i < R) Z[i] = std::min(R - i, Z[i - L]);
		while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]])
			Z[i]++;
		if (i + Z[i] > R) L = i, R = i + Z[i];
	}
	return Z;
}
