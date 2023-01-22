#include <iostream>
#include "TutorialSolution.h"
#include "SolutionRunner.h"

TutorialSolution::~TutorialSolution() {}

void TutorialSolution::SolutionSourceCode( SolutionRunner *runner )
{
	int n = 0;
	std::cin >> n;

	runner->AddTimePoint("User Defined");

	for (int i = 0; i < n; i++)
	{
		int x = 0;
		std::cin >> x;
		std::cout << x * 2 << "\n";
	}
}