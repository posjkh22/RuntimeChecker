
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
	bb->getInstList().push_front(newInst);
	}
	return true;
}

bool transferIRcode::InsertFunction(std::unique_ptr<Module> &m, LLVMContext &context, IRBuilder<> &builder){


	/* Function-1 */

	/*
	Constant *c = m->getOrInsertFunction("checker0", \
											IntegerType::get(context, 32), \
											IntegerType::get(context, 32), \
											IntegerType::get(context, 32), \
											IntegerType::get(context, 32));
 	Function* checker0 = cast<Function>(c);
	checker0->setCallingConv(CallingConv::C);

	Function::arg_iterator args = checker0->arg_begin();
	Value* x = args++;
	x->setName("x");
	Value* y = args++;
	y->setName("y");
	Value* z = args++;
	z->setName("z");

	llvm::BasicBlock* block = BasicBlock::Create(context, "entry", checker0);
	IRBuilder<> builder2(block);

	Value* tmp = builder2.CreateBinOp(llvm::Instruction::Mul, x, y, "tmp");
	Value* tmp2 = builder2.CreateBinOp(llvm::Instruction::Add, tmp, z, "temp2");

	builder2.CreateRet(tmp2);
 	
	*/
	


	/* Function-type : void return/ no param */
	FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
	
	
	/* General Puts Function */

	/*
	std::vector<llvm::Type *> putsArgs;
	putsArgs.push_back(builder.getInt8Ty()->getPointerTo());
	llvm::ArrayRef<llvm::Type*>  argsRef(putsArgs);
	
	llvm::FunctionType *putsType = 
		llvm::FunctionType::get(builder.getInt32Ty(), argsRef, false);
 	
	llvm::Constant *putsFunc = m->getOrInsertFunction("puts", putsType);
 	*/
	
	/* checker1 */
	
	Constant *checker1_ptr = m->getOrInsertFunction("sig_initializer", funcType); 
	Function *checker1 = cast<Function>(checker1_ptr);

	/*
	llvm::BasicBlock *checker1_entry = BasicBlock::Create(context, "entry", checker1);
	IRBuilder<> checker_builder1(checker1_entry);
	Value *checker_message1 
		= checker_builder1.CreateGlobalStringPtr("Checker1 run!\n");
	checker_builder1.CreateCall(putsFunc, checker_message1);
	checker_builder1.CreateRetVoid();
	*/

	/* checker2 */
	
	Constant *checker2_ptr = m->getOrInsertFunction("sig_checker", funcType); 
	Function *checker2 = cast<Function>(checker2_ptr);

	/*
	llvm::BasicBlock *checker2_entry = BasicBlock::Create(context, "entry", checker2);
	IRBuilder<> checker_builder2(checker2_entry);
	Value *checker_message2 
		= checker_builder2.CreateGlobalStringPtr("Checker2 run!\n");
	checker_builder2.CreateCall(putsFunc, checker_message2);
	checker_builder2.CreateRetVoid();
	*/

	/* checker3 */
	/*
	Constant *checker3_ptr = m->getOrInsertFunction("checker3", funcType); 
	Function *checker3 = cast<Function>(checker3_ptr);
	llvm::BasicBlock *checker3_entry = BasicBlock::Create(context, "entry", checker3);
	IRBuilder<> checker_builder3(checker3_entry);
	Value *checker_message3 
		= checker_builder3.CreateGlobalStringPtr("Checker3 run!\n");
	checker_builder3.CreateCall(putsFunc, checker_message3);
	checker_builder3.CreateRetVoid();
	*/

	/* checker4 */
	/*
	Constant *checker4_ptr = m->getOrInsertFunction("checker4", funcType); 
	Function *checker4 = cast<Function>(checker4_ptr);
	llvm::BasicBlock *checker4_entry = BasicBlock::Create(context, "entry", checker4);
	IRBuilder<> checker_builder4(checker4_entry);
	Value *checker_message4 
		= checker_builder4.CreateGlobalStringPtr("Checker4 run!\n");
	checker_builder4.CreateCall(putsFunc, checker_message4);
	checker_builder4.CreateRetVoid();
	*/

	/* checker5 */
	/*
	Constant *checker5_ptr = m->getOrInsertFunction("checker5", funcType); 
	Function *checker5 = cast<Function>(checker5_ptr);
	llvm::BasicBlock *checker5_entry = BasicBlock::Create(context, "entry", checker5);
	IRBuilder<> checker_builder5(checker5_entry);
	Value *checker_message5 
		= checker_builder5.CreateGlobalStringPtr("Checker5 run!\n");
	checker_builder5.CreateCall(putsFunc, checker_message5);
	checker_builder5.CreateRetVoid();
	*/




	/* Call checker Set */
	
	Constant *gcdptr = m->getOrInsertFunction("CallcheckerSet", funcType); 
	Function *gcd = cast<Function>(gcdptr);
	llvm::BasicBlock *entry = BasicBlock::Create(context, "entry", gcd);
	IRBuilder<> CallChecker_builder(entry);
	

	Value *call_checker1 = CallChecker_builder.CreateCall(checker1);
	Value *call_checker2 = CallChecker_builder.CreateCall(checker2);

	/*
	Value *call_checker3 = CallChecker_builder.CreateCall(checker3);
	Value *call_checker4 = CallChecker_builder.CreateCall(checker4);
	Value *call_checker5 = CallChecker_builder.CreateCall(checker5);
	*/
	
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




