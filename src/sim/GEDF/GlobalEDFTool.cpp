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

#include "GlobalEDFTool.hpp"
#include <algorithm>
#include <cmath>

int calculateNbrProc( const std::vector<STask> &fc_vecTask )
{
	unsigned int iResult = fc_vecTask.size();

	float fMaxUtil = 0;
	float fTotUtil = 0;

	for(std::vector<STask>::const_iterator it = fc_vecTask.begin(); it != fc_vecTask.end(); ++it)
	{
		float fCurUtil = (float)(*it).m_uiWCET/ (float)(*it).m_uiPeriod;
		fTotUtil += fCurUtil;
		fMaxUtil = std::max(fMaxUtil, fCurUtil);
	}

	iResult = std::min<const float>(iResult, ceil( (fTotUtil-fMaxUtil) / (1.f - fMaxUtil) ) );

	return std::max<const float>(1,iResult);
}

