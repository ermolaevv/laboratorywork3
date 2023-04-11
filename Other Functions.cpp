#include "Other Functions.h"

void initSystemOfEquations(Matrix& A, Matrix& b)
{
	int N, M;

	std::cout << "Number of equations: ";
	std::cin >> N;
	std::cout << "Number of variables: ";
	std::cin >> M;
	std::cout << std::endl;

	A = Matrix(N, M);
	b = Matrix(N);


	if (A.getRows() <= 4 && A.getColomns() <= 5)
	{
		for (int i = 0; i < A.getRows(); i++)
		{
			std::cout << "Enter a row " << i + 1 << " of the matrix A: ";
			for (int j = 0; j < A.getColomns(); j++)
				std::cin >> A[i][j];
			std::cout << "Enter a b" << i + 1 << ": ";
			std::cin >> b[i][0];
		}
		std::cout << std::endl;
	}
	else
		for (int i = 0; i < A.getRows(); i++)
		{
			for (int j = 0; j < A.getColomns(); j++)
				A[i][j] = rand();
			b[i][0] = rand();
		}
}

void printSystemofEquations(Matrix& A, Matrix& b)
{
	for (int i = 0; i < std::min(A.getRows(), 10); i++)
	{
		if (i == 9 && A.getRows() > 10)
		{
			std::cout << "..." << std::endl;
			i++;
			
		}
		for (int j = 0; j < std::min(A.getColomns(), 10); j++)
		{
			std::cout << A[i][j] << "x";
			if (j != 0) 
				std::cout << "^" << j + 1;
			std::cout << " ";
			if (j != A.getColomns() - 1) 
				std::cout << "+ ";
			if (j == 9 && A.getColomns() > 10)
				std::cout << "... + " << A[i][A.getColomns()-1] << "x^" << A.getColomns() << " ";
		}
		std::cout << "= " << b[i][0] << std::endl;
	}
}

void solveSystemOfEquations0(Matrix A, Matrix b, Matrix& x)
{
	double sum;

	for (int j = 0; j < A.getColomns(); j++)
	{
		for (int i = j + 1; i < A.getRows(); i++)
		{
			double coefficient = A[i][j] / A[j][j];
			for (int k = j + 1; k < A.getColomns(); k++)
				A[i][k] -= A[j][k] * coefficient;
			b[i][0] -= b[j][0] * coefficient;
		}
	}

	for (int i = A.getRows() - 1; i >= 0; i--)
	{
		sum = 0;
		for (int j = i + 1; j < A.getColomns(); j++)
		{
			sum += A[i][j] * x[j][0];
		}
		x[i][0] = (b[i][0] - sum) / A[i][i];
	}
}

void solveSystemOfEquations1(Matrix A, Matrix b, Matrix& x)
{
	double sum;

	for (int j = 0; j < A.getColomns(); j++)
	{
		if (A[j][j] == 0)
		{
			int max_index = j;
			double max_element = 0;
			for (int i = j + 1; i < A.getRows(); i++)
			{
				if (abs(A[i][j]) > max_element)
				{
					max_index = i;
					max_element = A[i][j];
				}
			}
			A.swapRows(max_index, j);
			b.swapRows(max_index, j);
		}

		for (int i = j + 1; i < A.getRows(); i++)
		{
			double coefficient = A[i][j] / A[j][j];
			for (int k = j + 1; k < A.getColomns(); k++)
				A[i][k] -= A[j][k] * coefficient;
			b[i][0] -= b[j][0] * coefficient;
		}
	}

	for (int i = A.getRows() - 1; i >= 0; i--)
	{
		sum = 0;
		for (int j = i + 1; j < A.getColomns(); j++)
		{
			sum += A[i][j] * x[j][0];
		}
		x[i][0] = (b[i][0] - sum) / A[i][i];
	}
}

void saveSystemToFile(Matrix& A, Matrix& b, std::string file)
{
	std::ofstream out(file);

	out << A.getRows() << " " << A.getColomns() << std::endl << std::endl;

	for (int i = 0; i < A.getRows(); i++)
	{
		for (int j = 0; j < A.getColomns(); j++)
		{
			out << A[i][j] << " ";
		}
		out << std::endl;
	}
	out << std::endl;

	for (int i = 0; i < b.getRows(); i++)
	{
		out << b[i][0] << " ";
	}

	out.close();
}

void loadSystemFromFile(Matrix& A, Matrix& b, std::string file)
{
	try {
		std::ifstream in(file);
		in.exceptions(std::ifstream::failbit);

		int N, M;

		in >> N >> M;

		A = Matrix(N, M);
		b = Matrix(N);

		for (int i = 0; i < A.getRows(); i++)
			for (int j = 0; j < A.getColomns(); j++)
				in >> A[i][j];

		for (int i = 0; i < b.getRows(); i++)
			in >> b[i][0];

		in.close();
	}
	catch (std::ios_base::failure&) {
		std::cerr << "Couldn't open the file! Enter The System manually.\n";
		initSystemOfEquations(A, b);
		return;
	}
}

void checkRoots(Matrix& A, Matrix& b, Matrix& x)
{
	double sum = 0, maxDelta = 0, delta = 0;
	std::cout << "Num \t | \t Sum \t | \t b \t | \t Delta" << std::endl;
	for (int i = 0; i < A.getRows(); i++)
	{
		sum = 0;
		for (int j = 0; j < A.getColomns(); j++)
		{
			sum += A[i][j] * x[j][0];
		}

		delta = abs(b[i][0] - sum);
		maxDelta = std::max(delta, maxDelta);
		if (i < std::min(A.getRows() - 1, 10))
			std::cout << i + 1 << "\t | \t" << sum << "\t | \t" << b[i][0] << "\t | \t" << delta << std::endl;
	}
	if (A.getRows() > 10)
		std::cout << "..." << std::endl;
	std::cout << A.getRows() << "\t | \t" << sum << "\t | \t" << b[A.getRows()-1][0] << "\t | \t" << delta << std::endl;
	std::cout << "Max delta: " << maxDelta << std::endl << std::endl;
}

void printRoots(Matrix& x)
{
	for (int i = 0; i < std::min(x.getRows(), 10); i++)
	{
		if (i == 9 && x.getRows() > 10)
			std::cout << "..." << std::endl << "x" << x.getRows() << " = " << x[x.getRows()-1][0] << std::endl;
		else
			std::cout << "x" << i + 1 << " = " << x[i][0] << std::endl;
	}
}
