#include "Matrix.h"

Matrix::Matrix(const int _rows, const int _colomns)
{
	rows = _rows;
	colomns = _colomns;

	matrix = new double* [rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new double[colomns] { 0 };
	}
}

Matrix::Matrix(const Matrix& other)
{
	this->rows = other.rows;
	this->colomns = other.colomns;

	this->matrix = new double* [this->rows];
	for (int i = 0; i < this->rows; i++)
	{
		this->matrix[i] = new double[this->colomns];
		for (int j = 0; j < this->colomns; j++)
		{
			this->matrix[i][j] = other.matrix[i][j];
		}
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;
}

Matrix Matrix::operator+ (const Matrix& other)
{
	Matrix result(this->rows, this->colomns);

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->colomns; j++)
		{
			result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
		}
	}

	return result;
}

template <class Type> requires requires(Type t) { t * 1.; }
Matrix Matrix::operator* (const Type coefficient)
{
	Matrix result(this->rows, this->colomns);

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->colomns; j++)
		{
			result.matrix[i][j] = this->matrix[i][j] * coefficient;
		}
	}

	return result;
}

Matrix Matrix::operator- (Matrix B)
{
	return *this + B * -1;
}

Matrix Matrix::operator* (Matrix& other)
{
	Matrix result(this->rows, other.colomns);

	for (int i = 0; i < result.rows; i++)
	{
		for (int j = 0; j < result.colomns; j++)
		{
			result[i][j] = 0;
			for (int i1 = 0; i1 < this->colomns; i1++)
			{
				result[i][j] += this->matrix[i][i1] * other[i1][j];
			}
		}
	}
	return result;
}

Matrix& Matrix::operator= (const Matrix& other)
{
	if (this == &other)
		return *this;

	if (this->matrix)
	{
		for (int i = 0; i < this->rows; i++)
			delete[] matrix[i];
		delete[] matrix;
	}

	this->rows = other.rows;
	this->colomns = other.colomns;

	this->matrix = new double* [this->rows];
	for (int i = 0; i < this->rows; i++)
	{
		this->matrix[i] = new double[this->colomns];
		for (int j = 0; j < this->colomns; j++)
		{
			this->matrix[i][j] = other.matrix[i][j];
		}
	}

	return *this;
}

Matrix Matrix::transposition()
{
	Matrix result(this->colomns, this->rows);

	for (int i = 0; i < result.rows; i++)
	{
		for (int j = 0; j < result.colomns; j++)
		{
			result[i][j] = this->matrix[j][i];
		}
	}

	return result;
}

double* Matrix::operator[] (const int index)
{
	return matrix[index];
}

int Matrix::getRows()
{
	return rows;
}

int Matrix::getColomns()
{
	return colomns;
}

void Matrix::swapRows(const int i, const int j)
{
	double* tmp = matrix[i];
	matrix[i] = matrix[j];
	matrix[j] = tmp;
}

void Matrix::swapColomns(const int i, const int j)
{
	for (int k = 0; k < rows; k++)
	{
		std::swap(matrix[k][i], matrix[k][j]);
	}
}

void Matrix::print()
{
	std::cout << "Matrix: " << std::endl;
	for (int i = 0; i < std::min(rows, 10); i++)
	{
		for (int j = 0; j < std::min(colomns, 10); j++)
			std::cout << matrix[i][j] << "\t";

		if (colomns > 10) std::cout << "...\t";
		std::cout << std::endl;
	}
	if (rows > 10) std::cout << "...\t" << std::endl;
	std::cout << std::endl;
};
