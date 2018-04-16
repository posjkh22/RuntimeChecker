#ifndef WFUNCTION
#define WFUNCTION

#include <list>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <iostream>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include "wBasicBlock.hpp"
#include "Path.hpp"
//#include "Analyzer.hpp"


using namespace llvm;

class Path;
class Analyzer;
class wBasicBlock;

typedef std::unique_ptr<Module> ParsedIRmodule; 

typedef std::list<wBasicBlock* > PathTy;
typedef std::list<PathTy* > BBPathListTy;
typedef std::list<Path* > PathListTy;

typedef std::list<wBasicBlock* > BasicBlockListTy;


class wFunction 
{

public:
	std::string getName();

public:
	typedef enum {
		VoidTy,
		NonVoidTy
	}FuncRetTy;

private:
	Function *func;
	FuncRetTy retTy;
	BasicBlockListTy wBBList;

	wFunction *callerFunc;
	wBasicBlock *CurrentBasicBlock;

private:
	unsigned int ID;

public:
	unsigned int getID();
	bool setID(unsigned int);

private:
	BBPathListTy m_BBPathList;
	PathListTy m_PathList;

private:
	Analyzer* p_Analyzer;
	//Analyzer* m_IRcodeData;

private:
	ParsedIRmodule* p_ParsedIRmodule;

public:
	wFunction(ParsedIRmodule* , Analyzer* );

	bool determineFuncRetTy();
	bool setFuncRetTy(wFunction::FuncRetTy);
	wFunction::FuncRetTy getFuncRetTy();

public:
	/* wrapping function */
	bool setwFunction(Function *);
	Function *getFunction();

	wFunction* getCallerFunc();
	bool setCallerFunc(wFunction *);

	bool pushBBList(wBasicBlock *);
	wBasicBlock* getCurrentBasicBlock();

	bool setCurrentBasicBlock(wBasicBlock *);
	BasicBlockListTy* getwBBList();
	wBasicBlock* SearchBasicBlock(BasicBlock *);

	wBasicBlock* getEntryBlock();

public:
	/* cfg Impl */
	BBPathListTy* getBBPathList();
	bool makeBBPathList(wBasicBlock *);
	bool IntrinsicFuncMakePathsList(wBasicBlock *);
	unsigned int getNumPaths();
	bool showPathsList();

public:
	/* Path */
	PathListTy* makePathList();
	PathListTy* getPathList();

};

#endif
