#include "PropVar.h"

#include <stdexcept>

PropVar::PropVar(const std::string &name)
	: name(name)
{
}

PropVar::PropVar(const std::string &name, std::vector<bool> rows)
	:name(name)
	, rows(rows)
{
}

bool PropVar::operator[](const int index)
{
	if (index >= rows.size())
		throw std::runtime_error("Failed to get value with index");

	return rows[index];
}
