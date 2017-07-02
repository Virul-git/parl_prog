#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

//additions
#include <stdlib.h>

// sting manipulation header ** custom made **
#include "strmp.h"	


// global variables initialization
int port;
int clientSocket, portNum, nBytes;
char buffer[1024];
struct sockaddr_in serverAddr;
socklen_t addr_size;



int main( int argc, char *argv[] )
{
	 if (argc == 3)			// for command line arguments 
  {
  	printf("Current ip_addr :%s\n", argv[1]);
  }
  else
  {
  	printf("Error: Specify ip_addr and port_number\n");
  	printf("Correct way of entering arguments is, <file_name> <ip_addr> <port_number>\n " );
  	return 0;
  }

  port = strtol(argv[2],NULL,10);
  printf("Current port :%d\n", port);



  clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
  addr_size = sizeof serverAddr;

  while(1)
	{

	printf("Type a sentence for the server: \n");
	init_str(buffer);
	fgets(buffer, 1024,stdin);

	printf("You typed:%s", buffer);

  char fmsg[1036],ip[12];
  init_str(fmsg);
  init_str(ip);
  strcpy(ip,"192.168.7.5");

  wrap(fmsg,ip,buffer);

	nBytes = strlen(fmsg) +1;

	sendto(clientSocket, fmsg, nBytes, 0, (struct sockaddr *)&serverAddr, addr_size);

	nBytes = recvfrom(clientSocket, buffer, 1024, 0, NULL, NULL);

	printf("Recieved from server: %s \n", buffer);
	}

   return 0;

}
