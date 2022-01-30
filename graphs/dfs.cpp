//Depth First Search on an undirected graph to determine whether other nodes are accessible from a specified node
//author: Krzysztof Hałubek
#include <iostream>
#include <vector>

constexpr size_t MAXN = 100000; //insert the maximum amount of nodes in the graph

std::vector<size_t> graph[MAXN];
bool visited[MAXN];

void dfs(size_t v)
{
	visited[v] = true;
	for (auto x : graph[v])
		if (!visited[x]) dfs(x);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	size_t n, m, a, b;
	std::cin >> n >> m;
	for (size_t i = 0; i < m; ++i)
	{
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	std::cout.flush();
	_Exit(0);
}
