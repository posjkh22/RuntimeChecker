#include "wrapper.hpp"


/* wrapper */

wrapper::wrapper(){
	wtask = new wTask;
}

wrapper::~wrapper(){
	delete wtask;
}

wTask* wrapper::getwTask(){
	return wtask;
}


int wrapper::splitBBModuleChecker(std::unique_ptr<Module> &m){


	int CheckSum = 0;
	int InstCall_flag = 0;

	std::list<Data *> ToSplitBBList;
  
	for (auto iter1 = m->getFunctionList().begin(); 
			iter1 != m->getFunctionList().end(); iter1++) {

		Function &f = *iter1;
		for (auto iter2 = f.getBasicBlockList().begin(); 
				iter2 != f.getBasicBlockList().end(); iter2++) {

			InstCall_flag = 0;
			
			BasicBlock &bb = *iter2;
			for (auto iter3 = bb.begin(); iter3 != bb.end(); iter3++) {
				
				Instruction &inst = *iter3;
				/* Increase CheckSum per Call Inst */
				if(!strcmp(inst.getOpcodeName(), "call")){
					CheckSum++;
					InstCall_flag = 1;
				}
      		}
			/* Decrease CheckSum per BB if BB has a Call Inst */
			if(InstCall_flag == 1){
				CheckSum--;
			}
    	}
		
		
  	}

	std::cout << "[CheckSum]: " << CheckSum << std::endl;

	return CheckSum;
}



bool wrapper::splitBBModule(std::unique_ptr<Module> &m){

	std::list<Data *> ToSplitBBList;
	Data *data;
  
	for (auto iter1 = m->getFunctionList().begin(); iter1 != m->getFunctionList().end(); iter1++) {
		Function &f = *iter1;
		for (auto iter2 = f.getBasicBlockList().begin(); iter2 != f.getBasicBlockList().end(); iter2++) {

			BasicBlock &bb = *iter2;
			Instruction *pastInst = reinterpret_cast<Instruction *>(0);
			for (auto iter3 = bb.begin(); iter3 != bb.end(); iter3++) {

				Instruction &inst = *iter3;
				/* store split point */
				if(pastInst != reinterpret_cast<Instruction *>(0)){
					/* Ignore if the next instruction is "br" */
					//if((!strcmp(pastInst->getOpcodeName(), "call")) && (strcmp(inst.getOpcodeName(), "br") && strcmp(inst.getOpcodeName(), "ret"))){
					if((!strcmp(pastInst->getOpcodeName(), "call")) && strcmp(inst.getOpcodeName(), "br")){
						data = new Data(&f, &bb, &inst);
						ToSplitBBList.push_back(data);
						break;
					}
				}
				pastInst = &inst;
      		}
    	}
  	}


	BasicBlock *tmp;
	std::list<Data *>::iterator iter;
	/* split by using splitBasicBlock function */
	for(iter = ToSplitBBList.begin(); iter != ToSplitBBList.end(); iter++){
		tmp = (*iter)->bb->splitBasicBlock((*iter)->inst);
	}

	return true;
}

bool wrapper::BaiscBlockBranchAndFunctionCallImpl(wTask* wtask){

	std::list<wFunction *>::iterator iter1;
	for(iter1 = wtask->getwFuncList()->begin(); iter1 != wtask->getwFuncList()->end(); iter1++){

		wFunction *CurrentFunc = (*iter1);
		CurrentFunc->determineFuncRetTy();
		std::list<wBasicBlock *>::iterator iter2;
		for(iter2 = CurrentFunc->getwBBList()->begin(); iter2 != CurrentFunc->getwBBList()->end(); iter2++){

			wBasicBlock *CurrentBB = (*iter2);
			CurrentBB->setParent(CurrentFunc);
			std::list<wInstruction *>::iterator iter3;
			for(iter3 = CurrentBB->getwInstList()->begin(); iter3 != CurrentBB->getwInstList()->end(); iter3++){
				
				Instruction *CurrentInst = (*iter3)->getInstruction();

				if(!strcmp(CurrentInst->getOpcodeName(), "call")){
					CurrentBB->setCall(true);					
					Value *branch_opnd = CurrentInst->getOperand(CurrentInst->getNumOperands() -1);
					Function *branch_func = reinterpret_cast<Function *>(branch_opnd);
					wFunction *target_wfunc =  wtask->SearchFunction(branch_func);
					(*iter2)->pushFuncCallList(target_wfunc);
				}

				if(!strcmp(CurrentInst->getOpcodeName(), "br")){
					/* Unconditional branch */
					if(CurrentInst->getNumOperands() == 1){
						Value* opnd = CurrentInst->getOperand(CurrentInst->getNumOperands() -1);
						CurrentBB->setType(wBasicBlock::ONE_BRANCH);

						BasicBlock *BranchBB = reinterpret_cast<BasicBlock *>(opnd);
						wBasicBlock* BranchwBB = CurrentFunc->SearchBasicBlock(BranchBB);
			
						std::pair<wBasicBlock* , wBasicBlock *> *BranchwBBpair = new std::pair<wBasicBlock *, wBasicBlock *>(BranchwBB , reinterpret_cast<wBasicBlock *>(0)); 
						CurrentBB->setBranchBlock(BranchwBBpair);

					/* Conditional branch: LLVM IR only two direction */	
					}else if(CurrentInst->getNumOperands() == 3) {
						Value* opnd1 = CurrentInst->getOperand(CurrentInst->getNumOperands() -1);
						BasicBlock *BranchBB1 = reinterpret_cast<BasicBlock *>(opnd1);
						wBasicBlock* BranchwBB1 = CurrentFunc->SearchBasicBlock(BranchBB1);
					

						Value* opnd2 = CurrentInst->getOperand(CurrentInst->getNumOperands() -2);
						BasicBlock *BranchBB2 = reinterpret_cast<BasicBlock *>(opnd2);
						wBasicBlock* BranchwBB2 = CurrentFunc->SearchBasicBlock(BranchBB2);
						CurrentBB->setType(wBasicBlock::TWO_BRANCH);
						
						std::pair<wBasicBlock* , wBasicBlock *> *BranchwBBpair = new std::pair<wBasicBlock *, wBasicBlock *>(BranchwBB1 , BranchwBB2); 
						CurrentBB->setBranchBlock(BranchwBBpair);
					}
				}
				if(!strcmp(CurrentInst->getOpcodeName(), "ret")){		
					CurrentBB->setType(wBasicBlock::RETURN);
				}
			}
		}


	}
	return true;
}

