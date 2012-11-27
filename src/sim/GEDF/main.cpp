#include <iostream>
#include <vector>
#include "../../STask.hpp"
#include "../CSimulator.hpp"
#include "GlobalEDFTool.hpp"
#include <stdlib.h>

void showHelp(const char *fc_cstrProgName)
{
	std::cout << "usage :" << fc_cstrProgName << " file name" << std::endl;
	exit(0);
}

int main(int argc, char *argv[])
{
	if(argc != 2)
		showHelp(argv[0]);
	
	std::vector<STask> vecTask = loadTasks(argv[1]); // get the task list

	unsigned int uiNbrProc = calculateNbrProc(vecTask) ;
	
	CSimulator cSimulator( vecTask ); // creating the simulator

	cSimulator.simulate( uiNbrProc ); // run the simulation

	std::cout << cSimulator << std::endl;

	return 0;
}

