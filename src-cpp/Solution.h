#pragma once

class  SolutionRunner;

class Solution
{
public:
	virtual ~Solution();

	virtual void SolutionSourceCode( SolutionRunner *runner ) = 0;
};

