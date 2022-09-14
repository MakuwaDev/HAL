//Algorithm to count every occurence of many small strings in one bigger string using aho-corasick algorithm
//Authors: Paweł Zalewski, Krzysztof Hałubek
#include <iostream>
#include <queue>
#include <vector>
#include <string>

constexpr int alf = 26;

struct node 
{
	int next[alf];
	int parent;
	int val = 0;
	int longest_sufix;
	char new_letter;
	node() 
	{
		for (size_t i = 0; i < alf; ++i) next[i] = -1;
	}
};
std::vector<node> trie;

void add_string(const std::string& t) 
{
	int current_node = 0;
	for (size_t current_pos = 0; current_pos < t.size(); ++current_pos) 
	{
		if (trie[current_node].next[t[current_pos] - 'a'] == -1) 
		{
			trie.emplace_back();
			trie[current_node].next[t[current_pos] - 'a'] = trie.size() - 1;
			trie.rbegin()->parent = current_node;
			trie.rbegin()->new_letter = t[current_pos];
		}
		current_node = trie[current_node].next[t[current_pos] - 'a'];
	}
	++trie[current_node].val;
}

void set_sufix(int start) 
{
	int possible = trie[trie[start].parent].longest_sufix;
	while (possible != 0 && trie[possible].next[trie[start].new_letter - 'a'] == -1) 
		possible = trie[possible].longest_sufix;
	if (possible == 0 && trie[possible].next[trie[start].new_letter - 'a'] == -1 || trie[possible].next[trie[start].new_letter - 'a'] == start) 
	{
		trie[start].longest_sufix = 0;
		return;
	}
	trie[start].longest_sufix = trie[possible].next[trie[start].new_letter - 'a'];
}

void preprocess() 
{
	trie[0].longest_sufix = 0;
	std::vector<int> bfs_order;
	std::queue<int> Q;
	Q.push(0);
	while (!Q.empty()) 
	{
		int s = Q.front();
		Q.pop();
		if (s != 0) bfs_order.push_back(s);
		for (size_t i = 0; i < alf; ++i)
			if (trie[s].next[i] != -1)Q.push(trie[s].next[i]);
	}
	for (auto el : bfs_order) 
	{
		set_sufix(el);
		trie[el].val += trie[trie[el].longest_sufix].val;
	}
}

int aho_corasick(std::string& t) 
{
	int current_node = 0, res = 0;
	for (size_t i = 0; i < t.size(); ++i) 
	{
		int possible = current_node;
		while (possible != 0 && trie[possible].next[t[i] - 'a'] == -1)
			possible = trie[possible].longest_sufix;
		if (possible == 0 && trie[possible].next[t[i] - 'a'] == -1) 
		{
			current_node = 0;
			continue;
		}
		current_node = trie[possible].next[t[i] - 'a'];
		res += trie[current_node].val;
	}
	return res;
}

int main() 
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	int n;
	std::cin >> n;
	trie.emplace_back();
	std::string k;
	for (size_t i = 0; i < n; ++i) 
	{
		std::cin >> k;
		add_string(k);
	}
	preprocess();
	std::cin >> k;
	std::cout << aho_corasick(k);
}
