#include <stdio.h>
#include "Parser.h"

//Token tk;
//Scanner scanner;
//struct Token {
//	TokenID tokenID;
//	char lexeme[9];
//	int lineNum;
//};


//struct TreeNode {
//	int label;
//	Token token;
//	TreeNode *left;
//	TreeNode *middle;
//	TreeNode *right;
//};


enum NonTerminals {
	PROGRAM,
	VARS,
	VARLIST,
	BLOCK,
	STATS,
	MSTAT,
	STAT,
	READ,
	PRINT,
	COND,
	LOOP,
	ASSIGN,
	RELATIONAL,
	EXP,
	M,
	N,
	R,
};


void Parser::parse() {
	tk = scanner.scanToken();
	program();
	if (tk.tokenID != EOFTK) {
		printf("ERROR\n");
		exit(1);
	}
	else {
		printf("Success!");
	}
	return;
}



void Parser::program() {
	TreeNode *programNode = new TreeNode;
	programNode->label = PROGRAM;
	programNode->tokenArr[0] = tk;
	programNode->tokenArr[1] = tk;
	programNode->tokenArr[2] = tk;
	programNode->nodeArr[0] = nullptr;
	programNode->nodeArr[1] = nullptr;
	programNode->nodeArr[2] = nullptr;


	if (tk.tokenID == KEYWORD) {
		if (strcmp(tk.lexeme, "go") == 0) {
			tk = scanner.scanToken();
		}
		else {
			errorHandler("go lexeme");
		}
	} else {
		errorHandler(tokenNames[KEYWORD - 1000]);
	}
	programNode->nodeArr[0] = vars();
	programNode->nodeArr[1] = block();
	if(tk.tokenID == KEYWORD) {
		if (strcmp(tk.lexeme, "exit") == 0) {
			tk = scanner.scanToken();
		}
		else {
			errorHandler("exit lexeme");
		}
	}
	else {
		errorHandler("exit");
	}
	return;

}
//struct Token {
//	TokenID tokenID;
//	char lexeme[9];
//	int lineNum;
//};
//
//struct TreeNode {
//	int label;
//	Token tokenArr[3];
//	TreeNode *nodeArr[3];
//};


void Parser::vars() { // LIKELY INCORRECT DUE TO NOT BEING DEEPLY NESTED
	TreeNode varsNode = new TreeNode;
	varsNode->label = VARS;
	varsNode->tokenArr[0] = tk;
	varsNode->tokenArr[1] = tk;
	varsNode->tokenArr[2] = tk;
	varsNode->nodeArr[0] = nullptr;
	varsNode->nodeArr[1] = nullptr;
	varsNode->nodeArr[2] = nullptr;

	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "int") == 0) {
			tk = scanner.scanToken();
			if(tk.tokenID == IDTK) {
				varsNode->tokenArr[0] = tk
				tk = scanner.scanToken();
			} else {
				errorHandler(tokenNames[IDTK - 1000]);
			}
			if(tk.tokenID == ASSIGNOPTK) {
				tk = scanner.scanToken();
			}
			else {
				errorHandler(tokenNames[ASSIGNOPTK - 1000]);
			}
			if(tk.tokenID == NUMTK) {
				varsNode->tokenArr[1] = tk;
				tk = scanner.scanToken();
			}
			else {
				errorHandler(tokenNames[NUMTK - 1000]);
			}
			varsNode->nodeArr[0] = varList();
			if(tk.tokenID == DELOPTK) {
				tk = scanner.scanToken();
				return;
			}
			else {
				errorHandler(tokenNames[DELOPTK - 1000]);
			}
		}
		return; // for the empty case
	}
	return; // for the empty case
}

