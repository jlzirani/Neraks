#ifndef __HELPER_HPP__
#define __HELPER_HPP__

#include "SJob.hpp"
#include "../STask.hpp"
#include "SProc.hpp"

int gcd(unsigned int a,unsigned int b);
int lcm(unsigned int a,unsigned int b);

bool compareByUtilization(const STask &fc_sTaskA, const STask &fc_sTaskB);
bool compareByStartingTime(const SJob &fc_sJob1, const SJob &fc_sJob2);
bool compareByEDFKPriority(const SJob &fc_sJobA, const SJob &fc_sJobB);

bool compareByEDFKPrioirty(const SProc &fc_sProcA, const SProc &fc_sProcB);
SJob createJobFromTask(STask &f_sTask, bool f_bPriority);


#endif
