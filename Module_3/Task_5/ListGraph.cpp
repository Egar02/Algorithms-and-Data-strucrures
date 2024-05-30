#include "ListGraph.h"

ListGraph::ListGraph(int size) : adjacency_lists(size)
{
}

ListGraph::ListGraph(const IGraph& graph)
{
    std::vector<std::vector<std::pair<int, double>>> lists(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        lists[i] = graph.GetNextVertices(i);
    }
    adjacency_lists = lists;
}

ListGraph::~ListGraph()
{
}

void ListGraph::AddEdge(int from, int to, double weight)
{
    assert(0 <= from && from < VerticesCount());
    assert(0 <= to && to < VerticesCount());
    assert(weight >= 0);

    adjacency_lists[from].push_back({ to, weight });
}

int ListGraph::VerticesCount() const
{
    return (int)adjacency_lists.size();
}

std::vector<std::pair<int, double>> ListGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacency_lists.size());
    return adjacency_lists[vertex];
}


std::vector<std::pair<int, double>> ListGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacency_lists.size());
    std::vector<std::pair<int, double>> prev_vertices;

    for (int from = 0; from < adjacency_lists.size(); ++from)
    {
        for (std::pair<int, int> edge : adjacency_lists[from])
        {
            if (edge.second == vertex)
                prev_vertices.push_back(edge);
        }
    }
    return prev_vertices;
}

float ListGraph::GetWeight(int from, int to)
{
    for (auto edge : GetNextVertices(from))
    {
        if (edge.first == to)
        {
            return edge.second;
        }
    }
    for (auto edge : GetNextVertices(to))
    {
        if (edge.first == from)
        {
            return edge.second;
        }
    }
}


