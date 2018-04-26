#include "Analyzer.hpp"


/* Analyzer */

Analyzer::Analyzer()
{
	p_CompactBBInfoList = nullptr;
	p_CompactImplantedBBList = nullptr;
	p_MetaDataSet = new MetaDataSet;
}

Analyzer::Analyzer(IPA::SymbolManager& sm)
{
	p_CompactBBInfoList = nullptr;
	p_CompactImplantedBBList = nullptr;
	p_symbolManager = &sm;
	p_MetaDataSet = new MetaDataSet;
}

Analyzer::Analyzer(ParsedIRmodule& m, IPA::SymbolManager& sm)
{
	p_CompactBBInfoList = nullptr;
	p_CompactImplantedBBList = nullptr;
	p_IRmodule = &m;
	p_symbolManager = &sm;
	p_MetaDataSet = new MetaDataSet;
}

Analyzer::~Analyzer()
{
	delete p_MetaDataSet;
}

bool Analyzer::takeInput(ParsedIRmodule& m)
{
	p_IRmodule = &m;
	return true;
}



MetaDataSet* Analyzer::getMetaDataSet(){
	return p_MetaDataSet;
}


std::unique_ptr<Module>* Analyzer::getIRmodule()
{
	return p_IRmodule;
}

IPA::SymbolManager* Analyzer::getSymbolManager()
{
	return p_symbolManager;
}

CompactBBInfoList* Analyzer::getCompactBBInfoList()
{
	return p_CompactBBInfoList;
}

wBasicBlock* Analyzer::getProgramEntryBlock()
{
	return getMetaDataSet()->getEntryFunc()->getEntryBlock();
}



bool Analyzer::Preprocess()
{
	if(Preprocess1() != true){
		return false;
	}
	if(Preprocess2() != true){
		return false;
	}

	if(Preprocess3() != true){
		return false;
	}

	return true;
}


/* Preprocess1: Configure parsedIRmodule */
/*
   Preprocess1: Split the existing Basicblock
   An existing Basicblock could have one or more function call.
   This preprocess make one Basicblock has just one function call.
*/
bool Analyzer::Preprocess1(){

	ParsedIRmodule &m = *p_IRmodule;

	while(splitBBModuleChecker(m) != 0){
		splitBBModuleOnce(m);
	}
	splitBBModuleOnce(m);

	return true;
}

/* Preporcess1: splitBBModuleChecker */
int Analyzer::splitBBModuleChecker(ParsedIRmodule &m){


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
#ifdef DEBUG_WRAPPER
					std::cout << "[INCREASE]" <<std::endl;
#endif
					InstCall_flag = 1;
				}
      		}
			/* Decrease CheckSum per BB if BB has a Call Inst */
			if(InstCall_flag == 1){
				CheckSum--;
#ifdef DEBUG_WRAPPER
				std::cout << "[DECREASE]" <<std::endl;
#endif			
			}
    	}
		
		
  	}

#ifdef DEBUG_WRAPPER
	std::cout << "[CheckSum]: " << CheckSum << std::endl;
#endif			

	return CheckSum;
}


