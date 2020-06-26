#pragma once

#include <vector>

class TestRunner
{
public:
	TestRunner();
	virtual ~TestRunner();

	void RunTests();
	void EvaluateSolution();
	void Reset();

private:
	void Init();
	void ReadTestFiles();

	std::streambuf *CinBackup;
	std::streambuf *CoutBackup;

	struct Test
	{
		std::string Name;
		std::vector<std::string> TestInput;
		std::vector<std::string> TestSolution;
		std::vector<std::string> Solution;

		bool CheckSolution();
		void PrintTestSolution();
		void PrintSolution();
	};

	std::vector<Test> Tests;
};

