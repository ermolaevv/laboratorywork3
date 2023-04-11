#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"
#include "Other Functions.h"


int main()
{
	srand((unsigned)time(nullptr));

	int op;
	Matrix A, b;

	while (true)
	{
		std::cout << "Load a saved System? (1/0): ";
		std::cin >> op;
		switch (op)
		{
		case 1:
			loadSystemFromFile(A, b);
			break;

		default:
			initSystemOfEquations(A, b);
			break;
		}

		Matrix x(A.getRows());

		std::cout << std::endl;
		printSystemofEquations(A, b);
		std::cout << std::endl;

		//solveSystemOfEquations0(A, b, x);
		//printRoots(x);
		//std::cout << std::endl;
		//checkRoots(A, b, x);

		solveSystemOfEquations0(A, b, x);
		printRoots(x);
		std::cout << std::endl;
		checkRoots(A, b, x);

		std::cout << "Save the System? (1/0): ";
		std::cin >> op;
		if (op) saveSystemToFile(A, b);

		std::cout << "Repeat again? (1/0): ";
		std::cin >> op;
		if (op == 0)
			break;
		if (op == 1)
			system("cls");
	}

	system("cls");
	std::cout << "Created by @Yermolaev Vladislav" << std::endl;
	return 0;
}

