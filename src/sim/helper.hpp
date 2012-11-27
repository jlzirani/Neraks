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

#ifndef __HELPER_HPP__
#define __HELPER_HPP__

#include "SJob.hpp"
#include "../STask.hpp"
#include "SProc.hpp"

int gcd(unsigned int a,unsigned int b);
int lcm(unsigned int a,unsigned int b);

bool compareByUtilization(const STask &fc_sTaskA, const STask &fc_sTaskB);
bool compareByStartingTime(const SJob &fc_sJob1, const SJob &fc_sJob2);
bool compareByEDFKPriority(const SJob &fc_sJobA, const SJob &fc_sJobB);

bool compareByEDFKPrioirty(const SProc &fc_sProcA, const SProc &fc_sProcB);
SJob createJobFromTask(STask &f_sTask, bool f_bPriority);


#endif
