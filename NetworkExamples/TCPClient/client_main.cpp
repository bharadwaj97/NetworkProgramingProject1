// WinSock2 Windows Sockets
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

// Need to link Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#include"C:\Users\nukal\source\repos\Network Programming\Network Programming Lukas\gdp-6016\NetworkExamples\TCPBuffer\Buffer.h"


int main(int argc, char** argv) {
	// Initialization 



	WSADATA wsaData;
	int result;
	//------------------------------------------------ Breakpoint 1

	printf("WSAStartup . . . ");
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		printf("WSAStartup failed with error %d\n", result);
		return 1;
	}
	else {
		printf("Success!\n");
	}

	struct addrinfo* info = nullptr;
	struct addrinfo* ptr = nullptr;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));


	hints.ai_family = AF_INET;			// IPv4 #.#.#.#, AF_INET6 is IPv6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	//------------------------------------------ Breakpoint 2

	// 127.0.0.1 - local

	printf("Creating the AddrInfo . . . ");
	result = getaddrinfo("127.0.0.1", "5555", &hints, &info);
	if (result != 0) {
		printf("Get address info failed with error: %d\n", result);
		WSACleanup();
		return 1;
	}
	else {
		printf("Successful!\n");
	}

	// Create our connection [Socket] 
	SOCKET connectSocket;
	printf("Creating our Connection Socket . . . ");
	connectSocket = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if (connectSocket == INVALID_SOCKET) {
		printf("socket failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(info);
		WSACleanup();
		return 1;
	}
	else {
		printf("Success!\n");
	}
	//----------------------------------------------Breakpoint 3
	// [Connect] to the server
	printf("Connect to the server . . . ");
	result = connect(connectSocket, info->ai_addr, (int)info->ai_addrlen);
	if (result == SOCKET_ERROR) {
		printf("Failed to connect to the server with error: %d\n", WSAGetLastError());
		closesocket(connectSocket);
		freeaddrinfo(info);
		WSACleanup();
		return 1;
	}
	else {
		printf("Successfull!\n");
	}

	// input output control socket
	DWORD NonBlock = 1;
	result = ioctlsocket(connectSocket, FIONBIO, &NonBlock);
	if (result == SOCKET_ERROR) {
		printf("Unable connecting to Server,Failure with Error: %d\n", WSAGetLastError());
		closesocket(connectSocket);
		freeaddrinfo(info);
		WSACleanup();
		return 1;
	}
	else {
		printf("Successfull!\n");
	}


//-------------------------------------------------------------------Breakpoint 4



	// This will wait for the user to press any button to continue
	system("Pause");
	// TODO: read/write send/recv



	const int receivedBufferLength = 1024;
	char receivedBuffer[receivedBufferLength];
	bool tryAgain = true;
	//Telling the User to Intiate Messaging
	string UserMessage;
	string UserName;

	printf("Enter Username :");
	cin >> UserName;                   //scanf(UserName,%s);
	

	do
	{
		printf("Enter Message");
		cin >> UserMessage;

		// Sending the Text Message
		printf("Sending message to the server . . . ");
		result = send(connectSocket, UserMessage.c_str(), UserMessage.size() + 1, 0);
		if (result == SOCKET_ERROR) {
			printf("Failed to deliver the Message (Error Found): %d\n", WSAGetLastError());
			closesocket(connectSocket);
			WSACleanup();
			return 1;
		}
		else {
			printf("Success!\n");
			printf("Sent %d bytes to the server!\n", result);
		}



		while (tryAgain)
		{
			result = recv(connectSocket, receivedBuffer, receivedBufferLength, 0);

			// Expected result values:
			// 0 = closed connection, disconnection
			// >0 = number of bytes received
			// -1 = SOCKET_ERROR


			// NonBlocking recv, it will immediately return
			//		result will be -1 


			if (result == SOCKET_ERROR) {
				if (WSAGetLastError() == WSAEWOULDBLOCK) {
					printf("--\n");
					tryAgain = true;
				}
				else
				{
					printf("Failure in receiving the Message from Server (Error Found): %d\n", WSAGetLastError());
					closesocket(connectSocket);
					WSACleanup();
					return 1;
				}
			}
			else {
				printf("Success!\n");
				printf("Received %d bytes from the server!\n", result);
				tryAgain = false;
			}
		}
	} while (UserMessage.size() > 0);
	// Close

	printf("Shutting down . . . ");
	result = shutdown(connectSocket, SD_SEND);
	if (result == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(connectSocket);
		WSACleanup();
		return 1;
	}
	else {
		printf("Successful!\n");
	}

	printf("Closing . . . \n");
	closesocket(connectSocket);
	WSACleanup();

	return 0;
}
