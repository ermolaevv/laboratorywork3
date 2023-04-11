#pragma once
#include <cassert>
#include <iostream>

class Matrix
{
private:
	double** matrix;
	int rows, colomns;
public:
	Matrix(const int _rows = 1, const int _colomns = 1);
	Matrix(const Matrix& other);
	~Matrix();

	template <class Type> requires requires(Type t) { t * 1.; }
	Matrix operator* (const Type coefficient);

	Matrix operator+ (const Matrix& other);
	Matrix operator- (Matrix B);
	Matrix operator* (Matrix& other);
	Matrix& operator= (const Matrix& other);
	double* operator[] (const int index);

	Matrix transposition();
	int getRows();
	int getColomns();
	void swapRows(const int i, const int j);
	void swapColomns(const int i, const int j);
	void print();
};
