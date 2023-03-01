#include "include/TCPConnection.h"

namespace aaa
{
	TCPConnection::TCPConnection(const char* ip, const int port)
        : Connection(ip, port)
	{
        _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (_sock == INVALID_SOCKET) {
            std::cout << "socket function failed with error: " << WSAGetLastError() << std::endl;
            return;
        }

        int iResult = connect(_sock, (SOCKADDR*)&_service, sizeof(_service));
        if (iResult == SOCKET_ERROR) {
            _isOpen = false;
            std::cout << "connect function failed with error: " << WSAGetLastError() << std::endl;
            iResult = closesocket(_sock);
            if (iResult == SOCKET_ERROR)
                std::cout << "closesocket function failed with error: " << WSAGetLastError() << std::endl;
            return;
        }

        _isOpen = true;
	}

    void TCPConnection::Send(const char* buff, int size) const
	{
        if (!_isOpen)
            return;

        int iResult = send(_sock, buff, size, 0);
        if (iResult == SOCKET_ERROR) {
            std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
            closesocket(_sock);
        }
	}

    void TCPConnection::Recieve(char* buff, int size) const
    {
        if (!_isOpen)
            return;

        int iResult = recv(_sock, buff, size, 0);
        if (iResult > 0)
        {
            std::cout << "Bytes received: " << iResult << std::endl;
        }
        else if (iResult == 0)
            std::cout << "Connection closed\n" << std::endl;
        else
            std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
    }
}