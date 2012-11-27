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

#include "CSimulator.hpp"
#include "helper.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>

void CSimulator::init(unsigned int f_uiNbrProc, unsigned int f_uiK)
{
	// Reseting all variables and vectors

	m_bFeasible = true;	
	m_uiInternalTime = 0;
	m_uiMaxTime = 1;
	m_vecPassive.clear();
	m_vecActiveProc.clear();
	m_vecWaitJob.clear();
	m_vecIdleProc.clear();
	m_vecStatProc.clear();
	m_uiNbrPreemption = 0;
	m_uiNbrMigration = 0;
	
	unsigned int uiMaxOffset = 0;

	sort(m_vecsTask.begin(), m_vecsTask.end(), compareByUtilization);

	for(unsigned int i =0; i < m_vecsTask.size(); ++i)
	{
		uiMaxOffset = std::max(uiMaxOffset, m_vecsTask[i].m_uiOffset);
		m_uiMaxTime = lcm( m_vecsTask[i].m_uiPeriod, m_uiMaxTime );
		m_vecPassive.push_back(createJobFromTask(m_vecsTask[i], i < f_uiK-1));
	}

	m_uiMaxTime *= 2;
	m_uiMaxTime += uiMaxOffset;

	for(unsigned int i = 0; i < f_uiNbrProc; ++i)
	{
		SProc sNewProc;
		sNewProc.m_uiProcId = i+1;
		sNewProc.m_uiIdle = 0;
		m_vecIdleProc.push_back(sNewProc);
	}

	make_heap( m_vecPassive.begin(), m_vecPassive.end(), compareByStartingTime);	
	make_heap( m_vecActiveProc.begin(), m_vecActiveProc.end(), compareByEDFKPrioirty);
}

void CSimulator::pushJobToSystem()
{
	//pop event and push to active
	while( m_vecPassive.front().m_uiStart == m_uiInternalTime )
	{
		// Pushing the job on the system
		m_vecWaitJob.push_back(m_vecPassive.front());
		SJob sPassiveJob = m_vecPassive.front();

		// updating the job and re-pushing it on the passive vector.

		pop_heap (m_vecPassive.begin(),m_vecPassive.end(), compareByStartingTime); m_vecPassive.pop_back();
		sPassiveJob.m_uiStart += sPassiveJob.m_psTask->m_uiPeriod;
		sPassiveJob.m_uiDeadline += sPassiveJob.m_psTask->m_uiPeriod;
		m_vecPassive.push_back(sPassiveJob); push_heap(m_vecPassive.begin(),m_vecPassive.end(), compareByStartingTime);
	}
}

void CSimulator::pushFirstWaitJobToAct( SProc &f_sCurrProc )
{
	f_sCurrProc.m_sCurrJob = m_vecWaitJob.front();

	if(f_sCurrProc.m_sCurrJob.m_uiAssignedProc != 0 && f_sCurrProc.m_sCurrJob.m_uiAssignedProc != f_sCurrProc.m_uiProcId)
		++m_uiNbrMigration;

	f_sCurrProc.m_sCurrJob.m_uiAssignedProc = f_sCurrProc.m_uiProcId;

	m_vecWaitJob.erase(m_vecWaitJob.begin());
	m_vecActiveProc.push_back(f_sCurrProc);
	push_heap(m_vecActiveProc.begin(), m_vecActiveProc.end(), compareByEDFKPrioirty);
}

void CSimulator::reorganizeSystem()
{
	sort(m_vecWaitJob.begin(), m_vecWaitJob.end(), compareByEDFKPriority);
	sort_heap(m_vecActiveProc.begin(), m_vecActiveProc.end(), compareByEDFKPrioirty);

	while(!m_vecIdleProc.empty() && !m_vecWaitJob.empty())
	{
		SProc sCurrProc = m_vecIdleProc.back(); m_vecIdleProc.pop_back();
		pushFirstWaitJobToAct(sCurrProc);
	}

	while( !m_vecWaitJob.empty() && compareByEDFKPriority( m_vecWaitJob.front(), m_vecActiveProc.back().m_sCurrJob) )
	{
		++m_uiNbrPreemption;
		SProc sCurrProc = m_vecActiveProc.back(); m_vecActiveProc.pop_back();
		SJob sPreemptJob = sCurrProc.m_sCurrJob;
		
		pushFirstWaitJobToAct(sCurrProc);
		
		m_vecWaitJob.push_back(sPreemptJob);
		sort(m_vecWaitJob.begin(), m_vecWaitJob.end(), compareByEDFKPriority);
	}
}

