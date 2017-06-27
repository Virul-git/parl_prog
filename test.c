	#include <stdio.h>
#include <string.h>
#include "strmp.h"

/*

void init_str(char s[])
{
	memset(s,'\0',sizeof(*s));
}

void init_ip(char ip[])
{
	init_str(ip);
	strcpy(ip,"198.168.1.1");	// dummy ip address for reference.
}


void wrap(char fmsg[], char ip[], char msg[])
{
	strcat(fmsg,ip);
	strcat(fmsg,msg);
}
*/

int main(int argc, char const *argv[])
{
	char ip[14],msg[1024],fmsg[1036];
	init_str(ip);
	init_str(msg);
	init_str(fmsg);

	//memset(ip,'\0',sizeof(ip));
	//memset(msg,'\0',sizeof(msg));
	//memset(fmsg,'\0',sizeof(fmsg));

	strcpy(msg,"this is the msg");
	strcpy(ip,"192.168.7.5");	


	wrap(fmsg,ip,msg);
	init_str(msg);
	init_ip(ip);
	printf("%s\n", ip);
	printf("%s\n", msg);
	printf("%s\n",fmsg);	

	extract(fmsg,msg,ip);

	printf("%s\n",ip);
	printf("%s\n",msg );
	//printf("%s\n",msg);
	return 0;
}