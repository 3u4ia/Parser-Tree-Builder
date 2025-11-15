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
	printf("tk.tokenID: %d\ntk.lexeme: %s\ntk.lineNum %d\n", tk.tokenID, tk.lexeme, tk.lineNum);
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
		errorHandler("KEYWORDTk");
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
				errorHandler(tokenNames[tk.tokenID - 1000]);
			}
			if(strcmp(tk.lexeme, "=") == 0) {
				tk = scanner.scanToken();
			}
			else {
				errorHandler(tokenNames[tk.tokenID - 1000]);
			}
			if(tk.tokenID == NUMTK) {
				tk = scanner.scanToken();
			}
			else {
				errorHandler(tokenNames[tk.tokenID - 1000]);
			}
			varList();
			if(tk.tokenID == DELOPTK) {
				tk = scanner.scanToken();
			}
			else {
				errorHandler(tokenNames[tk.tokenID - 1000]);
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
			errorHandler(tokenNames[tk.tokenID - 1000]);
		}
		if(tk.tokenID == NUMTK) {
			tk = scanner.scanToken();
			varList();
			return;
		} else {
			errorHandler(tokenNames[tk.tokenID - 1000]);
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
		}
		
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
			errorHandler(tokenNames[tk.tokenID - 1000]);
		}
		if(tk.tokenID == DELOPTK) {
			tk = scanner.scanToken();
			return;
		} else {
			errorHandler(tokenNames[tk.tokenID - 1000]);
		}


	} else {
		errorHandler(tokenNames[tk.tokenID - 1000]);
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
		errorHandler(tokenNames[tk.tokenID - 1000]);
	}
	if(tk.tokenID == DELOPTK) {
		tk = scanner.scanToken();
		return;
	} else {
		errorHandler(tokenNames[tk.tokenID - 1000]);
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
		errorHandler(tokenNames[tk.tokenID - 1000]);
	}

	if(tk.tokenID == LFTSQREDELIM) {
		tk = scanner.scanToken();
	} else {
		errorHandler(tokenNames[tk.tokenID - 1000]);
	}

	if(tk.tokenID == IDTK) {
		tk = scanner.scanToken();
		relational();
		exp();
	} else {
		errorHandler(tokenNames[tk.tokenID - 1000]);
	}

	if(tk.tokenID == RGHTSQREDELIM) {
		tk = scanner.scanToken();
		stat();
		return;
	} else {
		errorHandler(tokenNames[tk.tokenID - 1000]);
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
		errorHandler(tokenNames[tk.tokenID - 1000]);
	}
	if(tk.tokenID == LFTSQREDELIM) {
		tk = scanner.scanToken();
	} else {
		errorHandler(tokenNames[tk.tokenID - 1000]);
	}
	if(tk.tokenID == IDTK) {
		tk = scanner.scanToken();
		relational();
		exp();
	} else {
		errorHandler(tokenNames[tk.tokenID - 1000]);
	}
	if(tk.tokenID == RGHTSQREDELIM) {
		tk = scanner.scanToken();
		stat();
		return;
	} else {
		errorHandler(tokenNames[tk.tokenID - 1000]);
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
		errorHandler(tokenNames[tk.tokenID - 1000]);
	}

	if(tk.tokenID = IDTK) {
		tk = scanner.scanToken();
	} else {
			errorHandler(tokenNames[tk.tokenID - 1000]);
	}

	if(tk.tokenID = ASSIGNOPTK) {
		tk = scanner.scanToken();
		exp();
	} else {
		errorHandler(tokenNames[tk.tokenID - 1000]);
	}
	if(tk.tokenID = DELOPTK) {
		tk = scanner.scanToken();
		return;
	} else {
		errorHandler(tokenNames[tk.tokenID - 1000]);
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
			errorHandler(tokenNames[tk.tokenID - 1000]);
		}
	} else {
		errorHandler("Any relational token");
	}
}

void Parser::exp() {
	m();
	if(tk.tokenID == DBLESTAR) {
		tk = scanner.scanToken();
		exp();
		return;
	} else if (tk.tokenID == DBLESLASH) {
		exp();
		return;
	} else {
		return;
	}
}


void Parser::m() {
	n();
	if(tk.tokenID == OPTK) {
		if(strcmp(tk.lexeme, "+") == 0) {
			tk = scanner.scanToken();
			m();
			return;
		} else {
			errorHandler("+");
		}
	} else {
		return;
	}
}


void Parser::n() {
	if(tk.tokenID == OPTK) {
		if(strcmp(tk.lexeme, "-") == 0) {
			tk = scanner.scanToken();
			n();
			return;
		} else {
			errorHandler("-");
		}
	} else {
		r();
		if(tk.tokenID == OPTK) {
			if(strcmp(tk.lexeme, "-") == 0) {
				tk = scanner.scanToken();
				n();
			}
		} else {
			return; // In case N -> R option
		}
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
			errorHandler(tokenNames[tk.tokenID - 1000]);
		}
	} else if(tk.tokenID == IDTK) {
		tk = scanner.scanToken();
		return;
	} else if(tk.tokenID == NUMTK) {
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
































