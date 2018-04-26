
#ifndef SIGNALCODEIMPLANTER
#define SIGNALCODEIMPLANTER

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Support/FileSystem.h>
#include <list>

#include "Analyzer.hpp"


using namespace llvm;

typedef std::unique_ptr<Module> ParsedIRmodule;
typedef std::map<BasicBlock* ,unsigned int > CompactImplantedBBList;
//typedef std::vector<BasicBlock* > CompactImplantedBBList;

class SignalCodeImplanter
{

private:
	Analyzer* p_Analyzer;
	CompactImplantedBBList* p_CompactImplantedBBList;
	ParsedIRmodule* p_ParsedIRmodule;
	LLVMContext& m_context;

typedef enum
{
	FINE_GRAINED_LEVEL,
	COARSE_GRAINED_LEVEL
} IMPLANT_LEVEL;


private:
	IMPLANT_LEVEL m_level;


public:
	SignalCodeImplanter(LLVMContext&);

public:
	bool TakeAnalysisResults(Analyzer* );	

public:
	bool run();

private:
	bool RunFineGrainedLevel();
	bool RunCoarseGrainedLevel();

private:
	bool DeclareSignalCodes(ParsedIRmodule &, LLVMContext &, IRBuilder<> &);
	bool ImplantSignalCodes(ParsedIRmodule &, LLVMContext &, IRBuilder<> &, 
			BasicBlock *, unsigned int, Instruction *);
	bool GenerateImplantedIRmodule();

private:
	llvm::BasicBlock *SearchTargetBasicBlock(ParsedIRmodule &m, std::string fname);
	llvm::Instruction *getTargetInstClonedforInitializer(ParsedIRmodule &);
	llvm::Instruction *getTargetInstClonedforChecker(ParsedIRmodule &);

public:
//	llvm::Instruction *GetTargetBasicBlockCloned(ParsedIRmodule &m);
//	bool InsertIRcode(ParsedIRmodule &m, LLVMContext &context, IRBuilder<> &builder, const char *fname);
//	bool InsertAllBasicBlock(ParsedIRmodule &m, LLVMContext &context, IRBuilder<> &builder);

};


#endif
