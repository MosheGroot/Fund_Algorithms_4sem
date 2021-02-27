#include "nomes.hpp"

#define STEP_BY_STEP
#define SPL << "\n--------\n"

void test1()
{
	std::cout << "I) Construct test\n" << std::endl;

	Polynome a;
	Polynome b("-9z3 + 2x2 + 5y2");
	Polynome c("42");

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

	Polynome a("2a + 3b2 + 9c3");
	Polynome b(a);

	std::cout << "a : " << a SPL << "b : " << b SPL << std::endl;
	std::cout << "TeX(a) : " << a.convert() SPL
				<< "TeX(b) : " << b.convert() SPL << std::endl;
	std::cout << "a == b : " << (a == b) << std::endl;
	std::cout << "a != b : " << (a != b) << std::endl;

	Polynome c("42");
	std::cout << "\n\nc : " << c SPL << std::endl;
	std::cout << "TeX(c) : " << c.convert() SPL << std::endl;
	std::cout << "c == a : " << (c == a)
				<< "\t|\tc == b : " << (c == b) << std::endl;
	std::cout << "c != a : " << (c != a)
				<< "\t|\tc != b : " << (c != b) << std::endl;


	std::cout << "\n\n part2 \n\n" << std::endl;

	a = "1x0y0z0 + 5x2y2z2";
	b = "1a0b0c0d0z0f0 + 5z2y2x2";

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
	std::cout << "III) Overloaded operators test with empty (!) polynomes\n"
																<< std::endl;

	Polynome a, b;

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
	std::cout << "IV) Overloaded operators test with different polynomes\n"
																<< std::endl;


	Polynome a = "2x2 + z6 + 2y";
	Polynome b = "2xy2";

	a = a;
	b = b;
	std::cout << "a : " << a SPL << "b : " << b SPL << std::endl;
	std::cout << "a == b : " << (a == b) SPL << std::endl;
	
	std::cout << "a + b : " << a + b SPL << std::endl;
	std::cout << "a - b : " << a - b SPL << std::endl;
	
	std::cout << "a += b : " << (a += b) SPL << std::endl;
	std::cout << "a -= b : " << (a -= b) SPL << std::endl;

	std::cout << "a * b : " << a * b SPL << std::endl;
	std::cout << "a *= b : " << (a *= b) SPL << std::endl;
	
	std::cout << std::endl;

	std::cout << "a'(x) : " << a / 'x' SPL << std::endl;
	std::cout << "a'=(x) : " << (a /= 'x') SPL << std::endl;
	std::cout << "b'(x) : " << b / 'x' SPL << std::endl;
	std::cout << "b'=(x) : " << (b /= 'x') SPL << std::endl;

	std::cout << "a'(xy) : " << a / "xy" SPL << std::endl;
	std::cout << "a'=(xy) : " << (a /= "xy") SPL << std::endl;
	std::cout << "b'(xy) : " << b / "xy" SPL << std::endl;
	std::cout << "b'=(xy) : " << (b /= "xy") SPL << std::endl;

	std::cout << std::endl;
	
	Polynome c;
	std::cout << "empty c : " << c SPL << std::endl;
	std::cout << "a + c : " << a + c SPL << std::endl;
	std::cout << "a - c : " << a - c SPL << std::endl;
	std::cout << "a * c : " << a * c SPL << std::endl;

	std::cout << "\n[SUCCESS]" << std::endl;
}

void test5_1()
{
	std::cout << "\n+=========================+\n";
	std::cout << "V.I) Overloaded operators test with same polynomes\n"
																<< std::endl;

	Polynome a = "x2 + y3";
	Polynome b = "5x2";

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

void test5_2()
{
	std::cout << "\n+=========================+\n";
	std::cout << "V.II) Overloaded operators test with same polynomes\n"
																<< std::endl;

	Polynome a = "x2 + y3 + -z4 + f";
	Polynome b = "5x2 + z4 + f52";

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
	std::cout << "VI) homogenous and harmonic polynomes\n" << std::endl;

	Polynome a = "xyz + x3 + y3";
	Polynome b = "x + y + z";

	std::cout << "a : " << a SPL << "b : " << b SPL << std::endl;
	std::cout << "a == b : " << (a == b) << '\n' << std::endl;

	std::cout << "Homogenous(a) : " << is_homogenous_polynome(a) << std::endl;
	std::cout << "Homogenous(b) : " << is_homogenous_polynome(b) << std::endl;

	std::cout << "Harmonic(a) : " << is_harmonic_polynome(a) << std::endl;
	std::cout << "Harmonic(b) : " << is_harmonic_polynome(b) << std::endl;

	std::cout << "\n[SUCCESS]" << std::endl;
}

void test7()
{
	std::cout << "\n+=========================+\n";
	std::cout << "VII) Manual input\n" << std::endl;

	std::cout << "Enter polynome (for example \"x2y2z2 + 25xy6\") below:"
																<< std::endl;

	Polynome a;
	std::cin >> a;
	std::cout << "\nGJ! here your polynome:\n" << a SPL
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
	
	test5_1();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif

	test5_2();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif
	
	test6();
#ifdef STEP_BY_STEP
	std::cout << "Press enter for next test." << std::endl;
	std::cin.get();
#endif

	test7();

}
