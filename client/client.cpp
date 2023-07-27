#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

void ErrorHandling(char* message);
int client_init(char* ip, int port);

int main(int argc, char* argv[]) {
    int sock;

    char rev[30], sen[30];
    int strLen;
    char ip[32] = #SERVER_IP;
    int port = #SERVER_PORT;
    //strcpy(ip, argv[1]);

    sock = client_init(ip, port);

    while (1) {
        printf("text : ");
        scanf("%s", sen);
        send(sock, sen, sizeof(sen), 0);
        // return value is str len or -1 when error
        printf("send end\n");
        strLen = recv(sock, rev, sizeof(rev), 0);
        printf("rev end\n");
        if (strLen == -1)
            ErrorHandling((char*)"read() error");
        printf("%s\n", rev);
    }
    closesocket(sock);
    WSACleanup(); //free socket

    return 0;
}

void ErrorHandling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int client_init(char* ip, int port) {
    SOCKET server_socket;
    WSADATA wsadata;
    SOCKADDR_IN server_address = { 0 };

    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
        ErrorHandling((char*)"WSAStartip() error");

    server_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET)
        ErrorHandling((char*)"sock() error");

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(ip);
    server_address.sin_port = htons(60000); //htons(atoi(argv[2]));

    if (connect(server_socket, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
        ErrorHandling((char*)"connect() error");

    return server_socket;
}