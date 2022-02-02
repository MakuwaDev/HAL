//A class for a segment tree to calculate the amount of directed (left to right) vectors in one dimension on any interval and turnaround any point (beginning to ending and vice versa), all points are initialized as beginings
//author: Krzysztof Hałubek
#include <iostream>

class PI_tree
{
private:
	static constexpr size_t TREESIZE = 2 << 17;
	struct node
	{
		long long begins;
		long long ends;
		long long vectors;
		size_t left;
		size_t right;
	};
	node TREE[2 * TREESIZE];
	void update(size_t id)
	{
		TREE[id].begins = (TREE[id].begins + 1) % 2;
		TREE[id].ends = (TREE[id].ends + 1) % 2;
		while (id != 0)
		{
			id /= 2;
			TREE[id].ends = TREE[2 * id].ends + TREE[2 * id + 1].ends;
			TREE[id].begins = TREE[2 * id].begins + TREE[2 * id + 1].begins;
			TREE[id].vectors = TREE[2 * id].vectors + TREE[2 * id + 1].vectors + TREE[2 * id].begins * TREE[2 * id + 1].ends;
		}
	}
	node read(size_t first, size_t last, size_t id)
	{
		node returnnode, left, right;
		returnnode.begins = returnnode.ends = returnnode.left = returnnode.right = returnnode.vectors = 0;
		if (last < TREE[id].left || TREE[id].right < first) return returnnode;
		if (first <= TREE[id].left && TREE[id].right <= last) return TREE[id];
		left = read(first, last, 2 * id);
		right = read(first, last, 2 * id + 1);
		returnnode.begins = left.begins + right.begins;
		returnnode.ends = left.ends + right.ends;
		returnnode.vectors = left.vectors + right.vectors + left.begins * right.ends;
		return returnnode;
	}
public:
	PI_tree()
	{
		for (size_t i = TREESIZE; i < 2 * TREESIZE; i++)
		{
			TREE[i].left = TREE[i].right = i;
			TREE[i].ends = TREE[i].vectors = 0;
			TREE[i].begins = 1;
		}
		for (size_t i = TREESIZE - 1; i > 0; i--)
		{
			TREE[i].left = TREE[2 * i].left;
			TREE[i].right = TREE[2 * i + 1].right;
			TREE[i].ends = TREE[2 * i].ends + TREE[2 * i + 1].ends;
			TREE[i].begins = TREE[2 * i].begins + TREE[2 * i + 1].begins;
			TREE[i].vectors = TREE[2 * i].vectors + TREE[2 * i + 1].vectors + TREE[2 * i].begins * TREE[2 * i + 1].ends;
		}
	}
	long long query(size_t first, size_t last)
	{
		return read(first + TREESIZE - 1, last + TREESIZE - 1, 1).vectors;
	}
	void turnaround(size_t id)
	{
		update(id + TREESIZE - 1);
	}
};
