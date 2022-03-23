#pragma once
#include <string>

class Problem
{
public:
	virtual ~Problem() = default;

	virtual std::string Solve(const std::string& input) = 0;
	virtual std::string GetName() const = 0;
	virtual int GetFileDigits() const { return 2; }
	virtual bool ShouldShowOutput() const {return true; }
};
