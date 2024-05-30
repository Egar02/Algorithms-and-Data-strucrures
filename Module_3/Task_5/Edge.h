#pragma once
struct Edge
{
	Edge() :
		from(0),
		to(0),
		weight(0) {}

	Edge(int from, int to, double weight) :
		from(from),
		to(to),
		weight(weight) {}

	int from;
	int to;
	double weight;
};

class EdgeComparator
{
public:
	EdgeComparator() {}

	bool operator()(Edge& left_edge, Edge& right_edge)
	{
		return left_edge.weight > right_edge.weight;
	}
};
