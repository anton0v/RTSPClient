#include "include/UDPConnection.h"

namespace aaa
{
	UDPConnection::UDPConnection(const std::string& ip, const int port) :
        _isOpen(false)
	{
        _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (_sock == INVALID_SOCKET) {
            wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
            return;
        }

        _service.sin_family = AF_INET;
        _service.sin_addr.s_addr = inet_addr(ip.c_str());
        _service.sin_port = htons(port);

        int iResult = connect(_sock, (SOCKADDR*)&_service, sizeof(_service));
        if (iResult == SOCKET_ERROR) {
            wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
            iResult = closesocket(_sock);
            if (iResult == SOCKET_ERROR)
                wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
            return;
        }

        _isOpen = true;
	}

    UDPConnection::~UDPConnection()
    {
        Close();
    }

    char* UDPConnection::Recieve() const
    {
        if (!_isOpen)
            return nullptr;

        char* recvbuf = new char[MAX_BUFF_SIZE] {'\0'};

        int iResult = recv(_sock, recvbuf, MAX_BUFF_SIZE, 0);
        if (iResult > 0)
        {
            wprintf(L"Bytes received: %d\n", iResult);
        }
        else if (iResult == 0)
            wprintf(L"Connection closed\n");
        else
            wprintf(L"recv failed with error: %d\n", WSAGetLastError());

        return recvbuf;
    }

    bool UDPConnection::Close()
    {
        if (!_isOpen)
            return false;
        int iResult = closesocket(_sock);
        if (iResult == SOCKET_ERROR) {
            wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
            return false;
        }
        _isOpen = false;
        return true;
    }
}