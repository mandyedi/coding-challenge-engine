#pragma once
#include "Solution.h"

class SolutionRunner;

class TutorialSolution : public Solution
{
public:
	~TutorialSolution();

	void SolutionSourceCode( SolutionRunner *runner ) override;
};

