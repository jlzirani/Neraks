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
#include "SJob.hpp"
#include "SProc.hpp"
#include <iostream>

#ifndef __SIMEDF_K_HPP__
#define __SIMEDF_K_HPP__

class CSimulator
{
	typedef std::vector<STask> VecTask;
	typedef std::vector<SJob> VecJob;
	typedef std::vector<SProc> VecProc;	

	VecTask m_vecsTask;	
	VecJob m_vecPassive;
	VecJob m_vecWaitJob; // active but there are no processor for them
	VecProc m_vecActiveProc, m_vecIdleProc;
	VecProc m_vecStatProc;
	
	unsigned int m_uiInternalTime;
	unsigned int m_uiMaxTime;


	// results values;
	unsigned int m_uiNbrPreemption;
	unsigned int m_uiNbrMigration;
	unsigned int m_uiNbrCores;
	unsigned int m_uiTotIdleTime;
	unsigned int m_uiMaxIdleTime;
	unsigned int m_uiMinIdleTime;
	float m_fAvgIdleTime;
	
	bool m_bFeasible;

	//Functions
	void init(unsigned int f_uiNbrProc, unsigned int f_uiK);
	void pushJobToSystem();
	void pushFirstWaitJobToAct( SProc &f_sCurrProc );
	void reorganizeSystem();
	unsigned int getDeltaTime();
	void updateJobs(unsigned int f_uiDTime);
	void updateIdleProc(unsigned int f_uiDTime);

	void setStatisticalResult();
	
public:
	CSimulator(): m_vecsTask(0) {}
	CSimulator(const VecTask &fc_vecTask): m_vecsTask(fc_vecTask) {}
	~CSimulator() {}

	void simulate(unsigned int f_uiNbrProc, unsigned int f_uiK = 1);

	// Results and statistical result;

	inline bool isSchedulable() const		{ return m_bFeasible; }
	inline unsigned int getNbrPreemption() const	{ return m_uiNbrPreemption; }
	inline unsigned int getNbrMigration() const	{ return m_uiNbrMigration; }
	inline unsigned int getNbrCores() const		{ return m_uiNbrCores; }
	inline unsigned int getTotIdleTime() const	{ return m_uiTotIdleTime; }
	inline unsigned int getMaxIdleTime() const	{ return m_uiMaxIdleTime; }
	inline unsigned int getMinIdleTime() const	{ return m_uiMinIdleTime; }
	inline float getAvgIdleTime() const		{ return m_fAvgIdleTime; }
	inline unsigned int getInternalTime() const	{ return m_uiInternalTime; }
	inline unsigned int getMaxTime() const		{ return m_uiMaxTime; }

};

std::ostream& operator<<(std::ostream &f_ostrOut, const CSimulator &fc_cSimulator);

#endif
