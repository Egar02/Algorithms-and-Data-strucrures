#pragma once
#include "ListGraph.h"
#include "Edge.h"
#include "DSU.h"

std::queue<Edge> SortEdges(IGraph& graph);

ListGraph BuildMST(IGraph& graph);

void BFS(const IGraph& graph, int vertex, std::vector<bool>& visited, std::vector<int>& path);

std::vector<int> MainBFS(const IGraph& graph);

double ApproximateSolution(ListGraph& full_graph);