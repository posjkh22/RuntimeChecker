#ifndef TRANSFERIRCODE
#define TRANSFERIRCODE

#include <list>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <iostream>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include "printIRcode.hpp"
#include <llvm/Support/FileSystem.h>

#include "CompactBBSet.hpp"

using namespace llvm;


class transferIRcode
{

private:
	CompactBBList* p_CompactBBList;

public:
	transferIRcode(CompactBBList* );

public:

	bool InsertCallInstruction(std::unique_ptr<Module> &m, LLVMContext &context, IRBuilder<> &builder, llvm::BasicBlock *bb, llvm::Instruction *inst);
	bool InsertFunction(std::unique_ptr<Module> &m, LLVMContext &context, IRBuilder<> &builder);

public:
	llvm::BasicBlock *GetTargetBasicBlock(std::unique_ptr<Module> &m, std::string fname);
	llvm::Instruction *GetTargetBasicBlockCloned(std::unique_ptr<Module> &m);
	llvm::Instruction *GetTargetBasicBlockCloned2(std::unique_ptr<Module> &m);

public:
	bool InsertIRcode(std::unique_ptr<Module> &m, LLVMContext &context, IRBuilder<> &builder, const char *fname);
	bool InsertAllBasicBlock(std::unique_ptr<Module> &m, LLVMContext &context, IRBuilder<> &builder);

};

#endif
