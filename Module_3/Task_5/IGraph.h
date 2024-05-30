#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <queue>
#include <deque>

struct IGraph
{
	virtual ~IGraph()
	{
	}

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to, double weight) = 0;

	virtual int VerticesCount() const = 0;

	virtual std::vector<std::pair<int, double>> GetNextVertices(int vertex) const = 0;
	virtual std::vector<std::pair<int, double>> GetPrevVertices(int vertex) const = 0;

};
