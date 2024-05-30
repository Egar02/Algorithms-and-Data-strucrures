#pragma once
#include <vector>
#include <stack>
class DSU
{
public:
	DSU(size_t size);

	size_t find_set(size_t u);

	bool union_set(size_t u, size_t v);
	

private:
	std::vector<size_t> parent;
	std::vector<size_t> rank;
};