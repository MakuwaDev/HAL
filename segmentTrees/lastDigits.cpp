//A class for a segment tree to add a given value to every point on a specified interval and calculate the sum of least significant digits on a given interval
//author: Krzysztof Hałubek
#include <iostream>
#include <array>
#include <algorithm>

static constexpr size_t TREESIZE = 2 << 17;

std::array<size_t, 10> rests[2 * TREESIZE];
std::pair<size_t, size_t> range[2 * TREESIZE];
size_t changed[2 * TREESIZE];
size_t help[10];

static inline void init()noexcept
{
	for (size_t i = TREESIZE; i < 2 * TREESIZE; i++)
	{
		range[i].first = range[i].second = i;
		for (size_t j = 0; j < 10; j++)
			rests[i][j] = 0;
		changed[i] = 0;
	}
	for (size_t i = TREESIZE - 1; i > 0; i--)
	{
		range[i].first = range[2 * i].first;
		range[i].second = range[2 * i + 1].second;
		for (size_t j = 0; j < 10; j++)
			rests[i][j] = 0;
		changed[i] = 0;
	}
}

static inline void push_to_children(size_t id)noexcept
{
	size_t k;
	changed[2 * id] += changed[id];
	changed[2 * id + 1] += changed[id];
	if (changed[2 * id] > 9) changed[2 * id] -= 10;
	if (changed[2 * id + 1] > 9) changed[2 * id + 1] -= 10;
	for (size_t i = 0; i < 10; i++)
	{
		k = i + changed[id];
		if (k > 9) k -= 10;
		help[k] = rests[2 * id][i];
	}
	for (size_t i = 0; i < 10; i++)
		rests[2 * id][i] = help[i];
	for (size_t i = 0; i < 10; i++)
	{
		k = i + changed[id];
		if (k > 9) k -= 10;
		help[k] = rests[2 * id + 1][i];
	}
	for (size_t i = 0; i < 10; i++)
		rests[2 * id + 1][i] = help[i];
}

static inline void update(size_t first, size_t last, size_t id, size_t x)noexcept
{
	if (range[id].first > last || range[id].second < first) return;
	if (changed[id] != 0)
	{
		if (id < TREESIZE) push_to_children(id);
		changed[id] = 0;
	}
	if (first <= range[id].first && range[id].second <= last)
	{
		changed[id] = x;
		std::rotate(rests[id].rbegin(), rests[id].rbegin() + x, rests[id].rend());
		return;
	}
	update(first, last, 2 * id, x);
	update(first, last, 2 * id + 1, x);
	for (size_t i = 0; i < 10; i++)
		rests[id][i] = rests[2 * id][i] + rests[2 * id + 1][i];
}

static inline size_t read(size_t first, size_t last, size_t id)noexcept
{
	if (range[id].first > last || range[id].second < first) return 0;
	if (changed[id] != 0)
	{
		if (id < TREESIZE) push_to_children(id);
		changed[id] = 0;
	}
	if (first <= range[id].first && range[id].second <= last)
	{
		size_t result = 0;
		for (size_t i = 0; i < 10; i++)
			result += (rests[id][i] * i);
		return result;
	}
	return read(first, last, 2 * id) + read(first, last, 2 * id + 1);
}

static inline void set(size_t id, size_t rest)noexcept
{
	rests[id][rest] = 1;
	while (id > 0)
	{
		id /= 2;
		rests[id][rest] = rests[2 * id][rest] + rests[2 * id + 1][rest];
	}
}
