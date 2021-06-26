#include <iostream>
#include "Solution.h"
#include "SolutionRunner.h"

Solution::Solution(SolutionRunner *context )
	: Context(context)
{}

Solution::~Solution(){}

void Solution::SolutionSourceCode()
{
	int n = 0;
	std::cin >> n;

	Context->AddTimePoint( "User Defined" );

	for ( int i = 0; i < n; i++ )
	{
		int x = 0;
		std::cin >> x;
		std::cout << x * 2 << "\n";
	}
}