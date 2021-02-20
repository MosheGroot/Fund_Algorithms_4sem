#pragma once

#include <string>

class TeX_convertible
{
public:
	virtual std::string convert() const = 0;
};
