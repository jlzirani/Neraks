#include <iostream>
#include "CArgAnalyzer.hpp"
#include "SGenerator.hpp"

int main(int argc, char *argv[])
{
	CArgAnalyzer cArgAnalyzer(argc, argv);
	std::cout << generate(cArgAnalyzer.getUtilization(), cArgAnalyzer.getNbrTasks());
}

