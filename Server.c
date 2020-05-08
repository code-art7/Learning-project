// Server side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <unistd.h> 
#include <string.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#define PORT 8080

int main() 
{ 
	// Creating socket file descriptor 
	// socket() return interger
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in address;  
	address.sin_family = AF_INET; // ip type i.e : ipv4 or ipv6
	address.sin_addr.s_addr = INADDR_ANY; // ip address 
	address.sin_port = htons( PORT ); // port
	
	// Forcefully attaching socket to the port 8080 
	int addrlen = sizeof(address); 
	printf("Address len = %d \n",addrlen);
	if ((bind(server_fd, (struct sockaddr *)&address, addrlen))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	}

	// Listen
	int x = listen(server_fd, 3);
	printf("listen on %d\n",x);
	if (x < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	}
	// Accept
	//int * ptr = (socklen_t*)&addrlen;
	
	printf("ready for new connection\n");
	printf("Ctrl+C to Exit server\n");

	int new_socket1 = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen); 
	printf("Accept on %d \n",new_socket1);
	if (new_socket1 <0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	printf("\nClient 1 Online\n");
	
	int new_socket2 = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen); 
	printf("Accept on %d \n",new_socket2);
	if (new_socket2 <0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	}
	printf("\nClient 2 Online");

	char str1[1024] = {0};
	char str2[1024] = {0};

	int num1, num2;
	read(new_socket1, &num1, 1024);
	read(new_socket2, &num2, 1024);

	int sum = num1+num2;
	send(new_socket1, &sum, sizeof(int), 0);
	send(new_socket2, &sum, sizeof(int), 0);
	
	return 0; 
}