/* Preporcess1: splitBBModuleOnce */
bool Analyzer::splitBBModuleOnce(ParsedIRmodule &m){

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
					//if((!strcmp(pastInst->getOpcodeName(), "call")) 
					//&& (strcmp(inst.getOpcodeName(), "br") && strcmp(inst.getOpcodeName(), "ret"))){
					
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


/* Preprocess2: Generate Meta data */
bool Analyzer::Preprocess2(){

	std::unique_ptr<Module> &m = *p_IRmodule;

	unsigned int FunctionID = 0x0000;
	unsigned int BasicBlockID = 0x0000;

	/* Module Entry */
  	for (auto iter1 = m->getFunctionList().begin(); iter1 != m->getFunctionList().end(); iter1++) {


		/* Function Entry */
		Function &f = *iter1;
		wFunction *wf = new wFunction(p_IRmodule, this);
		wf->setwFunction(&f);
		wf->setID(++FunctionID);
		BasicBlockID = 0x0000;
		p_MetaDataSet->pushFuncList(wf);
	
		if(f.getName().str() == "main")
		{
			p_MetaDataSet->setEntryFunc(wf);
		}


		/* Need to be fashioned */
		/* Not traverse FunctionList */

		/*
		if(isPathUncountedFunction(f.getName().str())){


			BasicBlock &bb = f.getBasicBlockList().front();
			wBasicBlock *wbb = new wBasicBlock;
			wbb->setName(f.getName().str() + std::string("%") + std::to_string(0));
				
			wbb->setwBasicBlock(&bb);
			wf->pushBBList(wbb);
			
			continue;
		}
		*/
		if(0)
		{

		}

		else {
	
			unsigned int BBNumber = 0;
			for (auto iter2 = f.getBasicBlockList().begin(); iter2 != f.getBasicBlockList().end(); iter2++) {


				/* BasicBlock Entry */
				BasicBlock &bb = *iter2;
				wBasicBlock *wbb = new wBasicBlock;
				wbb->setName(f.getName().str() + std::string("%") + std::to_string(BBNumber++));
				
				wbb->setwBasicBlock(&bb);
				wbb->setID(FunctionID << 16 | (++BasicBlockID));
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
		}
			/* Function EndPoint */	
  	}


	return true;

}


/* Preprocess2: isPathUncountedFunction */
/*   
   determine a path-uncounted function 
*/
bool Analyzer::isPathUncountedFunction(
		const std::string& fn)
{

	for(auto iter1 = p_symbolManager->getPUFL().begin();
			iter1 != p_symbolManager->getPUFL().end(); iter1++)
	{
		std::string& PUF = *(*iter1);
		if(fn == PUF)
		{
			return true;
		}
	}

	return false;
}




/* Preprocess3: Configure Meta data */
bool Analyzer::Preprocess3()
{
	
	if(BasicBlockBranchAndFunctionCallImpl() != true)
	{
		std::cout << " -BasicBlockBranchAndFunctionCallImpl Fails" << std::endl;
		return false;
	}

	if(makePathsInEachFunction() != true)
	{
		std::cout << " -makePathsInEachFunction Fails" << std::endl;
		return false;
	}

	return true;
}


/* Preporcess3: BasicBlockBranchAndFunctionCallImpl */
/*
   1. make connection of each Basicblock.
   2. classify each Basicblock(call/br/return)
    - call type: call a function
	- br: have a conditional branch
	- return: exit the function
*/

bool Analyzer::BasicBlockBranchAndFunctionCallImpl(){


	std::list<wFunction *>::iterator iter1;
	for(iter1 = p_MetaDataSet->getwFuncList()->begin(); iter1 != p_MetaDataSet->getwFuncList()->end(); iter1++){

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
					wFunction *target_wfunc =  p_MetaDataSet->SearchFunction(branch_func);
					(*iter2)->pushFuncCallList(target_wfunc);

					//CurrentBB->setType(wBasicBlock::ONE_BRANCH);
					CurrentBB->setType(wBasicBlock::CALL);
				}

				else if(!strcmp(CurrentInst->getOpcodeName(), "br")){
					/* Unconditional branch */
					if(CurrentInst->getNumOperands() == 1){
						Value* opnd = CurrentInst->getOperand(CurrentInst->getNumOperands() -1);

						BasicBlock *BranchBB = reinterpret_cast<BasicBlock *>(opnd);
						wBasicBlock* BranchwBB = CurrentFunc->SearchBasicBlock(BranchBB);
			
						std::pair<wBasicBlock* , wBasicBlock *> *BranchwBBpair 
							= new std::pair<wBasicBlock *, wBasicBlock *>
							(BranchwBB , reinterpret_cast<wBasicBlock *>(0)); 
						
						CurrentBB->setBranchBlock(BranchwBBpair);
			
						if(CurrentBB->hasCall() != true)
						{
							CurrentBB->setType(wBasicBlock::ONE_BRANCH);
						}
					}
					
					/* Conditional branch: LLVM IR only two direction */	
				
					
					else if(CurrentInst->getNumOperands() == 3) {
						Value* opnd1 = CurrentInst->getOperand(CurrentInst->getNumOperands() -1);
						BasicBlock *BranchBB1 = reinterpret_cast<BasicBlock *>(opnd1);
						wBasicBlock* BranchwBB1 = CurrentFunc->SearchBasicBlock(BranchBB1);
					

						Value* opnd2 = CurrentInst->getOperand(CurrentInst->getNumOperands() -2);
						BasicBlock *BranchBB2 = reinterpret_cast<BasicBlock *>(opnd2);
						wBasicBlock* BranchwBB2 = CurrentFunc->SearchBasicBlock(BranchBB2);
						
						std::pair<wBasicBlock* , wBasicBlock *> *BranchwBBpair 
							= new std::pair<wBasicBlock *, wBasicBlock *>(BranchwBB1 , BranchwBB2); 
					
						CurrentBB->setBranchBlock(BranchwBBpair);
						CurrentBB->setType(wBasicBlock::TWO_BRANCH);
					}

					else
					{
						continue;
					}
				}
				else if(!strcmp(CurrentInst->getOpcodeName(), "ret")){		
					CurrentBB->setType(wBasicBlock::RETURN);
					//CurrentBB->setType(0);
				}

				else
				{
					continue;
				}
			}
		}


	}
	
	return true;
}

