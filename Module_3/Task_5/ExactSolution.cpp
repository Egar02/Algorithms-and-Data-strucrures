#include "ExactSolution.h"

double ExactSolution(ListGraph& full_graph)
{
	const int vertex = full_graph.VerticesCount();
	std::vector<int> path;
	std::vector<int> final_path;

	for (int i = 0; i < vertex - 1; ++i)
	{
		path.push_back(i + 1);
	}

	for (int i = vertex - 1; i > 0; --i)
	{
		final_path.push_back(i);
	}

	double min_length = 1e9;
	std::vector<int> min_path;
	while (path != final_path)
	{
		double length = full_graph.GetWeight(0, path[0]);
		for (int i = 0; i < vertex - 2; ++i)
		{
			length += full_graph.GetWeight(path[i], path[i + 1]);
		}
		length += full_graph.GetWeight(path[vertex - 2], 0);
		if (length <= min_length)
		{
			min_length = length;
			min_path = path;
		}
		std::next_permutation(path.begin(), path.end());
	}
	return min_length;
}
