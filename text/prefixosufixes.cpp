//Algorithm to calculate the P array of a given string
//author: Krzysztof Hałubek
#include <vector>

std::vector<size_t> prefixosufixes(std::string& s)
{
   const size_t n = s.size();
   std::vector<size_t> P(n);
   P[0] = 0;
    for(size_t i = 1; i < n; i++)
    {
        P[i] = P[i - 1];
        while(P[i] && s[P[i]] != s[i]) P[i] = P[P[i] - 1];
        if(s[i] == s[P[i]])
            P[i]++;
    }
    return P;
}
