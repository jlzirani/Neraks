#include "CArgAnalyzer.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline bool bStrCompar(const char *f_cstrA, const char *f_cstrB, int f_iSize)
{
	return strncmp(f_cstrA, f_cstrB, f_iSize) == 0;
}

void CArgAnalyzer::showHelp(const char *f_ccstrProgName)
{
	std::cout << "usage: " << f_ccstrProgName << " [-o output file] [-u usage] [-n nbr tasks] | [-h|--help] " << std::endl
		<< std::endl << "Description" << std::endl
		<< "-o : Redirect the output to a file." << std::endl
		<< "-u : Set the usage target. The default value is 68." << std::endl
		<< "-n : Set the number of task. The default value is 10." << std::endl
		<< "-h|--help : display this text." << std::endl;	
	exit(0);
}

void CArgAnalyzer::analyze(int f_iIndex, char *f_pcstrArg[] )
{
	const char *ccstrCurArg = f_pcstrArg[f_iIndex];


        if( bStrCompar(ccstrCurArg,"-o", 2) )
        {
		m_pstrFile = new std::ofstream(f_pcstrArg[++f_iIndex]);
                std::cout.rdbuf(m_pstrFile->rdbuf());
        }
	if( bStrCompar(ccstrCurArg, "-u", 2) )
	{
		m_iUtilization = atoi(f_pcstrArg[++f_iIndex]);
	}
	if( bStrCompar(ccstrCurArg, "-n", 2) )
	{
		m_iNbrTasks = atoi(f_pcstrArg[++f_iIndex]);
	}
	if( f_iIndex == 1 && (bStrCompar(ccstrCurArg, "-h", 2) || bStrCompar(ccstrCurArg, "--help", 6)) )
	{
		showHelp(f_pcstrArg[0]);
	}
}

CArgAnalyzer::~CArgAnalyzer()
{
	if( m_pstrFile != 0)
	{
		m_pstrFile->close();
		delete m_pstrFile;
	}
	m_pstrFile = 0;
}

CArgAnalyzer::CArgAnalyzer( int f_iArg, char *f_pcstrArg[] ) : m_pstrFile(0), m_iUtilization(68), m_iNbrTasks(10)
{
	

        for(int i = 1; i < f_iArg; ++i)
        {
                analyze(i, f_pcstrArg);
        }
}
