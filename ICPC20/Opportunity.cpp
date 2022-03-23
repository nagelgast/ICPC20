#include "Opportunity.h"

#include <algorithm>

#include "StringUtils.h"

struct Phone
{
	int price;
	int perf;
	int ux;
};

std::string Opportunity::Solve(const std::string& input)
{
	// const auto test_input = "4\n20 5 5\n5 20 5\n5 5 20\n10 10 10";
	// const auto lines = StringUtils::Split(test_input);
	const auto lines = StringUtils::Split(input);

	const auto first_line = lines[0];
	const auto phone_count = std::stoi(first_line);

	std::vector<Phone> phones;

	// Construct phone list
	for (auto i = 1; i <= phone_count; i++)
	{
		const auto line = StringUtils::Split(lines[i], ' ');
		const auto price = std::stoi(line[0]);
		const auto perf = std::stoi(line[1]);
		const auto ux = std::stoi(line[2]);
		Phone phone{ price, perf, ux };
		phones.push_back(phone);
	}

	auto best_phone = INT_MAX;
	auto best_opp_cost = INT64_MAX;
	std::vector<long long> max_opp_costs(phone_count);
	for(auto i = 0; i < phone_count; i++)
	{
		auto max_opp_cost = max_opp_costs[i];

		// If the amount we start to compare with is already higher than our best phone so far, we can skip this phone
		if(max_opp_cost > best_opp_cost) continue;

		for(auto j = i; j < phone_count; j++)
		{
			// Not checking for self is fine, opportunity cost for that will always be zero
			// Calculating that once is probably cheaper than checking the index every time
			const auto& p1 = phones[i];
			const auto& p2 = phones[j];
			const auto opp_cost = GetOpportunityCost(p1, p2);
			const auto flipped_opp_cost = GetOpportunityCost(p2, p1);

			if(opp_cost > max_opp_cost)
			{
				max_opp_cost = opp_cost;
				if (max_opp_cost > best_opp_cost)
				{
					break;
				}
			}

			if(flipped_opp_cost > max_opp_costs[j])
			{
				max_opp_costs[j] = flipped_opp_cost;
			}

			// If this phone has a higher opportunity cost compared to the other one then this we can stop checking this phone
			if (flipped_opp_cost < opp_cost)
			{
				break;
			}
		}

		if(max_opp_cost < best_opp_cost)
		{
			best_opp_cost = max_opp_cost;
			best_phone = i+1;
		}
	}

	return std::to_string(best_opp_cost) + " " + std::to_string(best_phone);
}

long long Opportunity::GetOpportunityCost(const Phone& p, const Phone& comp_p) const
{
	return 0ll + std::max(comp_p.price - p.price, 0) + std::max(comp_p.perf - p.perf, 0) + std::max(comp_p.ux - p.ux, 0);
}
