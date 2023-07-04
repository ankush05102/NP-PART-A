#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>

int main()
{
	int sock,connected,sin_bytes;
	struct sockaddr_in server_addr, client_addr;
	char buffer[1024];
	
	if((sock = socket(AF_INET,SOCK_STREAM,0)) ==-1)
	{perror("Socket"); exit(1);}
	
	memset(&server_addr,'\0',sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(6119);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
	{perror("Bind"); exit(1);}
	
	if(listen(sock,5))
	{perror("Listen"); exit(1);}
	printf("Server is Listening...\n");
	
	while(1)
	{
		sin_bytes = sizeof(struct sockaddr_in);
		if((connected = accept(sock,(struct sockaddr *)&client_addr, &sin_bytes)) == -1)
		{perror("Connection"); exit(1);}
		
		bzero(buffer, 1024);
		recv(connected, buffer, 1024,0);
		printf("Client : %s\n",buffer);
		
		bzero(buffer,1024);
		strcpy(buffer,"HI");
		printf("Server :%s\n",buffer);
		send(connected, buffer, strlen(buffer),0);
		
		close(connected);
	
	}
}
