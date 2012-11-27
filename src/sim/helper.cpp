#include "helper.hpp"

int gcd(unsigned int a,unsigned int b)
{
    // We have no doubt about this inf loop :D
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int lcm(unsigned int a,unsigned int b)
{
    int temp = gcd(a, b);

    return temp ? (a / temp * b) : 0;
}

bool compareByUtilization(const STask &fc_sTaskA, const STask &fc_sTaskB)
{
	return	( (float)fc_sTaskA.m_uiWCET/(float)fc_sTaskA.m_uiPeriod ) > 
		( (float)fc_sTaskB.m_uiWCET/(float)fc_sTaskB.m_uiPeriod ); 
}

bool compareByStartingTime(const SJob &fc_sJob1, const SJob &fc_sJob2)
{
	return fc_sJob1.m_uiStart > fc_sJob2.m_uiStart;
}

bool compareByEDFKPriority(const SJob &fc_sJobA, const SJob &fc_sJobB)
{
	if( fc_sJobA.m_bPriority != fc_sJobB.m_bPriority)
		return fc_sJobA.m_bPriority;

	return fc_sJobA.m_uiDeadline < fc_sJobB.m_uiDeadline;
}

bool compareByEDFKPrioirty(const SProc &fc_sProcA, const SProc &fc_sProcB)
{
	return compareByEDFKPriority(fc_sProcA.m_sCurrJob,fc_sProcB.m_sCurrJob);
}

SJob createJobFromTask(STask &f_sTask, bool f_bPriority)
{
	SJob sNewJob;

	sNewJob.m_psTask = &f_sTask;
	sNewJob.m_uiStart = f_sTask.m_uiOffset;
	sNewJob.m_uiDeadline = f_sTask.m_uiOffset + f_sTask.m_uiDeadline;
	sNewJob.m_uiRemCost = f_sTask.m_uiWCET;
	sNewJob.m_bPriority = f_bPriority;
	sNewJob.m_uiAssignedProc = 0;

	return sNewJob;
}
