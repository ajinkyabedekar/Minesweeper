/*
	C socket server example, handles multiple clients using threads
*/

#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
int no=0;
//the thread function
void *connection_handler(void *);
int validat()
{
int lo;
FILE *f,*ff2;
char user[10], pass[20],user1[10], pass1[20];

	ff2=fopen("auth.txt","r");
	fscanf(ff2,"%s",user);
	fscanf(ff2,"%s",pass);
fclose(ff2);	
f = fopen("data.txt", "r");
for (lo = 0; lo < 10; lo++)
	{
		fscanf(f, "%s", user1);
		fscanf(f, "%s", pass1);
		if (strcmp(user, user1) == 0 && strcmp(pass, pass1) == 0)
			return 1;
	}
return 0;
}



int main(int argc , char *argv[])
{
	FILE *f1 = fopen("leaderboard.txt", "w");
	FILE *f2 = fopen("score.txt", "w");
	int socket_desc , client_sock , c , *new_sock;
	struct sockaddr_in server , client;

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );

	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");

	//Listen
	listen(socket_desc , 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	
	while(1)
	{
	
	if(no<=10)
	{
		client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		puts("Connection accepted");

		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = client_sock;

		if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
		{
			perror("could not create thread");
			return 1;
		}

		//Now join the thread , so that we dont terminate before the thread
		//pthread_join( sniffer_thread , NULL);
		puts("Handler assigned");
	no++;
	FILE *f1;
	f1=fopen("no.txt","w");
	fprintf(f1,"%d",no);
	fclose(f1);
	
	} //printf(".%d.\n",no);
	}
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}

	return 0;
}

/* * This will handle connection for each client* */
void *connection_handler(void *socket_desc)
{
	//Get the socket descriptor
	int sock = *(int*)socket_desc;
	int read_size;
	char *message , client_message[2000];

	//Receive a message from client
	while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
	{

		char r[10];
		int rr=validat();		
		if(rr==1)
			strcpy(r,"1");
		else
			strcpy(r,"0");
		//Send the message back to client
		write(sock , r , strlen(r));
	}

	if(read_size == 0)
	{
		puts("Client disconnected");
		no--;
		FILE *f1;
		f1=fopen("no.txt","w");
		fprintf(f1,"%d",no);
		fclose(f1);
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}

	//Free the socket pointer
	free(socket_desc);

	return 0;
}


