#pragma once

class SolutionRunner;

class Solution
{
public:
	Solution(SolutionRunner *context );
	virtual ~Solution();

	void SolutionSourceCode();

private:
	SolutionRunner *Context;

};

