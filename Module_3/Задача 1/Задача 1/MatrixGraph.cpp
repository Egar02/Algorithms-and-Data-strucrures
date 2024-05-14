#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int size) : adjacency_matrix(size, std::vector<int>(size, 0))
{
}

MatrixGraph::MatrixGraph(const IGraph& graph)
{
	std::vector<std::vector<int>> matrix(graph.VerticesCount(), std::vector<int>(graph.VerticesCount(), 0));
	for (int i = 0; i < graph.VerticesCount(); ++i)
	{
		for (int vertex : graph.GetNextVertices(i))
		{
			matrix[i][vertex]++;
		}
	}
	adjacency_matrix = matrix;
}

MatrixGraph::~MatrixGraph()
{
}

void MatrixGraph::AddEdge(int from, int to)
{
	assert(0 <= from && from < adjacency_matrix.size());
	assert(0 <= to && to < adjacency_matrix.size());
	adjacency_matrix[from][to]++;
}

int MatrixGraph::VerticesCount() const
{
	return (int)adjacency_matrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
{
	assert(0 <= vertex && vertex < adjacency_matrix.size());
	std::vector<int> next_vertices;
	for (int i = 0; i < adjacency_matrix.size(); ++i)
	{
		if (adjacency_matrix[vertex][i] > 0 && i != vertex)
		{
			next_vertices.push_back(i);
		}
	}
	return next_vertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
{
	assert(0 <= vertex && vertex < adjacency_matrix.size());
	std::vector<int> prev_vertices;
	for (int i = 0; i < adjacency_matrix.size(); ++i)
	{
		if (adjacency_matrix[i][vertex] > 0 && i != vertex)
		{
			prev_vertices.push_back(i);
		}
	}
	return prev_vertices;
}
