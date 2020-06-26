#include <iostream>
#include "Solution.h"

Solution::Solution(){}

Solution::~Solution(){}

void Solution::SolutionSourceCode()
{
	int n = 0;
	std::cin >> n;
	for ( int i = 0; i < n; i++ )
	{
		int x = 0;
		std::cin >> x;
		std::cout << x * 2 << "\n";
	}
}