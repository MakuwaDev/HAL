//Algorithm to find and print an Eulerian Cycle of a given undirected graph, returns -1 if no shuch exists
//author: Krzysztof Hałubek
#include <iostream>
#include <vector>

constexpr size_t MAXN = (size_t)1e5 + 5; //insert the maximum amount of nodes
constexpr size_t MAXM = (size_t)3e5 + 5; //insert the maximum amount of edges

std::vector<std::pair<size_t, size_t>> graph[MAXN];
size_t in[MAXN];
bool visited[MAXM];
size_t start[MAXN];
std::vector<size_t> res;

void dfs(size_t v)
{
	for (size_t i = start[v]; i < graph[v].size(); ++i)
	{
		start[v]++;
		if (!visited[graph[v][i].second])
		{
			visited[graph[v][i].second] = true;
			dfs(graph[v][i].first);
			i = start[v];
		}
	}
	res.push_back(v);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	size_t n, m, a, b, x;
	std::cin >> n >> m;
	std::cin >> x >> b;
	++in[x]; ++in[b];
	graph[x].push_back({ b, 1 });
	graph[b].push_back({ x, 1 });
	for (size_t i = 2; i <= m; ++i)
	{
		std::cin >> a >> b;
		++in[a]; ++in[b];
		graph[a].push_back({ b, i });
		graph[b].push_back({ a, i });
	}
	for (size_t i = 1; i <= n; ++i)
		if (in[i] % 2 == 1) return -1;
	dfs(x);
	for (size_t i = 1; i <= m; ++i)
		if (!visited[i]) return -1;
	for (size_t i = res.size() - 1; i > 0 && i < res.size(); --i)
		std::cout << res[i] << " ";
	std::cout.flush();
	_Exit(0);
}
