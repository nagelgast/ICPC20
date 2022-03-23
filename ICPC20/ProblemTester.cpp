#include "ProblemTester.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Problem.h"

ProblemTester::ProblemTester(std::string root) : root_(std::move(root))
{
}

void ProblemTester::TestProblem(Problem& problem, const int test_count) const
{
	const bool show_output = problem.ShouldShowOutput();
	const auto problem_name = problem.GetName();
	std::cout << "Testing '" + problem_name + "' for " << test_count << " tests\n-----\n";
	for (auto i = 1; i <= test_count; i++)
	{
		std::cout << "Test " << i << ": ";
		const auto input = LoadInput(problem, i);
		const auto result = problem.Solve(input);
		const auto answer = LoadSolution(problem, i);
		if (result == answer)
		{
			std::cout << "Correct! ";
		}
		else
		{
			std::cout << "Wrong!";
			if(show_output)
			{
				std::cout << " Expected: " << answer << " - ";
			}
		}

		if(show_output)
		{
			std::cout << "Result: " << result;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

std::string ProblemTester::LoadInput(const Problem& problem, const int index) const
{
	return LoadFile(GetProblemPath(problem.GetName()) + GetIndex(index, problem.GetFileDigits()) + input_ext_);
}

std::string ProblemTester::LoadSolution(const Problem& problem, const int index) const
{
	return LoadFile(GetProblemPath(problem.GetName()) + GetIndex(index, problem.GetFileDigits()) + answer_ext_);
}

std::string ProblemTester::GetProblemPath(const std::string& problem) const
{
	return root_ + problem + subfolder_;
}

std::string ProblemTester::LoadFile(const std::string& path)
{
	const std::ifstream t(path);
	std::stringstream buffer;
	buffer << t.rdbuf();
	auto text = buffer.str();
	TrimTrailingNewline(text);
	return text;
}

std::string ProblemTester::GetIndex(const int index, const int digits)
{
	char index_str[10];
	const auto format = "%0" + std::to_string(digits) + "d";
	snprintf(index_str, digits+1, format.c_str(), index);
	return index_str;
}

void ProblemTester::TrimTrailingNewline(std::string& text)
{
	if (!text.empty() && text[text.length() - 1] == '\n')
	{
		text.erase(text.length() - 1);
	}
}
