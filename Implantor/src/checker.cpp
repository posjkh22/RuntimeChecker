
#include "checker.hpp"



bool checker::setCheckerTy(checker::checker_ty ty){
	type = ty;
	return true;
}


/* checker creator */

checker::checker(PathList *pathlist){

	if(attachPathList(pathlist)){
		std::cout << "Checker(PathList) create! " << std::endl;
	}
}

checker::checker(Path *path){

	if(attachPath(path)){
		std::cout << "Checker(Path) create! " << std::endl;
	}

}


/* PathList */

bool checker::attachPathList(PathList *pathlist){

//	std::list<Path *>::iterator iter1;
//	std::list<wBasicBlock *>::iterator iter2;

	setCurrentPathList(pathlist);

	Path *entry_path = pathlist->getPathList()->front();

	setCurrentPath(entry_path);

	wBasicBlock *entry_BB = entry_path->getPath()->front();

	setCurrentBB(entry_BB);

	/*

	   More specific to Target


	*/

	return true;
}

bool checker::setCurrentPathList(PathList *pathlist){

	currentPathList = pathlist;

	return true;
}


PathList *checker::getCurrentPathList(){

	return currentPathList;
}


/* 
   	In this function, 
	Implement movePath at the end of PathList
	is Not considered(also return false).

*/
bool checker::movePath(){

	PathList *currentPathList = getCurrentPathList();

	std::list<Path *>::iterator iter;
	std::list<Path *> *CurrentPathList = currentPathList->getPathList();

	int found_flag = 0;

	for(iter = CurrentPathList->begin(); 
			iter != CurrentPathList->end(); iter++){

		Path *currentPath = (*iter);

		/* if found, break when next iter */
		if(currentPath == getCurrentPath()){

			found_flag = 1;
			iter++;
			break;
		}
	}

	/* No found */
	if(!found_flag){
		return false;
	}

	/* update currentPath */
	return setCurrentPath(*iter);
}


/* Path */

bool checker::attachPath(Path *path){

	setCurrentPath(path);
	
	wBasicBlock *entry_BB = path->getPath()->front();

	setCurrentBB(entry_BB);
	
	/*

	More specific to Target

	*/

	return true;
}


bool checker::setCurrentPath(Path *path){

	currentPath = path;

	return true;
}


Path *checker::getCurrentPath(){

	return currentPath;
}

bool checker::move(){

	Path *currentPath = getCurrentPath();
	
	std::list<wBasicBlock *> *CurrentPath = currentPath->getPath();

	std::list<wBasicBlock *>::iterator iter;
	
	int found_flag = 0;

	for(iter = CurrentPath->begin(); 
			iter != CurrentPath->end(); iter++){

		wBasicBlock *currentBB = (*iter);

		if(currentBB == getCurrentBB()){
			found_flag = 1;
			iter++;
			break;
		}
	}

	if(!found_flag){
		return false;
	}

	return setCurrentBB(*iter);
}


/* BB */

wBasicBlock *checker::getCurrentBB(){

	return currentBB;
}

bool checker::setCurrentBB(wBasicBlock *BB){
	
	currentBB = BB;
	return true;
}

wBasicBlock *checker::getNextBB(){

	Path *currentPath = getCurrentPath();
	
	std::list<wBasicBlock *> *CurrentPath = currentPath->getPath();

	std::list<wBasicBlock *>::iterator iter;
	
	int found_flag = 0;

	for(iter = CurrentPath->begin(); 
			iter != CurrentPath->end(); iter++){

		wBasicBlock *currentBB = (*iter);

		if(currentBB == getCurrentBB()){
			found_flag = 1;
			iter++;
			break;
		}
	}

	if(!found_flag){
		return nullptr;
	}

	return (*iter);

}





unsigned int checker::check_checker_state_flag(){

	unsigned int sumAbsolValue = 0;

	for(auto iter = traceValState.begin();
			iter != traceValState.end(); iter++){

		TraceData *current = (*iter);

		sumAbsolValue += std::abs(*(current->checker_state_flag));
	}

	return sumAbsolValue;

}

