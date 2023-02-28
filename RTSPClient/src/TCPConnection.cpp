#include "include/TCPConnection.h"

namespace aaa
{
	TCPConnection::TCPConnection(const std::string &ip, const int port)
	{
        _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (_sock == INVALID_SOCKET) {
            std::cout << "socket function failed with error: " << WSAGetLastError() << std::endl;
            return;
        }

        _service.sin_family = AF_INET;
        _service.sin_addr.s_addr = inet_addr(ip.c_str());
        _service.sin_port = htons(port);

        int iResult = connect(_sock, (SOCKADDR*)&_service, sizeof(_service));
        if (iResult == SOCKET_ERROR) {
            _isConnected = false;
            std::cout << "connect function failed with error: " << WSAGetLastError() << std::endl;
            iResult = closesocket(_sock);
            if (iResult == SOCKET_ERROR)
                std::cout << "closesocket function failed with error: " << WSAGetLastError() << std::endl;
            return;
        }

        _isConnected = true;
	}

	TCPConnection::~TCPConnection()
	{
        Close();
	}

    std::string TCPConnection::Send(const char* buff) const
	{
        if (!_isConnected)
            return std::string();

        int iResult = send(_sock, buff, (int)strlen(buff), 0);
        if (iResult == SOCKET_ERROR) {
            std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
            closesocket(_sock);
        }

        char recvbuf[MAX_BUFF_SIZE]{'\0'};

        iResult = recv(_sock, recvbuf, MAX_BUFF_SIZE, 0);
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

    bool TCPConnection::Close()
    {
        if (!_isConnected)
            return false;
        int iResult = closesocket(_sock);
        if (iResult == SOCKET_ERROR) {
            std::cout << "closesocket function failed with error: " << WSAGetLastError() << std::endl;
            return false;
        }
        _isConnected = false;
        return true;
    }
}