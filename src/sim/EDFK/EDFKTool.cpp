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