#pragma once

#include <vector>
#include <set>
#include <filesystem>
#include <chrono>
#include <utility>

class Solution;

class SolutionRunner
{
public:
	SolutionRunner();
	SolutionRunner( const std::filesystem::path &testFolderPath );
	virtual ~SolutionRunner();

	void InitWithAll();
	void InitWithFileNames( const std::set<std::string> &fileNames );

	void RunTests( Solution *solution );
	void EvaluateSolution();

	void AddTimePoint( const std::string &name );

private:
	void ReadTestFiles();

	unsigned int ActiveTestIndex;

	std::filesystem::path TestFolderPath;

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
		std::vector< std::pair<std::string, std::chrono::steady_clock::time_point> > TimePoints;

		bool CheckSolution();
		void PrintTestSolution();
		void PrintSolution();
	};

	std::vector<Test> Tests;
};

inline void SolutionRunner::AddTimePoint( const std::string &name )
{
	Tests[ActiveTestIndex].TimePoints.push_back( { name, std::chrono::steady_clock::now() } );
}