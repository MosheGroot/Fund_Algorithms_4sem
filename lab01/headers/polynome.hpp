#pragma once

#include <list>
#include "tex_convertible.hpp"
#include "monome.hpp"

class Polynome : public TeX_convertible
{
friend class Monome;

private:
	std::list<Monome> container;

	void compress_polynome();

public:

	Polynome() {};
	Polynome(const char *str);
	Polynome(const Polynome &copy);

	Polynome& operator=(const Polynome &m);
	Polynome& operator=(const char *str);

	Polynome& operator+=(const Polynome &m);
	Polynome operator+(const Polynome &m) const;

	Polynome& operator-=(const Polynome &m);
	Polynome operator-(const Polynome &m) const;
	
	Polynome& operator*=(const Polynome &m);
	Polynome operator*(const Polynome &m) const;

	Polynome& operator/=(const char var);
	Polynome operator/(const char var) const;

	Polynome& operator/=(const char *vars);
	Polynome operator/(const char *vars) const;
	
	bool operator==(const Polynome &m) const;
	bool operator!=(const Polynome &m) const;

	friend std::ostream& operator<<(std::ostream &os, const Polynome &m);
	friend std::istream& operator>>(std::istream &is, Polynome &m);

	friend bool is_homogenous_polynome(const Polynome &m);
	friend bool is_harmonic_polynome(const Polynome &m);

	std::string convert() const;

	~Polynome() {};
};
