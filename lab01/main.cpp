#include <cstdlib>
#include <unistd.h>
#include "class.hpp"

#define LEAKS_CHECK

void test1()
{
	Matrix_NN a;
	Matrix_NN b(5);
	Matrix_NN c {1, 2, 3, 4};
	//Matrix_NN d = {1, 2, 3, 4};
	Matrix_NN x(a);
	Matrix_NN y(b);
	//Matrix_NN z(c);

	/*
	 *try
	 *{
	 *    Matrix_NN f = {1, 2, 3};
	 *}
	 *catch (const std::exception& e)
	 *{
	 *    std::cerr << e.what() << std::endl;
	 *}
	 */

	/*
	 *try
	 *{
	 *    Matrix_NN f = {};
	 *}
	 *catch (const std::exception& e)
	 *{
	 *    std::cerr << e.what() << std::endl;
	 *}
	 */
}

void test2()
{
	Matrix_NN a;
	Matrix_NN b;

	a = a;
	b = b;
	std::cout << a << b;
	Matrix_NN c = a + b;
	c = a - b;
	c = a * b;
	c = b + a;
	c = a - b;
	c -= b;
	c += b;
	c *= b;

	c /= 9;
	c *= 5.;
	c = a * 5 + b * 10;

	std::cout << det(a) << det(b) << det(c) << std::endl;
	std::cout << invert(c) << transp(c) << std::endl;
	std::cout << trace(c) << '\t' << exp(c, 5) << std::endl;
}

void test3()
{
	Matrix_NN a = {1};
	Matrix_NN b = {1, 2, 3, 4};

	a = a;
	b = b;
	std::cout << a << b;
	std::cout << "Ожидаемое колво ошибок: 6" << std::endl;
	try
	{
		Matrix_NN c = a + b;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	Matrix_NN c;
	try
	{
		c = a * b;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		c = a - b;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		c += b;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		c -= b;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		c *= b;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

int main()
{
	test1();
#ifdef LEAKS_CHECK
	//std::string leaks_check = "memleax ";
	//leaks_check += std::to_string(getpid());
	//std::system(leaks_check.c_str());
#endif


	//test2();
#ifdef LEAKS_CHECK
	//std::system(leaks_check.c_str());
#endif


	//test3();
}
