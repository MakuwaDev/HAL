//Algorithm to generate a subset of points which will be the convex hull (convex envelope or convex closure) of a given set of points, points shall have whole coordinates
//author: Krzysztof Hałubek
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

constexpr size_t MAXN = (size_t)5e5 + 5; //insert the maximum amount of points
constexpr long long INF = std::numeric_limits<long long>::max();

class point
{
public:
	long long x;
	long long y;
	bool operator ==(const point& pkt)
	{
		if ((this->x == pkt.x) && (this->y == pkt.y))
			return true;
		else
			return false;
	}
};

point coordinates[MAXN];
point p0 = { INF, INF };

long long product(point A, point B, point C)
{
	return ((C.x - A.x) * (B.y - A.y) - (B.x - A.x) * (C.y - A.y));
}

bool comp(int a, int b)
{
	point A = coordinates[a], B = coordinates[b];
	if (A == p0) return true;
	if (B == p0) return false;
	if (product(p0, A, B) == 0)
	{
		if (A.x == B.x) return A.y < B.y;
		return A.x < B.x;
	}
	return (product(p0, A, B) < 0);
}

std::vector<size_t> generate_convex(std::vector<size_t>& points)
{
	std::vector<size_t> convex;
	for (size_t i = 0; i < points.size(); i++)
	{
		while (convex.size() > 2 && product(coordinates[convex[convex.size() - 2]], coordinates[convex[convex.size() - 1]], coordinates[points[i]]) >= 0)
			convex.pop_back();
		convex.push_back(points[i]);
	}
	return convex;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	size_t n;
	long long a, b;
	std::vector<size_t> points;
	std::vector<size_t> convex;
	std::cin >> n;
	for (size_t i = 0; i < n; i++)
	{
		std::cin >> a >> b;
		coordinates[i].x = a; coordinates[i].y = b;
		points.push_back(i);
		if (a < p0.x) p0 = { a, b };
		else if (a == p0.x && b < p0.y) p0 = { a, b };
	}
	std::sort(points.begin(), points.end(), comp);
	convex = generate_convex(points);
	std::cout.flush();
	_Exit(0);
}
