#include "DSU.h"

DSU::DSU(size_t size)
		: parent(size), rank(size, 1)
	{
		for (int i = 0; i < size; i++)
		{
			parent[i] = i;
		}
	}

size_t DSU::find_set(size_t u)
{
	std::stack<size_t> stack;
	stack.push(u);

	while (parent[u] != u)
	{
		stack.push(parent[u]);
		u = parent[u];
	}

	size_t& root = u;

	while (!stack.empty())
	{
		parent[stack.top()] = root;
		stack.pop();
	}

	return root;
}

bool DSU::union_set(size_t u, size_t v)
{
	u = find_set(u);
	v = find_set(v);

	if (u != v)
	{
		if (rank[u] < rank[v])
			std::swap(u, v);

		parent[v] = u;
		rank[u] += rank[v];
		return true;
	}
	return false;
}

