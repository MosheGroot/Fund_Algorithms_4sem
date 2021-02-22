#pragma once

#include <iostream>
#include <initializer_list>
#include <exception>
#include "tex_convertible.hpp"

class Matrix_NN : public TeX_convertible
{
private:
	double **data;
	size_t N;

	void alloc_memory(size_t N);
	void free_memory();
	void copy_memory(double **src);
	void copy_value(double value);

public:

	Matrix_NN() : data(nullptr), N(0) {}
	Matrix_NN(size_t n, double value=0.);
	Matrix_NN(const Matrix_NN &copy);	
	Matrix_NN(const std::initializer_list<double> &list);

	~Matrix_NN();

	Matrix_NN& operator=(const Matrix_NN &b);
	Matrix_NN& operator=(const std::initializer_list<double> &list);

	double* operator[](const size_t i);
	bool operator==(const Matrix_NN &b);
	bool operator!=(const Matrix_NN &b);

	Matrix_NN operator+(const Matrix_NN &b);
	Matrix_NN operator-(const Matrix_NN &b);
	Matrix_NN operator*(const Matrix_NN &b);
	Matrix_NN operator*(const double l);
	friend Matrix_NN operator*(const double l, const Matrix_NN& dt);
	Matrix_NN operator/(const double l);

	Matrix_NN& operator+=(const Matrix_NN &b);
	Matrix_NN& operator-=(const Matrix_NN &b);
	Matrix_NN& operator*=(const Matrix_NN &b);
	Matrix_NN& operator*=(const double l);
	Matrix_NN& operator/=(const double l);

    friend std::ostream& operator<<(std::ostream& os, const Matrix_NN& m);
	friend std::istream& operator>>(std::istream& is, const Matrix_NN& m);

	friend double det(const Matrix_NN& m);
	friend Matrix_NN invert(const Matrix_NN &m);
	friend Matrix_NN transp(const Matrix_NN &m);
	friend double trace(const Matrix_NN &m);
	friend Matrix_NN exp(const Matrix_NN &m, size_t k);

	size_t size() { return N; }
	std::string convert() const override;	
};
