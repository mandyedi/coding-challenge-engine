#pragma once

class SolutionRunner;

class Solution
{
public:
	Solution(SolutionRunner *context );
	virtual ~Solution();

	virtual void SolutionSourceCode() = 0;

protected:
	SolutionRunner *Context;

};