bool checker::check(PathList *pathlist){


	attachPathList(pathlist);

	PathList *targetPathlist = getCurrentPathList();

	std::list<Path *>::iterator iter;
	std::list<Path *> *TargetPathList;

	TargetPathList = targetPathlist->getPathList();

	for(iter = TargetPathList->begin();
			iter != TargetPathList->end(); iter++){

		Path* currentPath = (*iter);
		check(currentPath);
	}

	/* trace_flag check */
	/* if the value is not set, the error is detected */

	if(check_checker_state_flag() != 0 
			&& ((type == checker::CHECK4) || (type == checker::CHECK5))){

		std::cout << "[Checker Error]: " << std::endl;

		for(auto iter = traceValState.begin();
				iter != traceValState.end(); iter++){

			TraceData *current = (*iter);
			
			if(*(current->checker_state_flag) < 0 
					&& current->bug_location_flag == 1){
				
				if(type == checker::CHECK4){
					std::cout << "FILE Double close";
				}
				else if(type == checker::CHECK5){
					std::cout << "FILE Double free";
				}
				std::cout << "(" << current->traceVal << "/";
				std::cout << current->f->getName().str() << ")" <<std::endl;

			}

			/*
			if(*(current->checker_state_flag) > 0 
				|| ( (*(current->checker_state_flag) > 0 
					&& current->bug_location_flag == 1) )
			*/

			if(( (*(current->checker_state_flag) > 0 
					&& current->bug_location_flag == 1) )
				
				){

				if(type == checker::CHECK4){
					std::cout << "FILE is Not close";
				}
				else if(type == checker::CHECK5){
					std::cout << "Memory is Not free";
				}
				std::cout << "(" << current->traceVal << "/";
				std::cout << current->f->getName().str() << ")" <<std::endl;

			}

		}

		ShowPassingReturnVal();
		/*
		if(checker_state_flag < 0){

			std::cout << "FILE Double close" << std::endl;
		}
		
		if(checker_state_flag > 0){

			std::cout << "FILE is Not close" << std::endl;
		}
		*/
	}

	return true;
}

bool checker::check(Path *path){

	std::cout << *(path->getName()) << std::endl;

	attachPath(path);

	Path *targetPath = getCurrentPath();

	std::list<wBasicBlock *>::iterator iter;
	std::list<wBasicBlock *> *TargetPath;

	TargetPath = targetPath->getPath();

	for(iter = TargetPath->begin();
			iter != TargetPath->end(); iter++){

		wBasicBlock *currentBB = (*iter);
		check(currentBB);	
	}


	return true;
}

bool checker::check(wBasicBlock *BB){

	std::list<wInstruction *>::iterator iter;
	std::list<wInstruction *> *InstList;


	InstList = BB->getwInstList();

	for(iter = InstList->begin();
			iter != InstList->end(); iter++){

		wInstruction *currentInst = (*iter);

		/* checker set */
		//check1(BB, currentInst);
		//check2(BB, currentInst, comp_gv);
		//check3(BB, currentInst, comp_gv);
		//setCheckerTy(checker::CHECK4);
		//check4(BB, currentInst); 
		setCheckerTy(checker::CHECK5);
		check5(BB, currentInst); 
	}

	return true;
}


/* checker set */

bool checker::check1(wBasicBlock *BB, wInstruction *Inst){

	llvm::Instruction *bare_inst = Inst->getInstruction();

	if(bare_inst->getOpcodeName() == std::string("call")){
		std::cout << *(BB->getName()) << " ";
		std::cout << "[CheckF: " << bare_inst->getOpcodeName() << "]" << std::endl;
	}

	return true;
}


