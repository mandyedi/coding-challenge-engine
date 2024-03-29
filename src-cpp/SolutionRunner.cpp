#include <iostream>
#include <streambuf>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include "SolutionRunner.h"
#include "Solution.h"

// TODO: this should be not allowed, class can't be instanced with an undetermined state
SolutionRunner::SolutionRunner()
	: ActiveTestIndex( 0 )
	, TestFolderPath( "test-cases" )
	, CinBackup( nullptr )
	, CoutBackup( nullptr )
{
}

SolutionRunner::SolutionRunner( const std::filesystem::path &testFolderPath )
	: ActiveTestIndex( 0 )
	, TestFolderPath( testFolderPath )
	, CinBackup( nullptr )
	, CoutBackup( nullptr )
{
}

SolutionRunner::~SolutionRunner()
{
}

void SolutionRunner::InitWithAll()
{
	TestFileDirectoryEntries.clear();
	for ( auto &it : std::filesystem::directory_iterator( TestFolderPath ) )
	{
		TestFileDirectoryEntries.push_back( it );
	}

	ReadTestFiles();
}

void SolutionRunner::InitWithFileNames( const std::set<std::string> &fileNames )
{
	TestFileDirectoryEntries.clear();
	for ( auto &it : std::filesystem::directory_iterator( TestFolderPath ) )
	{
		if ( fileNames.find( it.path().filename().string() ) != fileNames.end() )
		{
			TestFileDirectoryEntries.push_back( it );
		}
	}

	ReadTestFiles();
}

void SolutionRunner::RunTests( Solution *solution )
{
	CinBackup = std::cin.rdbuf();
	CoutBackup = std::cout.rdbuf();

	for ( unsigned int i = 0; i < Tests.size(); i++ )
	{
		ActiveTestIndex = i;
		auto &test = Tests[i];

		std::stringstream cinStream;
		for ( auto &testInput : test.TestInput )
		{
			cinStream << testInput << "\n";
		}

		std::cin.rdbuf( cinStream.rdbuf() );

		std::stringstream coutStream;
		std::cout.rdbuf( coutStream.rdbuf() );

		AddTimePoint( "Start" );

		solution->SolutionSourceCode( this );

		AddTimePoint( "End" );

		std::string line;
		while ( std::getline( coutStream, line ) )
		{
			test.Solution.push_back( line );
		}
	}

	std::cin.rdbuf( CinBackup );
	std::cout.rdbuf( CoutBackup );
}

void SolutionRunner::EvaluateSolution()
{
	for ( auto &test : Tests )
	{
		bool success = test.CheckSolution();

		std::cout << test.Name << " solution " << (success ? "Success\n" : "Wrong Answer\n");

		if ( success == false )
		{
			std::cout << "Your output:\n";
			test.PrintSolution();
			std::cout << "Expected output:\n";
			test.PrintTestSolution();
		}

		if ( test.TimePoints.size() >= 2 )
		{
			std::cout << "Time measurements:\n";
			std::cout << std::setw( 42 ) << std::right << "Absolute Time"
				<< std::setw( 19 ) << std::right << "Relateive Time\n";

			auto start = test.TimePoints[0].second;
			long long prev = 0;
			for ( auto &timePoint : test.TimePoints )
			{
				long long elapsedNano = std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint.second - start).count();
				double elapsedSec = static_cast<double>(elapsedNano) * 0.000000001;
				double elapsedSecRelative = static_cast<double>(elapsedNano - prev) * 0.000000001;

				std::cout << std::fixed
					<< std::setw( 24 ) << std::left << timePoint.first
					<< std::setw( 16 ) << std::right << elapsedSec << " s"
					<< std::setw( 16 ) << std::right << elapsedSecRelative << " s\n";

				prev = elapsedNano;
			}
		}
	}
}

void SolutionRunner::ReadTestFiles()
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

bool SolutionRunner::Test::CheckSolution()
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

void SolutionRunner::Test::PrintTestSolution()
{
	for ( auto &solution : TestSolution )
	{
		std::cout << solution << "\n";
	}
}

void SolutionRunner::Test::PrintSolution()
{
	for ( auto &solution : Solution )
	{
		std::cout << solution << "\n";
	}
}
