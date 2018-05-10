#include <stdio.h>
#include "parser.h"
#include "token.h"
#include "scanner.h"

int main(){
	FILE *file;
	char str[MAX_BUFF];
	char* filename = "homework.txt"; //set file name
	struct token *tok;
	
	file = fopen(filename,"r");
	if (file == NULL){ // if file open fail
		printf("Could not open this file : %s",filename);
		return 1;
	}
	// pass file to scanner
	scanner(file);
	
	while((tok = nextToken()) != NULL) {
		printf("\t%s\n",tokenShow(tok));
	}
	
//	//get file
//	while (fgets(str, MAX_BUFF, file) != NULL){
//		for(int i=0 ; str[i] != '\0'; i++) {
//			if(str[i] == '\n')
//				break;
//			if(isDigit(str[i])){
//				printf("%c is digit.\n",str[i]);
//			}
//			else if(isLetter(str[i])){
//				printf("%c is letter.\n",str[i]);
//			}
//			else {
//				printf("%c is operator.\n",str[i]);
//			}
//		}
//	}
//	fclose(file);
	
	return 0;
}