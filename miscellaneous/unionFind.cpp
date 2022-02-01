//Functions needed to perform find and union operations on an indexed set of elements
//author: Krzysztof Hałubek
#include <iostream>
#include <algorithm>

constexpr size_t MAXN = 200000; //insert maximum amount of elements

size_t representative[MAXN];

size_t Find(size_t x)
{
	if (representative[x] == x) return x;
	return representative[x] = Find(representative[x]);
}

void Union(size_t x, size_t y)
{
	if (Find(x) != Find(y)) representative[Find(x)] = Find(y);
}
