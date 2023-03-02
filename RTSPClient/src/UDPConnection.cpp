#include "include/UDPConnection.h"

namespace aaa
{
	UDPConnection::UDPConnection(const char* ip, const int port)
        : Connection(ip, port)
	{
        _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (_sock == INVALID_SOCKET) {
            std::cout << "socket function failed with error: " << WSAGetLastError() << std::endl;
            return;
        }

        int iResult = bind(_sock, (struct sockaddr*)&_service, sizeof(_service));
        if (iResult == SOCKET_ERROR) {
            std::cout << "connect function failed with error: " << WSAGetLastError() << std::endl;
            iResult = closesocket(_sock);
            if (iResult == SOCKET_ERROR)
                std::cout << "closesocket function failed with error: " << WSAGetLastError() << std::endl;
            return;
        }

        _isOpen = true;
	}

    void UDPConnection::Send(const char* buff) const
    {
        //to do
    }

    void UDPConnection::Recieve(char* buff, int size) const
    {
        if (!_isOpen)
            return;

        sockaddr other;
        int otherSize = sizeof(other);

        int iResult = recvfrom(_sock, buff, size, 0, &other, &otherSize);
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