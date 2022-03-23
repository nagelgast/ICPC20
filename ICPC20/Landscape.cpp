#include "Landscape.h"

#include "StringUtils.h"

// Needed for changes at the end of the graph
constexpr auto kTrailingMargin = 2;

std::string Landscape::Solve(const std::string& input)
{
	const auto lines = StringUtils::Split(input);
	const auto point_count_str = StringUtils::Split(lines[0], ' ')[0];
	const auto point_count = std::stoi(point_count_str);
	acc_deltas_ = std::vector<int64_t>(point_count + kTrailingMargin);
	deltas_ = std::vector<int64_t>(point_count + kTrailingMargin);

	for (size_t i = 1; i < lines.size(); i++)
	{
		auto line = lines[i];
		const auto mod = ParseModification(line);
		HandleModification(mod);
	}

	// Parse point list to result string
	std::string result;
	int64_t acc = 0;
	int64_t vel = 0;
	for (auto i = 0; i < point_count; i++)
	{
		acc += acc_deltas_[i];
		vel += deltas_[i] + acc;
		result += std::to_string(vel) + "\n";
	}
	result.pop_back(); // Remove trailing newline
	return result;
}

void Landscape::HandleModification(const Modification& mod)
{
	switch (mod.operation)
	{
	case 'R':
		ApplyRaise(mod.start, mod.end);
		break;
	case 'D':
		ApplyDepress(mod.start, mod.end);
		break;
	case 'H':
		ApplyHill(mod.start, mod.end);
		break;
	case 'V':
		ApplyValley(mod.start, mod.end);
		break;
	default:
		break;
	}
}

Modification Landscape::ParseModification(const std::string& line) const
{
	const auto params = StringUtils::Split(line, ' ');
	return Modification{ params[0][0], std::stoi(params[1]), std::stoi(params[2]) };
}

void Landscape::ApplyRaise(const int start, const int end)
{
	deltas_[start - 1]++;
	deltas_[end]--;
}

void Landscape::ApplyDepress(const int start, const int end)
{
	deltas_[start - 1]--;
	deltas_[end]++;
}

void Landscape::ApplyHill(const int start, const int end)
{
	AddLinearChange(start, end, true);
}

void Landscape::ApplyValley(const int start, const int end)
{
	AddLinearChange(start, end, false);
}

void Landscape::AddLinearChange(const int start, const int end, const bool is_hill)
{
	const auto dir = is_hill ? 1 : -1;
	acc_deltas_[start - 1] += dir;
	acc_deltas_[end + 1] += dir;

	const auto mid_left = (end + start) / 2;
	const auto mid_right = (end + start + 1) / 2;

	acc_deltas_[mid_left] -= dir;
	acc_deltas_[mid_right] -= dir;
}
