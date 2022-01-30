//Bellman-Ford algorithm to calculate the distance from a specified node to all the other nodes (>= 1e18 if node unreachable) in a directed, weighted graph with negative edges and without negative cycles
//autor: Krzysztof Hałubek
#include <iostream>
#include <vector>

constexpr size_t MAXN = 100000; //insert the maximum amount of nodes in the graph
constexpr long long INF = (long long)1e18;

std::vector<std::pair<long long, size_t>> graph[MAXN];
long long dist[MAXN];

void bellmanFord(size_t s, size_t n)
{
	for (size_t i = 0; i < MAXN; i++)
		dist[i] = 2 * INF;
	dist[s] = 0;
	for (size_t i = 0; i < n - 1; i++)
		for (size_t v = 1; v <= n; v++)
			for (auto e : graph[v])
				if (dist[v] + e.first < dist[e.second]) dist[e.second] = dist[v] + e.first;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	size_t n, m, a, b;
	long long c;
	std::cin >> n >> m;
	for (size_t i = 0; i < m; ++i)
	{
		std::cin >> a >> b >> c;
		graph[a].push_back({ c, b });
	}
	std::cout.flush();
	_Exit(0);
}
