//Algorithm to perform centroid decomposition on a tree in O(nlogn), the algorithm generates a rooted tree such that centroidTree[v] contains children of v, and parent[v] is the father of v in the decomposed tree
//Warning: In order to construct the centroid tree, following algorithm deletes the given tree, so if you want to use it later, make sure to make a copy of it
//Author: Krzysztof Hałubek
#include <iostream>
#include <vector>
#include <set>

constexpr int MAXN = (int)1e5 + 5;

std::set<int> tree[MAXN];
int subtreeSize[MAXN];
int parent[MAXN];
std::vector<int> centroidTree[MAXN];

int findSubtreeSizes(int v, int father)
{
	subtreeSize[v] = 1;
	for (auto x : tree[v])
		if (x != father) subtreeSize[v] += findSubtreeSizes(x, v);
	return subtreeSize[v];
}

int getCentroid(int v, int father, int n)
{
	for (auto x : tree[v]) if (x != father)
		if (subtreeSize[x] > n / 2) return getCentroid(x, v, n);
	return v;
}

void decomposeTree(int v = 1, int father = 0)
{
	int n = findSubtreeSizes(v, father);
	int centroid = getCentroid(v, father, n);
	parent[centroid] = father;
	centroidTree[father].push_back(centroid);
	std::vector<int> tmp(tree[centroid].begin(), tree[centroid].end());
	for (auto x : tmp)
	{
		tree[centroid].erase(x);
		tree[x].erase(centroid);
		decomposeTree(x, centroid);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n, a, b;
	std::cin >> n;
	for (int i = 1; i < n; ++i)
	{
		std::cin >> a >> b;
		tree[a].insert(b);
		tree[b].insert(a);
	}
	decomposeTree();
}
