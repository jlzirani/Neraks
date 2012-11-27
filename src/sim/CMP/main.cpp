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

#include "CArgAnalyzer.hpp"
#include "../../STask.hpp"
#include "../../generator/SGenerator.hpp"
#include "../EDFK/EDFKTool.hpp"
#include "../GEDF/GlobalEDFTool.hpp"
#include "../CSimulator.hpp"
#include "SStatistic.hpp"


void showResult( const std::vector<SStatistic> &fc_vecEDFKStat, const std::vector<SStatistic> &fc_vecGEDFStat)
{
	SStatistic sEDFKStat = {0,0,0,0}, sGEDFStat = {0,0,0,0};

	for( std::vector<SStatistic>::const_iterator it = fc_vecEDFKStat.begin(); it != fc_vecEDFKStat.end(); ++it)
	{
		sEDFKStat.m_uiNbrCore +=  (*it).m_uiNbrCore;
		sEDFKStat.m_uiTotIdleTime +=  (*it).m_uiTotIdleTime;
		sEDFKStat.m_uiPreemptions +=  (*it).m_uiPreemptions;
		sEDFKStat.m_uiMigrations +=  (*it).m_uiMigrations;
	}

	if(!fc_vecEDFKStat.empty())
	{
		sEDFKStat.m_uiNbrCore /= fc_vecEDFKStat.size();
		sEDFKStat.m_uiTotIdleTime /=  fc_vecEDFKStat.size();
		sEDFKStat.m_uiPreemptions /=  fc_vecEDFKStat.size();
		sEDFKStat.m_uiMigrations /=  fc_vecEDFKStat.size();
	}

	for( std::vector<SStatistic>::const_iterator it = fc_vecGEDFStat.begin(); it != fc_vecGEDFStat.end(); ++it)
	{
		sGEDFStat.m_uiNbrCore +=  (*it).m_uiNbrCore;
		sGEDFStat.m_uiTotIdleTime +=  (*it).m_uiTotIdleTime;
		sGEDFStat.m_uiPreemptions +=  (*it).m_uiPreemptions;
		sGEDFStat.m_uiMigrations +=  (*it).m_uiMigrations;
	}

	if(!fc_vecGEDFStat.empty())
	{
		sGEDFStat.m_uiNbrCore /= fc_vecGEDFStat.size();
		sGEDFStat.m_uiTotIdleTime /=  fc_vecGEDFStat.size();
		sGEDFStat.m_uiPreemptions /=  fc_vecGEDFStat.size();
		sGEDFStat.m_uiMigrations /=  fc_vecGEDFStat.size();
	}


	std::cout << "\t\t\tEDFK\tGlobalEDF" << std::endl;
	std::cout << "Schedulable\t\t" << fc_vecEDFKStat.size() << "\t" << fc_vecGEDFStat.size() << std::endl;
	std::cout << "Avg nbr Core\t\t" << sEDFKStat.m_uiNbrCore << "\t" << sGEDFStat.m_uiNbrCore << std::endl;
	std::cout << "Avg Tot Idle\t\t" << sEDFKStat.m_uiTotIdleTime << "\t" << sGEDFStat.m_uiTotIdleTime << std::endl;
	std::cout << "Avg nbr of preemptions\t" << sEDFKStat.m_uiPreemptions << "\t" << sGEDFStat.m_uiPreemptions << std::endl;
	std::cout << "Avg nbr of migrations\t" << sEDFKStat.m_uiMigrations << "\t" << sGEDFStat.m_uiMigrations << std::endl;

}


int main(int argc, char *argv[])
{
	CArgAnalyzer cArg(argc, argv);

	std::vector<SStatistic> vecEDFKStat, vecGEDFStat;


	std::cout << "Utilization target : " << cArg.getUtilization() << std::endl;
	std::cout << "Nbr of tasks : " << cArg.getNbrTasks() << std::endl;
	std::cout << "Nbr of systems to test: " << cArg.getNbrTest() << std::endl;


	for(unsigned int i = 0 ; i < cArg.getNbrTest(); ++i)
	{
		std::vector<STask> vecTask = generate(cArg.getUtilization(), cArg.getNbrTasks());
		unsigned int uiEDFK = 0, uiEDFMMin = 0, uiGEDFNbrProc = 0;
		uiGEDFNbrProc = calculateNbrProc(vecTask);

		calculateK( vecTask, uiEDFMMin, uiEDFK );
	
		CSimulator cSimulator(vecTask);
		cSimulator.simulate(uiEDFK, uiEDFMMin);
		if(cSimulator.isSchedulable())
			vecEDFKStat.push_back(createStatFromSim(cSimulator));
		
		cSimulator.simulate(uiGEDFNbrProc);
		if(cSimulator.isSchedulable())
			vecGEDFStat.push_back(createStatFromSim(cSimulator));
	}

	showResult(vecEDFKStat, vecGEDFStat);

	return 0;
}

