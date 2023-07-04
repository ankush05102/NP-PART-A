#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>

int main()
{
	int sock,n_bytes;
	struct sockaddr_in server_addr, client_addr;
	char *message = "Hello this is server";
	char buffer[1024];
	
	//printf("Enter the message to be sent\n");
	//scanf("%s",message);
	
	sock = socket(AF_INET,SOCK_DGRAM,0);
	
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port  = htons(5000);
	server_addr.sin_addr.s_addr =  inet_addr("127.0.0.1");
	
	bind(sock,(struct sockaddr *)&server_addr, sizeof(server_addr));
	
	n_bytes = sizeof(client_addr);
	int n = recvfrom(sock,buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &n_bytes);
	buffer[n] = '\0';
	puts(buffer);
	
	
	sendto(sock, message, 1024,0,  (struct sockaddr *)&client_addr, n_bytes);
	
}
