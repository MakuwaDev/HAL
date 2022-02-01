//Algorithm utilizing Kruskal's algorithm to determine whether an edge is a part of any minnimum spanning tree of a given undirected weighted graph and print the results
//author: Krzysztof Hałubek
#include <iostream>
#include <algorithm>

constexpr size_t MAXN = 200000;
constexpr size_t MAXM = 300000;

struct edge
{
	size_t v1 = 0;
	size_t v2 = 0;
	size_t index = 0;
	int val = 0;
	bool inMST = false;
};

edge edges[MAXM];
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

bool valcomp(edge A, edge B)
{
	return A.val < B.val;
}
bool idcomp(edge A, edge B)
{
	return A.index < B.index;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	size_t n, m, i = 1, akt = 1;
	bool czy = false;
	for (size_t i = 0; i < MAXN; ++i)
		representative[i] = i;
	std::cin >> n >> m;
	for (size_t i = 1; i <= m; ++i)
	{
		std::cin >> edges[i].v1 >> edges[i].v2 >> edges[i].val;
		edges[i].index = i;
	}
	edges[0].val = -1;
	std::sort(edges, edges + m + 1, valcomp);
	edges[0].val = edges[1].val;
	while (i <= m)
	{
		if (edges[i].val == edges[i - 1].val)
		{
			if (!czy)
			{
				if (Find(edges[i].v1) != Find(edges[i].v2)) edges[i].inMST = true;
			}
			else if (Find(edges[i].v1) != Find(edges[i].v2)) Union(edges[i].v1, edges[i].v2);
		}
		else
		{
			if (!czy)
			{
				std::swap(akt, i);
				--i;
			}
			else
			{
				akt = i;
				--i;
				edges[i].val = edges[i + 1].val;
			}
			czy = !czy;
		}
		++i;
	}
	std::sort(edges, edges + m + 1, idcomp);
	for (size_t i = 1; i <= m; ++i)
	{
		std::cout << i << ": ";
		if (edges[i].inMST) std::cout << "YES\n";
		else std::cout << "NO\n";
	}
	std::cout.flush();
	_Exit(0);
}
