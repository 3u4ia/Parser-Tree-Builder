#include <stdio.h>
#include "Parser.h"

//Token tk;
//Scanner scanner;
//struct Token {
//	TokenID tokenID;
//	char lexeme[9];
//	int lineNum;
//};

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
	vars();
	block();
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

void Parser::vars() { // LIKELY INCORRECT DUE TO NOT BEING DEEPLY NESTED
	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "int") == 0) {
			tk = scanner.scanToken();
			if(tk.tokenID == IDTK) {
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
				tk = scanner.scanToken();
			}
			else {
				errorHandler(tokenNames[NUMTK - 1000]);
			}
			varList();
			if(tk.tokenID == DELOPTK) {
				tk = scanner.scanToken();
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
	if(tk.tokenID == IDTK) {
		tk = scanner.scanToken();

		if(tk.tokenID == ASSIGNOPTK) {
			tk = scanner.scanToken();
		} else {
			errorHandler(tokenNames[ASSIGNOPTK - 1000]);
		}
		if(tk.tokenID == NUMTK) {
			tk = scanner.scanToken();
			varList();
			return;
		} else {
			errorHandler(tokenNames[NUMTK - 1000]);
		}
	} else {
		return;
	}
}

void Parser::block() {
	if (tk.tokenID == LFTCURLYDELIM) {
		tk = scanner.scanToken();
		vars();
		stats();
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
	stat();
	mStat();
}

void Parser::mStat() {
	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "scan") == 0 ||
			strcmp(tk.lexeme, "output") == 0 ||
			strcmp(tk.lexeme, "cond") == 0 ||
			strcmp(tk.lexeme, "loop") == 0 ||
			strcmp(tk.lexeme, "set") == 0) {
			

			stat();
			mStat();
			return;
		}
	} else if(tk.tokenID == LFTCURLYDELIM) {
		stat();
		mStat();
		return;
	}


	return;
}

void Parser::stat() {
	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "scan") == 0) {
			read();
			return;
		} else if(strcmp(tk.lexeme, "output") == 0) {
			print();
			return;
		} else if(strcmp(tk.lexeme, "cond") == 0) {
			cond();
			return;
		} else if(strcmp(tk.lexeme, "loop") == 0) {
			loop();
			return;
		} else if(strcmp(tk.lexeme, "set") == 0) {
			assign();
			return;
		} else {
			errorHandler("scan, output, cond, loop or set");
		}
			
	} 
	else if(tk.tokenID == LFTCURLYDELIM) {
		block();
		return;
	}
	else {
		errorHandler("scan, output, cond, loop, set or {");
	}


}

void Parser::read() {
	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "scan") == 0) {
			tk = scanner.scanToken();
		} else {
			errorHandler("scan");
		}
		if(tk.tokenID == IDTK) {
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
	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "output") == 0) {
			tk = scanner.scanToken();
			exp();

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
		tk = scanner.scanToken();
		relational();
		exp();
	} else {
		errorHandler(tokenNames[IDTK - 1000]);
	}

	if(tk.tokenID == RGHTSQREDELIM) {
		tk = scanner.scanToken();
		stat();
		return;
	} else {
		errorHandler(tokenNames[RGHTSQREDELIM - 1000]);
	}



}


void Parser::loop() {
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
		tk = scanner.scanToken();
		relational();
		exp();
	} else {
		errorHandler(tokenNames[IDTK - 1000]);
	}
	if(tk.tokenID == RGHTSQREDELIM) {
		tk = scanner.scanToken();
		stat();
		return;
	} else {
		errorHandler(tokenNames[RGHTSQREDELIM - 1000]);
	}



}


void Parser::assign() {
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
		tk = scanner.scanToken();
	} else {
			errorHandler(tokenNames[IDTK - 1000]);
	}

	if(tk.tokenID = ASSIGNOPTK) {
		tk = scanner.scanToken();
		exp();
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
	if(tk.tokenID == LEOPTK) {
		tk = scanner.scanToken();
		return;
	} else if(tk.tokenID == GEOPTK) {
		tk = scanner.scanToken();
		return;
	} else if(tk.tokenID == LTOPTK) {
		tk = scanner.scanToken();
		return;
	} else if(tk.tokenID == EQOPTK) {
		tk = scanner.scanToken();
		return;
	} else if(tk.tokenID == ASSIGNOPTK) {
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
	m();
	if(tk.tokenID == DBLESTAR) {
		printf("EXP: took M ** <EXP> Opt\n");
		tk = scanner.scanToken();
		exp();
		return;
	} else if (tk.tokenID == DBLESLASH) {
		printf("EXP: took M // <EXP> Opt\n");
		tk = scanner.scanToken();
		exp();
		return;
	} else {
		printf("EXP: took <M> opt\n");
		return;
	}
}


void Parser::m() {
	n();
	printf("M: n just ran\n");
	if(tk.tokenID == OPTK) {
		if(strcmp(tk.lexeme, "+") == 0) {
			printf("M: N+M opt took\n");
			tk = scanner.scanToken();
			m();
			return;
		} else {
			return; // In case M -> N opt
		}
	} else {
		printf("M: Took the Lone N Opt\n");
		return;
	}
}


void Parser::n() {
	if(tk.tokenID == OPTK) {
		if(strcmp(tk.lexeme, "-") == 0) {
			printf("N: took -N opt\n");
			tk = scanner.scanToken();
			n();
			return;
		}	
	}
	r();
	printf("N: Just ran R\n");
	if(tk.tokenID == OPTK) {
		if(strcmp(tk.lexeme, "-") == 0) {
			printf("N: took R-N Opt\n");
			tk = scanner.scanToken();
			n();
		} else {
			return; // In case N -> R option
		}
	} else {
		printf("N: Took Lone R Opt\n");
		return; // In case N -> R option
	}
	
}

void Parser::r() {
	if(tk.tokenID == LFTPARENDELIM) {
		tk = scanner.scanToken();
		exp();
		if(tk.tokenID == RGHTPARENDELIM) {
			tk = scanner.scanToken();
			return;
		} else {
			errorHandler(tokenNames[RGHTPARENDELIM - 1000]);
		}
	} else if(tk.tokenID == IDTK) {
		printf("R: took ID opt\n");
		tk = scanner.scanToken();
		return;
	} else if(tk.tokenID == NUMTK) {
		printf("R: took NumOpt\n");
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
































