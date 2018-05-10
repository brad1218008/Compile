#include <stdio.h>
char nextChar=' ';
int linenum = 1;
char line[512];
int cp=0, errorCount=0;
char s[10][128];
int wordcount = 0;
void error(int e)
{
	errorCount++;
}
void advance()
{
	nextChar = line[cp++];
}
void E();
int A()
{
	if((nextChar>='a' && nextChar<='z')||
	   (nextChar>='A' && nextChar<='Z'))
	{
		return 1;
	}
	return 0;
}
int D()
{
	if(nextChar>='0' && nextChar<='9')
	{
		return 1;
	}
	return 0;
}
int K()
{
	if(nextChar=='(')
	{
		advance();
		E();
		if(nextChar==')')
		{
			advance();
		}
		else
			error(3);
		return 1;
	}
	return 0;
}
int N()
{
	if(D())
	{
		do
		{
			advance();
			if(A())
				error(1);
		}while(D());
		return 1;
	}
	return 0;
}
int I()
{
	if(A())
	{
		int n=0;
		s[wordcount][n++] = nextChar;
		advance();
		while(A() || D())
		{
			s[wordcount][n++] = nextChar;
			advance();
		}
		s[wordcount][n] = '\0';
		int diff = 1;
		for(int i=0 ;i < wordcount; i++)
		{
			if(strcmp(s[i],s[wordcount]) == 0)
			{
				diff = 0;
				break;
			}
		}
		if(diff)
		{
			wordcount++;
		}
		else
		{
			strcpy(s[wordcount]," ");
		}
		return 1;
	}
	return 0;
}
void F()
{
	if (K()){}
	else if(N()){}
	else if(I()){}
	else
	 	error(2);
}
void T()
{
	F();
	while (nextChar=='*' || nextChar=='/')
	{
		advance();
		F();
	}
}
void E()	
{
	if(nextChar=='+' || nextChar=='-')
	{
		advance();
	}
	T();
	while (nextChar=='+' || nextChar=='-')
	{
	  advance();
	  T();
	}
}
int main(int argc, char *argv[])
{
	FILE *file;
	char str[256];
	char* filename = "homework.txt"; //set file name
	
	file = fopen(filename,"r");
	
	while (fgets(line,sizeof(line),file)!=NULL)
	{
		printf("%d. %s",linenum,line);
		errorCount = 0;
		cp = 0;
		wordcount = 1;
		advance();
		E();
		if (errorCount>0)
		 printf("  *ERROR* \n\n");
		else
		 printf("  *OK* \n\n");
		for(int i=1; i < wordcount; i++)
		{
			printf(" id_%d. %s\n",i,s[i]);
		}
		printf("\n");
		linenum++;
	}
	return 0;
}
