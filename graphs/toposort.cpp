//Algorithm to generate topologically ordered list of nodes of given Directed Acyclic Graph
//author: Krzysztof Hałubek
#include <iostream>
#include <vector>
#include <queue>

constexpr size_t MAXN = 100000; //insert the maximum amount of nodes in the graph

std::vector<size_t> graph[MAXN];
int in[MAXN];
std::vector<size_t> order;

void toposort(size_t  n)
{
	size_t v;
	std::queue<size_t> q;
	for (size_t i = 1; i <= n; ++i)
		if (in[i] == 0) q.push(i);
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		order.push_back(v);
		for (auto x : graph[v])
		{
			--in[x];
			if (in[x] == 0) q.push(x);
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
		++in[b];
	}
	std::cout.flush();
	_Exit(0);
}
