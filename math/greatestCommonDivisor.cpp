//Function to calculate greatest common divisor for given a, b in logn time
//Author: Krzysztof Hałubek
#include <iostream>
 
long long gcd(long long a, long long b)
{
    long long h;
    while(b != 0)
    {
        h = b;
        b = a % b;
        a = h;
    }
    return a;
}
