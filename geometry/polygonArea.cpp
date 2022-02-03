//Algorithm to calculate the area of a given polygon, the polygon shall be determined as a clockwise ordered set of points with whole coordinates
//author: Krzysztof Hałubek
#include <iostream>
#include <limits>

constexpr size_t MAXN = 20000; //insert the maximum amount of vertexes

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

point t[MAXN];

long long product(point A, point B, point C)
{
	return ((C.x - A.x) * (B.y - A.y)) - ((B.x - A.x) * (C.y - A.y));
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t n;
    long long w = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> t[i].x >> t[i].y;
    for (int i = 1; i <= n; i++)
    {
        if (i < n) w += product(t[i], t[i + 1], { 0, 0 });
        else w += product(t[n], t[1], { 0, 0 });
    }
    if (w < 0) w *= -1;
    std::cout << w / 2;
    if (w % 2 == 1) std::cout << ".5";
    std::cout.flush();
    _Exit(0);
}
