#pragma once

#include <iostream>
#include <cctype>
#include <string>
#include <map>
#include "tex_convertible.hpp"

class Polynome; // forward declaring

class Monome : public TeX_convertible
{
friend class Polynome;

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

	friend bool compare_ascending(const Monome &a, const Monome &b);
	friend bool compare_vars(const Monome &a, const Monome &b);
	friend bool is_harmonic_polynome(const Polynome &m);

	unsigned int general_degree() const;
	std::string convert() const;

	~Monome() {};
};

bool compare_ascending(const Monome &a, const Monome &b);
bool compare_vars(const Monome &a, const Monome &b);
