#include "include/UDPConnection.h"

namespace aaa
{
	UDPConnection::UDPConnection(const std::string& ip, const int port) :
        _isOpen(false)
	{
        _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (_sock == INVALID_SOCKET) {
            std::cout << "socket function failed with error: " << WSAGetLastError() << std::endl;
            return;
        }

        _service.sin_family = AF_INET;
        _service.sin_addr.s_addr = inet_addr(ip.c_str());
        _service.sin_port = htons(port);

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

    UDPConnection::~UDPConnection()
    {
        Close();
    }

    std::string UDPConnection::Recieve() const
    {
        if (!_isOpen)
            return std::string();

        char recvbuf[MAX_BUFF_SIZE] {'\0'};

        sockaddr other;
        int otherSize = sizeof(other);

        int iResult = recvfrom(_sock, recvbuf, MAX_BUFF_SIZE, 0, &other, &otherSize);
        if (iResult > 0)
        {
            std::cout << "Bytes received: " << iResult << std::endl;
        }
        else if (iResult == 0)
            std::cout << "Connection closed\n" << std::endl;
        else
            std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;

        return std::string(recvbuf);
    }

    bool UDPConnection::Close()
    {
        if (!_isOpen)
            return false;
        int iResult = closesocket(_sock);
        if (iResult == SOCKET_ERROR) {
            std::cout << "closesocket function failed with error: " << WSAGetLastError() << std::endl;
            return false;
        }
        _isOpen = false;
        return true;
    }
}