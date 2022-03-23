#pragma once
#include <string>

// Time
// Input handling 15m
// Testing logic 15m

class Problem;

class ProblemTester
{
public:
	explicit ProblemTester(std::string root);

	void TestProblem(Problem& problem, int test_count) const;

private:
    const std::string root_;

    const std::string subfolder_ = "/data/secret/";
    const std::string input_ext_ = ".in";
    const std::string answer_ext_ = ".ans";

	std::string LoadInput(const Problem& problem, const int index) const;
	std::string LoadSolution(const Problem& problem, const int index) const;

	std::string GetProblemPath(const std::string& problem) const;
	static std::string LoadFile(const std::string& path);
	static std::string GetIndex(int index, int digits);
	static void TrimTrailingNewline(std::string& text);
};

