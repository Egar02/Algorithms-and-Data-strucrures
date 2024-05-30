#include "NPoints.h"

NPoints::NPoints(int n)
{
	if (n < 0) //Example from lecture and seminar - for debugging
	{
		points.push_back({ 1, 4 });
		points.push_back({ 1, 2 });
		points.push_back({ 0, 1 });
		points.push_back({ 3, 4 });
		points.push_back({ 4, 3 });
		points.push_back({ 3, 2 });
		points.push_back({ 5, 2 });
		points.push_back({ 2, 0 });
	}
	else
	{
		for (int i = 0; i < n; ++i)
		{
			points.push_back(GeneratePoint());
		}
	}
}

ListGraph NPoints::CreateGraph()
{
	ListGraph full_graph(points.size());
	for (int i = 0; i < points.size() - 1; ++i)
	{
		for (int j = i + 1; j < points.size(); ++j)
		{
			full_graph.AddEdge(i, j, Distance(points[i], points[j]));
		}
	}
    return full_graph;
}

std::pair<double, double> NPoints::GeneratePoint()
{
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_real_distribution<double> dist(-1.0, 1.0);

	double x = 0.0;
	double y = 0.0;
	while (true)
	{
		double u = dist(generator);
		double v = dist(generator);
		double s = u * u + v * v;
		if (s <= 1 && s > 0)
		{
			x = u * std::sqrt(-2 * std::log(s) / s);
			y = v * std::sqrt(-2 * std::log(s) / s);
			break;
		}
	}
	return { x, y };
}

float NPoints::Distance(std::pair<double, double> point_1, std::pair<double, double> point_2)
{
	return std::sqrt((point_1.first - point_2.first) * (point_1.first - point_2.first) + (point_1.second - point_2.second) * (point_1.second - point_2.second));
}
