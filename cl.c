#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	int sock,n_bytes;
	struct sockaddr_in server_addr;
	char buffer[1024];
	
	char message[1024];
	printf("Enter the message to send to server\n");
	scanf("%s",message);
	
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&server_addr, sizeof(server_addr));
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{perror("Connect"); exit(1);}
	
	sendto(sock, message, 1024, 0, (struct sockaddr*)NULL, sizeof(server_addr));
	
	int n = recvfrom(sock, buffer, sizeof(buffer),0, NULL, NULL);
	buffer[n] = '\0';
	puts(buffer);
	
	close(sock);
}
