#include <iostream>
#include "NPoints.h"
#include "ApproximateSolution.h"
#include "ExactSolution.h"
#include "Experiment.h"
#define N_EXPERIMENTS 10

int main()
{
	std::cout << "	EXAMPLE FROM LECTURE AND SEMINAR:\n\n";
	NPoints desk(-1);
	ListGraph full_graph = desk.CreateGraph();
	std::cout << "Exact Solution: " << ExactSolution(full_graph) << std::endl;
	std::cout << "Approximate Solution: " << ApproximateSolution(full_graph) << "\n\n\n";

	std::cout << "		EXPERIMENT\n\n";
	std::cout << "Interval of N: [3, 10]\n";
	std::cout << "Number of Experiments for Each N: " << N_EXPERIMENTS << "\n\n\n";

	for (int i = 3; i <= 10; ++i)
	{
		Experiment experiment(i, N_EXPERIMENTS);
		std::pair<double, double> result = experiment.GetResult();
		std::cout << "		N vertices = " << i << ":\n\n";
		std::cout << "Approximation Factor Mean: " << result.first << std::endl;
		std::cout << "Approximation Factor Standard Deviation: " << result.second << std::endl << std::endl;
	}
}
