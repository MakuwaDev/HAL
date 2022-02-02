//Algorithm to sort angularly a given set of points with whole coordinates relatively to the point with the smallest first coordinate (if we have several such points we choose the one with the smallest second coordinate)
//author: Krzysztof Hałubek
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

constexpr size_t MAXN = 200010; //insert the maximum amount of points increased by at least 3
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

point coordinates[MAXN];
std::vector<size_t> order;

point p0;

long long product(point A, point B, point C)
{
	return ((C.x - A.x) * (B.y - A.y)) - ((B.x - A.x) * (C.y - A.y));
}

bool comp(size_t a, size_t b)
{
	point A = coordinates[a], B = coordinates[b];
	if (A == p0) return true;
	if (B == p0) return false;
	if (product(p0, A, B) == 0)
	{
		if (A.x != B.x) return A.x < B.x;
		return A.y < B.y;
	}
	return (product(p0, A, B) < 0);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	size_t n, minid = MAXN - 2, x, y;
	coordinates[minid] = { INF, INF };
	std::cin >> n;
	for (size_t i = 0; i < n; ++i)
	{
		std::cin >> x >> y;
		order.push_back(i);
		coordinates[i].x = x;
		coordinates[i].y = y;
		if ((coordinates[i].x < coordinates[minid].x) || (coordinates[i].x == coordinates[minid].x && coordinates[i].y < coordinates[minid].y)) minid = i;
	}
	p0 = coordinates[minid];
	std::sort(order.begin(), order.end(), comp);
	std::cout.flush();
	_Exit(0);
}