bool wrapper::setPathsInEachFunc(wTask* wtask){

	std::list<wFunction *> *TraverseFuncList = wtask->getwFuncList();
	std::list<wFunction *>::iterator iter;

	for(iter = TraverseFuncList->begin(); iter != TraverseFuncList->end(); iter++){
		(*iter)->makePathsList((*iter)->SearchBasicBlock(&((*iter)->getFunction()->getEntryBlock())));
		(*iter)->makePATHSLIST();
	}
	return true;
}

bool wrapper::ShowPathsInEachFunc(wTask* wtask){

	std::list<wFunction *> *TraverseFuncList = wtask->getwFuncList();
	std::list<wFunction *>::iterator iter;

	for(iter = TraverseFuncList->begin(); iter != TraverseFuncList->end(); iter++){
		std::cout << (*iter)->getFunction()->getName().str();
		std::cout << "[" << (*iter)->getNumPaths()  << "]";
		std::cout <<":" << std:: endl;
		(*iter)->viewPathsList();	
	}
	return true;
}


bool wrapper::wrapperModule(std::unique_ptr<Module> &m, wTask* wtask){

	/* Module Entry */
  	for (auto iter1 = m->getFunctionList().begin(); iter1 != m->getFunctionList().end(); iter1++) {

		/* Function Entry */
		Function &f = *iter1;
		wFunction *wf = new wFunction;
		wf->setwFunction(&f);
		wtask->pushFuncList(wf);

		unsigned int BBNumber = 0;
		for (auto iter2 = f.getBasicBlockList().begin(); iter2 != f.getBasicBlockList().end(); iter2++) {

			/* BasicBlock Entry */
			BasicBlock &bb = *iter2;
			wBasicBlock *wbb = new wBasicBlock;
			wbb->setName(f.getName().str() + std::string("%") + std::to_string(BBNumber++));
			
			/* split BB by "call instruction" */

			#ifdef DD
		  	for (auto iter3 = bb.begin(); iter3 != bb.end(); iter3++) {

				/* Instruction Entry */
				Instruction &inst = *iter3;

				BasicBlock *newSplitedBB;
				if(!strcmp(inst.getOpcodeName(), "call")){
					newSplitedBB = bb.splitBasicBlock(&inst);
					//f.getBasicBlockList().insert((iter2), newSplitedBB);
					//f.getBasicBlockList().push_back(newSplitedBB);
					//std::cout << "long" << std::endl;
				}
				
				/*
       		 	int opnt_cnt = inst.getNumOperands();

				for(int i = 0; i < opnt_cnt; i++){
          			Value *opnd = inst.getOperand(i);
					wInst->pushOperandList(opnd);
        		}
				*/
			}
			#endif

			wbb->setwBasicBlock(&bb);
			wf->pushBBList(wbb);
	
			
			Instruction* br_inst;
		  	for (auto iter3 = bb.begin(); iter3 != bb.end(); iter3++) {

				/* Instruction Entry */
				Instruction &inst = *iter3;
				br_inst = &inst;

				wInstruction *wInst = new wInstruction;
				wInst->setwInstruction(&inst);
				wbb->pushInstList(wInst);

       		 	int opnt_cnt = inst.getNumOperands();

				for(int i = 0; i < opnt_cnt; i++){
          			Value *opnd = inst.getOperand(i);
					wInst->pushOperandList(opnd);
        		}

      		}
			/* BasicBlock EndPoint */
		
    	}
		/* Function EndPoint */	
  	}

	return true;

}

/////////////////////////////////////////////////////////////

