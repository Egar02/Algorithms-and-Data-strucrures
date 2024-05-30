#include "ApproximateSolution.h"

std::queue<Edge> SortEdges(IGraph& graph)
{
    std::queue<Edge> sorted_edges;
    std::priority_queue<Edge, std::vector<Edge>, EdgeComparator> min_heap;
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        for (std::pair<int, double> edge : graph.GetNextVertices(i))
        {
            {
                min_heap.push(Edge(i, edge.first, edge.second));
            }
        }
    }
    while (!min_heap.empty())
    {
        sorted_edges.push(min_heap.top());
        min_heap.pop();
    }
    return sorted_edges;
}

ListGraph BuildMST(IGraph& graph)
{
	std::queue<Edge> sorted_edges = SortEdges(graph);
	DSU dsu(graph.VerticesCount());
	ListGraph MST(graph.VerticesCount());
	while (!sorted_edges.empty())
	{
		Edge top_edge = sorted_edges.front();
		sorted_edges.pop();

		if (dsu.union_set(top_edge.from, top_edge.to))
		{
			MST.AddEdge(top_edge.from, top_edge.to, top_edge.weight);
			MST.AddEdge(top_edge.to, top_edge.from, top_edge.weight);
		}
	}
	return MST;
}

void BFS(const IGraph& graph, int vertex, std::vector<bool>& visited, std::vector<int>& path)
{
    std::queue<int> queue;
    queue.push(vertex);
    visited[vertex] = true;

    while (!queue.empty())
    {
        int currentVertex = queue.front();
        queue.pop();

        path.push_back(currentVertex);

        for (auto nextVertex : graph.GetNextVertices(currentVertex))
        {
            if (!visited[nextVertex.first])
            {
                visited[nextVertex.first] = true;
                queue.push(nextVertex.first);
            }
        }
    }
}

std::vector<int> MainBFS(const IGraph& graph)
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::vector<int> path;

    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            BFS(graph, i, visited, path);
        }
    }
    return path;
}

double ApproximateSolution(ListGraph& full_graph)
{
    ListGraph mst = BuildMST(full_graph);
    std::vector<int> approximate_path = MainBFS(mst);
    approximate_path.push_back(0);
    double length = 0.0;
    for (int i = 0; i < approximate_path.size() - 1; ++i)
    {
        length += full_graph.GetWeight(approximate_path[i], approximate_path[i + 1]);
    }
	return length;
}
