//Program to solve a linear congruence in the form of ax = b (mod m), when given a, b, m
//Author: Krzysztof Hałubek
#include <iostream>
#include <algorithm>

void euclid(long long a, long long b, long long& x, long long& y)
{
    if (b != 0)
    {
        euclid(b, a % b, x, y);
        long long h = y;
        y = x - a / b * y;
        x = h;
    }
}

int main() 
{
	long long a, b, m, x = 1, y = 0, gcd, step, ile;
	std::cin >> a >> b >> m;
	euclid(a, m, x, y);
	gcd = a * x + m * y;
	if (b % gcd != 0) 
	{
		std::cout << "NIE";
		return 0;
	}
	x *= b / gcd;
	step = m / gcd;
	x %= m;
	if (x < 0) 
	{
		ile = (x * -1) / step;
		x += (ile * step);
		if (x < 0) x += step;
	}
	else x %= step;
	x %= m;
	std::cout << x << '\n';
}
