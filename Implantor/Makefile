SRC				=./src
LIB				=./lib
INCLUDE			=./include
BIT				=./bit
CHECK			=./check

TEST			= cg_example

run: 
	./test $(TEST).bc > test_out
	rm -f Result.ll
	llvm-dis Result.bc -o Result.ll

link: 
	clang++ -std=c++11 \
	$(LIB)/main.o \
	$(LIB)/wrapper.o \
	$(LIB)/wTask.o \
	$(LIB)/wFunction.o \
	$(LIB)/wBasicBlock.o \
	$(LIB)/wInstruction.o \
	$(LIB)/Path.o \
	$(LIB)/PathImpl.o \
	$(LIB)/checker.o \
	$(LIB)/printIRcode.o \
	$(LIB)/transferIRcode.o \
	$(LIB)/CompactBBSet.o	\
	-o test \
	`llvm-config --cxxflags --libs --ldflags --system-libs`

all: clean main printIRcode wrapper wTask wFunction wBasicBlock wInstruction path pathImpl checker transferIRcode CompactBBSet
	clang++ -std=c++11 \
	$(LIB)/main.o \
	$(LIB)/wrapper.o \
	$(LIB)/wTask.o \
	$(LIB)/wFunction.o \
	$(LIB)/wBasicBlock.o \
	$(LIB)/wInstruction.o \
	$(LIB)/Path.o \
	$(LIB)/PathImpl.o \
	$(LIB)/checker.o \
	$(LIB)/printIRcode.o \
	$(LIB)/transferIRcode.o \
	$(LIB)/CompactBBSet.o	\
	-o test \
	`llvm-config --cxxflags --libs --ldflags --system-libs`
	
main:
	clang++ -std=c++11 -c main.cpp  \
	-o $(LIB)/main.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

wrapper:
	clang++ -std=c++11 \
	-c $(SRC)/wrapper.cpp \
	-o $(LIB)/wrapper.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)

wTask:
	clang++ -std=c++11 \
	-c $(SRC)/wTask.cpp \
	-o $(LIB)/wTask.o \
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

transferIRcode:
	clang++ -std=c++11 \
	-c $(SRC)/transferIRcode.cpp \
	-o $(LIB)/transferIRcode.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`

CompactBBSet:
	clang++ -std=c++11 \
	-c $(SRC)/CompactBBSet.cpp \
	-o $(LIB)/CompactBBSet.o \
	`llvm-config --cxxflags` \
	-I$(INCLUDE)


printIRcode:
	clang++ -std=c++11 \
	-c $(SRC)/printIRcode.cpp \
	-o $(LIB)/printIRcode.o \
	-I$(INCLUDE) \
	`llvm-config --cxxflags`


clean:
	rm -f test test_out $(LIB)/*.o Result.bc

bcclean:
	rm -f $(BIT)/*.bc
