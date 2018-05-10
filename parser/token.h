#include "parser.h"

typedef enum { false, true } bool;

enum TOK {
	tokEOF = 0, 	//'EOF'
	tokERROR,   	//'error'
	tokID,      	//variable
	tokNUMBER,  	//number
	tokPLUS,    	//'+'
	tokPLUSONE, 	//'++'
	tokPLUSSELF,	//'+='
	tokMINUS,   	//'-'
	tokMINUSONE,	//'--'
	tokMINUSSELF,   //'-='
	tokMUL,     	//'*'
	tokMULSELF,     //'*='
	tokDIV,     	//'/'
	tokDIVSELF,     //'/='
	tokPASS,    	//'='
	tokEQ,      	//'=='
	tokNOT,     	//'!'
	tokNEQ,     	//'!='
	tokLESS,		//'<'
	tokLEQ,    		//'<='
	tokGREATER, 	//'>'
	tokGEQ,     	//'>='
	tokLPAREN,  	//'('
	tokRPAREN,  	//')'
	tokCOMMA,   	//','
	tokSEMI,    	//';'
	tokPERIOD,  	//'.'
	tokBECOMES, 	//':'
	tokEND,     	//'end'
	tokIF,
	tokTHEN,
	tokWHILE,
	tokDO,
	tokREAD,
	tokWRITE,
	tokIDLIST,
	tokCALL,
	tokCONST,
	tokVAR,
	tokPROCEDURE,
	tokPROGRAM,
	tokSTRING
	
};

struct token {
	int tok;
	int line;
	int position;
	char value[36];
};

struct token *newToken(int tok, int line, int position, char *value) {
	
	struct token *tmp = malloc(sizeof(struct token));
	tmp->tok = tok;
	tmp->line = line;
	tmp->position = position;
	strcpy(tmp->value, value);
	return tmp;
}

char *tokenShow(struct token *tmp){
	
	static char tokenStr[MAX_BUFF];
	sprintf(tokenStr,"tok=%d line=%d position=%d value=\"%-s\"",
		   tmp->tok, tmp->line, tmp->position, tmp->value);
	return tokenStr;
}

bool isDigit(int a){
	if(a >= '0' && a <= '9')
		return true;
	return false;
}

bool isLetter(int a) {
	if((a >= 'a' && a <='z')||(a >= 'A' && a <= 'Z'))
		return true;
	return false;
}
