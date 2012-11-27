#include "../CSimulator.hpp"

#ifndef __SSTATISTIC_HPP__
#define __SSTATISTIC_HPP__

struct SStatistic
{
	unsigned int m_uiNbrCore;
	unsigned int m_uiTotIdleTime;
	unsigned int m_uiPreemptions;
	unsigned int m_uiMigrations;
};

SStatistic createStatFromSim( const CSimulator &fc_cSim );


#endif
