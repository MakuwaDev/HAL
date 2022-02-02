//Algorithm to determine wheter given point (with whole coordinates) is located on the edge of a polygon (returns 0), inside the polygon (return 1) or outside of it (returns -1) the polygon shall be defined as a clockwise ordered set of points with whole coordinates
//author: Krzysztof Hałubek
#include <iostream>
#include <limits>

constexpr size_t MAXN = 20000; //insert the maximum amount of vertexes
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

long long inline iloczyn(point A, point B, point C)
{
	return ((C.x - A.x) * (B.y - A.y)) - ((B.x - A.x) * (C.y - A.y));
}

bool inline znak(long long a, long long b)
{
	if (a > 0 && b < 0) return true;
	if (a < 0 && b>0) return true;
	return false;
}

bool xd(point A, point B, point C)
{
	bool a1 = std::min(A.x, B.x) <= C.x;
	bool a2 = std::max(A.x, B.x) >= C.x;
	bool a3 = std::min(A.y, B.y) <= C.y;
	bool a4 = std::max(A.y, B.y) >= C.y;
	return a1 && a2 && a3 && a4;
}

point coordinates[MAXN];
point t1[MAXN];
point t2[MAXN];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, wynik;
	long long x, y, i1, i2, i3, i4;
	std::cin >> n;
	for (int i = 0; i < n; i++)
		std::cin >> coordinates[i].x >> coordinates[i].y;
	for (int i = 0; i < n - 1; i++)
	{
		t1[i] = coordinates[i];
		t2[i] = coordinates[i + 1];
	}
	t1[n - 1] = coordinates[n - 1];
	t2[n - 1] = coordinates[0];
	std::cin >> x >> y;
	wynik = 0;
	bool bok = false;
	for (int i = 0; i < n; i++)
	{
		int w = 0;
		point A = { x, y };
		point B = { INF, y + 1 };
		i1 = iloczyn(t1[i], t2[i], A);
		i2 = iloczyn(t1[i], t2[i], B);
		i3 = iloczyn(A, B, t1[i]);
		i4 = iloczyn(A, B, t2[i]);
		if (znak(i1, i2) && znak(i3, i4)) w = 2;
		else
		{
			if (i1 == 0 && xd(t1[i], t2[i], A)) w = 1;
			else
			{
				if (i2 == 0 && xd(t1[i], t2[i], B)) w = 2;
				else
				{
					if (i3 == 0 && xd(A, B, t1[i])) w = 2;
					else
					{
						if (i4 == 0 && xd(A, B, t2[i])) w = 2;
					}
				}
			}
		}
		if (w == 1) {
			bok = true;
			break;
		}
		if (w == 2) {
			wynik++;
		}
	}
	if (bok) return 0;
	else if (wynik % 2 == 0) return -1;
	else return 1;
}
