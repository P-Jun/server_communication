#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void trans(int connfd);

void errhandle(char *errmsg){
    fputs(errmsg, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char **argv) 
{
    int listenfd, connfd;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    char client_hostname[128], client_port[128];

    int port = #;
    
    listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == -1) errhandle("socket() ERR!");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    int bind_ret = bind(listenfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr) );
    if(bind_ret == -1) errhandle("bind() ERR!");

    int listen_ret = listen(listenfd, 10); // 10 is wait queue size
    if(listen_ret == -1) errhandle("listen() ERR!");

    while (1) {
	int clientlen = sizeof(clnt_addr); 
	printf("Wait Coneection...\n");
	connfd = accept(listenfd, (struct sockaddr *)&clnt_addr, &clientlen);
	if(connfd == -1) errhandle("accept() ERR!");
        getnameinfo((struct sockaddr *) &clnt_addr, clientlen, client_hostname, 128, 
                    client_port, 128, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
	trans(connfd);
	close(connfd);
    }
    close(listenfd);

    exit(0);
}
