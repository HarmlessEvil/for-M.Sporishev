//
// Created by Alexander on 06.10.2016.
//

#include "Matrix.hpp"

#include <cstdlib>
#include <ctime>
#include <thread>

unsigned Matrix::threads = 1;

Matrix::Matrix(unsigned  n, unsigned m, std::string argv) {

	m = m == 0 ? n : m;
	tab = std::vector<std::vector<double>>(n, std::vector<double>(m, 0));

	if (!argv.compare("generate")) {
		srand((unsigned int)time(NULL));

		for (unsigned i = 0; i < n; i++) {
			for (unsigned j = 0; j < m; j++) {
				tab[i][j] = rand();
			}
		}
	}
}

Matrix nothread(Matrix& lhs, Matrix& rhs) {
	Matrix result(lhs.rows(), rhs.cols());

	for (unsigned i = 0; i < lhs.rows(); i++) {
		for (unsigned j = 0; j < rhs.cols(); j++) {
			for (unsigned k = 0; k < lhs.cols(); k++) {
				result[i][j] += lhs[i][k] * rhs[k][j];
			}
		}
	}

	return result;
}

std::vector<double> vecMatMul(std::vector<double>& lhs, Matrix& rhs) {

	unsigned Rcols = rhs.cols();
	unsigned cols = lhs.size();

	std::vector<double>result(Rcols, 0);

	for (unsigned i = 0; i < Rcols; i++) {
		for (unsigned j = 0; j < cols; j++) {
			result[i] += lhs[j] * rhs[j][i];
		}
	}

	return result;
}

void inThreadHandler(unsigned j, unsigned k, Matrix& lhs, Matrix& rhs, Matrix& res) {
	for (unsigned i = j; i <= k; i++) {
		res[i] = vecMatMul(lhs[i], rhs);
	}
}

Matrix Matrix :: operator*(Matrix& x)
{
	unsigned col = cols();
	unsigned row = rows();

	if (col != x.rows()) {
		return Matrix();
	}

	Matrix result = Matrix(rows(), x.cols());
	std::vector<std::thread> threadPool;

	if (row > threads) {
		if (row % threads) {
			for (unsigned i = 0; i < row; i += row / threads + 1) {
				threadPool.push_back(std::thread(inThreadHandler, i, (i + row / threads) >= row ? row - 1 : i + row / threads, *this, x, std::ref(result)));
			}
		}
		else {
			for (unsigned i = 0; i < row; i += row / threads) {
				threadPool.push_back(std::thread(inThreadHandler, i, i + row / threads - 1, *this, x, std::ref(result)));
			}
		}
	}
	else {
		for (unsigned i = 0; i < row; i++) {
			threadPool.push_back(std::thread(inThreadHandler, i, i, *this, x, std::ref(result)));
		}
	}

	unsigned s = threadPool.size();

	for (unsigned i = 0; i < s; i++) {
		threadPool[i].join();
	}

	return result;
}

std::vector<double> Matrix :: operator*(std::vector<double>& x)
{
	unsigned s = cols();
	std::vector<double> result(s + 1, 0);

	for (unsigned i = 0; i <= s; i++) {
		for (unsigned j = 0; j <= s; j++) {
			result[i] += tab[i][j] * x[j];
		}
	}

	return result;
}

Matrix Matrix :: operator*(double x)
{
	unsigned s = cols();
	Matrix result(s + 1);
	result.quadratize();

	for (unsigned i = 0; i <= s; i++) {
		for (unsigned j = 0; j <= s; j++) {
			result[i][j] = tab[i][j] * x;
		}
	}

	return result;
}

std::vector<double> Matrix::quadratize()
{
	std::vector<double> result;
	unsigned int s = cols();
	if (tab.size() != tab[0].size()) {
		for (unsigned int i = 0; i < s; i++) {
			result.push_back(tab[i][s]);
			tab[i].resize(s);
		}
	}

	return result;
}

Matrix Matrix::transpose()
{
	unsigned int s = cols();
	Matrix result = Matrix(s + 1);
	result.quadratize();

	for (unsigned int i = 0; i < s; i++) {
		for (unsigned int j = 0; j < s; j++) {
			result[j][i] = tab[i][j];
		}
	}

	return result;
}

unsigned int Matrix::cols() {
	return tab[0].size();
}

unsigned int Matrix::rows()
{
	return tab.size();
}

Matrix :: ~Matrix() {
	for (unsigned i = 0; i < cols() + 1; i++) {
		tab[i].clear();
	}
	tab.clear();
}

std::vector<double>& Matrix :: operator[](int i) {
	return tab[i];
}

std::vector<double> Matrix :: operator()(unsigned j)
{
	unsigned s = cols();
	std::vector<double> result(s + 1, 0);

	for (unsigned i = 0; i <= s; i++) {
		result[i] = tab[i][j];
	}

	return result;
}

std::istream& operator>> (std::istream& is, Matrix& x) {
	unsigned int s = x.cols();

	for (unsigned int i = 0; i < s; i++) {
		for (unsigned int j = 0; j < s + 1; j++) {
			if (j == s) {
				std::cout << "Enter the free member of the string " << i << " ";
			}
			else {
				std::cout << "Enter element (" << i << ',' << j << ") ";
			}
			is >> x[i][j];
		}
	}
	return is;
}

std::ostream& operator<< (std::ostream& os, Matrix& x) {
	unsigned int s = x.cols();

	for (unsigned int i = 0; i < s; i++) {
		for (unsigned int j = 0; j < s + 1; j++) { os << x[i][j] << ' '; }
		os << std::endl;
	}
	return os;
}

std::ifstream& operator>>(std::ifstream& is, Matrix& x)
{
	unsigned int c = x.cols();
	unsigned int r = x.rows();

	for (unsigned int i = 0; i < r; i++) {
		for (unsigned int j = 0; j < c; j++) {
			is >> x[i][j];
		}
	}
	return is;
}

std::vector<double> solve(Matrix a) {
	int cols = (int)a.cols();

	for (int i = 0; i < cols; i++) {
		for (int j = i; j < cols; j++) {
			if ((a[j][i] == 0) || (a[j][i] == 1))
				continue;
			if (i == j) {
				for (int k = cols; k >= i; k--) {
					a[j][k] /= a[j][i];
				}
			}
			else {
				for (int k = cols; k >= i; k--) {
					a[j][k] = a[j][k] / a[j][i] - a[i][k];
				}
			}
		}
	}

	for (int i = cols - 1; i > 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			a[j][cols] -= a[i][cols] * a[j][i];
			a[j][i] = 0;
		}
	}

	std::vector<double> res;

	for (int i = 0; i < cols; res.push_back(a[i++][cols]));

	return res;
}

std::vector<double> vsMul(std::vector<double>& lhs, double rhs)
{
	std::vector<double> result(lhs);

	for (unsigned i = 0; i < lhs.size(); i++) {
		result[i] *= rhs;
	}

	return result;
}

double scalarMul(std::vector<double>& lhs, std::vector<double>& rhs)
{
	double result = 0;

	for (unsigned i = 0; i < lhs.size(); i++) {
		result += lhs[i] * rhs[i];
	}

	return result;
}
