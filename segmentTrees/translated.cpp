//Algorithm to flip the bits at a given interval of positions and count the amount of lit bits on a specified interval; more imporantly the algorithm is able to translate the ranges so that presuming that there will be less than 2 * 10^5 intervals to be asked about (flip or calculate the amount), the maximum point mentioned can reach up to 10^9
//author: Krzysztof Hałubek
#include <iostream>
#include <set>
#include <limits>

constexpr size_t MAXM = 2 << 19;
constexpr size_t INF = std::numeric_limits<size_t>::max();

struct query
{
	size_t first;
	size_t last;
	bool type;
};

std::pair<size_t, size_t> range[2 * MAXM];
size_t value[2 * MAXM];
bool changed[2 * MAXM];
query queries[MAXM];
std::set<size_t> leaves;

void init()
{
	for (size_t i = MAXM; i < 2 * MAXM; i++)
	{
		range[i].first = range[i].second = INF;
		value[i] = 0;
	}
	size_t prev = -4, id = 1;
	prev = *leaves.begin();
	value[MAXM] = 1;
	range[MAXM].first = range[MAXM].second = *leaves.begin();
	for (auto x = ++leaves.begin(); x != leaves.end(); ++x)
	{
		if (*x != prev + 1)
		{
			value[MAXM + id] = *x - prev - 1;
			range[MAXM + id].first = prev + 1;
			range[MAXM + id].second = *x - 1;
			id++;
		}
		prev = *x;
		value[MAXM + id] = 1;
		range[MAXM + id].first = range[MAXM + id].second = *x;
		id++;
	}
	for (size_t i = MAXM - 1; i > 0; i--)
	{
		value[i] = value[2 * i] + value[2 * i + 1];
		range[i].first = range[2 * i].first;
		range[i].second = range[2 * i + 1].second;
	}
}

void push_to_children(size_t id)
{
	changed[2 * id] = !changed[2 * id];
	changed[2 * id + 1] = !changed[2 * id + 1];
	value[2 * id] = (range[2 * id].second - range[2 * id].first + 1) - value[2 * id];
	value[2 * id + 1] = (range[2 * id + 1].second - range[2 * id + 1].first + 1) - value[2 * id + 1];
}

void update(size_t first, size_t last, size_t id)
{
	if (changed[id])
	{
		changed[id] = false;
		if (id < MAXM) push_to_children(id);
	}
	if (range[id].second < first || range[id].first > last) return;
	if (range[id].first >= first && range[id].second <= last)
	{
		changed[id] = !changed[id];
		value[id] = (range[id].second - range[id].first + 1) - value[id];
		size_t newid = id;
		while (newid > 0)
		{
			newid /= 2;
			value[newid] = value[2 * newid] + value[2 * newid + 1];
		}
		return;
	}
	update(first, last, 2 * id);
	update(first, last, 2 * id + 1);
}

size_t read(size_t first, size_t last, size_t id)
{
	if (changed[id])
	{
		changed[id] = false;
		if (id < MAXM) push_to_children(id);
	}
	if (range[id].second < first || range[id].first > last)
		return 0;
	if (range[id].first >= first && range[id].second <= last)
		return value[id];
	return read(first, last, id * 2) + read(first, last, id * 2 + 1);
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	size_t n, m;
	char c;
	std::cin >> n >> m;
	for (size_t i = 0; i < m; i++)
	{
		std::cin >> c >> queries[i].first >> queries[i].last;
		if (c == '*') queries[i].type = 0;
		else if (c == '?') queries[i].type = 1;
		queries[i].first--;
		queries[i].last--;
		leaves.insert(queries[i].first);
		leaves.insert(queries[i].last);
	}
	init();
	for (size_t q = 0; q < m; q++)
	{
		if (queries[q].type) std::cout << read(queries[q].first, queries[q].last, 1) << "\n";
		else update(queries[q].first, queries[q].last, 1);
	}
}
