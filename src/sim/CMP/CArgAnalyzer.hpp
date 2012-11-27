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
#include <fstream>

#ifndef __CARGANALYZER_HPP__
#define __CARGANALYZER_HPP__

class CArgAnalyzer
{
	std::ofstream *m_pstrFile;
	unsigned int m_iUtilization, m_iNbrTasks, m_iNbrTest;

	void analyze( int f_iIndex, char *f_pcstrArg[]);
	void showHelp(const char *f_ccstrProgName);
public:
	CArgAnalyzer(int f_iNbrArg, char *f_pcstrArg[] );
	~CArgAnalyzer();

	inline unsigned int getUtilization() { return m_iUtilization; }
	inline unsigned int getNbrTasks() { return m_iNbrTasks; }
	inline unsigned int getNbrTest() { return m_iNbrTest; }
};


#endif

