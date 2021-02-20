#include "matrix_nn.hpp"

/*=========================*/
/* PRIVATE METHODS & UTILS */
/*=========================*/

void Matrix_NN::alloc_memory(size_t n)
{
	N = n;
	if (!N)
	{
		data = nullptr;
		return;
	}

	if (!(data = new double*[N]))
		throw std::bad_alloc();
	for (size_t i = 0; i < N; i++)
		if (!(data[i] = new double[N]))
			throw std::bad_alloc();
}

void Matrix_NN::free_memory()
{
	for (size_t i = 0; i < N; i++)
		delete[] data[i];
	delete[] data;

	data = nullptr;
	N = 0;
}

void Matrix_NN::copy_memory(double **src)
{
	size_t i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			data[i][j] = src[i][j];
}

void Matrix_NN::copy_value(double value)
{
	size_t i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			data[i][j] = value;
}

static size_t binary_sqrt_search(size_t n)
{
	size_t l = 1, r = n;

	size_t mid;
	while (r - l > 1)
	{
		mid = l + (r - l) / 2;
		if (mid * mid <= n)
			l = mid;
		else
			r = mid;
	}
	
	return l;
}
/*===============================*/
/* CONSTRUCTOR, COPY, DESTRUCTOR */
/*===============================*/

Matrix_NN::Matrix_NN(size_t n, double value)
{
	alloc_memory(n);
	copy_value(value);
}

Matrix_NN::Matrix_NN(const std::initializer_list<double> &list)
{
	size_t s = binary_sqrt_search(list.size());
	if (s * s != list.size())
		throw std::length_error("Initialize list must have size = N * N!");
	
	alloc_memory(s);

	size_t i = 0;
	for (const auto& elem : list)
	{
		data[i / N][i % N] = elem;
		i++;
	}
}

Matrix_NN::Matrix_NN(const Matrix_NN &copy)
{
	alloc_memory(copy.N);
	copy_memory(copy.data);
}

Matrix_NN::~Matrix_NN()
{
	if (!data)
		return;
	free_memory();
}

/*======================*/
/*		OPERATOR =		*/
/*======================*/

Matrix_NN& Matrix_NN::operator=(const Matrix_NN &b)
{
	if (N != b.N)
	{
		free_memory();
		alloc_memory(b.N);
	}
	copy_memory(b.data);
	return (*this);
}

Matrix_NN& Matrix_NN::operator=(const std::initializer_list<double> &list)
{
	size_t s = binary_sqrt_search(list.size());
	if (s * s != list.size())
		throw std::length_error("List must have size = N * N!");

	if (s != N)
	{
		free_memory();
		alloc_memory(s);
	}

	size_t i = 0;
	for (const auto& elem : list)
		data[i / N][i % N] = elem;
	return (*this);
}

/*==========================*/
/*		OPERATORS []==		*/
/*==========================*/

double* Matrix_NN::operator[](const size_t i)
{
	return (this->data[i]);
}

bool Matrix_NN::operator==(const Matrix_NN &b)
{
	if (N != b.N)
		return false;

	const double EPS = 1e-6;
	size_t i, j;
	for (i = 0; i < b.N; i++)
		for (j = 0; j < b.N; j++)
			if (b.data[i][j] < data[i][j] - EPS ||
					b.data[i][j] > data[i][j] + EPS)
				return false;
	return true;
}

/*==========================*/
/*		OPERATORS +-*\		*/
/*==========================*/

Matrix_NN Matrix_NN::operator+(const Matrix_NN &b)
{
	if (N != b.N)
		throw std::invalid_argument("Matrixes must be same sizes!");

	Matrix_NN c(*this);
	size_t i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c.data[i][j] += b.data[i][j];
	return c;
}

Matrix_NN Matrix_NN::operator-(const Matrix_NN &b)
{
	if (N != b.N)
		throw std::invalid_argument("Matrixes must be same sizes!");

	Matrix_NN c(*this);
	size_t i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c.data[i][j] -= b.data[i][j];
	return c;
}

Matrix_NN Matrix_NN::operator*(const Matrix_NN &b)
{
	if (N != b.N)
		throw std::invalid_argument("Matrixes must be same sizes!");

	Matrix_NN c(N);
	size_t i, j, k;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			c.data[i][j] = 0;
			for (k = 0; k < N; k++)
				c.data[i][j] += data[i][k] * b.data[k][j];
		}
	return c;
}

Matrix_NN Matrix_NN::operator*(const double l)
{
	Matrix_NN c(*this);
	size_t i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c.data[i][j] *= l;
	return c;
}

Matrix_NN operator*(const double l, const Matrix_NN &m)
{
	Matrix_NN c(m);
	size_t i, j;
	for (i = 0; i < m.N; i++)
		for (j = 0; j < m.N; j++)
			c.data[i][j] *= l;
	return c;
}

