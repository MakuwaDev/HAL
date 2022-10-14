//A class for a segment tree to set a value in a certain point and return the maximum sum of a coherent subsequence inside of a given interval
//author: Krzysztof Hałubek
#include <iostream>

class tree
{
private:
	static constexpr size_t TREESIZE = 2 << 17;
	struct node
	{
		long long sum;
		long long psoms;
		long long suf;
		long long pref;
		size_t left;
		size_t right;
	};
	node TREE[2 * TREESIZE];
	void update(size_t id, long long x)
	{
		TREE[id].sum = x;
		TREE[id].suf = TREE[id].pref = TREE[id].psoms = std::max(TREE[id].sum, (long long)0);
		while (id != 1)
		{
			id /= 2;
			TREE[id].sum = TREE[2 * id].sum + TREE[2 * id + 1].sum;
			TREE[id].pref = std::max(TREE[2 * id].pref, TREE[2 * id].sum + TREE[2 * id + 1].pref);
			TREE[id].suf = std::max(TREE[2 * id + 1].suf, TREE[2 * id + 1].sum + TREE[2 * id].suf);
			TREE[id].psoms = std::max(TREE[2 * id].suf + TREE[2 * id + 1].pref, std::max(TREE[2 * id].psoms, TREE[2 * id + 1].psoms));
		}
	}
	node read(size_t id, size_t first, size_t last)
	{
		node returnnode, left, right;
		returnnode.left = returnnode.pref = returnnode.psoms = returnnode.right = returnnode.suf = returnnode.sum = 0;
		if (last < TREE[id].left || TREE[id].right < first) return returnnode;
		if (first <= TREE[id].left && TREE[id].right <= last) return TREE[id];
		left = read(2 * id, first, last);
		right = read(2 * id + 1, first, last);
		returnnode.sum = left.sum + right.sum;
		returnnode.pref = std::max(left.pref, left.sum + right.pref);
		returnnode.suf = std::max(right.pref, right.sum + left.suf);
		returnnode.psoms = std::max(left.suf + right.pref, std::max(left.psoms, right.psoms));
		return returnnode;
	}
public:
	tree()
	{
		for (size_t i = TREESIZE; i < 2 * TREESIZE; i++)
		{
			TREE[i].sum = TREE[i].psoms = TREE[i].suf = TREE[i].pref = 0;
			TREE[i].left = TREE[i].right = i;
		}
		for (size_t i = TREESIZE - 1; i > 0; i--)
		{
			TREE[i].sum = TREE[i].psoms = TREE[i].suf = TREE[i].pref = 0;
			TREE[i].left = TREE[2 * i].left;
			TREE[i].right = TREE[2 * i + 1].right;
		}
	}
	void set(size_t id, long long x)
	{
		update(TREESIZE + id - 1, x);
	}
	long long get(size_t first, size_t last)
	{
		return read(1, first + TREESIZE - 1, last + TREESIZE - 1).psoms;
	}
};
