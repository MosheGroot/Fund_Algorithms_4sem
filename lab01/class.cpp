#include "class.hpp"

Matrix_NN::Matrix_NN(size_t n)
	: N(n)
{
	if (!N)
	{
		data = nullptr;
		return;
	}

	data = new double*[N];
	for (size_t i = 0; i < N; i++)
		data[i] = new double[N];
}

Matrix_NN::Matrix_NN(size_t n, double value)
	: Matrix_NN(Matrix_NN(n))
{
	//Matrix_NN(n);
	size_t i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			data[i][j] = value;
}

Matrix_NN::Matrix_NN(size_t n, std::initializer_list<double> &list)
{
	if (list.size() != N * N)
	{
		Matrix_NN();
		return;
	}

	Matrix_NN(n);
	size_t i = 0;
	for (const auto& elem : list)
	{
		data[i / N][i % N] = elem;
		i++;
	}
}

Matrix_NN::Matrix_NN(const Matrix_NN &copy)
{
	if (N != copy.N)
	{
		if (data)
		{
			for (size_t i = 0; i < N; i++)
				delete[] data[i];
			delete[] data;
		}
		Matrix_NN(copy.N);
	}

	size_t i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			data[i][j] = copy.data[i][j];
}

Matrix_NN::~Matrix_NN()
{
	if (!data)
		return;

	for (int i = 0; i < N; i++)
		delete[] data[i];
	delete[] data;
}
