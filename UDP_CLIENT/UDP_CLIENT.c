#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(){

	int tcpsockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in recvinfo; 
	memset(&recvinfo, 0, sizeof(recvinfo)); 
	recvinfo.sin_family = AF_INET;
	recvinfo.sin_port = htons(8080);
	recvinfo.sin_addr.s_addr = INADDR_ANY;
	socklen_t recvlen = sizeof(recvinfo);
	
	int opt = 1; 
	setsockopt(tcpsockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	bind(tcpsockfd,(struct sockaddr*)&recvinfo, recvlen);

	char recvbuffer[8] = {0};
	recvbuffer[7] = '\0';

	int udpsockfd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in serverinfo;
	memset(&serverinfo, 0, sizeof(serverinfo));
	serverinfo.sin_family = AF_INET;
	serverinfo.sin_port = htons(8080);

	if(inet_pton(AF_INET, "192.168.4.1", &serverinfo.sin_addr)<=0){
		printf("%s\n", "FAILED TO CONVERT IP");
	}
	
	socklen_t serverlen = sizeof(serverinfo);
	while(1){
		
		listen(tcpsockfd, 1);
		int guiclientfd = accept(tcpsockfd, NULL, NULL); 
		memset(&recvbuffer, 0, sizeof(recvbuffer));
		int bytes = recv(guiclientfd ,recvbuffer, sizeof(recvbuffer), 0); 
		recvbuffer[bytes] = '\0';
		printf("%s\n",recvbuffer);
		sendto(udpsockfd, recvbuffer, strlen(recvbuffer), 0, (struct sockaddr *) &serverinfo, sizeof(serverinfo));
		close(udpsockfd);
	}

	return 0;
}