bool checker::check2(wBasicBlock *BB, wInstruction *Inst, GlobalVariable *gv){
	
	llvm::Instruction *bare_inst = Inst->getInstruction();

	if(bare_inst->getOpcodeName() == std::string("store")){
		

		for(int i = 0; i < bare_inst->getNumOperands(); i++){
			if(bare_inst->getOperand(i) == reinterpret_cast<Value *>(gv)){
			
				std::cout << i <<": ";
				std::cout << *(BB->getName()) << " ";
				std::cout << "[CheckF: " << bare_inst->getOpcodeName() << "]";
				std::cout << " " << gv->getName().str() << std::endl;
			}
		}
	}
	
	return true;
}

bool checker::check3(wBasicBlock *BB, wInstruction *Inst, GlobalVariable *gv){
	
	llvm::Instruction *bare_inst = Inst->getInstruction();

	if(bare_inst->getOpcodeName() == std::string("store")){
		

		for(int i = 0; i < bare_inst->getNumOperands(); i++){
			if(bare_inst->getOperand(i) == reinterpret_cast<Value *>(gv)){
			
				std::cout << i <<": ";
				std::cout << *(BB->getName()) << " ";
				std::cout << "[CheckF: " << bare_inst->getOpcodeName() << "]";
				std::cout << " " << gv->getName().str() << std::endl;

				std::cout << "size: " << bare_inst->getNumOperands() << std::endl;
				std::cout << "0: " << bare_inst->getOperand(0) << std::endl;

				Value *load_val = bare_inst->getOperand(0);
				llvm::Instruction *load_inst = reinterpret_cast<llvm::Instruction *>(load_val);
				std::cout << load_inst->getOpcodeName() << std::endl;			

			}
		}
	}
	return true;
}


checker::TraceData *checker::SearchTraceVal(unsigned int iter_count){

	unsigned int count = 0;
	int found_flag = 0; 
	
	std::list<checker::TraceData *>::iterator iter;

	for(iter = traceValState.begin();
			iter != traceValState.end(); iter++, count++){

		if(count == iter_count){
			found_flag = 1;
			break;
		}

	}

	if(found_flag == 0){

		return nullptr;
	}

	return (*iter);

}

/* Backward search: C lang is run sequentially. */
checker::TraceData *checker::SearchTraceVal(llvm::Value *cmp_val){

	std::list<TraceData *>::reverse_iterator iter;

	int found_flag = 0;

	for(iter = traceValState.rbegin(); 
			iter !=traceValState.rend(); iter++){

		if( (*iter)->traceVal == cmp_val){
			found_flag = 1;
			break;
		}

	}

	if(found_flag == 0){
		return nullptr;
	}

	return (*iter);
}


bool checker::ShowTraceData(){

	int i = 1;
	for(auto iter = traceValState.begin();
			iter != traceValState.end(); iter++, i++){

		TraceData *current = *iter;

		std::cout << "[" << std::setw(2) << i << "] ";
		std::cout << "(" << current->traceVal << "/";
		std::cout << std::setw(2) << *(current->checker_state_flag) <<"/";
		std::cout << current->f->getName().str() <<  "/"; 
		std::cout << current->bug_location_flag << "/";
		std::cout << current->unique_number << ") ";

		if(i != 0 && i %3 == 0){
			std::cout << std::endl;
		}

	}
	std::cout << std::endl;
	return true;
}

bool checker::ShowPassingReturnVal(){

	int i = 1;
	for(auto iter = PassingReturnVal.begin();
			iter != PassingReturnVal.end(); iter++, i++){

		TraceData *current = *iter;

		std::cout << "[" << std::setw(2) << i << "] ";
		std::cout << "(" << current->traceVal << "/";
		std::cout << std::setw(2) << *(current->checker_state_flag) <<"/";
		std::cout << current->f->getName().str() <<  "/"; 
		std::cout << current->bug_location_flag << ") ";

		if(i != 0 && i %3 == 0){
			std::cout << std::endl;
		}

	}
	std::cout << std::endl;
	return true;
}

