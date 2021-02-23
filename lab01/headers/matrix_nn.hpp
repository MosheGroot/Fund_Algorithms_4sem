#pragma once

#include <iostream>
#include <initializer_list>
#include <exception>
#include <algorithm>
#include <memory>
#include "tex_convertible.hpp"

#define EPS 1e-6

class Matrix_NN : public TeX_convertible
{
private:
	std::vector<std::vector<double>> data;
	size_t N;

	void alloc_memory(size_t N);
	void free_memory();
	void copy_memory(const std::vector<std::vector<double>> &src);
	void copy_value(double value);

public:

	Matrix_NN() : N(0) {}
	Matrix_NN(size_t n, double value=0.);
	Matrix_NN(const Matrix_NN &copy);	
	Matrix_NN(const std::initializer_list<double> &list);

	~Matrix_NN();

	Matrix_NN& operator=(const Matrix_NN &b);
	Matrix_NN& operator=(const std::initializer_list<double> &list);

	std::vector<double>& operator[](const size_t i);
	bool operator==(const Matrix_NN &b) const;
	bool operator!=(const Matrix_NN &b) const;

	Matrix_NN operator+(const Matrix_NN &b) const;
	Matrix_NN operator-(const Matrix_NN &b) const;
	Matrix_NN operator*(const Matrix_NN &b) const;
	Matrix_NN operator*(const double l) const;
	friend Matrix_NN operator*(const double l, const Matrix_NN& dt);
	Matrix_NN operator/(const double l) const;

	Matrix_NN& operator+=(const Matrix_NN &b);
	Matrix_NN& operator-=(const Matrix_NN &b);
	Matrix_NN& operator*=(const Matrix_NN &b);
	Matrix_NN& operator*=(const double l);
	Matrix_NN& operator/=(const double l);

	friend std::ostream& operator<<(std::ostream& os, const Matrix_NN& m);
	friend std::istream& operator>>(std::istream& is, Matrix_NN& m);

	friend double det(const Matrix_NN& m);
	friend Matrix_NN invert(const Matrix_NN &m);
	friend Matrix_NN transp(const Matrix_NN &m);
	friend double trace(const Matrix_NN &m);
	friend Matrix_NN exp(const Matrix_NN &m, size_t k);

	size_t size() const { return N; }
	std::string convert() const override;	
};
