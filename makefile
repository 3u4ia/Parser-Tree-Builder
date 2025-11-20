CC = g++ -g3
CFLAGS = -g3 -Wall
TARGET = P2

OBJS1 = P2.o
OBJS2 = Scanner.o
OBJS3 = TokensAndStates.o
OBJS4 = Parser.o
OBJS5 = Tree.o

CLSFLDR = ScannerClass
PRSRCLASS = Parser
TREECLS = TreeClass

OBJS = P2.o \
	$(CLSFLDR)/$(OBJS2) \
	TokensAndStates/$(OBJS3) \
	$(PRSRCLASS)/$(OBJS4) \
	$(TREECLS)/$(OBJS5)


all: $(TARGET)
main: $(OBJS1)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
 
$(OBJS1): P2.cpp $(CLSFLDR)/Scanner.h TokensAndStates/TokensAndStates.h $(PRSRCLASS)/Parser.h
	$(CC) $(CFLAGS) -c P2.cpp -o $(OBJS1)

$(OBJS2): $(CLSFLDR)/Scanner.cpp $(CLSFLDR)/Scanner.h TokensAndStates/TokensAndStates.h
	$(CC) $(CFLAGS) -c $(CLSFLDR)/Scanner.cpp -o $(CLSFLDR)/$(OBJS2)

$(OBJS3): TokensAndStates/TokensAndStates.cpp TokensAndStates/TokensAndStates.h
	$(CC) $(CFLAGS) -c TokensAndStates/TokensAndStates.cpp -o TokensAndStates/$(OBJS3)

$(OBJS4): $(PRSRCLASS)/Parser.cpp $(PRSRCLASS)/Parser.h TokensAndStates/TokensAndStates.h $(CLSFLDR)/Scanner.h $(TREECLS)/TreeNodeStruct.h $(TREECLS)/Tree.h
	$(CC) $(CFLAGS) -c $(PRSRCLASS)/Parser.cpp -o $(PRSRCLASS)/$(OBJS4)

$(OBJS5): $(TREECLS)/Tree.cpp $(TREECLS)/Tree.h TokensAndStates/TokensAndStates.h $(TREECLS)/TreeNodeStruct.h
	$(CC) $(CFLAGS) -c $(TREECLS)/Tree.cpp -o $(TREECLS)/$(OBJS5)

clean:
	/bin/rm -f *.o ./ScannerClass/*.o ./TokensAndStates/*.o ./Parser/*.o $(TARGET)

cleanTest: 
	/bin/rm -f *.fs25s1
