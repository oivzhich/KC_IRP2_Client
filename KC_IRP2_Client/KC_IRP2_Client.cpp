// KC_IRP2_Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment(lib, "ws2_32.lib") 
#include<WinSock2.h>
#include<iostream>
#include<stdlib.h>
#include <string>
#pragma warning(disable: 4996)

using namespace std;

void getServerResponse(const SOCKET& server_socket, const string& message) {
	char buf[500];
	memset(&buf[0], 0, sizeof(buf));
	recv(server_socket, buf, sizeof(buf), 0);
	string result = buf;
	cout << message << endl << result << endl;
}

void sendUserInput(const SOCKET& server_socket, const string& message) {
	char buf[256];
	memset(&buf[0], 0, sizeof(buf));
	cout << message << endl;
	fgets(buf, sizeof(buf), stdin);
	send(server_socket, buf, sizeof(buf), 0);
}
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
		puts("4 - Delete book by index");
		puts("5 - Exit\n");
		printf("Input: ");

		memset(&buf[0], 0, sizeof(buf));
		fgets(buf, sizeof(buf), stdin);
		send(server_socket, buf, sizeof(buf), 0);
		main_menu_choise = buf[0];

		switch (main_menu_choise) {
		case '1'://поиск книги по автору
			sendUserInput(server_socket, "Enter author name: ");
			getServerResponse(server_socket, "Books of author: ");
			break;
		case '2'://просмотреть все книги
			//получаем список всех книг
			getServerResponse(server_socket, "All books: ");
			break;
		case '3'://добавить запись
			sendUserInput(server_socket, "Enter registration number:");
			sendUserInput(server_socket, "Enter author:");
			sendUserInput(server_socket, "Enter book name:");
			sendUserInput(server_socket, "Enter year pushlished:");
			sendUserInput(server_socket, "Enter number of pages:");

			getServerResponse(server_socket, "Result of adding");
			break;
		case '4'://удалить запись
			sendUserInput(server_socket, "Enter book index to delete:");
			getServerResponse(server_socket, "Result of deletion:");
			break;
		default:
			closesocket(server_socket);
			exit(0);
		}
	}
	WSACleanup();
}
