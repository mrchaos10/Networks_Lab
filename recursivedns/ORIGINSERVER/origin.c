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
#define PORT 1024
#define PORT1 2024
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
	char hostname[100],ip[100];
	int size=sizeof(struct sockaddr);
	recvbytes=recvfrom(sockid,hostname,sizeof(hostname),0,(struct sockaddr*)&dummy,&size);
	hostname[recvbytes]='\0';
	printf("\nHostname From Client : %s ",hostname);
	char extension[20];
	int count=0,j,k;
	for(i=0;hostname[i]!='\0';i++)
	{
		if(hostname[i]=='.')
		{
			count++;
			if(count==2)
			{
				break;
			}
		}
	}
	strcpy(extension,hostname+i);
	//printf("%s",extension);
	int fd=open("origin.txt",O_RDWR | S_IREAD | S_IWRITE);
	if(fd==-1)
	{
		printf("File Error");
		close(sockid);
		return 0;
	}
	char filecontent[300];
	lseek(fd,0,0);
	read(fd,filecontent,300);
	int flag=0;
	count=0;
	for(i=0;i<strlen(filecontent);i++)
	{
		count=0;
		for(j=0;j<strlen(extension);j++)
		{
			if(extension[j]==filecontent[i+j])
			{
				count++;
				if(count==strlen(extension))
				{
					flag=1;
					break;
				}
			}
		}
		if(flag)
		{
			k=0;
			for(j=i+strlen(extension)+1;filecontent[j]!='\n';j++)
			{
				ip[k++]=filecontent[j];
			}
			break;
		}
	}
	ip[k]='\0';
        
        int mainsock=socket(AF_INET,SOCK_DGRAM,0);
        struct sockaddr_in client;
        client.sin_family=AF_INET;
        client.sin_port=htons(PORT1);
        client.sin_addr.s_addr=INADDR_ANY; 
        for(i=0;i<8;i++)
		server.sin_zero[i]='\0';
	
        int connectstatus=(mainsock,(struct sockaddr*)&client,sizeof(struct sockaddr));
        if(connectstatus==-1)
        {
         printf("\n Connect Error to the TLDSERVER");
         close(mainsock);
        }
        char ip1[100];
        int sentbytes1=sendto(mainsock,hostname,sizeof(hostname),0,(struct sockaddr*)&client,sizeof(struct sockaddr));
        int recvbytes1=recvfrom(mainsock,ip1,sizeof(ip1),0,NULL,NULL);
        ip1[recvbytes1]='\0';
        printf("\nIp from TLD is %s\n",ip1);
        close(mainsock);

        sentbytes=sendto(sockid,ip,strlen(ip),0,(struct sockaddr*)&dummy,size);
	
        close(sockid);
	return 0;
}
