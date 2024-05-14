#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <queue>
#include <deque>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"

void BFS(const IGraph& graph, int vertex, std::vector<bool>& visited, const std::function<void(int)>& func)
{
    std::queue<int> queue;
    queue.push(vertex);
    visited[vertex] = true;

    while (!queue.empty())
    {
        int currentVertex = queue.front();
        queue.pop();

        func(currentVertex);

        for (int nextVertex : graph.GetNextVertices(currentVertex))
        {
            if (!visited[nextVertex])
            {
                visited[nextVertex] = true;
                queue.push(nextVertex);
            }
        }
    }
}

void MainBFS(const IGraph& graph, const std::function<void(int)>& func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            BFS(graph, i, visited, func);
        }
    }
}

void DFS(const IGraph& graph, int vertex, std::vector<bool>& visited, const std::function<void(int)>& func)
{
    visited[vertex] = true;
    func(vertex);

    for (int nextVertex : graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            DFS(graph, nextVertex, visited, func);
        }
    }
}

void MainDFS(const IGraph& graph, const std::function<void(int)>& func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            DFS(graph, i, visited, func);
        }
    }
}

void TopologicalSortInternal(const IGraph& graph, int vertex, std::vector<bool>& visited, std::deque<int>& sorted)
{
    visited[vertex] = true;

    for (int nextVertex : graph.GetNextVertices(vertex))
    {
        if (!visited[nextVertex])
        {
            TopologicalSortInternal(graph, nextVertex, visited, sorted);
        }
    }

    sorted.push_front(vertex);
}

std::deque<int> TopologicalSort(const IGraph& graph)
{
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        if (!visited[i])
        {
            TopologicalSortInternal(graph, i, visited, sorted);
        }
    }

    return sorted;
}

void GraphDemo(const IGraph& graph)
{
    std::cout << "BFS: ";
    MainBFS(graph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "DFS: ";
    MainDFS(graph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << "Topological search: ";
    for (int vertex : TopologicalSort(graph))
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl << std::endl;
}

int main(int argc, const char* argv[]) {
    ListGraph graph(7);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 5);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 5);
    graph.AddEdge(1, 6);
    graph.AddEdge(3, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 6);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 4);
 
    ListGraph list_graph(graph);
    MatrixGraph matrix_graph(list_graph);
    ArcGraph arc_graph(matrix_graph);
    SetGraph set_graph(arc_graph);

    std::cout << "List Graph:\n";
    GraphDemo(list_graph);

    std::cout << "Matrix Graph:\n";
    GraphDemo(matrix_graph);

    std::cout << "Set Graph:\n";
    GraphDemo(set_graph);

    std::cout << "Arc Graph:\n";
    GraphDemo(arc_graph);

    return 0;
}