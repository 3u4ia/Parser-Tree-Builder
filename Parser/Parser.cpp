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
			if(tk.tokenID == IDTk) {
				tk = scanner.scanToken();
			} else {
				printf("Error expected IDTk lexeme received: %s\n", tk.lexeme);
				exit(1);
			}
			if(strcmp(tk.lexeme, "=") == 0) {
				tk = scanner.scanToken();
			}
			else {
				errorHandler("Parsing Error line %d: expected EQUALSOP got %s\n");
				printf("Error expected = lexeme received: %s\n", tk.lexeme);
				exit(1);
			}
			if(tk.tokenID == NUMTk) {
				tk = scanner.scanToken();
			}
			else {
				printf("Error expected numTk received: %s\n", tk.lexeme);
				exit(1);
			}
			varList();
			if(tk.tokenID == COLONTk) {
				tk = scanner.scanToken();
			}
			else {
				printf("Error expected colon received: %s\n", tk.lexeme);
			}
		}
		return; // for the empty case
	}
	return; // for the empty case
}

void Parser::block() {
	if (tk.tokenID == LEFTCURLYDELIM) {
		tk = scanner.scanToken();
		vars();
		stats();
		if(tk.tokenID == RIGHTCURLYDELIM) {
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
	if(tk.tokenID == LEFTCURLYDELIM) {
		stat();
		mStat();
		return;
	}


	return;
}

void Parser::stat() {
	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "scan") == 0) {
			scan();
			return;
		}
		if(strcmp(tk.lexeme, "output") == 0) {
			print();
			return;
		}
		if(strcmp(tk.lexeme, "cond") == 0) {
			cond();
			return;
		}
		if(strcmp(tk.lexeme, "loop") == 0) {
			loop();
			return;
		}
		if(strcmp(tk.lexeme, "set") == 0) {
			assign();
			return;
		}
			
	} 
	else if(tk.tokenID == LEFTCURLYDELIM) {
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

			if(tk.tokenID == IDTK) {
				tk = scanner.scanToken();

				if(tk.tokenID == DELOPTK) {
					tk = scanner.scanToken();
					return;
				} else {
					errorHandler(tokenNames[tk.tokenID]);
				}
			} else {
				errorHandler(tokenNames[tk.tokenID]);
			}
		} else {
			errorHandler("scan");
		}
	} else {
		errorHandler(tokenNames[tk.tokenID]);
	}
}



void Parser::print() {
	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "output") == 0) {
			tk = scanner.scanToken();
			exp();

			if(tk.tokenID == DELOPTK) {
				tk = scanner.scanToken();
				return;
			} else {
				errorHandler(tokenNames[tk.tokenID]);
			}
		}
		else {
			errorHandler("output");
		}
	} else {
		errorHandler(tokenNames[tk.tokenID]);
	}
}


void Parser::cond() {
	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "cond") == 0) {
			tk = scanner.scanToken();

			if(tk.tokenID == LFTSQREDELIM) {
				tk = scanner.scanToken();

				if(tk.tokenID == IDTK) {
					tk = scanner.scanToken();
					relational();
					exp();
					if(tk.tokenID == RGHTSQREDELIM) {
						tk = scanner.scanToken();
						stat();
						return;
					} else {
						errorHandler(tokenNames[tk.tokenID]);
					}
				} else {
					errorHandler(tokenNames[tk.tokenID]);
				}
			} else {
				errorHandler(tokenNames[tk.tokenID]);
			}
		} else {
			errorHandler("cond");
		}
	} else {
		errorHandler(tokenNames[tk.tokenID]);
	}
}


void Parser::loop() {
	if(tk.tokenID == KEYWORD) {
		if(strcmp(tk.lexeme, "loop") == 0) {
			tk = scanner.scanToken();

			if(tk.tokenID == LFTSQREDELIM) {
				tk = scanner.scanToken();

				if(tk.tokenID == IDTK) {
					tk = scanner.scanToken();

					relational();
					exp();
					if(tk.tokenID == RGHTSQREDELIM) {
						tk = scanner.scanToken();
						scan();
						return;
					} else {
						errorHandler(tokenNames[tk.tokenID]);
					}
				} else {
					errorHandler(tokenNames[tk.tokenID]);
				}
			} else {
				errorHandler(tokenNames[tk.tokenID]);
			}
		} else {
			errorHandler("loop");
		}
	} else {
		errorHandler(tokenNames[tk.tokenID]);
	}
}






void Parser::errorHandler(const char *expectedTk) {
	printf("Error: %s expected but received %s with lexeme %s on line %d\n", expectedTk, tokenNames[tk.tokenID], tk.lexeme, tk.lineNum); 
	exit(1);
}
































