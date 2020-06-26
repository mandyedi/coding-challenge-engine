// coding-challenge-engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TestRunner.h"

int main(int argc, char **argv)
{
    TestRunner Runner;
    Runner.RunTests();
    Runner.EvaluateSolution();
    Runner.Reset();

    return 0;
}


