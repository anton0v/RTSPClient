#pragma once
#include <string>
#include <WinSock2.h>

#define MAX_BUFF_SIZE 500

namespace aaa
{
	class TCPConnection
	{
	public:
		TCPConnection(const std::string &ip, const int port);
		~TCPConnection();
		bool IsConnected() const { return _isConnected; }
		char* Send(const char* buff) const;
		bool Close();
	private:
		SOCKET _sock;
		sockaddr_in _service;
		bool _isConnected;
	};
}