//Dijkstra's algorithm on an undirected, weighted graph to calculate the distance from a specified node to all the other nodes (LLONG_MAX if node unreachable)
//autor: Krzysztof Hałubek
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

constexpr size_t MAXN = 100000; //insert the maximum amount of nodes in the graph
constexpr long long INF = std::numeric_limits<long long>::max();

std::vector<std::pair<size_t, size_t>> graph[MAXN];
long long dist[MAXN];

void dijkstra(size_t start)
{
	size_t v;
	long long curr;
	std::priority_queue<std::pair<long long, size_t>, std::vector<std::pair<long long, size_t>>, std::greater<std::pair<long long, size_t>>> q;
	for (size_t i = 0; i < MAXN; ++i)
		dist[i] = INF;
	q.push({ 0, start });
	while (!q.empty())
	{
		v = q.top().second;
		curr = q.top().first;
		q.pop();
		if (dist[v] != INF) continue;
		dist[v] = curr;
		for (auto x : graph[v])
			q.push({ curr + x.first, x.second });
	}
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
		graph[b].push_back({ c, a });
	}
	std::cout.flush();
	_Exit(0);
}
