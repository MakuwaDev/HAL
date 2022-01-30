//Algorithm to calculate Lowest Common Ancestor of any two nodes in an undirected tree rooted in node 1
//author: Krzysztof Hałubek
#include <iostream>
#include <vector>

constexpr size_t MAXN = (size_t)5e5 + 5; //insert the maximum amount of nodes
constexpr size_t MAXPOW = 20; // this should be set as ceiling(log2(MAXN))

std::vector<size_t> graph[MAXN];
size_t depth[MAXN];
size_t ancestors[MAXN][MAXPOW + 1];

void init(size_t v = 1, size_t father = 1)
{
	depth[v] = depth[father] + 1;
	ancestors[v][0] = father;
	for (size_t i = 1; i <= MAXPOW; ++i)
		ancestors[v][i] = ancestors[ancestors[v][i - 1]][i - 1];
	for (auto x : graph[v])
		if (x != father) init(x, v);
}

size_t lca(size_t a, size_t b)
{
	if (a == b) return a;
	if (depth[a] > depth[b]) std::swap(a, b);
	for (size_t i = MAXPOW; i >= 0 && i <= MAXPOW; --i)
		if (depth[ancestors[b][i]] >= depth[a]) b = ancestors[b][i];
	if (a == b) return a;
	for (size_t i = MAXPOW; i >= 0 && i <= MAXPOW; --i)
		if (ancestors[a][i] != ancestors[b][i])
		{
			a = ancestors[a][i];
			b = ancestors[b][i];
		}
	return ancestors[a][0];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	size_t n, a, b;
	std::cin >> n;
	for (size_t i = 0; i < n - 1; ++i)
	{
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	depth[1] = -1;
	init();
}
