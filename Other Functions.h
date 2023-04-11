#pragma once
#include "Matrix.h"
#include <fstream>

void initSystemOfEquations(Matrix& A, Matrix& b);
void printSystemofEquations(Matrix& A, Matrix& b);
void solveSystemOfEquations0(Matrix A, Matrix b, Matrix& x);
void solveSystemOfEquations1(Matrix A, Matrix b, Matrix& x);
void saveSystemToFile(Matrix& A, Matrix& b, std::string file = "data.txt");
void loadSystemFromFile(Matrix& A, Matrix& b, std::string file = "data.txt");
void checkRoots(Matrix& A, Matrix& b, Matrix& x);
void printRoots(Matrix& x);
