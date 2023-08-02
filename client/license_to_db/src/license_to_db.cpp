#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <winsock2.h>
#include <licensecc/licensecc.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")
void ErrorHandling(char* message);
int client_init(char* ip, int port);
void get_hardware_id(char* pc_identifier);

int main(int argc, char *argv[]) {
	char pc_identifier[LCC_API_PC_IDENTIFIER_SIZE + 1];
	get_hardware_id(pc_identifier);

	int sock;

	char rev[30];
	int strLen;
	char ip[32] = #IP;
	int port = #PORT;
	sock = client_init(ip, port);
	send(sock, pc_identifier, sizeof(pc_identifier), 0);
	strLen = recv(sock, rev, sizeof(rev), 0);
	if (strLen == -1) ErrorHandling((char*)"read() error");
		printf("%s\n", rev);
	closesocket(sock);
	WSACleanup();
	return 0;
}

void get_hardware_id(char* pc_identifier) {
	size_t pc_id_sz = LCC_API_PC_IDENTIFIER_SIZE + 1;
	bool identify_flag = identify_pc(STRATEGY_DEFAULT, pc_identifier, &pc_id_sz, nullptr);
	if (!identify_flag)
		cerr << "errors in identify_pc" << endl;
}

void ErrorHandling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int client_init(char* ip, int port) {
	SOCKET server_socket;
	WSADATA wsadata;
	SOCKADDR_IN server_address = {0};

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) ErrorHandling((char*)"WSAStartip() error");

	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (server_socket == INVALID_SOCKET) ErrorHandling((char*)"sock() error");

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(ip);
	server_address.sin_port = htons(#PORT);	 // htons(atoi(argv[2]));

	if (connect(server_socket, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
		ErrorHandling((char*)"connect() error");

	return server_socket;
}