#pragma once

#include <vector>
#include <set>
#include <filesystem>

class TestRunner
{
public:
	TestRunner();
	virtual ~TestRunner();

	void InitWithAll();
	void InitWithFileNames( const std::set<std::string> &fileNames );

	void RunTests();
	void EvaluateSolution();

private:
	void ReadTestFiles();

	std::streambuf *CinBackup;
	std::streambuf *CoutBackup;

	std::set<std::string> TestFileNames;

	std::vector<std::filesystem::directory_entry> TestFileDirectoryEntries;

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

