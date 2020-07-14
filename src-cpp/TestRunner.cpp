#include <iostream>
#include <streambuf>
#include <fstream>
#include <string>
#include <sstream>
#include "TestRunner.h"
#include "Solution.h"

TestRunner::TestRunner()
	: CinBackup( nullptr )
	, CoutBackup( nullptr )
{
}

TestRunner::~TestRunner()
{
}

void TestRunner::InitWithAll()
{
	TestFileDirectoryEntries.clear();
	for ( auto it : std::filesystem::directory_iterator( "tests" ) )
	{
		TestFileDirectoryEntries.push_back( it );
	}

	ReadTestFiles();
}

void TestRunner::InitWithFileNames( const std::set<std::string> &fileNames )
{
	TestFileDirectoryEntries.clear();
	for ( auto it : std::filesystem::directory_iterator( "tests" ) )
	{
		if ( fileNames.find( it.path().filename().string() ) != fileNames.end() )
		{
			TestFileDirectoryEntries.push_back( it );
		}
	}

	ReadTestFiles();
}

void TestRunner::RunTests()
{
	CinBackup = std::cin.rdbuf();
	CoutBackup = std::cout.rdbuf();

	Solution solution;

	for ( auto &test : Tests )
	{
		// Send test inputs to cin
		std::stringstream cinStream;
		for ( auto &testInput : test.TestInput )
		{
			cinStream << testInput << "\n";
		}

		std::cin.rdbuf( cinStream.rdbuf() );

		// Run solution
		std::stringstream coutStream;
		std::cout.rdbuf( coutStream.rdbuf() );
		solution.SolutionSourceCode();

		// Send solution from cout to Test
		std::string line;
		while ( std::getline( coutStream, line ) )
		{
			test.Solution.push_back( line );
		}
	}

	EvaluateSolution();

	std::cin.rdbuf( CinBackup );
	std::cout.rdbuf( CoutBackup );
}

void TestRunner::EvaluateSolution()
{
	for ( auto &test : Tests )
	{
		bool success = test.CheckSolution();

		std::cout << test.Name << " solution " << ( success ? "Success\n" : "Wrong Answer\n" );
		
		if ( success == false )
		{
			std::cout << "Your output:\n";
			test.PrintSolution();
			std::cout << "Expected output:\n";
			test.PrintTestSolution();
		}
	}
}

void TestRunner::ReadTestFiles()
{
	Tests.clear();

	enum class TestFileStatus
	{
		Comment,
		TestData,
		SolutionData
	};

	for ( auto &entry : TestFileDirectoryEntries )
	{
		std::ifstream fileStream( entry.path() );
		if ( fileStream )
		{
			Test test;
			test.Name = entry.path().filename().string();
			TestFileStatus fileStatus = TestFileStatus::Comment;
			std::string line;
			while ( std::getline( fileStream, line ) )
			{
				if ( line.compare( "TEST_START" ) == 0 )
				{
					fileStatus = TestFileStatus::TestData;
					continue;
				}
				else if ( line.compare( "TEST_END" ) == 0 )
				{
					fileStatus = TestFileStatus::Comment;
					continue;
				}
				else if ( line.compare( "SOLUTION_START" ) == 0 )
				{
					fileStatus = TestFileStatus::SolutionData;
					continue;
				}
				else if ( line.compare( "SOLUTION_END" ) == 0 )
				{
					fileStatus = TestFileStatus::Comment;
					continue;
				}

				switch ( fileStatus )
				{
					case TestFileStatus::TestData:
						test.TestInput.push_back( line );
						break;
					case TestFileStatus::SolutionData:
						test.TestSolution.push_back( line );
						break;
					case TestFileStatus::Comment:
					default:
						break;
				}
			}
			Tests.push_back( test );

			fileStream.close();
		}
	}
}

bool TestRunner::Test::CheckSolution()
{
	size_t sizeTestSolution = TestSolution.size();
	size_t sizeSolution = Solution.size();

	if ( sizeTestSolution != sizeSolution )
	{
		return false;
	}
	
	for ( size_t i = 0; i < sizeSolution; i++ )
	{
		if ( TestSolution[i] != Solution[i] )
		{
			return false;
		}
	}

	return true;
}

void TestRunner::Test::PrintTestSolution()
{
	for ( auto &solution : TestSolution )
	{
		std::cout << solution << "\n";
	}
}

void TestRunner::Test::PrintSolution()
{
	for ( auto &solution : Solution )
	{
		std::cout << solution << "\n";
	}
}
