
#ifndef WRAPPER
#define WRAPPER

#include <vector>
#include <list>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <iostream>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include "MetaDataSet.hpp"
#include "wFunction.hpp"
#include "wBasicBlock.hpp"
#include "wInstruction.hpp"
#include "SymbolManager.hpp"

using namespace llvm;

class Analyzer;
class MetaDataSet;


typedef std::vector<BasicBlock* > CompactImplantedBBList;


class CompactBBInfo
{
public:
	unsigned int node_id;
	unsigned int numConnection;
	unsigned int nextNode[2];

public:
	CompactBBInfo(
			unsigned int node_id,
			unsigned int numConnection,
			unsigned int next_node_id1,
			unsigned int next_node_id2)
		: node_id(node_id), numConnection(numConnection)
	{
		nextNode[0] = next_node_id1;
		nextNode[1] = next_node_id2;
	}
};

typedef std::unique_ptr<Module> ParsedIRmodule;
typedef std::vector<CompactBBInfo* > CompactBBInfoList;

class Analyzer
{

private:
	MetaDataSet* p_MetaDataSet;
	ParsedIRmodule* p_IRmodule;
	IPA::SymbolManager* p_symbolManager;

private:
	CompactBBInfoList* p_CompactBBInfoList;
	CompactImplantedBBList* p_CompactImplantedBBList;

public:

	class Data
	{
	public:
		Function *f;
		BasicBlock *bb;
		Instruction *inst;

		Data(
			Function *f, 
			BasicBlock *bb, 
			Instruction *inst)
			:f(f), bb(bb), inst(inst){}
	};
	


public:
	Analyzer();
	Analyzer(IPA::SymbolManager& sm);
	Analyzer(ParsedIRmodule &m, IPA::SymbolManager& sm);
	~Analyzer();

/* Take ParsedIRmodule as input */	
public:
	bool takeInput(ParsedIRmodule &m);


/* Preprocess */
public:	
	bool Preprocess();

/* Preprocess1 */
private:
	bool Preprocess1();
private:
	bool splitBBModuleOnce(std::unique_ptr<Module> &m);
	int splitBBModuleChecker(std::unique_ptr<Module> &m);

/* Preprcoess2 */
private:
	bool Preprocess2();
private:
	bool isPathUncountedFunction(const std::string&);


/* Preprcoess3 */
private:
	bool Preprocess3();
private:
	bool BasicBlockBranchAndFunctionCallImpl();
	bool makePathsInEachFunction();

/* Process */
public:
	bool Process();

private:
	bool AnalysisForSignalCodeImplanter();

private:
	bool AnalysisForMonitoringCodeGenerator();


/* GetFunctions */
public:
	IPA::SymbolManager* getSymbolManager();

public:
	MetaDataSet* getMetaDataSet();
	ParsedIRmodule* getIRmodule();
	wBasicBlock* getProgramEntryBlock();
	CompactImplantedBBList* getCompactImplantedBBList();

public:
	CompactBBInfoList* getCompactBBInfoList();

/* DebugFunctions */	
public:
	/* Create Wrapper class */	
	bool ShowPathsInEachFunc();

	/* [debug] show Analyzer element */
	bool DebugWrapperModule();

	bool Debug_Show_CompactBBInfo();
};


#endif
