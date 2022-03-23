#pragma once

#include <string>
#include <vector>

#include "Problem.h"

// Time
// Algorithm 10m
// Implementation 30m
// Input handling 10m
// Performance optimization 1h
// Cleanup 10m

class GeneFolding final :
	public Problem
{
public:
	std::string Solve(const std::string& input) override;

	std::string GetName() const override
	{
		return "genefolding";
	}

	int GetFileDigits() const override
	{
		return 3;
	}

private:
	std::string sequence_;
	std::vector<unsigned int> check_indices_;

	bool CheckForFold(unsigned int char_index);

	static std::string FoldLeft(const std::string& input, unsigned int length);

	static std::string FoldRight(const std::string& input, unsigned int length);
};