void Parser::varList() {
	TreeNode varsListNode = new TreeNode;
	varListNode->label = VARLIST;
	varListNode->tokenArr[0] = tk;
	varListNode->tokenArr[1] = tk;
	varListNode->tokenArr[2] = tk;
	varListNode->nodeArr[0] = nullptr;
	varListNode->nodeArr[1] = nullptr;
	varListNode->nodeArr[2] = nullptr;

	if(tk.tokenID == IDTK) {
		varListNode->tokenArr[0] = tk;
		tk = scanner.scanToken();
		if(tk.tokenID == ASSIGNOPTK) {
			tk = scanner.scanToken();
		} else {
			errorHandler(tokenNames[ASSIGNOPTK - 1000]);
		}
		if(tk.tokenID == NUMTK) {
			varListNode->tokenArr[1] = tk;
			tk = scanner.scanToken();
			varListNode->nodeArr[0] = varList();
			return;
		} else {
			errorHandler(tokenNames[NUMTK - 1000]);
		}
	} else {
		return;
	}
}

void Parser::block() {
	TreeNode blockNode = new TreeNode;
	blockNode->label = BLOCK;
	blockNode->tokenArr[0] = tk;
	blockNode->tokenArr[1] = tk;
	blockNode->tokenArr[2] = tk;
	blockNode->nodeArr[0] = nullptr;
	blockNode->nodeArr[1] = nullptr;
	blockNode->nodeArr[2] = nullptr;

	if (tk.tokenID == LFTCURLYDELIM) {
		tk = scanner.scanToken();
		blockNode->nodeArr[0] = vars();
		blockNode->nodeArr[1] = stats();
		if(tk.tokenID == RGHTCURLYDELIM) {
			tk = scanner.scanToken();
		} else {
			errorHandler(tokenNames[RGHTCURLYDELIM - 1000]);
		}
	} else {
		errorHandler(tokenNames[LFTCURLYDELIM - 1000]);
	}
}

void Parser::stats() {
	TreeNode statsNode = new TreeNode;
	statsNode->label = STATS;
	statsNode->tokenArr[0] = tk;
	statsNode->tokenArr[1] = tk;
	statsNode->tokenArr[2] = tk;
	statsNode->nodeArr[0] = nullptr;
	statsNode->nodeArr[1] = nullptr;
	statsNode->nodeArr[2] = nullptr;

	statsNode->nodeArr[0] = stat();
	statsNode->nodeArr[1] = mStat();
}

void Parser::mStat() {
	TreeNode mStatNode = new TreeNode;
	mStatNode->label = MSTAT;
	mStatNode->tokenArr[0] = tk;
	mStatNode->tokenArr[1] = tk;
	mStatNode->tokenArr[2] = tk;
	mStatNode->nodeArr[0] = nullptr;
	mStatNode->nodeArr[1] = nullptr;
	mStatNode->nodeArr[2] = nullptr;

	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "scan") == 0 ||
			strcmp(tk.lexeme, "output") == 0 ||
			strcmp(tk.lexeme, "cond") == 0 ||
			strcmp(tk.lexeme, "loop") == 0 ||
			strcmp(tk.lexeme, "set") == 0) {
			

			mStatNode->nodeArr[0] = stat();
			mStatNode->nodeArr[1] = mStat();
			return;
		}
	} else if(tk.tokenID == LFTCURLYDELIM) {
		mStatNode->nodeArr[0] = stat();
		mStatNode->nodeArr[1] = mStat();
		return;
	}


	return;
}

void Parser::stat() {
	TreeNode statNode = new TreeNode;
	statNode->label = STAT;
	statNode->tokenArr[0] = tk;
	statNode->tokenArr[1] = tk;
	statNode->tokenArr[2] = tk;
	statNode->nodeArr[0] = nullptr;
	statNode->nodeArr[1] = nullptr;
	statNode->nodeArr[2] = nullptr;

	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "scan") == 0) {
			statNode->nodeArr[0] = read();
			return;
		} else if(strcmp(tk.lexeme, "output") == 0) {
			statNode->nodeArr[0] = print();
			return;
		} else if(strcmp(tk.lexeme, "cond") == 0) {
			statNode->nodeArr[0] = cond();
			return;
		} else if(strcmp(tk.lexeme, "loop") == 0) {
			statNode->nodeArr[0] = loop();
			return;
		} else if(strcmp(tk.lexeme, "set") == 0) {
			statNode->nodeArr[0] = assign();
			return;
		} else {
			errorHandler("scan, output, cond, loop or set");
		}
			
	} 
	else if(tk.tokenID == LFTCURLYDELIM) {
		statNode->nodeArr[0] = block();
		return;
	}
	else {
		errorHandler("scan, output, cond, loop, set or {");
	}


}

