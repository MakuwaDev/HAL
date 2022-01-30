//Algorithm to generate Strongly Connected Components in a given directed graph by assigning every node a number that represents it's division
//author: Krzysztof Hałubek
#include <iostream>
#include <vector>
#include <queue>

constexpr size_t MAXN = 100000; //insert the maximum amount of nodes in the graph

std::vector<size_t> graph[MAXN];
std::vector<size_t> transposed_graph[MAXN];
bool visited[MAXN];
size_t division[MAXN];
std::vector<size_t> postorder;

void graph_dfs(int v)
{
	visited[v] = true;
	for (auto x : graph[v])
		if (!visited[x]) graph_dfs(x);
	postorder.push_back(v);
}

void transposed_graph_dfs(int v, int s)
{
	visited[v] = true;
	division[v] = s;
	for (auto x : transposed_graph[v])
		if (!visited[x]) transposed_graph_dfs(x, s);
}

void generate_strongly_connected_components(size_t n)
{
	size_t x, curr = 1;
	for (size_t i = 1; i <= n; ++i)
		if (!visited[i]) graph_dfs(i);
	for (size_t i = 1; i <= n; ++i)
		visited[i] = false;
	while (!postorder.empty())
	{
		x = postorder.back();
		postorder.pop_back();
		if (!visited[x])
		{
			transposed_graph_dfs(x, curr);
			++curr;
		}
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
		transposed_graph[b].push_back(a);
	}
	std::cout.flush();
	_Exit(0);
}