Matrix_NN Matrix_NN::operator/(const double l)
{
	Matrix_NN c(*this);
	size_t i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c[i][j] /= l;
	return c;
}

/*==========================*/
/*		OPERATORS +-*\=		*/
/*==========================*/

Matrix_NN& Matrix_NN::operator+=(const Matrix_NN &b)
{
	if (N != b.N)
		throw std::invalid_argument("Matrixes must be same sizes!");

	size_t i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			data[i][j] += b.data[i][j];
	return (*this);		
}

Matrix_NN& Matrix_NN::operator-=(const Matrix_NN &b)
{
	if (N != b.N)
		throw std::invalid_argument("Matrixes must be same sizes!");

	size_t i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			data[i][j] -= b.data[i][j];
	return (*this);
}

Matrix_NN& Matrix_NN::operator*=(const Matrix_NN &b)
{
	if (N != b.N)
		throw std::invalid_argument("Matrixes must be same sizes!");

	Matrix_NN tmp = *this * b;
	*this = tmp;
	return (*this);
}

Matrix_NN& Matrix_NN::operator*=(const double l)
{
	size_t i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			data[i][j] *= l;
	return (*this);
}

Matrix_NN& Matrix_NN::operator/=(const double l)
{
	size_t i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			data[i][j] /= l;
	return (*this);
}

/*==========================*/
/*		OPERATORS <<>>		*/
/*==========================*/

std::ostream& operator<<(std::ostream& os, const Matrix_NN& m)
{
	if (!m.data)
	{
		os << std::endl;
		return os;
	}

	size_t i, j;
	for (i = 0; i < m.N; i++)
	{
		for (j = 0; j < m.N; j++)
			os << m.data[i][j] << ' ';
		os << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, const Matrix_NN& m)
{
	size_t i, j;
	for (i = 0; i < m.N; i++)
		for (j = 0; j < m.N; j++)
			is >> m.data[i][j];
	return is;
}

/*==================*/
/* FRIEND FUNCTIONS */
/*==================*/

/* determinant */

double det(const Matrix_NN& m)
{
	if (!m.N)
		return (0. / 0.);

	Matrix_NN tmp(m);

	size_t i, j, k;
	double coeff;
	for (j = 0; j < m.N; j++)
		for (i = j + 1; i < m.N; i++)
		{
			coeff = m.data[i][j] / m.data[j][j];
			for (k = 0; k < m.N; k++)
				m.data[j][k] -= m.data[i][k] * coeff;
		}

	double out = 1;
	for (i = 0; i < m.N; i++)
		out *= m.data[i][i];

	return out;
}

/* invertion (Gauss) */

Matrix_NN invert(const Matrix_NN& m)
{
	Matrix_NN tmp(m), inv(m.N);
	
	size_t i, j, k;
	for (i = 0; i < m.N; i++)
		for (j = 0; j < m.N; j++)
			if (i == j)
				inv.data[i][j] = 1.;
			else
				inv.data[i][j] = 0.;

	double coeff;
	for (j = 0; j < m.N; j++)
		for (i = j + 1; i < m.N; i++)
		{
			coeff = m.data[i][j] / m.data[j][j];
			for (k = 0; k < m.N; k++)
			{
				m.data[j][k] -= m.data[i][k] * coeff;
				inv.data[j][k] -= inv.data[i][k] * coeff;
			}
		}

	return inv;
}

/* transpose */

Matrix_NN transp(const Matrix_NN &m)
{
	Matrix_NN tmp(m.N);

	size_t i, j;
	for (i = 0; i < m.N; i++)
		for (j = 0; j < m.N; j++)
			tmp.data[j][i] = m.data[i][j];

	return tmp;
}

/* trace */

double trace(const Matrix_NN &m)
{
	double out = 0.;

	for (size_t i = 0; i < m.N; i++)
		out += m.data[i][i];

	return out;
}

/* exp */

Matrix_NN exp(const Matrix_NN &m, size_t k)
{
	Matrix_NN tmp(m), e(m.N);

	size_t i, j;
	for (i = 0; i < m.N; i++)
		for (j = 0; j < m.N; j++)
			if (i == j)
				e.data[i][j] = 1.;
			else
				e.data[i][j] = 0.;

	double c = 1;
	for (i = 1; i <= k; i++)
	{
		e = tmp * c;
		tmp = tmp * m;
		c /= i;
	}
	
	return e;
}

/*==================*/
/*	  CONVERTION    */
/*==================*/

std::string Matrix_NN::convert() const
{
	std::string out = "$$\\begin{pmatrix}";

	size_t i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N - 1; j++)
		{
			out += std::to_string(data[i][j]);
			out += " & ";
		}
		out += std::to_string(data[i][N - 1]);
		out += "\\\\";
	}

	out += "\\end{pmatrix}$$";
	return out;
}
