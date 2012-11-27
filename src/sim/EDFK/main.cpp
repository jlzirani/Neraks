#include <iostream>
#include <vector>
#include "../../STask.hpp"
#include "../CSimulator.hpp"
#include "EDFKTool.hpp"
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

	unsigned int uiK = 0, uiMMin = 0;
	calculateK( vecTask, uiMMin, uiK ); // calculate the number of processors and the K

	CSimulator cSimulator( vecTask ); // creating the simulator

	cSimulator.simulate( uiMMin, uiK ); // run the simulation

	std::cout << cSimulator << std::endl;

	return 0;
}

