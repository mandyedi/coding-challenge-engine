// coding-challenge-engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SolutionRunner.h"

int main(int argc, char **argv)
{
    SolutionRunner Runner( "test-cases" );
    //Runner.InitWithAll();
    Runner.InitWithFileNames( {
          "test-case-0.txt"
        , "test-case-1.txt"
        //, "test-case-2.txt"
        //, "test-case-3.txt"
        //, "test-case-4.txt"
        //, "test-case-5.txt"
    } );
    Runner.RunTests();
    Runner.EvaluateSolution();

    return 0;
}


