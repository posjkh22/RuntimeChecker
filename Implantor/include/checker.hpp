#ifndef CHECKER
#define CHECKER

#include <iomanip>
#include <list>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instruction.h>
#include <iostream>
#include <llvm/IR/LLVMContext.h>

#include "wBasicBlock.hpp"
#include "wInstruction.hpp"
#include "Path.hpp"
#include "PathImpl.hpp"



using namespace llvm;


class wBasicBlock;
class wInstruction;
class Path;
class PathList;


extern GlobalVariable *comp_gv;




class checker
{

public:
	typedef enum {
		CHECK1,
		CHECK2,
		CHECK3,
		CHECK4,
		CHECK5
	}checker_ty;

	class TraceData
	{
	
	public:
		Value *traceVal;
		int *checker_state_flag;
		int bug_location_flag;
		int return_update_flag;
		int unique_number;
		llvm::Function *f;
			
		TraceData(Value *tVal, int *tStatef, llvm::Function *F, 
				int uNumber){
			traceVal = tVal;
			checker_state_flag = tStatef;
			f = F;
			bug_location_flag = 0;
			return_update_flag = 0;
			unique_number= uNumber;
		}
		
		TraceData(Value *tVal, int *tStatef, llvm::Function *F){
			traceVal = tVal;
			checker_state_flag = tStatef;
			f = F;
			bug_location_flag = 0;
			return_update_flag = 0;
		}

		bool setUniqueNumber(){

			static int number = 0;
			unique_number = number++;
			return true;
		}
		
	};

	class Argument 
	{
	public:
		int number;
		Value *traceVal;

		Argument(int num, Value *tVal){
			number = num;
			traceVal = tVal;
		}
	};

	/*
	class ReturnVal
	{
	public:
		Value *traceVal;
	
		ReturnVal(Value *tVal){
			traceVal = tVal;
		}
	};
	*/

private:
	checker_ty type;
	int trace_flag;
	int trace_new_func_flag;
	int basic_checker_state_flag;

	//int checker_state_flag;
	//Value *traceVal;
	//std::list<int> checker_state_flag;
	//std::list<Value *>traceVal;

	//std::map<Value *, int> traceValState;

	std::list<checker::Argument *> PassingArgument;
	std::list<TraceData *> PassingReturnVal;
	std::list<TraceData *> traceValState;

	wBasicBlock *currentBB;
	PathList *currentPathList;
	Path *currentPath;


public:
	checker(){
		trace_flag = 0;
		trace_new_func_flag = 0;
		basic_checker_state_flag = 0;
		//checker_state_flag = 0;
		//traceVal = nullptr;
	};


	bool setCheckerTy(checker_ty ty);
	TraceData *SearchTraceVal(unsigned int iter_count);
	TraceData *SearchTraceVal(llvm::Value *cmp_val);
	bool ShowTraceData();
	bool ShowPassingReturnVal();
	unsigned int check_checker_state_flag();
	bool deleteTraceValwithReturn(llvm::Function *fid);
	bool setBugLocationFlag(llvm::Function *fid);
	


	/* check */

	bool check(PathList *pathlist);
	bool check(Path *path);
	bool check(wBasicBlock *BB);

	/* checker set */
	bool check1(wBasicBlock *BB, wInstruction *Inst);
	bool check2(wBasicBlock *BB, wInstruction *Inst, GlobalVariable *gv);
	bool check3(wBasicBlock *BB, wInstruction *Inst, GlobalVariable *gv);
	bool check4(wBasicBlock *BB, wInstruction *Inst);
	bool check5(wBasicBlock *BB, wInstruction *Inst);

	/* PathList */
	checker(PathList *);

	bool attachPathList(PathList *);
	
	bool setCurrentPathList(PathList *);

	PathList *getCurrentPathList();

	bool movePath();


	/* Path */
	checker(Path *);

	bool attachPath(Path *);
	
	Path *getCurrentPath();
	bool setCurrentPath(Path *);

	bool move();


	/* BB */

	wBasicBlock *getCurrentBB();
	bool setCurrentBB(wBasicBlock *);

	wBasicBlock *getNextBB();
	wBasicBlock *getNextBB(Path *);


};


#endif
