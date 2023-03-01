#pragma once
#include "Connection.h"

namespace aaa
{
	class TCPConnection : public Connection
	{
	public:
		TCPConnection(const char* ip, const int port);
		~TCPConnection() {};
		void Send(const char* buff, int size) const override;
		void Recieve(char* buff, int size) const override;
	};
}