bool checker::deleteTraceValwithReturn(llvm::Function *fid){

	
	std::list<TraceData *>::iterator iter;

	iter = traceValState.begin();
	while(iter != traceValState.end()){
		
		TraceData *current = (*iter);
		/* 
		   	if checker_state_flag is Not normal, 
		 	leave the traceVal.
		*/
		if(current->f == fid  
			&& !(*(current->checker_state_flag) > 0
				|| *(current->checker_state_flag) < 0)		
				
			){
			std::cout << "[TraceData DEL]: ";
			std::cout << "(" << current->traceVal << "/";
			std::cout << *(current->checker_state_flag) <<"/";
			std::cout << current->f->getName().str() << ")";
			std::cout << std::endl;
			traceValState.erase(iter++);
		}
		else{
			++iter;
		}
		
	}
	return true;
}

bool checker::setBugLocationFlag(llvm::Function *fid){

	
	std::list<TraceData *>::iterator iter;

	iter = traceValState.begin();
	while(iter != traceValState.end()){
		
		TraceData *current = (*iter);
		/* 
		   	if checker_state_flag is Not normal, 
		 	leave the traceVal.
		*/
		if(current->f == fid  
			&& (*(current->checker_state_flag) > 0)
//			&& (*(current->checker_state_flag) > 0
//				|| *(current->checker_state_flag) < 0)		
				
			){
			current->bug_location_flag = 1;
			std::cout << "[SetBugLocationFlag]: ";
			std::cout << "(" << current->traceVal << "/";
			std::cout << *(current->checker_state_flag) <<"/";
			std::cout << current->f->getName().str() << ")";
			std::cout << std::endl;
		}
		
		++iter;
	}
	return true;
}


bool checker::check4(wBasicBlock *BB, wInstruction *Inst){
	

	return true;
}

