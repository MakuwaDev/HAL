//Breadth First Search on an undirected, unweighted graph to calculate the distance from a specified node to all the other nodes (INT_MAX if node unreachable)
//autor: Krzysztof Hałubek
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

constexpr size_t MAXN = 100000; //insert the maximum amount of nodes in the graph
constexpr int INF = std::numeric_limits<int>::max();

std::vector<size_t> graph[MAXN];
int dist[MAXN];

void bfs(size_t start)
{
	size_t v, father;
	std::queue<std::pair<size_t, size_t>> q;
	for (size_t i = 0; i < MAXN; ++i)
		dist[i] = INF;
	dist[start] = 0;
	for (auto x : graph[start])
		q.push({ x, start });
	while (!q.empty())
	{
		v = q.front().first;
		father = q.front().second;
		q.pop();
		if (dist[v] != INF) continue;
		dist[v] = dist[father] + 1;
		for (auto x : graph[v])
			q.push({ x, v });
	}
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
