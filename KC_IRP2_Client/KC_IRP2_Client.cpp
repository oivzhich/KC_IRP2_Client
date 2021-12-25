// KC_IRP2_Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment(lib, "ws2_32.lib") 
#include<WinSock2.h>
#include<iostream>
#include<stdlib.h>
#pragma warning(disable: 4996)

using namespace std;

void main() {
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return; }
	while (true) {
		char buf[256],
			main_menu_choise,
			switch_menu_choise;

		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		// указание адреса и порта сервера
		sockaddr_in dest_addr;
		dest_addr.sin_family = AF_INET;
		dest_addr.sin_port = htons(1280);
		dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		connect(s, (sockaddr*)&dest_addr, sizeof(dest_addr));

		//Выбор пункта меню и отправка его серверу
		puts("\nChoose:\n");
		puts("1 - Individual task");
		puts("2 - Redact");
		puts("3 - View");
		puts("4 - Exit\n");
		printf("Input: ");

		fgets(buf, sizeof(buf), stdin);
		buf[1] = '\0';
		send(s, buf, sizeof(buf), 0);
		main_menu_choise = buf[0];

		switch (main_menu_choise) {
		case '1'://Выбрать
			printf("\nInput necessary product name: ");
			fgets(buf, sizeof(buf), stdin);
			send(s, buf, sizeof(buf), 0);
			recv(s, buf, sizeof(buf), 0);
			printf("\nAuthor: %s\n", buf);
			break;
		default:
			closesocket(s);
			exit(0);
		}
	}
	WSACleanup();
}
