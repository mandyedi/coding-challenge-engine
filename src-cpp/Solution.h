#pragma once

class TestRunner;

class Solution
{
public:
	Solution( TestRunner *context );
	virtual ~Solution();

	void SolutionSourceCode();

private:
	TestRunner *Context;

};

