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

#include "EDFKTool.hpp"
#include "../helper.hpp"
#include <algorithm>
#include <cmath>


struct SMMin
{
	unsigned int m_uiMMin;
	unsigned int m_uiK;
};

bool compareByMMin(const SMMin &fc_sMMinA, const SMMin fc_sMMinB)
{
	return fc_sMMinA.m_uiMMin < fc_sMMinB.m_uiMMin;
} 

void calculateK( const std::vector<STask> &fc_vecTask, unsigned int &f_uiMMin, unsigned int &f_uiK )
{
	std::vector<STask> vecTask(fc_vecTask);
	sort(vecTask.begin(), vecTask.end(), compareByUtilization);

	float fTotUtil = 0;
	std::vector<SMMin> vecMMin;

	for(unsigned int i = vecTask.size(); i > 0; --i)
	{
		float fUtilization = (float) vecTask[i-1].m_uiWCET / (float) vecTask[i-1].m_uiPeriod;

		SMMin iResult;

		iResult.m_uiMMin = (i - 1) + ceil ( fTotUtil / (1.f - fUtilization) );
		iResult.m_uiK = i;		

		vecMMin.push_back( iResult );

		fTotUtil += fUtilization;
	}
	sort(vecMMin.begin(), vecMMin.end(), compareByMMin);

	f_uiMMin = vecMMin.front().m_uiMMin;
	f_uiK = vecMMin.front().m_uiK;
}