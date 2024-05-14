#include "ListGraph.h"

ListGraph::ListGraph(int size) : adjacency_lists(size)
{
}

ListGraph::ListGraph(const IGraph& graph)
{
    std::vector<std::vector<int>> lists(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        lists[i] = graph.GetNextVertices(i);
    }
    adjacency_lists = lists;
}

ListGraph::~ListGraph()
{
}

void ListGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < adjacency_lists.size());
    assert(0 <= to && to < adjacency_lists.size());
    adjacency_lists[from].push_back(to);
}

int ListGraph::VerticesCount() const
{
    return (int)adjacency_lists.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacency_lists.size());
    return adjacency_lists[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacency_lists.size());
    std::vector<int> prev_vertices;

    for (int from = 0; from < adjacency_lists.size(); ++from)
    {
        for (int to : adjacency_lists[from])
        {
            if (to == vertex)
                prev_vertices.push_back(from);
        }
    }
    return prev_vertices;
}


