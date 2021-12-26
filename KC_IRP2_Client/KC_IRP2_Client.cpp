// KC_IRP2_Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment(lib, "ws2_32.lib") 
#include<WinSock2.h>
#include<iostream>
#include<stdlib.h>
#include <string>
#pragma warning(disable: 4996)

using namespace std;

void main() {
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return; }

	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
	// указание адреса и порта сервера
	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(1280);
	dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(server_socket, (sockaddr*)&dest_addr, sizeof(dest_addr));

	while (true) {
		char buf[500],
			main_menu_choise,
			switch_menu_choise;
		string result;

		//Выбор пункта меню и отправка его серверу
		puts("\nChoose:\n");
		puts("1 - Search books by author");
		puts("2 - View all");
		puts("3 - Edit");
		puts("4 - Add");
		puts("5 - Exit\n");
		printf("Input: ");

		memset(&buf[0], 0, sizeof(buf));
		fgets(buf, sizeof(buf), stdin);
		buf[1] = '\0';
		send(server_socket, buf, sizeof(buf), 0);
		main_menu_choise = buf[0];

		switch (main_menu_choise) {
		case '1'://поиск книги по автору
			memset(&buf[0], 0, sizeof(buf));
			printf("\nEnter author name: ");
			fgets(buf, sizeof(buf), stdin);
			send(server_socket, buf, sizeof(buf), 0);
			memset(&buf[0], 0, sizeof(buf));
			recv(server_socket, buf, sizeof(buf), 0);
			result = buf;
			result.pop_back();
			cout << "Books of author: " << endl << result << endl;
			break;
		case '2'://просмотреть все книги
			memset(&buf[0], 0, sizeof(buf));
			//получаем список всех книг
			recv(server_socket, buf, sizeof(buf), 0);
			result = buf;
			result.pop_back();
			cout << "All books:" << endl << result << endl;
			break;
		default:
			closesocket(server_socket);
			exit(0);
		}
	}
	WSACleanup();
}
