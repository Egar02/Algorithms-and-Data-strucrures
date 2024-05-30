#pragma once

#include "IGraph.h"

struct ListGraph: public IGraph
{
public:

	ListGraph(int size);

	ListGraph(const IGraph& graph);

	~ListGraph();

	void AddEdge(int from, int to, double weight) override;

	int VerticesCount() const override;

	std::vector<std::pair<int, double>> GetNextVertices(int vertex) const override;

	std::vector<std::pair<int, double>> GetPrevVertices(int vertex) const override;

	float GetWeight(int from, int to);
	
private:

	std::vector<std::vector<std::pair<int, double>>> adjacency_lists;
};