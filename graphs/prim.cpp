//Prim's algorithm to find a minimum spanning tree for a weighted undirected graph and return the sum of it's edges
//author: Krzysztof Hałubek
#include <iostream>
#include <vector>
#include <queue>

constexpr size_t MAXN = (size_t)1e5 + 5; //insert the maximum amount of nodes
constexpr size_t MAXM = (size_t)3e5 + 5; //insert the maximum amount of edges

std::vector<std::pair<long long, size_t>> graph[MAXN];
bool visited[MAXN];

long double prim(int start, int n)
{
	std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> q;
	long long res = 0, e;
	int v, sz = 1;
	visited[start] = true;
	for (auto x : graph[start])
		q.push(x);
	while (sz < n)
	{
		e = q.top().first;
		v = q.top().second;
		q.pop();
		if (visited[v]) continue;
		++sz;
		visited[v] = true;
		res += e;
		for (auto x : graph[v])
			if (!visited[x.second]) q.push(x);
	}
	return res;
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
