## Coding Challenge Engine
Simple framework to develop and debug coding challenge solutions.

This project aims to help the development of solutions for challenge websites like  
[CodinGame](https://www.codingame.com)  
[HackerRank](https://www.hackerrank.com)  

Currently it supports only C++, but Python is coming soon. Feel free to request any other language support. :)

### Features
- [x] Check solution code against test cases
- [x] Report results
- [ ] Time limit for solution
- [x] Select test/tests to run
- [ ] Rerun test case/cases for a given number of times
- [ ] DebugPrint that does not affect the solution output
- [ ] Unit test the solution code (Google Test?)
- [ ] [#1](https://github.com/mandyedi/coding-challenge-engine/issues/1 "Solution cocde generation") Automate solution code generation (do not have to edit solution class by hand, a script generates the final version that can be submitted)

### Engine usage
 1. Add test files to tests folder (e.g. src-cpp/tests).
 2. Add your solution in to Solution::SolutionSourceCode().
 3. Build and run the project and see the output.

### Test file
You can add multiple test files to tests folder.  
You can run all the tests by calling **Runner::InitWithAll()**.
```cpp
TestRunner Runner;
Runner.InitWithAll();
Runner.RunTests();
Runner.EvaluateSolution();
```
Or you can run one or multiple test files by calling **Runner::InitWithFileNames( { "test0.txt" } )**.
```cpp
TestRunner Runner;
Runner.InitWithFileNames( { "test0.txt", "test1.txt" } );
Runner.RunTests();
Runner.EvaluateSolution();
```
The test runner only reads two sections:
 - Between TEST_START and TEST_END.
 - Between SOLUTION_START and SOLUTION_END.

### Data input and output
The engine is communicating via stdin and stdout.
In Solution::SolutionSourceCode() stdin an stdout are redirected so its behavior is equivalent to most of the challenge websites.

### Test file structure:  
```
You can add comments here or to any other part that is outside the sections.

Input data:
1st line: 1 positive integer n
n lines of integers

Output data (the solution):
n lines with the input data multiplied with 2

TEST_START
4
2
-3
0
9
TEST_END

SOLUTION_START
4
-6
0
18
SOLUTION_END
```
