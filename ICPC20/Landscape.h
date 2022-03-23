#pragma once

#include <vector>

#include "Problem.h"

// Time
// Algorithm 15m
// Implementation 1h
// Performance optimization 1.5h
// Fix for large values 15m
// Cleanup 15m

// Note:
// Got stuck on performance optimization again, took a look at the submissions for inspiration, which led me
// to the solution of storing changes as velocity and acceleration deltas

struct Modification
{
	char operation;
	int start;
	int end;
};

class Landscape final :
    public Problem
{
public:
	std::string Solve(const std::string& input) override;

	std::string GetName() const override
	{
		return "landscape";
	}
	
	bool ShouldShowOutput() const override
	{
		return false;
	}

private:
	std::vector<int64_t> deltas_;
	std::vector<int64_t> acc_deltas_;

	void HandleModification(const Modification& mod);
	Modification ParseModification(const std::string& line) const;
	void ApplyRaise(int start, int end);
	void ApplyDepress(int start, int end);
	void ApplyHill(int start, int end);
	void ApplyValley(int start, int end);
	void AddLinearChange(int start, int end, bool is_hill);
};
