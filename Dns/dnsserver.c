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
#define PORT0 9024
#define PORT 1024
#define PORT1 2024
#define PORT2 3024

int main()
{
        // ROOT
int count,j,k;
        int sentbytes,recvbytes;
	struct sockaddr_in server,dummy;
        int i,sockid0;
        char hostname[100];
	sockid0=socket(AF_INET,SOCK_DGRAM,0);
	if(sockid0==-1)
	{
		printf("Socket Error");
		return 0;
	}
server.sin_family=AF_INET;
server.sin_port=htons(PORT0);
server.sin_addr.s_addr=INADDR_ANY;
for(i=0;i<8;i++)
server.sin_zero[i]='\0';
printf("\nConnected to Client\n");
int size=sizeof(struct sockaddr);
char ress[100];
strcpy(ress," ");
strcat(ress,"Enter the Hostname ");
sentbytes=sendto(sockid0,hostname,strlen(hostname),0,(struct sockaddr*)&server,size);
printf("\nEntered HostName : ");
recvbytes=recvfrom(sockid0,hostname,sizeof(hostname),0,NULL,NULL);
hostname[recvbytes]='\0';
printf("%s",hostname);

//origin
int sockid;
struct sockaddr_in client,client1,client2;
sockid=socket(AF_INET,SOCK_DGRAM,0);
client.sin_family=AF_INET;
client.sin_port=htons(PORT);
client.sin_addr.s_addr=INADDR_ANY;
for(i=0;i<8;i++)
client.sin_zero[i]='\0';
printf("\nConnected to Origin\n");
char nip[100],ip1[100],ip2[100];
printf("\nEntered HostName : ");
size=sizeof(struct sockaddr);
sentbytes=sendto(sockid,hostname,strlen(hostname),0,(struct sockaddr*)&client,size);
recvbytes=recvfrom(sockid,nip,sizeof(nip),0,NULL,NULL);
nip[recvbytes]='\0';
printf("\nIp from origin is %s\n",nip);
char result[1000];
strcpy(result,"");
strcat(result,"\nIp from origin is %s\n");
strcat(result,nip);
close(sockid);

//TLD


int sockid1;
sockid1=socket(AF_INET,SOCK_DGRAM,0);
client1.sin_family=AF_INET;
client1.sin_port=htons(PORT1);
client1.sin_addr.s_addr=INADDR_ANY;
for(i=0;i<8;i++)
client1.sin_zero[i]='\0';
printf("\nConnected to TLD\n");
sentbytes=sendto(sockid1,hostname,strlen(hostname),0,(struct sockaddr*)&client1,size);
recvbytes=recvfrom(sockid1,ip1,sizeof(ip1),0,NULL,NULL);
ip1[recvbytes]='\0';
printf("\nIp from TLD is %s\n",ip1);
strcat(result,"\nIp from TLD is %s\n");
strcat(result,ip1);
close(sockid1);

// Authoritative


int sockid2;
sockid2=socket(AF_INET,SOCK_DGRAM,0);
client2.sin_family=AF_INET;
client2.sin_port=htons(PORT2);
client2.sin_addr.s_addr=INADDR_ANY;
for(i=0;i<8;i++)
client2.sin_zero[i]='\0';
printf("\nConnected to Authoritative\n");
sentbytes=sendto(sockid2,hostname,strlen(hostname),0,(struct sockaddr*)&client2,size);
recvbytes=recvfrom(sockid2,ip2,sizeof(ip2),0,NULL,NULL);
ip2[recvbytes]='\0';
printf("\nIp from Authoritative is %s\n",ip2);
strcat(result,"\nIp from Authoritative server is %s\n");
strcat(result,ip2);
close(sockid2);


printf("\n\n\n\n\n\n\n");
printf("%s",result);

sentbytes=sendto(sockid0,result,strlen(result),0,(struct sockaddr*)&server,size);
printf("%d",sentbytes);
close(sockid0);

return 0;
}
