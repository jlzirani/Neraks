#include "SGenerator.hpp"
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int g_cMaxOffset = 100;
const int g_cMaxCost = 100;
const int gc_iMaxPeriod = 100;

int g_iRandTime = time(NULL);

STask createTask(int f_iPeriod, int f_iWCET)
{
	STask newTask;

	newTask.m_uiOffset = rand() % g_cMaxOffset;
	newTask.m_uiPeriod = f_iPeriod;
	newTask.m_uiWCET = f_iWCET;
	newTask.m_uiDeadline = newTask.m_uiWCET;
	
	if(f_iWCET != f_iPeriod)
		newTask.m_uiDeadline += ( rand() % (newTask.m_uiPeriod - newTask.m_uiWCET) );
	
	return newTask;
}

std::vector<int> generateTaskRepartition(int f_iUtil, unsigned f_iNbrTask)
{
	std::vector<int> veciRep;

	srand ( ++g_iRandTime );

	while(veciRep.empty())
	{	
		while(veciRep.size() < f_iNbrTask-1)
		{
			int iPoint = (rand() % (f_iUtil-1)) +1;
			if(std::find(veciRep.begin(), veciRep.end(), iPoint) == veciRep.end())
				veciRep.push_back( iPoint );
		}

		veciRep.push_back(0); // this element permits to use vec[1]-vec[0]
		veciRep.push_back(f_iUtil); // this element represents the last segment
		
		std::sort( veciRep.begin(), veciRep.end() ); 

		for(unsigned i = 1; i < veciRep.size(); ++i)
			if(veciRep[i] - veciRep[i-1] > 100)
				veciRep.clear(); // the solution has a problem and we will regenate one
	}	
	return veciRep;
}

std::vector<STask> generateVecTask(int f_iUtil, unsigned f_uiNbrTask)
{
	std::vector<STask> vecsResult;
	std::vector<int> veciRep = generateTaskRepartition(f_iUtil, f_uiNbrTask);
	
	float fUtilization=0;
	for(std::vector<int>::iterator it = veciRep.begin()+1; it+1 != veciRep.end(); ++it)
	{
		int iPeriod = (((rand() % gc_iMaxPeriod)/10)+1)*10;
		int iCost = std::max(1, ((*it - *(it-1)) * iPeriod)/100);
		fUtilization += ((float) iCost/ (float) iPeriod)*100;
		// int iCost = (((rand() % g_cMaxCost)/10)+1)*10;
		// int iPeriod = ceil( (double)(iCost*100) / (double)(*it - *(it-1)) );

		vecsResult.push_back(createTask( iPeriod, iCost ));
	}
	int iCost = 10;
	int iPeriod = ceil((float) (iCost * 10) / (float)(f_iUtil - fUtilization )) *10;
	vecsResult.push_back( createTask( iPeriod, iCost ));	

	return vecsResult;
}

std::vector<STask> generate(int f_iUtil, unsigned f_uiNbrTask)
{
	std::vector<STask> vecTask;
	do
	{
		vecTask = generateVecTask(f_iUtil, f_uiNbrTask);
	}while( vecTask.back().m_uiPeriod > 5*gc_iMaxPeriod );

	return vecTask;
}
