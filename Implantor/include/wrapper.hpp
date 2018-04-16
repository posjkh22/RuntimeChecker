
#ifndef WRAPPER
#define WRAPPER

#include <list>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <iostream>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include "wTask.hpp"
#include "wFunction.hpp"
#include "wBasicBlock.hpp"
#include "wInstruction.hpp"

using namespace llvm;

class wrapper;
class wTaskList;
class wTask;
class wFunction;
class wBasicBlock;
class wInstruction;


class wrapper
{

private:
	wTask* wtask;

	class Data
	{
	public:
		Function *f;
		BasicBlock *bb;
		Instruction *inst;

		Data(Function *f, BasicBlock *bb, Instruction *inst):f(f), bb(bb), inst(inst){}
	};

public:

	wrapper();
	~wrapper();
	wTask* getwTask();

	bool splitBBModule(std::unique_ptr<Module> &m);
	int splitBBModuleChecker(std::unique_ptr<Module> &m);
	
	bool wrapperModule(std::unique_ptr<Module> &m, wTask* wtask);	
	bool BaiscBlockBranchAndFunctionCallImpl(wTask* wtask);
	bool setPathsInEachFunc(wTask* wtask);
	bool ShowPathsInEachFunc(wTask* wtask);

};


#endif
