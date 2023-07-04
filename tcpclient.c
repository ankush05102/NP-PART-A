#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>

int main()
{
	int sock;
	char buffer[1024], message[30];
	
	struct sockaddr_in server_addr;
	struct hostent* host;
	host = gethostbyname("127.0.0.1");
	
	if((sock = socket(AF_INET,SOCK_STREAM,0))==-1)
	{perror("Socket"); exit(1);}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port =  htons(6119);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
	{perror("Connection"); exit(1); }
	
	bzero(buffer,1024);
	printf("Enter the message you want to send from client\n");
	scanf("%s",message);
	strcpy(buffer, message);
	printf("Client : %s\n",buffer);
	send(sock, buffer, strlen(buffer), 0);
	
	bzero(buffer, 1024);
	recv(sock, buffer, 1024, 0);
	printf("Server : %s\n", buffer);
	
	close(sock);
}
