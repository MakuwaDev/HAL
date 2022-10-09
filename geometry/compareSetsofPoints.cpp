//Program to check wheter two sets of points (of the same size) are equal to each other if angularly rotated (by any angle) around point (0, 0)
//Author: Krzysztof Hałubek, with the help of Paweł Zalewski and Miłosz Wąsiniak
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

constexpr size_t MAXN = (size_t)1e6 + 6;
constexpr long long INF = std::numeric_limits<long long>::max();

class point
{
public:
	long long x;
	long long y;
	bool operator ==(const point& pkt)
	{
		if ((this->x == pkt.x) && (this->y == pkt.y)) return true;
		else return false;
	}
};

struct parameters
{
	long long distance;
	long long scalar;
	long long vector;
	bool operator ==(const parameters& param)
	{
		if (this->distance == param.distance && this->scalar == param.scalar && this->vector == param.vector) return true;
		else return false;
	}
	bool operator !=(const parameters& param)
	{
		if (this->distance != param.distance || this->scalar != param.scalar || this->vector != param.vector) return true;
		else return false;
	}
};

point coordinates1[MAXN];
point coordinates2[MAXN];

std::vector<size_t> order1;
std::vector<size_t> order2;

std::vector<parameters> slowo;

point p0 = { 0, 0 };

long long vector_product(point A, point B, point C)
{
	return ((C.x - A.x) * (B.y - A.y)) - ((B.x - A.x) * (C.y - A.y));
}

long long scalar_product(point A, point B, point C)
{
	return (C.x - A.x) * ((B.x - A.x)) + ((C.y - A.y) * (B.y - A.y));
}

long long dist(point A, point B)
{
	return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

bool comp1(size_t a, size_t b)
{
	point A = coordinates1[a], B = coordinates1[b];
	size_t cwA, cwB;
	long long iloczyn;
	if (A.x == 0 && A.y == 0) return false;
	if (B.x == 0 && B.y == 0) return true;
	if (A.x >= 0 && A.y < 0) cwA = 1;
	if (A.x > 0 && A.y >= 0) cwA = 2;
	if (A.x <= 0 && A.y > 0) cwA = 3;
	if (A.x < 0 && A.y <= 0) cwA = 4;
	if (B.x >= 0 && B.y < 0) cwB = 1;
	if (B.x > 0 && B.y >= 0) cwB = 2;
	if (B.x <= 0 && B.y > 0) cwB = 3;
	if (B.x < 0 && B.y <= 0) cwB = 4;
	if (cwA != cwB) return cwA < cwB;
	iloczyn = A.x * B.y - B.x * A.y;
	if (iloczyn == 0) return dist(p0, A) > dist(p0, B);
	return iloczyn < 0;
}

bool comp2(size_t a, size_t b)
{
	point A = coordinates2[a], B = coordinates2[b];
	size_t cwA, cwB;
	long long iloczyn;
	if (A.x == 0 && A.y == 0) return false;
	if (B.x == 0 && B.y == 0) return true;
	if (A.x >= 0 && A.y < 0) cwA = 1;
	if (A.x > 0 && A.y >= 0) cwA = 2;
	if (A.x <= 0 && A.y > 0) cwA = 3;
	if (A.x < 0 && A.y <= 0) cwA = 4;
	if (B.x >= 0 && B.y < 0) cwB = 1;
	if (B.x > 0 && B.y >= 0) cwB = 2;
	if (B.x <= 0 && B.y > 0) cwB = 3;
	if (B.x < 0 && B.y <= 0) cwB = 4;
	if (cwA != cwB) return cwA < cwB;
	iloczyn = A.x * B.y - B.x * A.y;
	if (iloczyn == 0) return dist(p0, A) > dist(p0, B);
	return iloczyn < 0;
}

std::vector<size_t> prefixosufixes(std::vector<parameters>& s)
{
	const size_t n = s.size();
	std::vector<size_t> P(n);
	P[0] = 0;
	for (size_t i = 1; i < n; i++)
	{
		P[i] = P[i - 1];
		while (P[i] && s[P[i]] != s[i]) P[i] = P[P[i] - 1];
		if (s[i] == s[P[i]])
			P[i]++;
	}
	return P;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	size_t n, czy1 = 0, czy2 = 0;
	parameters param;
	std::vector<size_t> p;
	std::cin >> n;
	for (size_t i = 0; i < n; ++i)
	{
		std::cin >> coordinates1[i].x >> coordinates1[i].y;
		order1.push_back(i);
	}
	for (size_t i = 0; i < n; ++i)
	{
		std::cin >> coordinates2[i].x >> coordinates2[i].y;
		order2.push_back(i);
	}
	std::sort(order1.begin(), order1.end(), comp1);
	std::sort(order2.begin(), order2.end(), comp2);
	while (!order1.empty() && coordinates1[order1[order1.size() - 1]].x == 0 && coordinates1[order1[order1.size() - 1]].y == 0)
	{
		order1.pop_back();
		if (coordinates2[order2[order2.size() - 1]].x == 0 && coordinates2[order2[order2.size() - 1]].y == 0) order2.pop_back();
		else
		{
			std::cout << "NO";
			return 0;
		}
	}
	for (size_t i = 0; i < order1.size(); ++i)
	{
		param.distance = dist(p0, coordinates1[order1[i]]);
		param.scalar = scalar_product(p0, coordinates1[order1[i]], coordinates1[order1[(i + 1) % order1.size()]]);
		param.vector = vector_product(p0, coordinates1[order1[i]], coordinates1[order1[(i + 1) % order1.size()]]);
		slowo.push_back(param);
	}
	slowo.push_back({ 69, 420, 2137 });
	for (size_t i = 0; i < order2.size(); ++i)
	{
		param.distance = dist(p0, coordinates2[order2[i]]);
		param.scalar = scalar_product(p0, coordinates2[order2[i]], coordinates2[order2[(i + 1) % order2.size()]]);
		param.vector = vector_product(p0, coordinates2[order2[i]], coordinates2[order2[(i + 1) % order2.size()]]);
		slowo.push_back(param);
	}
	size_t currsize = slowo.size();
	for (size_t i = order1.size() + 1; i < currsize; ++i)
		slowo.push_back(slowo[i]);
	p = prefixosufixes(slowo);
	for (size_t i = 0; i < p.size(); ++i)
		if (p[i] == order1.size())
		{
			std::cout << "YES";
			return 0;
		}
	std::cout << "NO";
	return 0;
}