/* Preporcess3: makePathsInEachFunction */
/*
   1. make Pathlist in each function
   2. determine the uncounted function when generating path
*/
bool Analyzer::makePathsInEachFunction(){

	std::list<wFunction *> *TraverseFuncList = p_MetaDataSet->getwFuncList();
	std::list<wFunction *>::iterator iter;


	for(iter = TraverseFuncList->begin(); iter != TraverseFuncList->end(); iter++){

		wFunction *current = *iter;

		/* if work well without this, delete it */
		 
		if( current->getFunction()->getName().str() == "free" 
				|| current->getFunction()->getName().str() == "malloc"){

			Function *f = current->getFunction();
			BasicBlock &entry = f->getBasicBlockList().front();
			wBasicBlock *entrywBB = current->SearchBasicBlock(&entry);
			(*iter)->IntrinsicFuncMakePathsList(entrywBB);
			(*iter)->makePathList();
		}
		
		else{
		
		
			(*iter)->makeBBPathList((*iter)->SearchBasicBlock(&((*iter)->getFunction()->getEntryBlock())));
			(*iter)->makePathList();
		
		}
	}
	return true;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool Analyzer::ShowPathsInEachFunc(){

	std::cout << "[Function Paths]" << std::endl;

	std::list<wFunction *> *TraverseFuncList = p_MetaDataSet->getwFuncList();
	std::list<wFunction *>::iterator iter;

	for(iter = TraverseFuncList->begin(); iter != TraverseFuncList->end(); iter++){
		std::cout << (*iter)->getFunction()->getName().str();
		std::cout << "(PathNum: " << (*iter)->getNumPaths()  << ")" << std::endl;;
		(*iter)->showPathsList();	
		std::cout << std::endl;
	}

	std::cout << std::endl;
	return true;
}





bool Analyzer::DebugWrapperModule()
{

	std::cout << "[Debug Test]" << std::endl;
	std::list<wFunction *>::iterator iter1;
	for(iter1 = p_MetaDataSet->getwFuncList()->begin(); iter1 != p_MetaDataSet->getwFuncList()->end(); iter1++){
		std::cout << "Function: " << (*iter1)->getFunction()->getName().str() << "(" ;

		wFunction *wfunc = (*iter1);
		std::list<wBasicBlock *>::iterator iter2;

		if(wfunc->getFuncRetTy() == wFunction::FuncRetTy::VoidTy){
			std::cout << "VoidTy)" << std::endl;
		}else{
			std::cout << "NonVoidTy)" << std::endl;
		}

		for(iter2 = wfunc->getwBBList()->begin(); iter2 != wfunc->getwBBList()->end(); iter2++){
			std::cout << " BasicBlock: " << (*iter2)->getBasicBlock() << " ";
			std::cout << " wBasicBlock: " << (*iter2) << " ";
			std::cout << "[" << *((*iter2)->getName()) << "]";	
			std::cout << "Call Num: " << (*iter2)->getNumFuncCall() << std::endl;
			std::cout << " BB_ID: " << std::hex <<  (*iter2)->getID() << std::dec;
		
			std::cout << ", Type: " << (*iter2)->getType();
			
			std::pair<wBasicBlock *, wBasicBlock *> *branchBlockPair = (*iter2)->getBranchBlock();

			if((*iter2)->getType() == wBasicBlock::ONE_BRANCH){
				wBasicBlock *target1 = branchBlockPair->first;
				std::cout << " [BranchBlock]: " << target1->getBasicBlock() << " ";
				std::cout << " [wBranchBlock]: " << target1->getBasicBlock() << std::endl;

			}	
			else if((*iter2)->getType() == wBasicBlock::TWO_BRANCH)
			{
				wBasicBlock *target1 = branchBlockPair->first;
				wBasicBlock *target2 = branchBlockPair->second;
				std::cout << " [BranchBlock]: " << target1->getBasicBlock() << " ";
				std::cout << " [wBranchBlock]: " << target1 << std::endl;
				std::cout << " [BranchBlock]: " << target2->getBasicBlock() << " ";
				std::cout << " [wBranchBlock]: " << target2 << std::endl;
			
			}
			else if((*iter2)->getType() == wBasicBlock::CALL)
			{
				std::cout << " [CALL]" << std::endl;
			}			
			else 
			{
				std::cout << " [Return]" << std::endl;
			}

			wBasicBlock *wbb = (*iter2);
			std::list<wInstruction *>::iterator iter3;
			for(iter3 = wbb->getwInstList()->begin(); iter3 != wbb->getwInstList()->end(); iter3++){
				std::cout << "   Instruction: " << (*iter3)->getInstruction()->getOpcodeName();
					
				wInstruction *wInst = *iter3;
				int opnt_cnt = wInst->getInstruction()->getNumOperands();

				for(int i = 0; i < opnt_cnt; i++)
       	 		{
          			Value *opnd = wInst->getInstruction()->getOperand(i);
					std::string o = opnd->getName();
					if(opnd->hasName()) {
						std::cout << " [S]" << o;

					} else {
						std::cout << " [P]" << opnd;
					}
				}
				std::cout << std::endl;
				
			}
		}	
	}
	return true;

}

/* Process */
/*
   1. IRImplanter
   : Implant Signal Codes into the input IR code
    - sig_initializer();
	- sig_checker();

   2. MonitoringCodeGenerator
   : Generate Monitoring code according to Analysis Results

*/
bool Analyzer::Process()
{

	if(AnalysisForSignalCodeImplanter() != true)
	{
		std::cout << " -AnalysisForSignalCodeImplanter Fails" << std::endl;
		return false;
	}

	if(AnalysisForMonitoringCodeGenerator() != true)
	{
		std::cout << " -AnalsysForMonitoringCodeGenerator Fails" << std::endl;
		return false;
	}

	return true;
}

bool Analyzer::AnalysisForSignalCodeImplanter()
{
	
	if(p_CompactImplantedBBList == nullptr)
	{
		p_CompactImplantedBBList = new CompactImplantedBBList;
	}

	for(auto iter1 = p_MetaDataSet->getwFuncList()->begin();
			iter1 != p_MetaDataSet->getwFuncList()->end();
			iter1++)
	{

		wFunction* Wf = *iter1;

		for(auto iter2 = Wf->getwBBList()->begin();
				iter2 != Wf->getwBBList()->end();
				iter2++)
		{

			wBasicBlock* currentWBB = *iter2;
			llvm::BasicBlock* currentBB = currentWBB->getBasicBlock();

			p_CompactImplantedBBList->insert(std::make_pair(currentBB, currentWBB->getID()));
	
			//p_CompactImplantedBBList->push_back(currentBB);
		}
	}
	

	return true;
}


CompactImplantedBBList* Analyzer::getCompactImplantedBBList()
{
	return p_CompactImplantedBBList;
}




bool Analyzer::AnalysisForMonitoringCodeGenerator()
{
	
	if(p_CompactBBInfoList == nullptr)
	{
		p_CompactBBInfoList = new CompactBBInfoList;
	}

	for(auto iter1 = p_MetaDataSet->getwFuncList()->begin();
			iter1 != p_MetaDataSet->getwFuncList()->end();
			iter1++)
	{
		wFunction* currentF = *iter1;
		for(auto iter2 = currentF->getwBBList()->begin();
				iter2 != currentF->getwBBList()->end();
				iter2++)
		{
			wBasicBlock* currentBB = *iter2;

			CompactBBInfo* newCompactBBInfo = nullptr;
			if(currentBB->getType() == wBasicBlock::BB_type::RETURN)
			{
				if(currentBB->getParentFunction()->getName().str() == "main")
				{
					newCompactBBInfo
						= new CompactBBInfo(
								currentBB->getID(),
								4,
								0, 
								0);
				}

				else
				{
					newCompactBBInfo
						= new CompactBBInfo(
								currentBB->getID(),
								0,
								0, 
								0);
				}
			}

			else if(currentBB->getType() == wBasicBlock::BB_type::CALL)
			{
				wBasicBlock* nextBB1 = currentBB->getFuncCallEntryBB();
				wBasicBlock* nextBB2 = currentBB->getBranchBlock()->first;

				newCompactBBInfo
					= new CompactBBInfo(
							currentBB->getID(),
							3,
							nextBB1->getID(),
							nextBB2->getID());
					
			}

			else if(currentBB->getType() == wBasicBlock::BB_type::ONE_BRANCH)
			{	
				wBasicBlock* nextBB1 = currentBB->getBranchBlock()->first;

				newCompactBBInfo
					= new CompactBBInfo(
							currentBB->getID(),
							1,
							nextBB1->getID(),
							0);
			}

			else if(currentBB->getType() == wBasicBlock::BB_type::TWO_BRANCH)
			{
				wBasicBlock* nextBB1 = currentBB->getBranchBlock()->first;
				wBasicBlock* nextBB2 = currentBB->getBranchBlock()->second;
				
				newCompactBBInfo
					= new CompactBBInfo(
							currentBB->getID(),
							2,
							nextBB1->getID(),
							nextBB2->getID());
			}

			else
			{
				/* Undefined BasicBlock type */
				return false;
			}

			p_CompactBBInfoList->push_back(newCompactBBInfo);
						
		}

	}

	return true;
}

bool Analyzer::Debug_Show_CompactBBInfo()
{
	for(auto iter = p_CompactBBInfoList->begin();
			iter != p_CompactBBInfoList->end();
			iter++)
	{

		CompactBBInfo* currentCompactBBInfo = *iter;

		std::cout << "node_id: " << std::hex << currentCompactBBInfo->node_id << std::endl;
		std::cout << "numConnection: " << std::dec << currentCompactBBInfo->numConnection << std::endl;
		std::cout << "nextNode[0]: " << std::hex << currentCompactBBInfo->nextNode[0] << std::endl;
		std::cout << "nextNode[1]: " << currentCompactBBInfo->nextNode[1] << std::endl << std::dec;
		std::cout << std::endl;
	}

	return true;
}


/////////////////////////////////////////////////////////////