void Parser::read() {
	TreeNode readNode = new TreeNode;
	readNode->label = READ;
	readNode->tokenArr[0] = tk;
	readNode->tokenArr[1] = tk;
	readNode->tokenArr[2] = tk;
	readNode->nodeArr[0] = nullptr;
	readNode->nodeArr[1] = nullptr;
	readNode->nodeArr[2] = nullptr;

	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "scan") == 0) {
			tk = scanner.scanToken();
		} else {
			errorHandler("scan");
		}
		if(tk.tokenID == IDTK) {
			readNode->tokenArr[0] = tk;
			tk = scanner.scanToken();

		} else {
			errorHandler(tokenNames[IDTK - 1000]);
		}
		if(tk.tokenID == DELOPTK) {
			tk = scanner.scanToken();
			return;
		} else {
			errorHandler(tokenNames[DELOPTK - 1000]);
		}


	} else {
		errorHandler(tokenNames[KEYWORD - 1000]);
	}
}



void Parser::print() {
	TreeNode printNode = new TreeNode;
	printNode->label = PRINT;
	printNode->tokenArr[0] = tk;
	printNode->tokenArr[1] = tk;
	printNode->tokenArr[2] = tk;
	printNode->nodeArr[0] = nullptr;
	printNode->nodeArr[1] = nullptr;
	printNode->nodeArr[2] = nullptr;


	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "output") == 0) {
			tk = scanner.scanToken();
			printNode->nodeArr[0] = exp();

		}
		else {
			errorHandler("output");
		}	
	} else {
		errorHandler(tokenNames[KEYWORD - 1000]);
	}
	if(tk.tokenID == DELOPTK) {
		tk = scanner.scanToken();
		return;
	} else {
		errorHandler(tokenNames[DELOPTK - 1000]);
	}

}


void Parser::cond() {
	TreeNode condNode = new TreeNode;
	condNode->label = COND;
	condNode->tokenArr[0] = tk;
	condNode->tokenArr[1] = tk;
	condNode->tokenArr[2] = tk;
	condNode->nodeArr[0] = nullptr;
	condNode->nodeArr[1] = nullptr;
	condNode->nodeArr[2] = nullptr;


	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "cond") == 0) {
			tk = scanner.scanToken();

		} else {
			errorHandler("cond");
		}
	} else {
		errorHandler(tokenNames[KEYWORD - 1000]);
	}

	if(tk.tokenID == LFTSQREDELIM) {
		tk = scanner.scanToken();
	} else {
		errorHandler(tokenNames[LFTSQREDELIM - 1000]);
	}

	if(tk.tokenID == IDTK) {
		condNode->tokenArr[0] = tk;
		tk = scanner.scanToken();
		condNode->nodeArr[0] = relational();
		condNode->nodeArr[1] = exp();
	} else {
		errorHandler(tokenNames[IDTK - 1000]);
	}

	if(tk.tokenID == RGHTSQREDELIM) {
		tk = scanner.scanToken();
		condNode->nodeArr[2] = stat();
		return;
	} else {
		errorHandler(tokenNames[RGHTSQREDELIM - 1000]);
	}



}


