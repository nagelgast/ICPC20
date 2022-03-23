#include "Cardiology.h"

#include "StringUtils.h"

std::string Cardiology::Solve(const std::string& input)
{
	const auto data = StringUtils::Split(input, ' ');

	rows_ = std::stoi(data[0]);
	middle_row_ = rows_ / 2;
	has_even_rows_ = rows_ % 2 == 0;

	columns_ = std::stoi(data[1]);
	has_even_columns_ = columns_ % 2 == 0;
	middle_column_ = columns_ / 2;

	int64_t best_stable_index = 0;
	int64_t best_pickup_column = 0;
	int64_t best_distance = INT64_MAX;
	for (auto col = 0; col < columns_; col++)
	{
		const auto start_index = col * rows_;

		// If the stable position found from both the start and end of the column match, we know that the column is stable
		const auto stable_index = FindStablePosition(start_index, 0);
		const auto stable_index_from_end = FindStablePosition(start_index, rows_ - 1);

		if (stable_index != stable_index_from_end)
		{
			continue;
		}

		const auto dist = GetDistance(stable_index);

		// Ignore columns with the same distance as the current best since the current is a lower column index
		if (dist < best_distance)
		{
			best_pickup_column = col;
			best_stable_index = stable_index;
			best_distance = dist;
		}
	}

	// Get the max iterations last, since it doesn't change which pickup column to choose
	auto max_iterations = 0;
	for (int row = 0; row < rows_; row++)
	{
		const auto current_max_iterations = GetMaxIterations(best_pickup_column, row);
		if (current_max_iterations > max_iterations)
		{
			max_iterations = current_max_iterations;
		}
	}

	const auto row = best_stable_index / columns_;
	const auto column = best_stable_index % columns_;

	// Adding one to the outputs since the answer expects 1-indexed counting
	return
		std::to_string(best_pickup_column + 1) + " " +
		std::to_string(row + 1) + " " +
		std::to_string(column + 1) + " " +
		std::to_string(max_iterations);
}

int64_t Cardiology::FindStablePosition(const int64_t start_index, const int64_t start_row) const
{
	int64_t current_row = start_row;
	int64_t old_row = -1;
	int64_t current_index = -1;
	while (current_row != old_row)
	{
		old_row = current_row;
		current_index = start_index + current_row;
		current_row = current_index / columns_;
	}

	return current_index;
}

int64_t Cardiology::GetDistance(const int64_t index) const
{
	const auto row = index / columns_;
	auto ver_dist = row - middle_row_;
	if (has_even_rows_ && row < middle_row_)
	{
		ver_dist++;
	}

	const auto column = index % columns_;
	auto hor_dist = abs(column - middle_column_);
	if (has_even_columns_ && column < middle_column_)
	{
		hor_dist--;
	}

	return abs(hor_dist) + abs(ver_dist);
}

int Cardiology::GetMaxIterations(const int64_t column, const int64_t starting_row) const
{
	auto current_row = starting_row;
	int64_t old_row = -1;
	int iteration_counter = 0;
	while (current_row != old_row)
	{
		old_row = current_row;
		const auto current_index = column * rows_ + current_row;
		current_row = current_index / columns_;
		iteration_counter++;
	}

	return iteration_counter;
}
