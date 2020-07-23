// coding-challenge-engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TestRunner.h"

int main(int argc, char **argv)
{
    TestRunner Runner( "tests" );
    //Runner.InitWithAll();
    Runner.InitWithFileNames( {
          "test0.txt"
        , "test1.txt"
        //, "test2.txt"
        //, "test3.txt"
        //, "test4.txt"
        //, "test5.txt"
    } );
    Runner.RunTests();
    Runner.EvaluateSolution();

    return 0;
}


