/*
	C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
extern int start();
int sock;int ij;
char message[1000] , server_reply[2000];
	
int main(int argc , char *argv[])
{
	struct sockaddr_in server;
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}

	puts("Connected\n");
	int ii = 0;
	//keep communicating with server
	while (1)
	{
		if (ii==0)
		{
			ii = 1;
			//Send some data
			if( send(sock , message , strlen(message) , 0) < 0)
			{
				puts("Send failed");
				return 1;
			}

			//Receive a reply from the server
			
			for (ij = 0; ij < 2000; ij++)
				server_reply[ij]='\0';
		}
		else
		{
			char no[2];
			FILE *f11;int aa=0;
			f11=fopen("no.txt","r");
			fscanf(f11,"%s",no);
			fclose(f11);
			//printf("%s",no);
			if(strcmp(no,"1")==0 || strcmp(no,"2")==0 || strcmp(no,"3")==0 || strcmp(no,"4")==0 || strcmp(no,"5")==0 || strcmp(no,"6")==0 || strcmp(no,"7")==0 || strcmp(no,"8")==0 || strcmp(no,"9")==0 || strcmp(no,"0")==0)
				//aa++;
				start();
			else
				printf("Try after some time");
			break;
		}
		
	}

	close(sock);
	return 0;
}

int validation()
{
strcpy(message,"1");
send(sock, message, strlen(message), 0);
recv(sock, server_reply,2000,0);
if(strcmp(server_reply,"1")==0)
	return 1;
else
	return 0;
}
