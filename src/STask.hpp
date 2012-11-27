#include <iostream>
#include <vector>

#ifndef __STASK_HPP__
#define __STASK_HPP__

struct STask
{
	unsigned int m_uiOffset;
	unsigned int m_uiPeriod;
	unsigned int m_uiDeadline;
	unsigned int m_uiWCET;
};

std::ostream &operator<<(std::ostream &f_strOut, const STask &f_csTask);
std::istream &operator>>(std::istream &f_strIn, STask &f_sTask);

std::ostream& operator<<(std::ostream &f_ostrOut, const std::vector<STask> &f_cvecTask);

std::vector<STask> loadTasks(const char *fc_cstrFilePath);

#endif