bool checker::check5(wBasicBlock *BB, wInstruction *Inst){
	
	int arg = -1; 
	
	if(Inst->getInstruction()->getOpcodeName() == std::string("br")){	
		/* Do not consider "br" instruction */
		//std::cout << "BR" << std::endl;
		return true;
	}

	if(Inst->getInstruction()->getOpcodeName() == std::string("call")){		
		
		llvm::Instruction *bare_inst = Inst->getInstruction();
		
		Value *get_opnd = bare_inst->getOperand(bare_inst->getNumOperands() - 1);
		/* if malloc is found */
		if(get_opnd->getName().str() == std::string("malloc")){
			std::cout << "[call]: ";
			std::cout << get_opnd->getName().str() << std::endl;

			/* First malloc */
			if(traceValState.empty() == true){
				Value *traceVal = reinterpret_cast<llvm::Value *>(bare_inst);
				int *checker_state_flag = new int(1);	
				llvm::Function *fid = BB->getParentFunction();

				TraceData *trace_data
					= new TraceData(traceVal, checker_state_flag, fid);
				
				trace_data->setUniqueNumber();

				traceValState.push_back(trace_data);
				trace_flag = 1;
				std::cout << "[MALLOC]";
				std::cout << trace_data->traceVal << std::endl;
				ShowTraceData();
	
			}
			/* After the second malloc */
			else{
				Value *traceVal = reinterpret_cast<llvm::Value *>(bare_inst);
				
				/* not found & new insert */
				TraceData *returnIterPtr
					= SearchTraceVal(traceVal);

				if(nullptr == returnIterPtr){
					llvm::Function *fid = BB->getParentFunction();
					int *checker_state_flag = new int(1);	
					
					TraceData *trace_data
						= new TraceData(traceVal, checker_state_flag, fid);				
				
					trace_data->setUniqueNumber();
					
					traceValState.push_back(trace_data);
					trace_flag = 1;
					std::cout << "[MALLOC]";
					std::cout << trace_data->traceVal << std::endl;
					ShowTraceData();					
				}
				
				else{
				
					/* If double open, */
					TraceData *get_trace_data = returnIterPtr;
					*(get_trace_data->checker_state_flag) += 1;
					get_trace_data->bug_location_flag = 1;

					//std::cout << "Double open: (";
					//std::cout << get_trace_data->traceVal << ")";
					//std::cout << std::endl;
					//trace_flag = 0;
				}

			}
		
		}
	}
	
	//if(traceVal != nullptr){
	if(traceValState.empty() == false){

		ShowTraceData();
		//std::cout << "traceVal(" << traceVal << ")  -> ";
	}


	if(trace_flag == 1){
		
		llvm::Instruction *bare_inst = Inst->getInstruction();

		if(trace_new_func_flag == 1){
			
			if(PassingArgument.empty() == false){

				llvm::BasicBlock *bb = BB->getBasicBlock();
				llvm::Function *f = bb->getParent();	
				std::cout << "F: " << f->getName().str() << std::endl;
				std::cout << "[found func]: " << f->getName().str() << std::endl;

				int tmp_count = 0;

				std::list<llvm::Argument *> temp_arg_list;
				llvm::Argument *argument;

				std::cout << "New Func ARG SIZE:" << f->arg_size() << std::endl;
				std::cout << "Passing  ARG SIZE:" << PassingArgument.size() << std::endl;
				for(auto iter = f->arg_begin(); 
						iter != f->arg_end(); iter++, tmp_count++){

					for(auto iter2 = PassingArgument.begin();
							iter2 != PassingArgument.end(); iter2++){

						arg = (*iter2)->number;				
						//arg = PassingArgument.front();
						//PassingArgument.pop_front();

						if(tmp_count == arg){
							argument = &(*iter);
							temp_arg_list.push_back(argument);
							std::cout << "New Func ARG(" << argument << ")"  << std::endl;
						}
					}
				}

				/*
				   	Always
					tem_arg_list.size() >= PassingArgument.size()
	

				*/

				unsigned int tmp_count2 = 0;
				for(auto iter = temp_arg_list.begin();
						iter != temp_arg_list.end(); iter++, tmp_count2++){

					llvm::Argument *passArg = *iter;

					unsigned int passIter = PassingArgument.front()->number;
					
					if(tmp_count2 == passIter){

						checker::Argument *argu = PassingArgument.front();


						TraceData *returnIterPtr
							= SearchTraceVal(PassingArgument.front()->traceVal);
						
						//TraceData *returnIterPtr
						//	= SearchTraceVal(passIter);
						
						if(returnIterPtr == nullptr){
							std::cout << "Something Wrong!" << std::endl;
							PassingArgument.pop_front();
							continue;
						}
						else{


							PassingArgument.pop_front();
							
							int *checker_state_flag 
								= returnIterPtr->checker_state_flag;
							
							int unique_number 
								= returnIterPtr->unique_number;
							
							Value *new_traceVal	
								= reinterpret_cast<Value *>(passArg);
						
							llvm::Function *fid = BB->getParentFunction();

							TraceData *new_trace_data 
								= new TraceData(new_traceVal, checker_state_flag, fid, unique_number);

							traceValState.push_back(new_trace_data);
								
										
							//returnIterPtr->traceVal
							//	= reinterpret_cast<Value *>(passArg);
						}

					}
					
					else{
						continue;
					}

					//Argument *passArg = temp_arg_list.front();
					//temp_arg_list.pop_front();
					//traceVal = reinterpret_cast<Value *>(passArg);
				}
				
				trace_new_func_flag = 0;



			}
			/* No argument */
			else{

				std::cout << "Need to be considered" << std::endl;
				trace_new_func_flag = 0;
			}		

		}

		if(bare_inst->getOpcodeName() == std::string("ret")){		

			llvm::Function *fid = BB->getParentFunction();
			std::cout << "[RET2: ";
			std::cout << fid->getName().str(); 
			std::cout << "]: ";

			/* Pass ReturnVal */
			if(bare_inst->getNumOperands() != 0){

				/* return Not Void */

				#define RET_OPERAND_ITER 0
				std::cout << bare_inst->getOperand(RET_OPERAND_ITER) << std::endl;
				TraceData *returnIterPtr
					= SearchTraceVal(bare_inst->getOperand(RET_OPERAND_ITER));
			
				if(returnIterPtr == nullptr){
					std::cout <<"ELSE: " << bare_inst->getOpcodeName() << std::endl;
	
				}

				else{
				
					Value* new_traceVal = reinterpret_cast<Value *>(bare_inst);
					llvm::Function *fid = BB->getParentFunction();	
					int *checker_state_flag = returnIterPtr->checker_state_flag;		
					int unique_number = returnIterPtr->unique_number;		

					TraceData *trace_data
						= new TraceData(new_traceVal, checker_state_flag, fid, unique_number);				
					traceValState.push_back(trace_data);

					/* Transfer TraceData */
					/* 1. get PassingReturnVal element(TraceData1) & remove it from PassingReturnVal  */
					/* 2. get TraceValState last element(TraceData2) & remove it from TraceValState */
					/* 3. copy TraceData2 to TraceData1 */
					/* 4. Insert the updated TraceData1 to TraceValState */
					/* Delete PassingRetunVal element & insert TraceValState element */
					
					wFunction *f = BB->getParent();
					if(f->getFuncRetTy() == wFunction::FuncRetTy::NonVoidTy){

						TraceData *new_trace_data 
							= PassingReturnVal.back();
						PassingReturnVal.pop_back();

						TraceData *ret_trace_data
							= traceValState.back();
						traceValState.pop_back();
						
						new_trace_data->checker_state_flag
							= ret_trace_data->checker_state_flag;
						new_trace_data->bug_location_flag
							= ret_trace_data->bug_location_flag;
						new_trace_data->unique_number
							= ret_trace_data->unique_number;

						traceValState.push_back(new_trace_data);
					
					}
					else{

					}
					

				}
				#undef RET_OPERAND_ITER


			}

			else{
				/* return Void */
				

				std::cout << std::endl;

			}


			/* Detach tracer: main function or task function */
			if(fid->getName().str() != "main"){

				deleteTraceValwithReturn(fid);
			}
			else{

				setBugLocationFlag(fid);
				/* blank */
			}

			return true;
		}
		else if(Inst->getInstruction()->getOpcodeName() == std::string("br")){	
			/* Do not consider "br" instruction */
			std::cout << "[BR]: SOMETHING WRONG!" << std::endl;
			return true;
		}

		else if(bare_inst->getOpcodeName() == std::string("call")){		
			Value *get_opnd = bare_inst->getOperand(bare_inst->getNumOperands() - 1);			
			std::cout << "[call]: ";
			std::cout << get_opnd->getName().str() << std::endl;
		
			/* if free is found */
			if(get_opnd->getName().str() == std::string("free")){
			
				#define FFREE_FP_ARG 0
				
				std::cout << "PASSING: (";
				std::cout << bare_inst->getOperand(FFREE_FP_ARG);
				std::cout << ")" << std::endl;

				TraceData *returnIterPtr
					= SearchTraceVal(bare_inst->getOperand(FFREE_FP_ARG));			
				if(returnIterPtr == nullptr){
					std::cout << "ERORR" << std::endl;
				}
				else{
					std::cout << "[FREE]: ";
					std::cout << returnIterPtr->traceVal << std::endl;
					*(returnIterPtr->checker_state_flag) -= 1;
					
					if( *(returnIterPtr->checker_state_flag) < 0){
						returnIterPtr->bug_location_flag = 1;
					}
				}

				#undef FFREE_FP_ARG
				
				//trace_flag = 0;
				/*@@@@@
				checker_state_flag -= 1;

				if(checker_state_flag < 0){
					trace_flag = 0;
					traceVal = nullptr;
				}
				*/
			}
			/* if FILE ptr is an argument of a function */
			else{
	
				wFunction *fid = BB->getParent();
				if(fid->getFuncRetTy() == wFunction::FuncRetTy::NonVoidTy){

					Value *new_traceVal = reinterpret_cast<Value *>(bare_inst);
					llvm::Function *fid = BB->getParentFunction();	
					int *checker_state_flag = &basic_checker_state_flag;		

					TraceData *trace_data
						= new TraceData(new_traceVal, checker_state_flag, fid);				
					
					PassingReturnVal.push_back(trace_data);

					
				}
				else {

						/* Blink */
				}


				/* arguemnt */
				for(int i = 0; i < bare_inst->getNumOperands() -1; i++){
				



					TraceData *returnIterPtr
						= SearchTraceVal(bare_inst->getOperand(unsigned(i)));
				
					if(returnIterPtr != nullptr){	
						std::cout << " Passing(before): ";
						std::cout << bare_inst->getOperand(unsigned(i));
						std::cout << std::endl;
						arg = i;
						
						checker::Argument *argument = new Argument(arg, bare_inst->getOperand(unsigned(i)));
						PassingArgument.push_back(argument);
						trace_new_func_flag = 1;
					
					}
					else{
	
						continue;
					}
					
					/*
					if(bare_inst->getOperand(unsigned(i)) == traceVal){
						arg = i;
						trace_new_func_flag = 1;
						break;
					}
					*/
				}
			}
		}
		else if( bare_inst->getOpcodeName() == std::string("load") 
				|| bare_inst->getOpcodeName() == std::string("bitcast") 
			){


				llvm::BasicBlock *bb = BB->getBasicBlock();
				llvm::Function *f = bb->getParent();	
				std::cout << "F: " << f->getName().str() << std::endl;
			
			#define LOADED_VALUE 0			
			TraceData *returnIterPtr
				= SearchTraceVal(bare_inst->getOperand(LOADED_VALUE));

			if(returnIterPtr == nullptr){
				std::cout << "ELSE: " << bare_inst->getOpcodeName() << std::endl;
			}

			else{
				Value* new_traceVal = reinterpret_cast<Value *>(bare_inst);
				llvm::Function *fid = BB->getParentFunction();	
				int *checker_state_flag = returnIterPtr->checker_state_flag;		
				int unique_number = returnIterPtr->unique_number;

				TraceData *trace_data
					= new TraceData(new_traceVal, checker_state_flag, fid, unique_number);				
				traceValState.push_back(trace_data);

				std::cout << "[load/bitcast]: PASSING! ";
				std::cout << bare_inst->getOperand(LOADED_VALUE) << "to " << new_traceVal << std::endl;
			}
			#undef LOADED_VALUE	

		}

		else if(bare_inst->getOpcodeName() == std::string("store")){	
			llvm::BasicBlock *bb = BB->getBasicBlock();
			llvm::Function *f = bb->getParent();	
			std::cout << "F: " << f->getName().str() << std::endl;

			#define STORED_VALUE 0
			#define STORAGE 1
		
			TraceData *returnIterPtr
				= SearchTraceVal(bare_inst->getOperand(STORED_VALUE));
			
			if(returnIterPtr == nullptr){
				std::cout <<"ELSE: " << bare_inst->getOpcodeName() << std::endl;

			}

			else{
				
				Value* new_traceVal = bare_inst->getOperand(STORAGE);
				llvm::Function *fid = BB->getParentFunction();	
				int *checker_state_flag = returnIterPtr->checker_state_flag;		
				int unique_number = returnIterPtr->unique_number;

				TraceData *trace_data
					= new TraceData(new_traceVal, checker_state_flag, fid, unique_number);				
				traceValState.push_back(trace_data);


				/*
				TraceData *get_trace_data = returnIterPtr;
				
				get_trace_data->traceVal
						= bare_inst->getOperand(STORAGE);
				*/
		
				std::cout << "[store]: PASSING!" << std::endl;
			}
			
			#undef STORED_VALUE
			#undef STORAGE


		}else{

				llvm::BasicBlock *bb = BB->getBasicBlock();
				llvm::Function *f = bb->getParent();	
				std::cout << "F: " << f->getName().str() << std::endl;
			std::cout <<"ELSE: " << bare_inst->getOpcodeName() << std::endl;
		}


	}
	else {
		/*
		blank: If No target object to be checked,
		*/
	}



	return true;
}

