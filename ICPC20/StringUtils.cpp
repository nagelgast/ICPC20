#include "StringUtils.h"

#include <sstream>

std::vector<std::string> StringUtils::Split(const std::string& string, const char delimiter)
{
	std::vector<std::string> split_string;
	std::istringstream iss(string);
	std::string line;
	while(std::getline(iss, line, delimiter))
	{
		split_string.push_back(line);
	}
	return split_string;
}
