#pragma once
/* COMPARATOR INTERFACE */
template<typename T>
class Comparator
{
public:
	Comparator() {}
	~Comparator() {}

	virtual int	compare(const T& first, const T& second) = 0;
};

/* INTERFACE REALIZATIONS */
/* ascending*/
template<typename T>
class Ascending_comparator : public Comparator<T>
{
public:
	int		compare(const T& first, const T& second) override
	{
		if (first < second)
			return (-1);
		else if (first == second)
			return (0);
		return (1);
	}
};

/* descending*/
template<typename T>
class Descending_comparator : public Comparator<T>
{
public:
	int		compare(const T& first, const T& second) override
	{
		if (first > second)
			return (-1);
		else if (first == second)
			return (0);
		return (1);
	}
};