#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<fcntl.h>
#define PORT 9024
int main()
{

int i,sockid;
	sockid=socket(AF_INET,SOCK_DGRAM,0);
	if(sockid==-1)
	{
		printf("Socket Error");
		return 0;
	}
	int sentbytes,recvbytes;
	struct sockaddr_in server,dummy;
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=INADDR_ANY;
	for(i=0;i<8;i++)
		server.sin_zero[i]='\0';
	int bindstatus=bind(sockid,(struct sockaddr*)&server,sizeof(struct sockaddr));
	if(bindstatus==-1)
	{
		printf("Bind Error");
		close(sockid);
	}
	char hostname[100],msg[100];
	int size=sizeof(struct sockaddr);
	recvbytes=recvfrom(sockid,msg,sizeof(msg),0,(struct sockaddr*)&dummy,&size);
	msg[recvbytes]='\0';
	printf("\nMessage From  local Dns Server : \n %s ",msg);
        printf("\n Enter the hostname: ");
        scanf("%s",hostname);
        sentbytes=sendto(sockid,hostname,strlen(hostname),0,(struct sockaddr*)&dummy,size);
        
	char msg1[1000]; 
        recvbytes=recvfrom(sockid,msg1,sizeof(msg1),0,(struct sockaddr*)&dummy,&size);
	msg1[recvbytes]='\0';
        printf("bytes recieved %d",recvbytes);
	printf("\nMessage From  local Dns Server : \n %s ",msg1);

close(sockid);

return 0;
}
