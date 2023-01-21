#pragma once
#include "Solution.h"

class TutorialSolution : public Solution
{
public:
	TutorialSolution(SolutionRunner *context);
	~TutorialSolution();

	void SolutionSourceCode() override;
};

