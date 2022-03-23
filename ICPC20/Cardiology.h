#pragma once
#include <cstdint>

#include "Problem.h"

// Time
// Algorithm 30m
// Implementation 1h
// Fix for large values 15m
// Performance improvement 1.5h
// Cleanup 15m

// Note:
// Main problem I ran into while optimizing was not realizing a column can have at most 2 stable positions.
// This led me to iterate over the entire column to check if there was more than one stable position.
// Once I realized I could determine this based off the stable positions found from the start and the end
// I managed to optimize it fairly quickly.

class Cardiology :
	public Problem
{
public:
	std::string Solve(const std::string& input) override;

	std::string GetName() const override
	{
		return "cardiology";
	}

private:
	int64_t rows_ = 0;
	int64_t middle_row_ = 0;
	bool has_even_rows_ = false;
	int64_t columns_ = 0;
	bool has_even_columns_ = false;
	int64_t middle_column_ = 0;

	int64_t FindStablePosition(int64_t start_index, int64_t start_row) const;
	int64_t GetDistance(int64_t index) const;
	int GetMaxIterations(int64_t column, int64_t starting_row) const;
};
