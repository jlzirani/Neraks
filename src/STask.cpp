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

#include "STask.hpp"
#include <fstream>

std::ostream& operator<<(std::ostream &f_ostrOut, const STask &f_csTask)
{
	f_ostrOut << f_csTask.m_uiOffset << "\t" 
		<< f_csTask.m_uiPeriod << "\t" 
		<< f_csTask.m_uiDeadline << "\t" 
		<< f_csTask.m_uiWCET ;

	return f_ostrOut;
}

std::istream &operator>>(std::istream &f_strIn, STask &f_sTask)
{
	f_strIn >> f_sTask.m_uiOffset 
		>> f_sTask.m_uiPeriod 
		>> f_sTask.m_uiDeadline 
		>> f_sTask.m_uiWCET ;

	return f_strIn;
}

std::ostream& operator<<(std::ostream &f_ostrOut, const std::vector<STask> &f_cvecTask)
{
	for(std::vector<STask>::const_iterator it = f_cvecTask.begin(); it != f_cvecTask.end(); ++it)
		f_ostrOut << (*it) << std::endl;

	return f_ostrOut;
}

std::vector<STask> loadTasks(const char *fc_cstrFilePath)
{
	std::vector<STask> vecsTask;

	std::ifstream strIn(fc_cstrFilePath);

	while(!strIn.eof())
	{
		STask sNewTask = { 0,0,0,0 };
		strIn >> sNewTask;

		if(sNewTask.m_uiWCET != 0)
			vecsTask.push_back(sNewTask);
	}

	return vecsTask;
}


