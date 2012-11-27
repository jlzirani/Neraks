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

#ifndef __STASK_HPP__
#define __STASK_HPP__

struct STask
{
	unsigned int m_uiOffset;
	unsigned int m_uiPeriod;
	unsigned int m_uiDeadline;
	unsigned int m_uiWCET;
};

std::ostream &operator<<(std::ostream &f_strOut, const STask &f_csTask);
std::istream &operator>>(std::istream &f_strIn, STask &f_sTask);

std::ostream& operator<<(std::ostream &f_ostrOut, const std::vector<STask> &f_cvecTask);

std::vector<STask> loadTasks(const char *fc_cstrFilePath);

#endif
