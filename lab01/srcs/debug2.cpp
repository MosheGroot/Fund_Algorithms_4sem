#include "monome.hpp"

#define STEP_BY_STEP
#define SPL << "\n--------\n"

void test1()
{
	std::cout << "I) Construct test\n" << std::endl;

	Monome a;
	Monome b("1a2b6c2");
	Monome c("5");

	std::cout << a SPL << b SPL << c SPL << std::endl;
	std::cout << a.convert() SPL
				<< b.convert() SPL
				<< c.convert() SPL << std::endl;

	std::cout << "\n[SUCCESS]" << std::endl;
}

void test2()
{
	std::cout << "\n+=========================+\n";
	std::cout << "II) Copy and ==,!= test\n" << std::endl;

	Monome a("1337a1b2c3d4e5f6g7");
	Monome b(a);

	std::cout << "a : " << a SPL << "b : " << b SPL << std::endl;
	std::cout << "TeX(a) : " << a.convert() SPL
				<< "TeX(b) : " << b.convert() SPL << std::endl;
	std::cout << "a == b : " << (a == b) << std::endl;
	std::cout << "a != b : " << (a != b) << std::endl;

	Monome c("42");
	std::cout << "\n\nc : " << c SPL << std::endl;
	std::cout << "TeX(c) : " << c.convert() SPL << std::endl;
	std::cout << "c == a : " << (c == a)
				<< "\t|\tc == b : " << (c == b) << std::endl;
	std::cout << "c != a : " << (c != a)
				<< "\t|\tc != b : " << (c != b) << std::endl;


	std::cout << "\n\n part2 \n\n" << std::endl;

	a = "1x0y0z0";
	b = "1a0b0c0d0z0f0";

	std::cout << "a : " << a SPL << "b : " << b SPL << std::endl;
	std::cout << "TeX(a) : " << a.convert() SPL
				<< "TeX(b) : " << b.convert() SPL << std::endl;
	std::cout << "a == b : " << (a == b) << std::endl;
	std::cout << "a != b : " << (a != b) << std::endl;


	std::cout << "\n[SUCCESS]" << std::endl;
}

void test3()
{
	std::cout << "\n+=========================+\n";
	std::cout << "III) Overloaded operators test with empty monomes\n"
																<< std::endl;

	Monome a, b;

	std::cout << "a + b : " << a + b << std::endl;
	std::cout << "a - b : " << a - b << std::endl;
	std::cout << "a * b : " << a * b << std::endl;
	std::cout << "a'(l) : " << a / 'l' << std::endl;
	std::cout << "b'(f) : " << b / 'f' << std::endl;

	std::cout << "a += b : " << (a += b) << std::endl;
	std::cout << "a -= b : " << (a -= b) << std::endl;
	std::cout << "a *= b : " << (a *= b) << std::endl;
	std::cout << "a'(l) : " << (a / 'l') << std::endl;
	std::cout << "b'(f) : " << (b / 'f') << std::endl;

	std::cout << "\n[SUCCESS]" << std::endl;
}

void test4()
{
	std::cout << "\n+=========================+\n";
	std::cout << "IV) Overloaded operators test with different monomes\n"
																<< std::endl;


	Monome a = "2x2";
	Monome b = "2xy2";

	a = a;
	b = b;
	std::cout << "a : " << a SPL << "b : " << b SPL << std::endl;
	std::cout << "a == b : " << (a == b) << std::endl;
	std::cout << "\nNext expected numbers of errors: 4" << std::endl;
	try
	{
		std::cout << a + b << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << '\t' << e.what() << std::endl;
	}
	try
	{
		std::cout << a - b << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << '\t' << e.what() << std::endl;
	}
	try
	{
		a += b;
	}
	catch (const std::exception& e)
	{
		std::cerr << '\t' << e.what() << std::endl;
	}
	try
	{
		a -= b;
	}
	catch (const std::exception& e)
	{
		std::cerr << '\t' << e.what() << std::endl;
	}

	std::cout << "a * b : " << a * b SPL << std::endl;
	std::cout << "a *= b : " << (a *= b) SPL << std::endl;
	
	std::cout << std::endl;

	std::cout << "a'(x) : " << a / 'x' SPL << std::endl;
	std::cout << "a'=(x) : " << (a /= 'x') SPL << std::endl;
	std::cout << "b'(x) : " << b / 'x' SPL << std::endl;
	std::cout << "b'=(x) : " << (b /= 'x') SPL << std::endl;

	std::cout << "\n[SUCCESS]" << std::endl;
}

void test5()
{
	std::cout << "\n+=========================+\n";
	std::cout << "V) Overloaded operators test with same monomes\n"
																<< std::endl;

	Monome a = "5xy2";
	Monome b = "1xy2";

	a = a;
	b = b;
	std::cout << "a : " << a SPL << "b : " << b SPL << std::endl;
	std::cout << "a == b : " << (a == b) << '\n' << std::endl;

	std::cout << "a + b : " << a + b SPL << std::endl;
	std::cout << "a - b : " << a - b SPL << std::endl;
	std::cout << "a += b : " << (a += b) SPL << std::endl;
	std::cout << "a -= b : " << (a -= b) SPL << std::endl;

	std::cout << std::endl;

	std::cout << "a * b : " << a * b SPL << std::endl;
	std::cout << "a *= b : " << (a *= b) SPL << std::endl;
	
	std::cout << std::endl;

	std::cout << "a'(x) : " << a / 'x' SPL << std::endl;
	std::cout << "a'=(x) : " << (a /= 'x') SPL << std::endl;
	std::cout << "b'(x) : " << b / 'x' SPL << std::endl;
	std::cout << "b'=(x) : " << (b /= 'x') SPL << std::endl;

	std::cout << "\n[SUCCESS]" << std::endl;
}

void test6()
{
	std::cout << "\n+=========================+\n";
	std::cout << "VI) Manual input\n" << std::endl;

	std::cout << "Enter monome (for example \"1x2y3z32\") below:" << std::endl;

	Monome a;
	std::cin >> a;
	std::cout << "\nGJ! here your monome:\n" << a SPL
						<< "and it's TeX code:\n" << a.convert() << std::endl;

	std::cout << "\n[SUCCESS]" << std::endl;
}

int main()
{
	test1();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif

	test2();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif

	test3();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif
	
	test4();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif
	
	test5();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif

	test6();
}
