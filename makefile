CC = g++ -g3
CFLAGS = -g3 -Wall
TARGET = P2

OBJS1 = P2.o
OBJS2 = Scanner.o
OBJS3 = TokensAndStates.o

CLSFLDR = ScannerClass


all: $(TARGET)
main: $(OBJS1)

$(TARGET): $(OBJS1) $(CLSFLDR)/$(OBJS2) TokensAndStates/$(OBJS3)
	$(CC) -o $(TARGET) $(OBJS1) $(CLSFLDR)/$(OBJS2) TokensAndStates/$(OBJS3)

$(OBJS1): P2.cpp $(CLSFLDR)/Scanner.h TokensAndStates/TokensAndStates.h
	$(CC) $(CFLAGS) -c P2.cpp -o $(OBJS1)

$(OBJS2): $(CLSFLDR)/Scanner.cpp $(CLSFLDR)/Scanner.h TokensAndStates/TokensAndStates.h
	$(CC) $(CFLAGS) -c $(CLSFLDR)/Scanner.cpp -o $(CLSFLDR)/$(OBJS2)

$(OBJS3): TokensAndStates/TokensAndStates.cpp TokensAndStates/TokensAndStates.h
	$(CC) $(CFLAGS) -c TokensAndStates/TokensAndStates.cpp -o TokensAndStates/$(OBJS3)

clean:
	/bin/rm -f *.o ./ScannerClass/*.o ./TokensAndStates/*.o $(TARGET)
