#include "Cardiology.h"
#include "GeneFolding.h"
#include "Landscape.h"
#include "Opportunity.h"
#include "ProblemTester.h"

const std::string kRoot = "C:/Users/Tom/Desktop/ICPC/";

int main()
{
    const auto tester = ProblemTester(kRoot);

    auto cardiology = Cardiology();
    tester.TestProblem(cardiology, 19);
    
    auto gene_folding = GeneFolding();
    tester.TestProblem(gene_folding, 9);
    
    auto landscape = Landscape();
    tester.TestProblem(landscape, 4);
    
    auto opportunity = Opportunity();
    tester.TestProblem(opportunity, 18);
}
