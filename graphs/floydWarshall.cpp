//Floyd-Warshall algorithm to print the distance between all pairs of nodes ('*' if no path between a pair doesn't exist and '-oo' if the lightest path between a pair doesn't exist) in a directed weighted graph with positive or negative edge weights, but without negative cycles
//author: Krzysztof Hałubek
#include <iostream>
#include <vector>

constexpr long long INF = (long long)25e6 + 15;
constexpr size_t MAXN = (size_t)5e2 + 10; // insert maximum amount of nodes

long long dist[MAXN][MAXN];
std::vector<size_t> cycles;

size_t n, m;

void initDist()
{
	for (size_t i = 1; i < MAXN; i++)
	{
		for (size_t j = 1; j < MAXN; j++)
		{
			if (j == i) dist[i][j] = 0;
			else dist[i][j] = INF;
		}
	}
}

void floydWarshall()
{
	for (size_t v = 1; v <= n; v++)
		for (size_t a = 1; a <= n; a++)
			for (size_t b = 1; b <= n; b++)
				if (dist[a][v] != INF && dist[v][b] != INF) dist[a][b] = std::min(dist[a][b], dist[a][v] + dist[v][b]);
}

void findNegativeCycles()
{
	for (size_t i = 1; i <= n; i++)
		if (dist[i][i] < 0) cycles.push_back(i);
	for (auto v : cycles)
		for (size_t a = 1; a <= n; a++)
			for (size_t b = 1; b <= n; b++)
				if (a != b)
					if (dist[a][v] < INF && dist[v][b] < INF) dist[a][b] = -INF;
	for (auto x : cycles)
		dist[x][x] = -INF;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	initDist();
	int a, b;
	long long g;
	std::cin >> n >> m;
	for (size_t i = 1; i <= m; i++)
	{
		std::cin >> a >> b >> g;
		if (a != b || g < 0) dist[a][b] = g;
	}
	floydWarshall();
	findNegativeCycles();
	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = 1; j <= n; j++)
		{
			if (dist[i][j] >= INF) std::cout << "* ";
			else if (dist[i][j] == -INF) std::cout << "-oo ";
			else std::cout << dist[i][j] << " ";
		}
		std::cout << "\n";
	}
}
