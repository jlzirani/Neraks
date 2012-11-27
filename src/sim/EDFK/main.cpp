/*
 This file is part of Neraks.
 
 Neraks is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Neraks is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 Copyright 2012 Cédric L && Jean-Luc Z
 */

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

