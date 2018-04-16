
#ifndef COMPACTBBLIST
#define COMPACTBBLIST

#include <vector>

#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/Support/FileSystem.h>

#include "wBasicBlock.hpp"
#include "wrapper.hpp"

typedef std::vector<llvm::BasicBlock* > CompactBBList;
typedef std::unique_ptr<Module> ParsedIRmodule;

class CompactBBSet
{

public:
	CompactBBSet();

private:
	wrapper* p_wrapper;
	CompactBBList* p_CompactBBList;
	ParsedIRmodule* p_ParsedIRmodule;

public:
	bool generate(wrapper* );

public:
	CompactBBList* getCompactBBList();

public:
	bool Debug_CompactBBListShow();
};


#endif
