#include <stdio.h>
#include <stdlib.h>
#include "parser.h"


int nextChar;
int currentPosition;
int linelen = 0;
int linenum = 0;
char str[MAX_BUFF];
FILE *fp;

void readNext() {
	currentPosition++;
	if(currentPosition < linelen)
		nextChar = str[currentPosition];
	else {
		if (feof(fp)) {
			linelen = 0;
			nextChar = -1;
		}
		else {
			if (fgets(str, MAX_BUFF, fp) != NULL) {
				linelen = strlen(str);
				linenum++;
				currentPosition = 0;
				nextChar = str[currentPosition];
				printf("%4d %s", linenum, str);
			}
		}
	}
}

struct token *nextToken() {
	static char s[128] = "";
	int n=0;
	while (1) {
		if(isLetter(nextChar)) {
			do {
				s[n++] = nextChar;
				readNext();
			}while(isLetter(nextChar) || isDigit(nextChar));
			s[n]='\0';
			return newToken(tokID,linenum,currentPosition,s);
		}
		else if(isDigit(nextChar)) {
			do {
				s[n++] = nextChar;
				readNext();
			}while(isDigit(nextChar));
			s[n] = '\0';
			return newToken(tokNUMBER,linenum,currentPosition,s);
		}
		else {
			switch (nextChar) {
				case '+':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					if(nextChar == '+') {
						s[n++] = nextChar;
						readNext();
						s[n] = '\0';
						return newToken(tokPLUSONE,linenum,currentPosition,s);
					}
					else if(nextChar == '=') {
						s[n++] = nextChar;
						readNext();
						s[n] = '\0';
						return newToken(tokPLUSSELF,linenum,currentPosition,s);
					}
					else {
						return newToken(tokPLUS,linenum,currentPosition,s);
					}
				case '-':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					if(nextChar == '-') {
						s[n++] = nextChar;
						readNext();
						s[n] = '\0';
						return newToken(tokMINUSONE,linenum,currentPosition,s);
					}
					else if(nextChar == '=') {
						s[n++] = nextChar;
						readNext();
						s[n] = '\0';
						return newToken(tokMINUSSELF,linenum,currentPosition,s);
					}
					else {
						return newToken(tokMINUS,linenum,currentPosition,s);
					}
				case '*':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					if(nextChar == '=') {
						s[n++] = nextChar;
						readNext();
						s[n] = '\0';
						return newToken(tokMULSELF,linenum,currentPosition,s);
					}
					else {
						return newToken(tokMUL,linenum,currentPosition,s);
					}
				case '/':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					if(nextChar == '=') {
						s[n++] = nextChar;
						readNext();
						s[n] = '\0';
						return newToken(tokDIVSELF,linenum,currentPosition,s);
					}
					else {
						return newToken(tokDIV,linenum,currentPosition,s);
					}
				case '=':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					if(nextChar == '=') {
						s[n++] = nextChar;
						readNext();
						s[n] = '\0';
						return newToken(tokEQ,linenum,currentPosition,s);
					}
					else {
						return newToken(tokPASS,linenum,currentPosition,s);
					}
				case '!':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					if(nextChar == '=') {
						s[n++] = nextChar;
						readNext();
						s[n] = '\0';
						return newToken(tokNEQ,linenum,currentPosition,s);
					}
					else {
						return newToken(tokNOT,linenum,currentPosition,s);
					}
				case '<':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					if(nextChar == '=') {
						s[n++] = nextChar;
						readNext();
						s[n] = '\0';
						return newToken(tokLEQ,linenum,currentPosition,s);
					}
					else {
						return newToken(tokLESS,linenum,currentPosition,s);
					}
				case '>':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					if(nextChar == '=') {
						s[n++] = nextChar;
						readNext();
						s[n] = '\0';
						return newToken(tokGEQ,linenum,currentPosition,s);
					}
					else {
						return newToken(tokGREATER,linenum,currentPosition,s);
					}
				case '(':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					return newToken(tokLPAREN,linenum,currentPosition,s);
				case ')':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					return newToken(tokRPAREN,linenum,currentPosition,s);
				case ',':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					return newToken(tokCOMMA,linenum,currentPosition,s);
				case ';':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					return newToken(tokSEMI,linenum,currentPosition,s);
				case '.':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					return newToken(tokPERIOD,linenum,currentPosition,s);
				case ':':
					s[n++] = nextChar;
					s[n] = '\0';
					readNext();
					return newToken(tokBECOMES,linenum,currentPosition,s);
				case '"':
					readNext();
					while(nextChar != '"') {
						s[n++] = nextChar;
						readNext;
					}
					readNext();
					s[n] = '\0';
					return newToken(tokSTRING,linenum,currentPosition,s);
				case '\0':
				case ' ':
				case '\t':
				case '\r':
				case '\n':
					readNext();
					break;
				case -1:
					return NULL;
				default:
					s[n++]=nextChar;
					s[n] = '\0';
					readNext();
					return newToken(tokERROR,linenum,currentPosition,s);
			}
		}
	}
}

void scanner(FILE *f) {
	fp = f;
}