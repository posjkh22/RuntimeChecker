
#ifndef MONITORINGCODEGENERATOR
#define MONITORINGCODEGENERATOR

#include "Analyzer.hpp"

typedef std::vector<CompactBBInfo* > CompactBBInfoList;


class MonitoringCodeGenerator
{

private:
	Analyzer* p_Analyzer;
	

public:
	MonitoringCodeGenerator();

public:
	bool TakeAnalysisResults(Analyzer* );

public:
	bool run();

private:
	bool Make_Initializer(CompactBBInfoList* );


};


#endif