unsigned int CSimulator::getDeltaTime()
{
	unsigned int uiDTime = m_vecPassive.front().m_uiStart - m_uiInternalTime;
	for(VecProc::iterator it = m_vecActiveProc.begin(); it != m_vecActiveProc.end(); ++it)
		uiDTime = std::min(uiDTime, (*it).m_sCurrJob.m_uiRemCost);
	return uiDTime;
}

void CSimulator::updateJobs(unsigned int f_uiDTime)
{
	for(VecProc::iterator it = m_vecActiveProc.begin(); it != m_vecActiveProc.end(); )
	{
		SJob &sCurrJob = (*it).m_sCurrJob; 
		
		m_bFeasible &= sCurrJob.m_uiDeadline >= m_uiInternalTime + f_uiDTime;
		
		sCurrJob.m_uiRemCost -= f_uiDTime;
		
		if(sCurrJob.m_uiRemCost == 0)
		{
			m_vecIdleProc.push_back(*it);
			it = m_vecActiveProc.erase(it);
		}
		else
			++it;
	}
}

void CSimulator::updateIdleProc(unsigned int f_uiDTime)
{
	for(VecProc::iterator it = m_vecIdleProc.begin(); it != m_vecIdleProc.end(); ++it)
		(*it).m_uiIdle += f_uiDTime;
}

void CSimulator::simulate(unsigned int f_uiNbrProc, unsigned int f_uiK)
{
	m_uiNbrCores = f_uiNbrProc;
	init(f_uiNbrProc, f_uiK);

	m_uiInternalTime = m_vecPassive.front().m_uiStart;

	while( m_bFeasible && m_uiInternalTime < m_uiMaxTime )
	{
		unsigned int uiDTime = 0;
	
		pushJobToSystem();
		reorganizeSystem();

		uiDTime = getDeltaTime();
		
		updateIdleProc(uiDTime);

		updateJobs(uiDTime);

		m_uiInternalTime += uiDTime;
	}
	
	m_vecStatProc.insert(m_vecStatProc.end(), m_vecActiveProc.begin(), m_vecActiveProc.end());
	m_vecStatProc.insert(m_vecStatProc.end(), m_vecIdleProc.begin(), m_vecIdleProc.end());

	setStatisticalResult();
}

void CSimulator::setStatisticalResult()
{
	m_uiTotIdleTime = 0;
	m_uiMaxIdleTime = 0;
	m_uiMinIdleTime = m_vecStatProc.front().m_uiIdle;
	m_fAvgIdleTime = 0;
	
	for(VecProc::iterator it = m_vecStatProc.begin(); it != m_vecStatProc.end(); ++it)
	{
		m_uiTotIdleTime += (*it).m_uiIdle;
		m_uiMaxIdleTime = std::max(m_uiMaxIdleTime, (*it).m_uiIdle);
		m_uiMinIdleTime = std::min(m_uiMinIdleTime, (*it).m_uiIdle);
	}
	m_fAvgIdleTime = (float)m_uiTotIdleTime/(float)m_uiNbrCores;
}

std::ostream& operator<<(std::ostream &f_ostrOut, const CSimulator &fc_cSimulator)
{
	f_ostrOut 	<< "schedulable : " ;
	if(fc_cSimulator.isSchedulable())
		f_ostrOut << "True";
	else
		f_ostrOut << "False";
	f_ostrOut	<< std::endl 
			<< "Nbr of Cores : " << fc_cSimulator.getNbrCores() << std::endl 
			<< "Internal Time cnt : " << fc_cSimulator.getInternalTime() << std::endl
			<< "Study Interval : " << fc_cSimulator.getMaxTime() <<std::endl 
			<< "Nbr of preemptions : " << fc_cSimulator.getNbrPreemption() <<std::endl
			<< "Nbr of migrations : " << fc_cSimulator.getNbrMigration() << std::endl 
			//<< "Min idle time : "	<< fc_cSimulator.getMinIdleTime() << std::endl
			//<< "Max idle time : " << fc_cSimulator.getMaxIdleTime() << std::endl 
			//<< "Avg idle time : " << fc_cSimulator.getAvgIdleTime() << std::endl 
			<< "Tot idle time : " << fc_cSimulator.getTotIdleTime();
	return f_ostrOut;
}
