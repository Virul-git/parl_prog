#ifndef _STRMP_H
#define _STRMP_H 

#include <string.h>

size_t strlen(const char *str)
{
    const char *s;
    for (s = str; *s; ++s);
    return(s - str);
}


void reverse(char s[])
{
 int i, j;
 char c;

 for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
     c = s[i];
     s[i] = s[j];
     s[j] = c;
 }
}

void itoa(int n, char s[])
{
 int i, sign;

 if ((sign = n) < 0)  /* record sign */
     n = -n;          /* make n positive */
 i = 0;
 do {       /* generate digits in reverse order */
     s[i++] = n % 10 + '0';   /* get next digit */
 } while ((n /= 10) > 0);     /* delete it */
 if (sign < 0)
     s[i++] = '-';
 s[i] = '\0';
 reverse(s);
}




void extract(char fmsg[], char msg[1024], char ip[14])
{
	int j,len,len_ip;
	len = strlen(fmsg);
	len_ip = strlen(ip);
	for(j=0;j<len_ip;j++)
	{
		ip[j]=fmsg[j];
	}
	for(j=0;j<len-len_ip;j++)
	{
		msg[j]=fmsg[j+len_ip];
	}
}

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
#endif