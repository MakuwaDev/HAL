//A class for a segment tree to set a value in a specified element of a series and return the maximum element on a specified interval of the series
//author: Krzysztof Hałubek
#include <iostream>

class PI_tree
{
private:
	static constexpr size_t TREESIZE = 2 << 17;
	struct node
	{
		int value;
		size_t left;
		size_t right;
	};
	node TREE[2 * TREESIZE];
	void update(size_t id, int x)
	{
		TREE[id].value = x;
		while (id > 0)
		{
			id /= 2;
			TREE[id].value = std::max(TREE[id * 2].value, TREE[id * 2 + 1].value);
		}
	}
	int read(size_t first, size_t last, size_t id)
	{
		if (TREE[id].right < first || TREE[id].left > last) return 0;
		if (TREE[id].left >= first && TREE[id].right <= last) return TREE[id].value;
		return std::max(read(first, last, id * 2), read(first, last, id * 2 + 1));
	}
public:
	PI_tree()
	{
		for (size_t i = TREESIZE; i < 2 * TREESIZE; i++)
		{
			TREE[i].left = TREE[i].right = i;
			TREE[i].value = 0;
		}
		for (size_t i = TREESIZE - 1; i > 0; i--)
		{
			TREE[i].left = TREE[2 * i].left;
			TREE[i].right = TREE[2 * i + 1].right;
			TREE[i].value = 0;
		}
	}
	void set(size_t id, int x)
	{
		update(id + TREESIZE - 1, x);
	}
	int get(size_t first, size_t last)
	{
		return read(first + TREESIZE - 1, last + TREESIZE - 1, 1);
	}
};
