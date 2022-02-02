//A class for a segment tree to add a given value to every point on a specified interval and calculate the minimum value on a given interval
//author: Krzysztof Hałubek
#include <iostream>
#include <limits>

class II_tree
{
private:
	static constexpr size_t TREESIZE = 2 << 17;
	static constexpr long long INF = std::numeric_limits<long long>::max();
	struct node
	{
		size_t left;
		size_t right;
		long long value;
		long long change;
	};
	node TREE[2 * TREESIZE];
	void update(size_t first, size_t last, size_t id, long long x)
	{
		if (TREE[id].right < first || TREE[id].left > last) return;
		else if (TREE[id].left >= first && TREE[id].right <= last)
		{
			TREE[id].value += x;
			TREE[id].change += x;
		}
		else
		{
			TREE[2 * id].value += TREE[id].change;
			TREE[2 * id + 1].value += TREE[id].change;
			TREE[2 * id].change += TREE[id].change;
			TREE[2 * id + 1].change += TREE[id].change;
			TREE[id].change = 0;
			update(first, last, 2 * id, x);
			update(first, last, 2 * id + 1, x);
			TREE[id].value = std::min(TREE[2 * id].value, TREE[2 * id + 1].value);
		}
	}
	void set1(size_t id, long long x)
	{
		//tylko przed jakimkolwiek wywołaniem funkcji update
		TREE[id].value = x;
		while (id > 0)
		{
			id /= 2;
			TREE[id].value = std::min(TREE[id * 2].value, TREE[id * 2 + 1].value);
		}
	}
	long long read(size_t first, size_t last, size_t id)
	{
		if (TREE[id].left > last || TREE[id].right < first) return INF;
		else if (TREE[id].left >= first && TREE[id].right <= last) return TREE[id].value;
		else
		{
			TREE[2 * id].value += TREE[id].change;
			TREE[2 * id + 1].value += TREE[id].change;
			TREE[2 * id].change += TREE[id].change;
			TREE[2 * id + 1].change += TREE[id].change;
			TREE[id].change = 0;
			return std::min(read(first, last, 2 * id), read(first, last, 2 * id + 1));
		}
	}
public:
	II_tree()
	{
		for (size_t i = TREESIZE; i < 2 * TREESIZE; i++)
		{
			TREE[i].left = TREE[i].right = i;
			TREE[i].value = INF;
			TREE[i].change = 0;
		}
		for (size_t i = TREESIZE - 1; i > 0; i--)
		{
			TREE[i].left = TREE[2 * i].left;
			TREE[i].right = TREE[2 * i + 1].right;
			TREE[i].value = std::min(TREE[2 * i].value, TREE[2 * i + 1].value);
			TREE[i].change = 0;
		}
	}
	void add(size_t first, size_t last, long long x)
	{
		update(first + TREESIZE - 1, last + TREESIZE - 1, 1, x);
	}
	void set(size_t id, long long x)
	{
		set1(id + TREESIZE - 1, x);
	}
	long long query(size_t first, size_t last)
	{
		return read(first + TREESIZE - 1, last + TREESIZE - 1, 1);
	}
};
