#include <ctime>
#include <chrono>
#include <iomanip>

#include "includes\Matrix.hpp"
int main() {
	std :: ifstream fin("input.txt");

	Matrix A = Matrix(2, 3), B = Matrix(3, 2);
	fin >> A >> B;

	fin.close();

	Matrix :: threads = 2;
	Matrix C = A * B;

	Matrix D = Matrix(250, 250, "generate"), E = Matrix(250, 250, "generate");
	
	std :: chrono :: time_point<std :: chrono :: system_clock> start, end;
	std :: chrono :: duration<double> elapsed_seconds;

	std :: cout << std :: setw(7) << " AMOUNT " << "| ELAPSED TIME" << std :: endl
		<< "--------+-------------" << std :: endl;
	for (int i = 1; i <= 10; i++) {
		Matrix :: threads = i;

		start = std :: chrono :: system_clock :: now();
		Matrix F = D * E;
		end = std :: chrono :: system_clock :: now();
		elapsed_seconds = end - start;

		std :: cout << std :: setw(7) << i << " | " << elapsed_seconds.count() << std :: endl;
	}
	std :: cout << "--------+-------------" << std :: endl;
	for (int i = 50; i <= 60; i++) {
		Matrix::threads = i;

		start = std::chrono::system_clock::now();
		Matrix F = D * E;
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;

		std::cout << std::setw(7) << i << " | " << elapsed_seconds.count() << std::endl;
	}

	system("pause");
	return 0;
}