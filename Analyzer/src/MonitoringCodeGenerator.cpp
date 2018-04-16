

#include "MonitoringCodeGenerator.hpp"
#include <fstream>

MonitoringCodeGenerator::MonitoringCodeGenerator()
{


}

bool MonitoringCodeGenerator::TakeAnalysisResults(Analyzer* analyzer)
{
	p_Analyzer = analyzer;
	return true;
}

bool MonitoringCodeGenerator::run()
{
	if(Make_Initializer(p_Analyzer->getCompactBBInfoList()) != true)
	{
		std::cout << " -Make_Initializer fails" << std::endl;
		return false;
	}
	
	return true;
}


bool MonitoringCodeGenerator::Make_Initializer(CompactBBInfoList* BI)
{
	std::ofstream fout;
	fout.open("./MonitoringCodes/checker_initializer.cpp");

	fout << "#include \"CheckerAPIs.h\" " << std::endl << std::endl;
	fout << "Pathtree* generate_path_tree();" << std::endl;
	fout << "void add_basicblock(Pathtree* ,unsigned int, unsigned int, unsigned int, unsigned int);" << std::endl;


	fout << "extern Pathtree* p_pathtree;" << std::endl;
	fout << "extern bool checker_init_flag; " << std::endl  << std::endl;

	fout << "extern \"C\" ";
	fout << "void checker_initializer(unsigned int node_id)" << std::endl;
	fout << "{" << std::endl;

	fout << "	if(checker_init_flag != true)" << std::endl;
	fout << "	{" << std::endl;
	fout << "		return;" << std::endl;
	fout << "	}" << std::endl << std::endl;

	fout << "	checker_init_flag = false;" << std::endl << std::endl;

	fout << "	generate_return_point_stack();" << std::endl;
	fout << "	p_pathtree = generate_path_tree();" << std::endl;
	
	for(auto iter = BI->begin();
			iter != BI->end(); iter++)
	{
		CompactBBInfo* bb = *iter;
		fout << "	add_basicblock(p_pathtree, ";
		fout << std::hex << "0x" << bb->node_id << ", ";
		fout << std::dec << bb->numConnection << ", ";
		fout << std::hex << "0x" << bb->nextNode[0] << ", ";
		fout << "0x" << bb->nextNode[1] << ");";
		fout << std::dec << std::endl;
		
	}
	fout << std::endl;
	fout << "	return;" << std::endl;
	fout << "}" << std::endl << std::endl;


	//MetaDataSet* t_m = p_Analyzer->getMetaDataSet();
	///wFunction* t_f = t_m->getEntryFunc();
	//wBasicBlock* ProgramEntryBlock  = t_f->getEntryBlock();
	//std:: cout << t_f->getName() << std::endl;

	wBasicBlock* ProgramEntryBlock  = p_Analyzer->getProgramEntryBlock();

	fout << "Pathtree* generate_path_tree()" << std::endl;
	fout << "{" << std::endl;
	fout << "	Pathtree* t_pathtree = new Pathtree;" << std::endl;
	fout << "	BBInfo* t_bb = new BBInfo(0x00000001, 1, ";
	fout << "0x" << std::hex << ProgramEntryBlock->getID() << ", 0);" << std::endl;
	fout << "	t_pathtree->insert(std::make_pair(0x00000001, t_bb));" << std::endl << std::endl;
	fout << "	return t_pathtree;" << std::endl;
	fout << "}" << std::endl << std::endl;
	
	
	fout.close();
	return true;
}
