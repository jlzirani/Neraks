#include "SStatistic.hpp"

SStatistic createStatFromSim( const CSimulator &fc_cSim )
{
	SStatistic sStat;

	sStat.m_uiNbrCore = fc_cSim.getNbrCores() ;
	sStat.m_uiTotIdleTime = fc_cSim.getTotIdleTime();
	sStat.m_uiPreemptions = fc_cSim.getNbrPreemption();
	sStat.m_uiMigrations = fc_cSim.getNbrMigration();

	return sStat;
}
