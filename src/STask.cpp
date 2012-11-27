#include "STask.hpp"
#include <fstream>

std::ostream& operator<<(std::ostream &f_ostrOut, const STask &f_csTask)
{
	f_ostrOut << f_csTask.m_uiOffset << "\t" 
		<< f_csTask.m_uiPeriod << "\t" 
		<< f_csTask.m_uiDeadline << "\t" 
		<< f_csTask.m_uiWCET ;

	return f_ostrOut;
}

std::istream &operator>>(std::istream &f_strIn, STask &f_sTask)
{
	f_strIn >> f_sTask.m_uiOffset 
		>> f_sTask.m_uiPeriod 
		>> f_sTask.m_uiDeadline 
		>> f_sTask.m_uiWCET ;

	return f_strIn;
}

std::ostream& operator<<(std::ostream &f_ostrOut, const std::vector<STask> &f_cvecTask)
{
	for(std::vector<STask>::const_iterator it = f_cvecTask.begin(); it != f_cvecTask.end(); ++it)
		f_ostrOut << (*it) << std::endl;

	return f_ostrOut;
}

std::vector<STask> loadTasks(const char *fc_cstrFilePath)
{
	std::vector<STask> vecsTask;

	std::ifstream strIn(fc_cstrFilePath);

	while(!strIn.eof())
	{
		STask sNewTask = { 0,0,0,0 };
		strIn >> sNewTask;

		if(sNewTask.m_uiWCET != 0)
			vecsTask.push_back(sNewTask);
	}

	return vecsTask;
}


