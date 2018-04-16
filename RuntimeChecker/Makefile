

OUTPUT 		= RuntimeChecker
SRC			= $(PWD)/src
LIB			= $(PWD)/lib
INCLUDE		= $(PWD)/include

MONITOR		= $(PWD)/monitor
SIGNAL 	 	= $(PWD)/signal
SAMPLE 	 	= $(PWD)/sample

run:
	$(PWD)/$(OUTPUT) $(SAMPLE)/testcase1.bc
	llvm-dis SignalCodeImplanted.bc -o $(SIGNAL)/SignalCodeImplanted.ll
	mv SignalCodeImplanted.bc $(SIGNAL)


link: result_clean
	clang++ -std=c++11 \
	$(LIB)/main.o \
	$(LIB)/SymbolManager.o \
	$(LIB)/MetaDataSet.o \
	$(LIB)/wFunction.o \
	$(LIB)/wBasicBlock.o \
	$(LIB)/wInstruction.o \
	$(LIB)/Path.o \
	$(LIB)/PathImpl.o \
	$(LIB)/Analyzer.o \
	$(LIB)/MonitoringCodeGenerator.o \
	$(LIB)/SignalCodeImplanter.o \
	-o $(OUTPUT) \
	-ljsoncpp \
	`llvm-config --cxxflags --libs --ldflags --system-libs`

all: clean \
		main \
		SymbolManager \
		Analyzer \
		MetaDataSet \
		wFunction \
		wBasicBlock \
		wInstruction \
		path \
		pathImpl \
		MonitoringCodeGenerator \
		SignalCodeImplanter
	clang++ -std=c++11 \
	$(LIB)/main.o \
	$(LIB)/SymbolManager.o \
	$(LIB)/MetaDataSet.o \
	$(LIB)/wFunction.o \
	$(LIB)/wBasicBlock.o \
	$(LIB)/wInstruction.o \
	$(LIB)/Path.o \
	$(LIB)/PathImpl.o \
	$(LIB)/Analyzer.o \
	$(LIB)/MonitoringCodeGenerator.o \
	$(LIB)/SignalCodeImplanter.o \
	-o $(OUTPUT) \
	-ljsoncpp \
	`llvm-config --cxxflags --libs --ldflags --system-libs`
	
	
main:
	clang++ -std=c++11 -c main.cpp  \
	-o $(LIB)/main.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

Task:
	clang++ -std=c++11 \
	-c $(SRC)/Task.cpp \
	-o $(LIB)/Task.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

TaskManager:
	clang++ -std=c++11 \
	-c $(SRC)/TaskManager.cpp \
	-o $(LIB)/TaskManager.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

SymbolManager:
	clang++ -std=c++11 \
	-c $(SRC)/SymbolManager.cpp \
	-o $(LIB)/SymbolManager.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

Analyzer:
	clang++ -std=c++11 \
	-c $(SRC)/Analyzer.cpp \
	-o $(LIB)/Analyzer.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

MetaDataSet:
	clang++ -std=c++11 \
	-c $(SRC)/MetaDataSet.cpp \
	-o $(LIB)/MetaDataSet.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

MonitoringCodeGenerator:
	clang++ -std=c++11 \
	-c $(SRC)/MonitoringCodeGenerator.cpp \
	-o $(LIB)/MonitoringCodeGenerator.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

SignalCodeImplanter:
	clang++ -std=c++11 \
	-c $(SRC)/SignalCodeImplanter.cpp \
	-o $(LIB)/SignalCodeImplanter.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

wFunction:
	clang++ -std=c++11 \
	-c $(SRC)/wFunction.cpp \
	-o $(LIB)/wFunction.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)
	
wBasicBlock:
	clang++ -std=c++11 \
	-c $(SRC)/wBasicBlock.cpp \
	-o $(LIB)/wBasicBlock.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

wInstruction:
	clang++ -std=c++11 \
	-c $(SRC)/wInstruction.cpp \
	-o $(LIB)/wInstruction.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

path:
	clang++ -std=c++11 \
	-c $(SRC)/Path.cpp \
	-o $(LIB)/Path.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

pathImpl:
	clang++ -std=c++11 \
	-c $(SRC)/PathImpl.cpp \
	-o $(LIB)/PathImpl.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

checker:
	clang++ -std=c++11 \
	-c $(SRC)/checker.cpp \
	-o $(LIB)/checker.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

clean:
	rm -f $(OUTPUT) test_out $(LIB)/*.o Analysis*

result_clean:
	rm -f Analysis* ./dat/*

