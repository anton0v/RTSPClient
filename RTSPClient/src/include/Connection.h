#pragma once
#include <WinSock2.h>
#include <iostream>

namespace aaa
{
	class Connection
	{
	public:
		Connection(const char* ip, const int port);
		~Connection();
		bool IsOpen() const { return _isOpen; }
		virtual void Send(const char* buff) const = 0;
		virtual void Recieve(char* buff, int size) const = 0;
		bool Close();
	protected:
		SOCKET _sock;
		sockaddr_in _service;
		bool _isOpen;
	};
}