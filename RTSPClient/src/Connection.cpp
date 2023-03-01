#include "include/Connection.h"

namespace aaa
{
    Connection::Connection(const char* ip, const int port) :
        _isOpen(false),
        _service()
    {
        _service.sin_family = AF_INET;
        _service.sin_addr.s_addr = inet_addr(ip);
        _service.sin_port = htons(port);
    }

    Connection::~Connection()
    {
        Close();
    }

    bool Connection::Close()
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