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
