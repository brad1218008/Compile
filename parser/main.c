#include <stdio.h>
#include "parser.h"

int main(){
	FILE *file;
	char str[MAX_BUFF];
	char* filename = "test.txt";
	
	file = fopen(filename,"r");
	if (file == NULL){
		printf("Could not open file %s",filename);
		return 1;
	}
	
	while (fgets(str, MAX_BUFF, file) != NULL)
		printf("%s",str);
	fclose(file);
	
	return 0;
}