void Parser::loop() {
	TreeNode loopNode = new TreeNode;
	loopNode->label = LOOP;
	loopNode->tokenArr[0] = tk;
	loopNode->tokenArr[1] = tk;
	loopNode->tokenArr[2] = tk;
	loopNode->nodeArr[0] = nullptr;
	loopNode->nodeArr[1] = nullptr;
	loopNode->nodeArr[2] = nullptr;


	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "loop") == 0) {
			tk = scanner.scanToken();
		} else {
			errorHandler("loop");
		}
	} else {
		errorHandler(tokenNames[KEYWORD - 1000]);
	}
	if(tk.tokenID == LFTSQREDELIM) {
		tk = scanner.scanToken();
	} else {
		errorHandler(tokenNames[LFTSQREDELIM - 1000]);
	}
	if(tk.tokenID == IDTK) {
		loopNode->tokenArr[0] = tk;
		tk = scanner.scanToken();
		loopNode->nodeArr[0] = relational();
		loopNode->nodeArr[1] = exp();
	} else {
		errorHandler(tokenNames[IDTK - 1000]);
	}
	if(tk.tokenID == RGHTSQREDELIM) {
		tk = scanner.scanToken();
		loopNode->nodeArr[2] = stat();
		return;
	} else {
		errorHandler(tokenNames[RGHTSQREDELIM - 1000]);
	}



}


void Parser::assign() {
	TreeNode assignNode = new TreeNode;
	assignNode->label = ASSIGN;
	assignNode->tokenArr[0] = tk;
	assignNode->tokenArr[1] = tk;
	assignNode->tokenArr[2] = tk;
	assignNode->nodeArr[0] = nullptr;
	assignNode->nodeArr[1] = nullptr;
	assignNode->nodeArr[2] = nullptr;


	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "set") == 0) {
			tk = scanner.scanToken();

		} else {
			errorHandler("set");
		}
	} else {
		errorHandler(tokenNames[KEYWORD - 1000]);
	}

	if(tk.tokenID = IDTK) {
		assignNode->tokenArr[0] = tk;
		tk = scanner.scanToken();
	} else {
			errorHandler(tokenNames[IDTK - 1000]);
	}

	if(tk.tokenID = ASSIGNOPTK) {
		tk = scanner.scanToken();
		assignNode->nodeArr[0] = exp();
	} else {
		errorHandler(tokenNames[ASSIGNOPTK - 1000]);
	}
	if(tk.tokenID = DELOPTK) {
		tk = scanner.scanToken();
		return;
	} else {
		errorHandler(tokenNames[DELOPTK - 1000]);
	}



}

void Parser::relational() {
	TreeNode relationalNode = new TreeNode;
	relationalNode->label = RELATIONAL;
	relationalNode->tokenArr[0] = tk;
	relationalNode->tokenArr[1] = tk;
	relationalNode->tokenArr[2] = tk;
	relationalNode->nodeArr[0] = nullptr;
	relationalNode->nodeArr[1] = nullptr;
	relationalNode->nodeArr[2] = nullptr;


	if(tk.tokenID == LEOPTK) {
		relationalNode->tokenArr[0] = tk;
		tk = scanner.scanToken();
		return;
	} else if(tk.tokenID == GEOPTK) {
		relationalNode->tokenArr[0] = tk;
		tk = scanner.scanToken();
		return;
	} else if(tk.tokenID == LTOPTK) {
		relationalNode->tokenArr[0] = tk;
		tk = scanner.scanToken();
		return;
	} else if(tk.tokenID == EQOPTK) {
		relationalNode->tokenArr[0] = tk;
		tk = scanner.scanToken();
		return;
	} else if(tk.tokenID == ASSIGNOPTK) {		//SHOULD I ADD THE TOKEN TO THE NODE HERE????
		tk = scanner.scanToken();

		if(tk.tokenID == ASSIGNOPTK) {
			tk = scanner.scanToken();
			return;
		} else {
			errorHandler(tokenNames[ASSIGNOPTK - 1000]);
		}
	} else {
		errorHandler("Any relational token");
	}
}

