#include "Experiment.h"

Experiment::Experiment(int n_vertices, int n_experiments)
{
	for (int i = 0; i < n_experiments; ++i)
	{
		NPoints desk(n_vertices);
		ListGraph full_graph = desk.CreateGraph();
		approximation_factors[i] = ApproximateSolution(full_graph) / ExactSolution(full_graph);
	}	
}

std::pair<double, double> Experiment::GetResult()
{
	return { Mean(), StandardDeviation() };
}

double Experiment::Mean()
{
	double sum = 0.0;
	for (int i = 0; i < approximation_factors.size(); ++i)
	{
		sum += approximation_factors[i];
	}
	return sum / approximation_factors.size();
}

double Experiment::StandardDeviation()
{
	double dispersion = 0.0;
	for (int i = 0; i < approximation_factors.size(); ++i)
	{
		dispersion += (approximation_factors[i] - Mean()) * (approximation_factors[i] - Mean());
	}
	dispersion /= approximation_factors.size();
	return std::sqrt(dispersion);
}
