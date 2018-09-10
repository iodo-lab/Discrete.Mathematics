#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

#include "PropVar.h"

class BoolGenerator
{
public:
	BoolGenerator &AddVarProp(const std::string &name);
	void Build();
	PropVar operator[](const int index);
	PropVar operator[](const std::string &name);
	std::vector<PropVar> GetPropVars();

private:
	bool Generate(const int num);

private:
	std::vector<PropVar> props;
	inline friend std::ostream &operator<<(std::ostream &os, const BoolGenerator &gen);
};

inline std::ostream &operator<<(std::ostream &os, const BoolGenerator &gen)
{
	for (auto prop : gen.props)
		os << std::setw(6) << prop.name << " ";

	os << std::endl;

	const int rows = int(gen.props[0].rows.size());
	const int cols = int(gen.props.size());
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
			os << std::setw(7) << std::boolalpha << gen.props[col].rows[row];

		os << std::endl;
	}

	return os;
}