void Parser::exp() {
	TreeNode expNode = new TreeNode;
	expNode->label = EXP;
	expNode->tokenArr[0] = tk;
	expNode->tokenArr[1] = tk;
	expNode->tokenArr[2] = tk;
	expNode->nodeArr[0] = nullptr;
	expNode->nodeArr[1] = nullptr;
	expNode->nodeArr[2] = nullptr;


	expNode->nodeArr[0] = m();
	if(tk.tokenID == DBLESTAR) {
		//printf("EXP: took M ** <EXP> Opt\n");
		expNode->tokenArr[0] = tk;
		tk = scanner.scanToken();
		expNode->nodeArr[1] = exp();
		return;
	} else if (tk.tokenID == DBLESLASH) {
		expNode->tokenArr[0] = tk;
		//printf("EXP: took M // <EXP> Opt\n");
		tk = scanner.scanToken();
		expNode->nodeArr[1] = exp();
		return;
	} else {
		//printf("EXP: took <M> opt\n");
		return;
	}
}


void Parser::m() {
	TreeNode mNode = new TreeNode;
	mNode->label = M;
	mNode->tokenArr[0] = tk;
	mNode->tokenArr[1] = tk;
	mNode->tokenArr[2] = tk;
	mNode->nodeArr[0] = nullptr;
	mNode->nodeArr[1] = nullptr;
	mNode->nodeArr[2] = nullptr;


	mNode->nodeArr[0] = n();
	//printf("M: n just ran\n");
	if(tk.tokenID == OPTK) {
		if(strcmp(tk.lexeme, "+") == 0) {
			//printf("M: N+M opt took\n");
			mNode->tokenArr[0] = tk;
			tk = scanner.scanToken();
			mNode->nodeArr[1] = m();
			return;
		} else {
			return; // In case M -> N opt
		}
	} else {
		//printf("M: Took the Lone N Opt\n");
		return;
	}
}


void Parser::n() {
	TreeNode nNode = new TreeNode;
	nNode->label = N;
	nNode->tokenArr[0] = tk;
	nNode->tokenArr[1] = tk;
	nNode->tokenArr[2] = tk;
	nNode->nodeArr[0] = nullptr;
	nNode->nodeArr[1] = nullptr;
	nNode->nodeArr[2] = nullptr;


	if(tk.tokenID == OPTK) {
		if(strcmp(tk.lexeme, "-") == 0) {
			//printf("N: took -N opt\n");
			nNode->tokenArr[0] = tk;
			tk = scanner.scanToken();
			nNode->nodeArr[0] = n();
			return;
		}	
	}

	nNode->nodeArr[0] = r();
	//printf("N: Just ran R\n");
	
	if(tk.tokenID == OPTK) {
		if(strcmp(tk.lexeme, "-") == 0) {
			//printf("N: took R-N Opt\n");
			nNode->tokenArr[0] = tk;
			tk = scanner.scanToken();
			nNode->nodeArr[1] = n();
		} else {
			return; // In case N -> R option
		}
	} else {
		//printf("N: Took Lone R Opt\n");
		return; // In case N -> R option
	}
	
}

void Parser::r() {
	TreeNode rNode = new TreeNode;
	rNode->label = R;
	rNode->tokenArr[0] = tk;
	rNode->tokenArr[1] = tk;
	rNode->tokenArr[2] = tk;
	rNode->nodeArr[0] = nullptr;
	rNode->nodeArr[1] = nullptr;
	rNode->nodeArr[2] = nullptr;


	if(tk.tokenID == LFTPARENDELIM) {
		tk = scanner.scanToken();
		rNode->nodeArr[0] = exp();
		if(tk.tokenID == RGHTPARENDELIM) {
			tk = scanner.scanToken();
			return;
		} else {
			errorHandler(tokenNames[RGHTPARENDELIM - 1000]);
		}
	} else if(tk.tokenID == IDTK) {
		//printf("R: took ID opt\n");
		rNode->tokenArr[0] = tk;
		tk = scanner.scanToken();
		return;
	} else if(tk.tokenID == NUMTK) {
		//printf("R: took NumOpt\n");
		rNode->tokenArr[0] = tk;
		tk = scanner.scanToken();
		return;
	} else {
		errorHandler("(, IDTK or NUMTK");
	}
}



void Parser::errorHandler(const char *expectedTk) {
	printf("Error: %s expected but received %s with lexeme %s on line %d\n", expectedTk, tokenNames[tk.tokenID - 1000], tk.lexeme, tk.lineNum); 
	exit(1);
}
































