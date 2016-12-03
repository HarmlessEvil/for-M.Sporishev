//
// Created by Alexander on 06.10.2016.
//

#ifndef NM_DIVSUB_MATRIX_HPP
#define NM_DIVSUB_MATRIX_HPP

#include <iostream>
#include <fstream>
#include <vector>

class Matrix {
public:
	Matrix (unsigned n, unsigned m = 0, std :: string argv = "");
	Matrix() = default;
    ~Matrix();

    std :: vector<double>&  operator[](int i);
	std :: vector<double>   operator()(unsigned  i);
    friend std :: istream&  operator>>(std :: istream& is, Matrix& x);
    friend std :: ostream&  operator<<(std :: ostream& os, Matrix& x);
	friend std :: ifstream& operator>>(std :: ifstream& is, Matrix& x);

	Matrix					 operator*(Matrix& x);
	std :: vector<double>	 operator*(std :: vector<double>& x);
	Matrix					 operator*(double x);

	std :: vector<double>	 quadratize();
	Matrix					 transpose();
    unsigned int			 cols();
	unsigned int			 rows();

	static unsigned	threads;
protected:
    std :: vector<std :: vector<double>> tab;
};

std :: vector<double> solve(Matrix a);

std :: vector<double> vsMul(std :: vector<double>& lhs, double rhs);
double scalarMul(std :: vector<double>& lhs, std :: vector<double>& rhs);

#endif //NM_DIVSUB_MATRIX_HPP