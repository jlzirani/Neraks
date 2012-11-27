#include <iostream>
#include <fstream>


#ifndef __CARGANALYZER_HPP__
#define __CARGANALYZER_HPP__

class CArgAnalyzer
{
	std::ofstream *m_pstrFile;
	unsigned int m_iUtilization, m_iNbrTasks;


	void analyze( int f_iIndex, char *f_pcstrArg[]);
	void showHelp(const char *f_ccstrProgName);
public:
	CArgAnalyzer(int f_iNbrArg, char *f_pcstrArg[] );
	~CArgAnalyzer();

	inline unsigned int getUtilization() { return m_iUtilization; }
	inline unsigned int getNbrTasks() { return m_iNbrTasks; }
};


#endif

