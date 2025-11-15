CC = g++ -g3
CFLAGS = -g3 -Wall
TARGET = P2

OBJS1 = P2.o
OBJS2 = Scanner.o
OBJS3 = TokensAndStates.o
OBJS4 = Parser.o

CLSFLDR = ScannerClass
PRSRCLASS = Parser


all: $(TARGET)
main: $(OBJS1)

$(TARGET): $(OBJS1) $(CLSFLDR)/$(OBJS2) TokensAndStates/$(OBJS3) $(PRSRCLASS)/$(OBJS4)
	$(CC) -o $(TARGET) $(OBJS1) $(CLSFLDR)/$(OBJS2) TokensAndStates/$(OBJS3) $(PRSRCLASS)/$(OBJS4)

$(OBJS1): P2.cpp $(CLSFLDR)/Scanner.h TokensAndStates/TokensAndStates.h $(PRSRCLASS)/Parser.h
	$(CC) $(CFLAGS) -c P2.cpp -o $(OBJS1)

$(OBJS2): $(CLSFLDR)/Scanner.cpp $(CLSFLDR)/Scanner.h TokensAndStates/TokensAndStates.h
	$(CC) $(CFLAGS) -c $(CLSFLDR)/Scanner.cpp -o $(CLSFLDR)/$(OBJS2)

$(OBJS3): TokensAndStates/TokensAndStates.cpp TokensAndStates/TokensAndStates.h
	$(CC) $(CFLAGS) -c TokensAndStates/TokensAndStates.cpp -o TokensAndStates/$(OBJS3)

$(OBJS4): $(PRSRCLASS)/Parser.cpp $(PRSRCLASS)/Parser.h TokensAndStates/TokensAndStates.h $(CLSFLDR)/Scanner.h
	$(CC) $(CFLAGS) -c $(PRSRCLASS)/Parser.cpp -o $(PRSRCLASS)/$(OBJS4)

clean:
	/bin/rm -f *.o ./ScannerClass/*.o ./TokensAndStates/*.o ./Parser/*.o $(TARGET)
