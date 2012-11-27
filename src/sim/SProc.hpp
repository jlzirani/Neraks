#ifndef __SPROC_HPP__
#define __SPROC_HPP__

struct SProc // processors
{
	unsigned int m_uiProcId;
	SJob m_sCurrJob;

	unsigned int m_uiIdle;
};

#endif