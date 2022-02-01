//Algorithm to determine whether two lines intersect with each other
//author: Krzysztof Hałubek
#include <iostream>
#include <bitset>

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

long long product(point A, point B, point C) 
{
	return ((C.x - A.x) * (B.y - A.y)) - ((B.x - A.x) * (C.y - A.y));
}

bool znak(long long a, long long b) 
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

bool intersect(point A, point B, point C, point D) 
{
	long long i1 = product(C, D, A);
	long long i2 = product(C, D, B);
	long long i3 = product(A, B, C);
	long long i4 = product(A, B, D);
	if (znak(i1, i2) && znak(i3, i4)) return true;
	if (i1 == 0 && xd(C, D, A)) return true;
	if (i2 == 0 && xd(C, D, B)) return true;
	if (i3 == 0 && xd(A, B, C)) return true;
	if (i4 == 0 && xd(A, B, D)) return true;
	return false;
}

int main() 
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	point A, B, C, D; //lines are defined like that: (A, B), (C, D)
	std::cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;
	std::cout.flush();
	_Exit(0);
}
