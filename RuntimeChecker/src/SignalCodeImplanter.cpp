
#include "SignalCodeImplanter.hpp"

using namespace llvm;

SignalCodeImplanter::SignalCodeImplanter(LLVMContext& context)
	: m_context(context)
{
	p_Analyzer = nullptr;
}

bool SignalCodeImplanter::TakeAnalysisResults(Analyzer* analyzer)
{
	if(p_Analyzer == nullptr)
	{
		p_Analyzer = analyzer;
		p_CompactImplantedBBList 
			= p_Analyzer->getCompactImplantedBBList();
		p_ParsedIRmodule = p_Analyzer->getIRmodule();
	}

	else
	{
		delete p_Analyzer;
		p_Analyzer = analyzer;
		p_CompactImplantedBBList 
			= p_Analyzer->getCompactImplantedBBList();
		p_ParsedIRmodule = p_Analyzer->getIRmodule();
	}

	m_level = IMPLANT_LEVEL::FINE_GRAINED_LEVEL;

	/*
	for(auto iter = p_CompactImplantedBBList->begin();
			iter != p_CompactImplantedBBList->end(); iter++)

	{
		std::cout << "node_id: " << std::hex << iter->second << std::oct << std::endl;
	}
	*/
	return true;
}

bool SignalCodeImplanter::run()
{

	if(m_level == FINE_GRAINED_LEVEL)
	{
		if(RunFineGrainedLevel() != true)
		{
			std::cout << " -RunFineGrainedLevel Fails" << std::endl;
		}
	}


	else if(m_level == COARSE_GRAINED_LEVEL)
	{
		if(RunCoarseGrainedLevel() != true)
		{
			std::cout << " -RunCoarseGrainedLevel Fails" << std::endl;
		}

	}

	else
	{
		return false;
	}

	GenerateImplantedIRmodule();

	return true;
}


bool SignalCodeImplanter::RunFineGrainedLevel()
{

	IRBuilder<> builder(m_context);

	/* declare sig_initializer, sig_checker */
	DeclareSignalCodes(*p_ParsedIRmodule, m_context, builder);

	/* implant sig_checker */
	for(auto iter = p_CompactImplantedBBList->begin();
			iter != p_CompactImplantedBBList->end(); iter++)
	{
		llvm::BasicBlock *Target = iter->first;
		unsigned int node_id = iter->second;
		llvm::Instruction *TargetCloned 
			= getTargetInstClonedforChecker(*p_ParsedIRmodule);

		ImplantSignalCodes(
				*p_ParsedIRmodule, 
				m_context, 
				builder, 
				Target,
				node_id,
				TargetCloned
				);
	}
	
	/* implant sig_initializer */
	BasicBlock *Target 
		= SearchTargetBasicBlock(*p_ParsedIRmodule, std::string("main"));
	Instruction *TargetCloned
		= getTargetInstClonedforInitializer(*p_ParsedIRmodule);

	ImplantSignalCodes(
			*p_ParsedIRmodule, 
			m_context, 
			builder, 
			Target, 
			0,
			TargetCloned
			);

	
	return true;
}



bool SignalCodeImplanter::RunCoarseGrainedLevel()
{

	return true;
}


/* Implant signal codes */
bool SignalCodeImplanter::ImplantSignalCodes(
		ParsedIRmodule &m, 
		LLVMContext &context, 
		IRBuilder<> &builder, 
		BasicBlock *bb,
		unsigned int node_id,
		Instruction *inst
	){

	if(bb->size() > 0)
	{
		inst->setParent(bb);
		llvm::Instruction *newInst = inst->clone();


		/* for checker */
		if(newInst->getNumOperands() > 1)
		{	
			llvm::Type *i32_type = llvm::IntegerType::getInt32Ty(context);
			Value *node_id_value = llvm::ConstantInt::get(i32_type, node_id, true);
			newInst->setOperand(0, node_id_value);
		}

		bb->getInstList().push_front(newInst);
	}

	return true;
}

/* Find Target BasicBlock to be implanted at */
llvm::BasicBlock *SignalCodeImplanter::SearchTargetBasicBlock(
		ParsedIRmodule &m, 
		std::string fname
	)
{

	llvm::Instruction *SavedInst;
	llvm::BasicBlock *SavedBB;

  	for(auto iter1 = m->getFunctionList().begin(); 
			iter1 != m->getFunctionList().end(); iter1++) {

		Function &f = *iter1;
		if(f.getName().str() == fname){

			llvm::Function::BasicBlockListType::iterator iter2;
			iter2 = f.getBasicBlockList().begin();

			llvm::BasicBlock &bb = *iter2;
			
			SavedBB = &bb;
			break;
		}
	}

	return SavedBB;
}


/* Find Target Instruction to be implanted */
llvm::Instruction *SignalCodeImplanter::getTargetInstClonedforInitializer(
		ParsedIRmodule &m
		)
{

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


	ReturnInst = *(InstList.begin());
	
	return ReturnInst;
}

/* Find Target Instruction to be implanted */
llvm::Instruction *SignalCodeImplanter::getTargetInstClonedforChecker(
		ParsedIRmodule &m
		)
{

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

	
	InstList_iter = InstList.begin();
	InstList_iter++;
	ReturnInst = *(InstList_iter);
	
	return ReturnInst;
}

/* Generate Implanted IRmodule */
bool SignalCodeImplanter::GenerateImplantedIRmodule()
{
	Module* writeModule = p_ParsedIRmodule->release();
	std::error_code EC;
	raw_fd_ostream OS("SignalCodeImplanted.bc", EC, sys::fs::F_None);
	
	WriteBitcodeToFile(writeModule, OS, true, nullptr, true, nullptr);
	OS.flush();

	return true;
}

/* declare sig_initializer, sig_checker */
bool SignalCodeImplanter::DeclareSignalCodes(
		ParsedIRmodule &m, 
		LLVMContext &context, 
		IRBuilder<> &builder
	)
{

	/* Function-type : void return/ no param */
	FunctionType *void_return_one_integer 
		= llvm::FunctionType::get(builder.getVoidTy(), IntegerType::get(context, 32), false);
	
	FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
	
	
	/* General Puts Function */

	/* sig_initializer */
	Constant *checker1_ptr = m->getOrInsertFunction("sig_initializer", funcType); 
	Function *checker1 = cast<Function>(checker1_ptr);

	/* sig_checker */
	Constant *checker2_ptr = m->getOrInsertFunction("sig_checker", void_return_one_integer); 
	Function *checker2 = cast<Function>(checker2_ptr);


	/* Call checker Set */
	Constant *gcdptr = m->getOrInsertFunction("CallcheckerSet", funcType); 
	Function *gcd = cast<Function>(gcdptr);
	llvm::BasicBlock *entry = BasicBlock::Create(context, "entry", gcd);
	IRBuilder<> CallChecker_builder(entry);
	
	llvm::Type *i32_type = llvm::IntegerType::getInt32Ty(context);
	Value *constant_one = llvm::ConstantInt::get(i32_type, 1, true);

	Value *call_checker1 = CallChecker_builder.CreateCall(checker1);
	Value *call_checker2 = CallChecker_builder.CreateCall(checker2, constant_one);
	
	CallChecker_builder.CreateRetVoid();
	
	return true;
}
