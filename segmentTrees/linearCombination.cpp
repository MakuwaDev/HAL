//A class for a segment tree to add specified value to every point on a specified interval of one out of two series and calculate the linear combination of those two series' on a given interval
//author: Krzysztof Hałubek
#include <iostream>

class II_tree
{
private:
	static constexpr size_t TREESIZE = 2 << 17;
	struct node
	{
		long long product;
		long long A;
		long long B;
		long long addA;
		long long addB;
		size_t left;
		size_t right;
	};
	node TREE[2 * TREESIZE];
	void updateA(size_t first, size_t last, size_t id, long long x)
	{
		if (TREE[id].left > last || TREE[id].right < first) return;
		if (id >= TREESIZE)
		{
			TREE[id].A += x;
			TREE[id].product = TREE[id].A * TREE[id].B;
			return;
		}
		if (TREE[id].left >= first && TREE[id].right <= last)
		{
			TREE[id].A += ((long long)TREE[id].right - (long long)TREE[id].left + 1) * x;
			TREE[id].addA += x;
			TREE[id].product += x * TREE[id].B;
			return;
		}
		if (TREE[id].addA != 0)
		{
			TREE[2 * id].A += TREE[id].addA * ((long long)TREE[2 * id].right - (long long)TREE[2 * id].left + 1);
			TREE[2 * id + 1].A += TREE[id].addA * ((long long)TREE[2 * id + 1].right - (long long)TREE[2 * id + 1].left + 1);
			TREE[2 * id].addA += TREE[id].addA;
			TREE[2 * id + 1].addA += TREE[id].addA;
			TREE[2 * id].product += TREE[id].addA * TREE[2 * id].B;
			TREE[2 * id + 1].product += TREE[id].addA * TREE[2 * id + 1].B;
			TREE[id].addA = 0;
		}
		if (TREE[id].addB != 0)
		{
			TREE[2 * id].B += TREE[id].addB * ((long long)TREE[2 * id].right - (long long)TREE[2 * id].left + 1);
			TREE[2 * id + 1].B += TREE[id].addB * ((long long)TREE[2 * id + 1].right - (long long)TREE[2 * id + 1].left + 1);
			TREE[2 * id].addB += TREE[id].addB;
			TREE[2 * id + 1].addB += TREE[id].addB;
			TREE[2 * id].product += TREE[id].addB * TREE[2 * id].A;
			TREE[2 * id + 1].product += TREE[id].addB * TREE[2 * id + 1].A;
			TREE[id].addB = 0;
		}
		updateA(first, last, 2 * id, x);
		updateA(first, last, 2 * id + 1, x);
		TREE[id].A = TREE[2 * id].A + TREE[2 * id + 1].A;
		TREE[id].B = TREE[2 * id].B + TREE[2 * id + 1].B;
		TREE[id].product = TREE[2 * id].product + TREE[2 * id + 1].product;
	}
	void updateB(size_t first, size_t last, size_t id, long long x)
	{
		if (TREE[id].left > last || TREE[id].right < first) return;
		if (id >= TREESIZE)
		{
			TREE[id].B += x;
			TREE[id].product = TREE[id].A * TREE[id].B;
			return;
		}
		if (TREE[id].left >= first && TREE[id].right <= last)
		{
			TREE[id].B += ((long long)TREE[id].right - (long long)TREE[id].left + 1) * x;
			TREE[id].addB += x;
			TREE[id].product += x * TREE[id].A;
			return;
		}
		if (TREE[id].addA != 0)
		{
			TREE[2 * id].A += TREE[id].addA * ((long long)TREE[2 * id].right - (long long)TREE[2 * id].left + 1);
			TREE[2 * id + 1].A += TREE[id].addA * ((long long)TREE[2 * id + 1].right - (long long)TREE[2 * id + 1].left + 1);
			TREE[2 * id].addA += TREE[id].addA;
			TREE[2 * id + 1].addA += TREE[id].addA;
			TREE[2 * id].product += TREE[id].addA * TREE[2 * id].B;
			TREE[2 * id + 1].product += TREE[id].addA * TREE[2 * id + 1].B;
			TREE[id].addA = 0;
		}
		if (TREE[id].addB != 0)
		{
			TREE[2 * id].B += TREE[id].addB * ((long long)TREE[2 * id].right - (long long)TREE[2 * id].left + 1);
			TREE[2 * id + 1].B += TREE[id].addB * ((long long)TREE[2 * id + 1].right - (long long)TREE[2 * id + 1].left + 1);
			TREE[2 * id].addB += TREE[id].addB;
			TREE[2 * id + 1].addB += TREE[id].addB;
			TREE[2 * id].product += TREE[id].addB * TREE[2 * id].A;
			TREE[2 * id + 1].product += TREE[id].addB * TREE[2 * id + 1].A;
			TREE[id].addB = 0;
		}
		updateB(first, last, 2 * id, x);
		updateB(first, last, 2 * id + 1, x);
		TREE[id].A = TREE[2 * id].A + TREE[2 * id + 1].A;
		TREE[id].B = TREE[2 * id].B + TREE[2 * id + 1].B;
		TREE[id].product = TREE[2 * id].product + TREE[2 * id + 1].product;
	}
	long long read(size_t first, size_t last, size_t id)
	{
		long long l, r;
		if (TREE[id].left > last || TREE[id].right < first) return 0;
		if (TREE[id].left >= first && TREE[id].right <= last) return TREE[id].product;
		if (TREE[id].addA != 0)
		{
			TREE[2 * id].A += TREE[id].addA * ((long long)TREE[2 * id].right - (long long)TREE[2 * id].left + 1);
			TREE[2 * id + 1].A += TREE[id].addA * ((long long)TREE[2 * id + 1].right - (long long)TREE[2 * id + 1].left + 1);
			TREE[2 * id].addA += TREE[id].addA;
			TREE[2 * id + 1].addA += TREE[id].addA;
			TREE[2 * id].product += TREE[id].addA * TREE[2 * id].B;
			TREE[2 * id + 1].product += TREE[id].addA * TREE[2 * id + 1].B;
			TREE[id].addA = 0;
		}
		if (TREE[id].addB != 0)
		{
			TREE[2 * id].B += TREE[id].addB * ((long long)TREE[2 * id].right - (long long)TREE[2 * id].left + 1);
			TREE[2 * id + 1].B += TREE[id].addB * ((long long)TREE[2 * id + 1].right - (long long)TREE[2 * id + 1].left + 1);
			TREE[2 * id].addB += TREE[id].addB;
			TREE[2 * id + 1].addB += TREE[id].addB;
			TREE[2 * id].product += TREE[id].addB * TREE[2 * id].A;
			TREE[2 * id + 1].product += TREE[id].addB * TREE[2 * id + 1].A;
			TREE[id].addB = 0;
		}
		l = read(first, last, 2 * id);
		r = read(first, last, 2 * id + 1);
		TREE[id].A = TREE[2 * id].A + TREE[2 * id + 1].A;
		TREE[id].B = TREE[2 * id].B + TREE[2 * id + 1].B;
		TREE[id].product = TREE[2 * id].product + TREE[2 * id + 1].product;
		return l + r;
	}
public:
	II_tree()
	{
		for (size_t i = TREESIZE; i < 2 * TREESIZE; i++)
		{
			TREE[i].left = TREE[i].right = i;
			TREE[i].A = TREE[i].B = TREE[i].addA = TREE[i].addB = TREE[i].product = 0;
		}
		for (size_t i = TREESIZE - 1; i > 0; i--)
		{
			TREE[i].left = TREE[2 * i].left;
			TREE[i].right = TREE[2 * i + 1].right;
			TREE[i].A = TREE[i].B = TREE[i].addA = TREE[i].addB = TREE[i].product = 0;
		}
	}
	void addA(size_t first, size_t last, long long x)
	{
		updateA(first + TREESIZE - 1, last + TREESIZE - 1, 1, x);
	}
	void addB(size_t first, size_t last, long long x)
	{
		updateB(first + TREESIZE - 1, last + TREESIZE - 1, 1, x);
	}
	long long query(size_t first, size_t last)
	{
		return read(first + TREESIZE - 1, last + TREESIZE - 1, 1);
	}
};
