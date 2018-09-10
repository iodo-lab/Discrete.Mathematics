#pragma once
#include <string>
#include <vector>

class PropVar
{
public:
	PropVar() = default;
	PropVar(const std::string &name);
	PropVar(const std::string &name, std::vector<bool> rows);

public:
	~PropVar() = default;

public:
	bool operator[](const int index);
	void Clear();

public:
	std::string name;
	std::vector<bool> rows;
};