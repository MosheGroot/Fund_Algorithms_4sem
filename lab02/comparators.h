#pragma once

/* INTERFACE COMPARATOR */
template<typename T>
class Comparator
{
public:
	~Comparator() {};

	virtual bool	cmp(const T& first, const T& second) = 0;
};

/* INTERFACE REALIZATIONS */
/* ascending*/
template<typename T>
class Ascending_comparator : public Comparator
{
public:
	Ascending_comparator() {};

	bool	cmp(const T& first, const T& second)
	{
		return (first < second);
	}
};

/* descending*/
template<typename T>
class Descending_comparator : public Comparator
{
public:
	Descending_comparator() {};

	bool	cmp(const T& first, const T& second)
	{
		return (first > second);
	}
};