//Turbo matching algorithm to generate the maximal matching of a bipartite graph, given the sizes of the groups. Input indexes from 1 to n + m, where n, m - sizes of the bipartite groups. Vertices with indexes 1 - n belong to the first group, while vertices with indexes n + 1 - n + m belong to the second group, tha graph shall be biparite, and every unordered pair (a, b) shall apear in input only once
//Author: Krzysztof Hałubek
#include <iostream>
#include <vector>
#include <algorithm>

constexpr int MAXN = 510;
constexpr int MAXM = 510;
constexpr int NUL = -1;

std::vector<int> graph[MAXN + MAXM];
bool visited[MAXN + MAXM];
int match[MAXN + MAXM];

bool augment(int u)
{
	if (visited[u]) return false;
	visited[u] = true;
	for (auto v : graph[u])
		if (match[v] == NUL)
		{
			match[u] = v; 
			match[v] = u;
			return true;
		}
	for (auto v : graph[u])
		if (augment(match[v]))
		{
			match[u] = v; 
			match[v] = u;
			return true;
		}
	return false;
}

void turboMatching(int n)
{
	std::fill(match, match + n + 1, NUL);
	bool any = true;
	while (any)
	{
		any = false;
		std::fill(visited, visited + n + 1, false);
		for (int u = 1; u <= n; u++)
			if (match[u] == NUL && augment(u)) any = true;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, m, a, b, v;
	std::cin >> n >> m >> v;
	for (int i = 0; i < v; ++i) 
	{
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	turboMatching(n + m);
	for (int i = 1; i <= n + m; ++i)
		std::cout << match[i] << " ";
}
