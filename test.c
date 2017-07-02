#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strmp.h"

// global varibles
int a,b;


void p(char* s)
{
	printf("%s\n",s );
	printf("%lu\n",sizeof(s) );
}

int main(int argc, char const *argv[])
{
	char str[50];
	memset(str,'\0',sizeof(str));
	printf("%s\n",str);
	printf("%lu\n",sizeof(str));


	strcpy(str,"asdasaaadad");
	printf("%s\n",str );
	printf("%lu\n",sizeof(str));


	memset(str,'\0',sizeof(str));
	printf("%s\n",str );
	printf("%lu\n",sizeof(str));


	strcpy(str,"aasa");
	printf("%s\n",str );
	printf("%lu\n",sizeof(str));

	p(str);



}