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

