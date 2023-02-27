#pragma once
#include <string>
#include <WinSock2.h>

#define MAX_BUFF_SIZE 500

namespace aaa
{
	class UDPConnection
	{
	public:
		UDPConnection(const std::string& ip, const int port);
		~UDPConnection();
		bool IsOpen() const { return _isOpen; }
		char* Recieve() const;
		bool Close();
	private:
		SOCKET _sock;
		sockaddr_in _service;
		bool _isOpen;
	};
}