#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "../TokensAndStates/TokensAndStates.h"
#include "../ScannerClass/Scanner.h"

using namespace std;

class Parser {
	private:
		Token tk;
		Scanner scanner;
		void program();
		void vars();
		void varList();
		void block();
		void stats();
		void mStat();
		void stat();
		void read();
		void print();
		void cond();
		void loop();
		void assign();
		void relational();
		void exp();
		void m();
		void n();
		void r();
		void errorHandler(const char*);
		void keywordHandler(const char*);
		

	public:
		Parser(const char *textBuffer): scanner(textBuffer) {
			printf("%s\n", textBuffer);
			printf("%p\n", textBuffer);
			printf("This doesn't run\n");
		}

		void parse();

		
};











#endif
