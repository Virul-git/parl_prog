#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>

//  custom header
#include "strmp.h"

// define global variables
int nclients =0;
int port;
int udpSocket, nBytes;

char buffer[1036];  // recieves with ip.
char ip[12],msg[1024];  // for extracting ip and message seperately

struct sockaddr_in serverAddr, clientAddr;
struct sockaddr_storage serverStorage;
socklen_t addr_size, client_addr_size;
bool server_active;


struct client
{
  char ip[12];
  char status;    // R - Ready
                  // N - Not Ready
                  // D - Disconnected
}clients[8];



void  display(char *argv[])
{
  system("clear");
  printf("IP:%s,\t Port:%s\n", argv[1],argv[2]);
  printf("Device   ---------------------------- status\n");
  int j;
  for(j=0;j<nclients;j++)
  {
    printf("%s -------------------------- %c\n",clients[j].ip,clients[j].status );
  };
  printf("number of clients connected: %d\n",nclients );
}



bool server_input()
{
  char action;
  printf("Select an action: W-wait, S-start, E-exit\n");
  printf(":/> ");
  scanf("%c",&action);
  printf("\n");
  switch(action)
  {
    case 'W':
      return  false;
      break;
    case 'S':
      return true;
      break;
    case 'E':
      return false;
      exit(0);
      break;
  }
  return false;
}

int main( int argc, char *argv[])
{
    if (argc == 3)
  {
  	printf("Current ip_addr :%s\n", argv[1]);
  	//printf("Current port :%d\n", (*(argv[2])));
  
  }
  else
  {
  	printf("Error: Specify ip_addr and port_number\n");
  	printf("Correct way of entering arguments is, <file_name> <ip_addr> <port_number>\n " );
  	return 0;
  }

   port = strtol(argv[2],NULL,10);
  printf("Current port :%d\n",port);
 //argv[2] = ((int) ((long int) (argv[2])));
 // printf("%d\n", argv[2] );
 


  udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  memset(serverAddr.sin_zero,'\0', sizeof serverAddr.sin_zero);

  bind(udpSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

  addr_size = sizeof serverStorage;

   server_active = false;

  while(1)
  { 

  init_str(buffer);
  init_str(msg);

  init_ip(ip);
  nBytes = recvfrom(udpSocket, buffer, 1036, 0, (struct sockaddr *)&serverStorage, &addr_size);

    if(nBytes >0)
    {
    extract(buffer,msg,ip);
    int j;
    bool new_client = true;
     for(j=0;j<nclients;j++)
      {
        if(strcmp(clients[j].ip ,ip)==0)
        {
          new_client = false;
        };
      };

      if(new_client)
      {
        strcpy(clients[nclients].ip,ip);
        clients[nclients].status = 'R';
        nclients++;
        init_str(msg);
        strcpy(msg,"welcome client");
        sendto(udpSocket,msg,1024,0,(struct sockaddr *)&serverStorage,addr_size);
      }
      else
      {
        init_str(msg);
        strcpy(msg,"wait for instructions");
        sendto(udpSocket,msg,1024,0,(struct sockaddr *)&serverStorage,addr_size);
      }
    };

  display(argv);
  server_active = server_input();

    while(server_active)
  	{

      init_str(buffer);
      init_str(msg);

      init_ip(ip);


    nBytes = recvfrom(udpSocket, buffer, 1036, 0, (struct sockaddr *)&serverStorage, &addr_size);

     extract(buffer,msg,ip);

     printf("%s\n",buffer);
     printf("%s\n",ip);
     printf("%s\n",msg);

     int i;
  	 for(i=0;i<nBytes-1-strlen(ip);i++)
  	 { 
  		msg[i] = toupper(msg[i]);
  	 };
  	
  	 sendto(udpSocket, msg, nBytes-strlen(ip), 0, (struct sockaddr *)&serverStorage, addr_size);
  	};
  };

 return 0;
}
