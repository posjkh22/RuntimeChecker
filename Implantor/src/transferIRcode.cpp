
#include "transferIRcode.hpp"

transferIRcode::transferIRcode(CompactBBList* CB)
{
	p_CompactBBList = CB;
}


bool transferIRcode::InsertCallInstruction(std::unique_ptr<Module> &m, LLVMContext &context, IRBuilder<> &builder, llvm::BasicBlock *bb, Instruction *inst){

	static int num1 = 0;
	static int num2 = 0;


	if(bb->size() > 0)
	{
	inst->setParent(bb);
	llvm::Instruction *newInst = inst->clone();
	
	llvm::Type *i32_type = llvm::IntegerType::getInt32Ty(context);
	Value *constant_two = llvm::ConstantInt::get(i32_type, 2, true);
	
	newInst->setOperand(0, constant_two);
	bb->getInstList().push_front(newInst);
	}
	return true;
}

bool transferIRcode::InsertFunction(std::unique_ptr<Module> &m, LLVMContext &context, IRBuilder<> &builder){


	/* Function-1 */

	FunctionType *void_return_one_integer = llvm::FunctionType::get(builder.getVoidTy(), IntegerType::get(context, 32), false);
	
	
	Constant *c = m->getOrInsertFunction("checker0", \
											void_return_one_integer);
	Function* checker0 = cast<Function>(c);
	


	/* Function-type : void return/ no param */
	FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
	
	
	/* General Puts Function */

	
	/* checker1 */
	
	Constant *checker1_ptr = m->getOrInsertFunction("sig_initializer", void_return_one_integer); 
	//Constant *checker1_ptr = m->getOrInsertFunction("sig_initializer", funcType); 
	Function *checker1 = cast<Function>(checker1_ptr);

	/* checker2 */
	
	Constant *checker2_ptr = m->getOrInsertFunction("sig_checker", void_return_one_integer); 
	//Constant *checker2_ptr = m->getOrInsertFunction("sig_checker", funcType); 
	Function *checker2 = cast<Function>(checker2_ptr);



	/* Call checker Set */

	
	Constant *gcdptr = m->getOrInsertFunction("CallcheckerSet", funcType); 
	Function *gcd = cast<Function>(gcdptr);
	llvm::BasicBlock *entry = BasicBlock::Create(context, "entry", gcd);
	IRBuilder<> CallChecker_builder(entry);
	

	/* Operand */
	Value *constant_one1 = llvm::ConstantVector::get(CallChecker_builder.getInt32(1));
	Value *constant_one2 = llvm::ConstantFP::get(CallChecker_builder.getDoubleTy(), 1);

	llvm::Type *i32_type = llvm::IntegerType::getInt32Ty(context);
	Value *constant_one3 = llvm::ConstantInt::get(i32_type, 1, true);
	
	//Value *constant_one4 = llvm::ConstantInt::get(CallChecker_builder.getInt32(1));
	//Value *constant_one3 = llvm::IntegerType::get(context, 1);

	Value *call_checker1 = CallChecker_builder.CreateCall(checker1, constant_one3);
	Value *call_checker2 = CallChecker_builder.CreateCall(checker2, constant_one3);

	//Value *call_checker1 = CallChecker_builder.CreateCall(checker1);
	//Value *call_checker2 = CallChecker_builder.CreateCall(checker2);
	Value *call_checker3 = CallChecker_builder.CreateCall(checker0, constant_one3);
	
	CallChecker_builder.CreateRetVoid();
	
	
	return true;
}



llvm::BasicBlock *transferIRcode::GetTargetBasicBlock(std::unique_ptr<Module> &m, std::string fname){

	llvm::Instruction *SavedInst;
	llvm::BasicBlock *SavedBB;

  	for (auto iter1 = m->getFunctionList().begin(); iter1 != m->getFunctionList().end(); iter1++) {

		Function &f = *iter1;
		if(f.getName().str() == fname){

			std::cout << "Function found!" << std::endl;


			llvm::Function::BasicBlockListType::iterator iter2;
			iter2 = f.getBasicBlockList().begin();

			llvm::BasicBlock &bb = *iter2;
			
			SavedBB = &bb;
			break;
		}
	}

	return SavedBB;
}


