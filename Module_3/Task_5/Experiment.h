#pragma once
#include "ExactSolution.h"
#include "ApproximateSolution.h"
#include "NPoints.h"
#include "ListGraph.h"
#include <array>
#include <cmath>

class Experiment
{
public:
	Experiment(int n_vertices, int n_experiments);

	std::pair<double, double> GetResult();
private:
	std::array<double, 10> approximation_factors;

	double Mean();

	double StandardDeviation();
};