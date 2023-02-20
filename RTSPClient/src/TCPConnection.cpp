#include "include/TCPConnection.h"

namespace aaa
{
	TCPConnection::TCPConnection(const std::string ip, const int port)
	{
        _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (_sock == INVALID_SOCKET) {
            wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        }

        sockaddr_in clientService;
        _service.sin_family = AF_INET;
        _service.sin_addr.s_addr = inet_addr(ip.c_str());
        _service.sin_port = htons(port);

        int iResult = connect(_sock, (SOCKADDR*)&_service, sizeof(_service));
        if (iResult == SOCKET_ERROR) {
            wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
            iResult = closesocket(_sock);
            if (iResult == SOCKET_ERROR)
                wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        }
	}

	TCPConnection::~TCPConnection()
	{
        int iResult = closesocket(_sock);
        if (iResult == SOCKET_ERROR) {
            wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        }
	}

	char* TCPConnection::Send(const char* buff) const
	{
        int iResult = send(_sock, buff, (int)strlen(buff), 0);
        if (iResult == SOCKET_ERROR) {
            wprintf(L"send failed with error: %d\n", WSAGetLastError());
            closesocket(_sock);
        }

        iResult = shutdown(_sock, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            wprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(_sock);
        }

        char* recvbuf = new char[MAX_BUFF_SIZE];

        do {

            iResult = recv(_sock, recvbuf, MAX_BUFF_SIZE, 0);
            if (iResult > 0)
            {
                wprintf(L"Bytes received: %d\n", iResult);
                printf("Message:\n%s\n", recvbuf);
            }
            else if (iResult == 0)
                wprintf(L"Connection closed\n");
            else
                wprintf(L"recv failed with error: %d\n", WSAGetLastError());

        } while (iResult > 0);

		return recvbuf;
	}
}