//2Sat to solve a sequence of n clauses of type (x or y), where x and y might also be negated, input example: 0 T 1 F <=> 0 v ~1, variables shall be indexed from 0
//Author: Krzysztof Hałubek
#include <iostream>
#include <vector>

constexpr int MAX_VARIABLES = 1000000, MAX_VERTICES = 2 * MAX_VARIABLES + 10;

//variables ~x_n and x_n are represented in vertices 2n and 2n + 1
//because of that, x ^ 1 (x xor 1) will simulate negation
//so x ^ 1 = ~x

std::vector<int> graph[MAX_VERTICES], transposed_graph[MAX_VERTICES];
bool visited[MAX_VERTICES];
int division[MAX_VERTICES];
std::vector<int> postorder;
int assignment[MAX_VARIABLES];

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

void generate_strongly_connected_components(int n)
{
	int x, curr = 1;
	for (int i = 0; i < n; ++i)
		if (!visited[i]) graph_dfs(i);
	for (int i = 0; i < n; ++i)
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

void makeEdge(int a, int b)
{
	graph[a ^ 1].push_back(b);
	graph[b ^ 1].push_back(a);
	transposed_graph[a].push_back(b ^ 1);
	transposed_graph[b].push_back(a ^ 1);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int variables, clauses, v1, v2;
	char c1, c2;
	std::cin >> variables >> clauses;
	for (int i = 0; i < clauses; ++i)
	{
		std::cin >> v1 >> c1 >> v2 >> c2;
		makeEdge(v1 * 2 + (c1 == 'T'), v2 * 2 + (c2 == 'T'));
	}
	generate_strongly_connected_components(2 * variables);
	for (int i = 0; i < variables; ++i)
	{
		if (division[2 * i] == division[2 * i + 1])
		{
			std::cout << "No Solutions";
			return 0;
		}
		assignment[i] = division[2 * i + 1] > division[2 * i];
	}
	for(int i = 0; i < variables; ++i)
		std::cout << (assignment[i] ? 'T' : 'F');
}
