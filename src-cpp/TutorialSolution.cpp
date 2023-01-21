#include <iostream>
#include "TutorialSolution.h"
#include "SolutionRunner.h"

TutorialSolution::TutorialSolution(SolutionRunner *context)
	: Solution(context)
{}

TutorialSolution::~TutorialSolution() {}

void TutorialSolution::SolutionSourceCode()
{
	int n = 0;
	std::cin >> n;

	Context->AddTimePoint("User Defined");

	for (int i = 0; i < n; i++)
	{
		int x = 0;
		std::cin >> x;
		std::cout << x * 2 << "\n";
	}
}