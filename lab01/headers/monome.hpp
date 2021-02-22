#pragma once

#include <iostream>
#include <cctype>
#include <string>
#include <map>
#include "tex_convertible.hpp"

class Monome : public TeX_convertible
{
private:
	int coeff;
	std::map<char, unsigned int> vars;

public:

	Monome(int coeff = 0) : coeff(coeff) {};
	Monome(const char *str);
	Monome(const Monome &copy);

	Monome& operator=(const Monome &m);
	Monome& operator=(const char *str);

	Monome& operator+=(const Monome &m);
	Monome operator+(const Monome &m) const;

	Monome& operator-=(const Monome &m);
	Monome operator-(const Monome &m) const;
	
	Monome& operator*=(const Monome &m);
	Monome operator*(const Monome &m) const;

	Monome& operator/=(const char var);
	Monome operator/(const char var) const;

	bool operator==(const Monome &m) const;
	bool operator!=(const Monome &m) const;

	friend std::ostream& operator<<(std::ostream& os, const Monome &m);
	friend std::istream& operator>>(std::istream& is, Monome &m);

	std::string convert() const;

	~Monome() {};
};
