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

#include "../STask.hpp"
#ifndef __SJOB_HPP__
#define __SJOB_HPP__

struct SJob
{
	STask *m_psTask;
	unsigned int m_uiStart;
	unsigned int m_uiDeadline;
	unsigned int m_uiRemCost; // Remaining Cost
	unsigned int m_uiAssignedProc;
	bool m_bPriority;
};

#endif
