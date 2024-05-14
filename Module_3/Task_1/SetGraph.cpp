#include "SetGraph.h"

SetGraph::SetGraph(int size) : adjacency_sets(size)
{
}

SetGraph::SetGraph(const IGraph& graph)
{
	std::vector<std::unordered_set<int>> sets(graph.VerticesCount());
	for (int i = 0; i < graph.VerticesCount(); ++i)
	{
		for (int vert : graph.GetNextVertices(i))
		{
			sets[i].insert(vert);
		}
	}
	adjacency_sets = sets;
}

SetGraph::~SetGraph()
{
}

void SetGraph::AddEdge(int from, int to)
{
	assert(0 <= from && from < adjacency_sets.size());
	assert(0 <= to && to < adjacency_sets.size());
	adjacency_sets[from].insert(to);
}

int SetGraph::VerticesCount() const
{
	return adjacency_sets.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
	assert(0 <= vertex && vertex < adjacency_sets.size());
	std::vector<int> next_vertices;
	for (int vert : adjacency_sets[vertex])
	{
		next_vertices.push_back(vert);
	}
	return next_vertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
	assert(0 <= vertex && vertex < adjacency_sets.size());
	std::vector<int> prev_vertices;
	for (int i = 0; i < adjacency_sets.size(); ++i)
	{
		if (vertex == i)
		{
			continue;
		}
		if (adjacency_sets[i].count(vertex) > 0)
		{
			prev_vertices.push_back(i);
		}
	}
	return prev_vertices;
}