llvm::Instruction *transferIRcode::GetTargetBasicBlockCloned(std::unique_ptr<Module> &m){

	llvm::Instruction *SavedInst = nullptr;
	llvm::BasicBlock *SavedBB = nullptr;

	std::list<llvm::Instruction *> InstList;
	std::list<llvm::Instruction *>::iterator InstList_iter;
  	static int iterPoint = 0;
	for (auto iter1 = m->getFunctionList().begin(); iter1 != m->getFunctionList().end(); iter1++) {

		Function &f = *iter1;
		if(f.getName().str() == std::string("CallcheckerSet")){

			std::cout << "Function found!" << std::endl;

			for (auto iter2 = f.getBasicBlockList().begin(); iter2 != f.getBasicBlockList().end(); iter2++) {

				llvm::BasicBlock &bb = *iter2;

				auto iter4 = bb.end();
				for (auto iter3 = bb.begin(); iter3 != iter4; iter3++) {


					llvm::Instruction &inst = *iter3;
					
					
					if(inst.getOpcodeName() == std::string("call")){
						
						SavedInst = &inst;
						SavedBB = &bb;

						InstList.push_back(SavedInst);
						
					}
					
				}
			}
		}
	}

	llvm::Instruction *ReturnInst = nullptr;
	int i = 0;
	for(InstList_iter = InstList.begin();  
			InstList_iter != InstList.end(); InstList_iter++, i++){

		if(i == iterPoint){
			ReturnInst = (*InstList_iter);
			break;
		}
	}

	iterPoint++;

	return ReturnInst;
}

llvm::Instruction *transferIRcode::GetTargetBasicBlockCloned2(std::unique_ptr<Module> &m){

	llvm::Instruction *SavedInst = nullptr;
	llvm::BasicBlock *SavedBB = nullptr;
	llvm::Instruction *ReturnInst = nullptr;


	std::list<llvm::Instruction *> InstList;
	std::list<llvm::Instruction *>::iterator InstList_iter;
  	static int iterPoint = 0;
	static bool init_flag = true;

	for(auto iter1 = m->getFunctionList().begin(); 
			iter1 != m->getFunctionList().end(); iter1++) {

		Function &f = *iter1;
		if(f.getName().str() == std::string("CallcheckerSet")){

			std::cout << "Function found!" << std::endl;

			for (auto iter2 = f.getBasicBlockList().begin(); 
					iter2 != f.getBasicBlockList().end(); iter2++) {

				llvm::BasicBlock &bb = *iter2;

				auto iter4 = bb.end();
				for (auto iter3 = bb.begin(); iter3 != iter4; iter3++) {


					llvm::Instruction &inst = *iter3;
					
					if(inst.getOpcodeName() == std::string("call")){
						
						SavedInst = &inst;
						SavedBB = &bb;

						InstList.push_back(SavedInst);
						
					}
					
				}
			}
		}
	}


	int i = 0;
	
	ReturnInst = *(InstList.begin());
	
	
	if(init_flag ==  true)
	{
		ReturnInst = *(InstList.begin());
	}
	else
	{
		InstList_iter = InstList.begin();
		InstList_iter++;
		ReturnInst = *(InstList_iter);
	}
	
	init_flag = false;
	
	return ReturnInst;
}


bool transferIRcode::InsertIRcode(std::unique_ptr<Module> &m, LLVMContext &context, IRBuilder<> &builder, const char *fname){

	/* Get Target llvm::BasicBlock */
	llvm::BasicBlock *Target 			= GetTargetBasicBlock(m, std::string(fname));

	/* Get llvm::Instruction to insert */
	llvm::Instruction *TargetCloned 	= GetTargetBasicBlockCloned(m);

	/* Insert the llvm::Instruction into Target llvm::BasicBlock at the entry of BB */
	InsertCallInstruction(m, context, builder, Target, TargetCloned);

	return true;
}


bool transferIRcode::InsertAllBasicBlock(
		std::unique_ptr<Module> &m, LLVMContext &context, IRBuilder<> &builder)
{
	
	/* sig_initializer */
	
	llvm::BasicBlock *Target 			= GetTargetBasicBlock(m, std::string("main"));
	llvm::Instruction *TargetCloned 	= GetTargetBasicBlockCloned2(m);

	InsertCallInstruction(m, context, builder, Target, TargetCloned);
	

	/* sig_checker */
	for(auto iter = p_CompactBBList->begin();
			iter != p_CompactBBList->end(); iter++)
	{
		std::cout << "Work done0!" << std::endl;
		llvm::BasicBlock *Target = *iter;
		llvm::Instruction *TargetCloned 	= GetTargetBasicBlockCloned2(m);

		InsertCallInstruction(m, context, builder, Target, TargetCloned);
	}
	return true;
}




