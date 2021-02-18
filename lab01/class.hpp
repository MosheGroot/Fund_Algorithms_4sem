#pragma once

#include <string>
#include <initializer_list>

class TeX_convertible
{
public:

	virtual std::string convert() const;
};

class Matrix_NN : TeX_convertible
{
private:
	double **data;
	size_t N;

public:

	Matrix_NN() : N(0), data(nullptr) {}
	Matrix_NN(size_t n);
	Matrix_NN(size_t n, double value);
	Matrix_NN(size_t n, std::initializer_list<double> &list);
	Matrix_NN(const Matrix_NN &copy);

	~Matrix_NN();
};
