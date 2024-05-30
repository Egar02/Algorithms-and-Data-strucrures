#pragma once
#include <vector>
#include "ListGraph.h"
#include <random>
#include <cmath>
#include <ctime>
#include <cstdlib>
class NPoints
{
public:
	NPoints(int n);
	ListGraph CreateGraph();

private:
	std::vector<std::pair<double, double>> points;
	std::pair<double, double> GeneratePoint();
	float Distance(std::pair<double, double> point_1, std::pair<double, double> point_2);
};
