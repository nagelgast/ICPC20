#pragma once
#include "Problem.h"

// Time
// Algorithm 5m
// Input parsing 10m
// Implementation 20m
// Performance optimization 45m

struct Phone;

class Opportunity final :
    public Problem
{
public:
	std::string Solve(const std::string& input) override;

	long long GetOpportunityCost(const Phone& p, const Phone& comp_p) const;

	std::string GetName() const override
	{
		return "opportunity";
	}
};

