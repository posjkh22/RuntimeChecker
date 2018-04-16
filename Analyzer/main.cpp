#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <utility>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Bitcode/BitcodeReader.h>

//#include "IRcodeTextDataSet.hpp"
//#include "wFunction.hpp"
//#include "wBasicBlock.hpp"
//#include "wInstruction.hpp"
//#include "Support.hpp"
//#include "checker.hpp"
//#include "ArgumentPass.hpp"
//#include "BugReport.hpp"
#include "SymbolManager.hpp"
#include "Analyzer.hpp"
#include "MonitoringCodeGenerator.hpp"
#include "SignalCodeImplanter.hpp"

//#include "Path.hpp"
//#include "PathImpl.hpp"
//#include "TaskManager.hpp"



/* 2018-04-11 */
/*

   KIHO CHOI
   posjkh22@gmail.com
   ACES Lab.
   KyungPook National University

*/


const char OSJSON[]="./Json/OperatingSystemList.json";
const char TFUNCJSON[]="./Json/TargetFunctionList.json";

using namespace llvm;


int main(int argc, char *argv[]) {

	/* Symbol Manager */
	IPA::SymbolManager sm(new IPA::PathUncountedFunction,
				new IPA::ThreadSupportOS);
	
	sm.Process(OSJSON, TFUNCJSON);

	/* IRParser */
	StringRef filename = argv[1];
	LLVMContext context;
	SMDiagnostic error;
	std::unique_ptr<Module> m = parseIRFile(filename, error, context);

	std::cout << "-------------IR Parse analysis done-------------" << std::endl;

	/* Wrapper */

	Analyzer machine;
	machine.takeInput(m);
	machine.Preprocess();
	machine.DebugWrapperModule();
	std::cout << "---------------Pre-analysis done----------------" << std::endl;
	
	if(machine.Process() != true)
		std::cout << " -Analyzer.Process Error" << std::endl;
	
	machine.Debug_Show_CompactBBInfo();

	std::cout << "---------------Main Analysis done---------------" << std::endl;
	
	MonitoringCodeGenerator monitor_gen_machine;
	monitor_gen_machine.TakeAnalysisResults(&machine);
	monitor_gen_machine.run();

	std::cout << "---------------MonCode gen done----------------" << std::endl;
		
	SignalCodeImplanter code_implanter_machine(context);
	code_implanter_machine.TakeAnalysisResults(&machine);
	code_implanter_machine.run();

	std::cout << "---------------SigCode Imp done----------------" << std::endl;
	

	/* TaskManager */
	//IPA::TaskManager tm(&arg, &IRcode);
	//tm.Process();
	
	//std::cout << "---------------Task-analysis done---------------" << std::endl;
	
	return 0;
}
