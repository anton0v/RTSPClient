#pragma once
#include <string>
#include <WinSock2.h>

#define MAX_BUFF_SIZE 500

namespace aaa
{
	class TCPConnection
	{
	public:
		TCPConnection(const std::string ip, const int port);
		~TCPConnection();
		char* Send(const char* buff) const;
	private:
		SOCKET _sock;
		sockaddr_in _service;
	};
}