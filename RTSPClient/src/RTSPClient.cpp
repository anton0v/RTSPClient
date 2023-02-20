#include <iostream>
#include <WinSock2.h>
#include "include/TCPConnection.h"

#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_PORT 554

int main()
{
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup function failed with error: %d\n", iResult);
        return 1;
    }

    aaa::TCPConnection conn("127.0.0.1", DEFAULT_PORT);

    char* answer;

    answer = conn.Send("OPTIONS rtsp://127.0.0.1/live/jpeg RTSP/1.0\r\nCSeq: 1\r\nUser-Agent: Agent 007");

    WSACleanup();

    return 0;
}

//SOCKET ConnectSocket;
//ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//if (ConnectSocket == INVALID_SOCKET) {
//    wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
//    WSACleanup();
//    return 1;
//}
//
//sockaddr_in clientService;
//clientService.sin_family = AF_INET;
//clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
//clientService.sin_port = htons(DEFAULT_PORT);
//
//iResult = connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
//if (iResult == SOCKET_ERROR) {
//    wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
//    iResult = closesocket(ConnectSocket);
//    if (iResult == SOCKET_ERROR)
//        wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
//    WSACleanup();
//    return 1;
//}
//
//wprintf(L"Connected to server.\n");
//
////char sendbuf[] = "OPTIONS rtsp://127.0.0.1/live/jpeg RTSP/1.0\r\nCSeq: 1\r\nUser-Agent: Agent 007";
//char sendbuf[] = "DESCRIBE rtsp://127.0.0.1:554/live RTSP/1.0\r\nCSeq: 1\r\nAccept: application/sdp\r\nUser-Agent: Agent 007";
//char recvbuf[DEFAULT_BUFLEN] = "";
//
//iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
//if (iResult == SOCKET_ERROR) {
//    wprintf(L"send failed with error: %d\n", WSAGetLastError());
//    closesocket(ConnectSocket);
//    WSACleanup();
//    return 1;
//}
//
//iResult = shutdown(ConnectSocket, SD_SEND);
//if (iResult == SOCKET_ERROR) {
//    wprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
//    closesocket(ConnectSocket);
//    WSACleanup();
//    return 1;
//}
//
//do {
//
//    iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);
//    if (iResult > 0)
//    {
//        wprintf(L"Bytes received: %d\n", iResult);
//        printf("Message:\n%s\n", recvbuf);
//    }
//    else if (iResult == 0)
//        wprintf(L"Connection closed\n");
//    else
//        wprintf(L"recv failed with error: %d\n", WSAGetLastError());
//
//} while (iResult > 0);
//
//iResult = closesocket(ConnectSocket);
//if (iResult == SOCKET_ERROR) {
//    wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
//    WSACleanup();
//    return 1;
//}
