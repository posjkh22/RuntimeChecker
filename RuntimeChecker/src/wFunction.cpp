#include "wFunction.hpp"

///////////////* wFunction */////////////


std::string wFunction::getName()
{
	
	llvm::Function* f = getFunction(); 
	return f->getName().str();
}

wBasicBlock* wFunction::getEntryBlock()
{
	return (*wBBList.begin()); 
}

wFunction::wFunction(ParsedIRmodule* module,  Analyzer* analyzer){
	p_ParsedIRmodule = module;
	p_Analyzer = analyzer;
	makePathList();

}

unsigned int wFunction::getID()
{
	return ID;
}

bool wFunction::setID(unsigned int id)
{
	ID = id;
	return true;
}

bool wFunction::determineFuncRetTy(){

	llvm::Function *f = getFunction();

	for(auto iter1 = f->getBasicBlockList().begin();
			iter1 != f->getBasicBlockList().end(); iter1++){

		llvm::BasicBlock &bb = *iter1;
		for (auto iter2 = bb.begin(); iter2 != bb.end(); iter2++) {

			llvm::Instruction &inst = *iter2; 

			if(inst.getOpcodeName() == std::string("ret")){

				if(inst.getNumOperands() == 0){
					setFuncRetTy(FuncRetTy::VoidTy);
				}
				else{
					setFuncRetTy(FuncRetTy::NonVoidTy);
				}
			}else{

				continue;
			}		
			
		}
	}
	/*
	if(){
		setFuncRetTy(FuncRetTy::voidTy)
	}
	else{
		setFuncRetTy(FuncRetTy::NonVoidTy)
	}
	*/
	return true;
}

bool wFunction::setFuncRetTy(wFunction::FuncRetTy type){
	retTy = type;
	return true;
}

wFunction::FuncRetTy wFunction::getFuncRetTy(){
	return retTy;
}


/* wrapper */
bool wFunction::setwFunction(Function *f){
	func = f;
	return true;
}

Function *wFunction::getFunction(){
	return func;
}

wFunction* wFunction::getCallerFunc(){
	return callerFunc;
}

bool wFunction::setCallerFunc(wFunction* func){
	callerFunc = func;
	return true;
}

bool wFunction::pushBBList(wBasicBlock *bb){
	wBBList.push_back(bb);
	return true;
}

wBasicBlock *wFunction::getCurrentBasicBlock(){
	return CurrentBasicBlock;
}

bool wFunction::setCurrentBasicBlock(wBasicBlock *wbb){
	CurrentBasicBlock = wbb;
	return true;
}

PathTy*wFunction::getwBBList(){
	return &wBBList;
}

wBasicBlock *wFunction::SearchBasicBlock(BasicBlock *bb){

	PathTy* wbblist = getwBBList();
	PathTy::iterator iter;

	for(iter = wbblist->begin(); iter != wbblist->end(); iter++){
		if( (*iter)->getBasicBlock() == bb){
			//std::cout << "Target BB Find! ";
			break;
		}
	}
	return (*iter);
}



/* CFG Impl */

BBPathListTy *wFunction::getBBPathList(){
	return &m_BBPathList;
}


bool wFunction::IntrinsicFuncMakePathsList(wBasicBlock *wbb){

	PathTy *new_cfg = new PathTy;
	new_cfg->push_back(wbb);
	m_BBPathList.push_back(new_cfg);
	
	return true;
}


bool wFunction::makeBBPathList(wBasicBlock *wbb){


	/* function entryBB */
	if(m_BBPathList.empty()){
	
		//std::cout << "FIRST!" << std::endl;
		PathTy*new_cfg = new PathTy;
		new_cfg->push_back(wbb);
		m_BBPathList.push_back(new_cfg);
	}

	/* NOT function entryBB */
	PathTy*current_cfg;
	BBPathListTy::iterator iter;
	/* Find out the right CFG */
	for(iter = m_BBPathList.begin(); iter != m_BBPathList.end(); iter++){
		current_cfg = (*iter);
		if(wbb == current_cfg->back()){
			//std::cout << "FIND!" << std::endl;
			break;
		}
	}

	if(wbb->getType() == wBasicBlock::ONE_BRANCH){
		//std::cout << "ONE PATH!" << std::endl;

		std::pair<wBasicBlock *, wBasicBlock *> *BranchBlockPair;
		BranchBlockPair = wbb->getBranchBlock();
		wBasicBlock *targetBlock = BranchBlockPair->first;
		current_cfg->push_back(targetBlock);
		makeBBPathList(targetBlock);
	}

	else if(wbb->getType() == wBasicBlock::TWO_BRANCH){

		//std::cout << "TWO PATH!" << std::endl;
		PathTy* new_copy_cfg = new PathTy(*current_cfg);
		
		std::pair<wBasicBlock *, wBasicBlock *> *BranchBlockPair;
		BranchBlockPair = wbb->getBranchBlock();
		wBasicBlock *targetBlock1 = BranchBlockPair->first;
		wBasicBlock *targetBlock2 = BranchBlockPair->second;
		
		current_cfg->push_back(targetBlock1);
		new_copy_cfg->push_back(targetBlock2);
		m_BBPathList.push_back(new_copy_cfg);
		makeBBPathList(targetBlock1);
		makeBBPathList(targetBlock2);

	}
	/* BB_type = RETURN*/

	else{
		//std::cout << "RETURN! " << std::endl;
		return true;
	}

	return true;
}

bool wFunction::showPathsList(){


	PathTy* current_cfg;
	BBPathListTy::iterator iter1;
	PathTy::iterator iter2;

	for(iter1 = m_BBPathList.begin(); iter1 != m_BBPathList.end(); iter1++){
		current_cfg = (*iter1);
		
		std::cout << " - path: ";
		for(iter2 = current_cfg->begin(); iter2 != current_cfg->end(); iter2++){

			std::cout << " " << *((*iter2)->getName());
		}
		std::cout << std::endl;
	}

	return true;
}

unsigned int wFunction::getNumPaths(){
	return m_BBPathList.size();
}

PathListTy *wFunction::makePathList(){

	BBPathListTy::iterator iter;

	Path *temp_path;
	for(iter = m_BBPathList.begin(); iter != m_BBPathList.end(); iter++){

		temp_path = new Path(*iter);
		m_PathList.push_back(temp_path);

	}

	return &m_PathList;
}

PathListTy *wFunction::getPathList(){
	return &m_PathList;
}
