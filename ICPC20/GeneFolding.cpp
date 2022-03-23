#include "GeneFolding.h"

std::string GeneFolding::Solve(const std::string& input)
{
	sequence_ = input;

	for (size_t char_index = 1; char_index < sequence_.size(); char_index++)
	{
		if (sequence_[char_index] == sequence_[char_index - 1])
		{
			check_indices_.push_back(char_index - 1);
		}

		const bool has_fold = CheckForFold(char_index);
		if (has_fold)
		{
			const auto fold_size = (char_index + 1) / 2;
			sequence_ = FoldLeft(sequence_, fold_size);
			check_indices_.clear();
			char_index = 0;
		}

		if (char_index == sequence_.size() - 1 && !check_indices_.empty())
		{
			const auto fold_size = (sequence_.size() - check_indices_[0]) / 2;
			sequence_ = FoldRight(sequence_, fold_size);
			check_indices_.clear();
			char_index = 0;
		}
	}

	return std::to_string(sequence_.size());
}

bool GeneFolding::CheckForFold(const unsigned int char_index)
{
	const auto current_char = sequence_[char_index];
	for (size_t i = 0; i < check_indices_.size(); i++)
	{
		const auto check_index = check_indices_[i];
		if (sequence_[check_index] == current_char)
		{
			if (check_index == 0)
			{
				return true;
			}

			check_indices_[i]--;
		}
		else
		{
			check_indices_.erase(check_indices_.begin() + i);
			i--;
		}
	}

	return false;
}

std::string GeneFolding::FoldLeft(const std::string& input, const unsigned int length)
{
	return input.substr(length, input.size() - length);
}

std::string GeneFolding::FoldRight(const std::string& input, const unsigned int length)
{
	return input.substr(0, input.size() - length);
}
