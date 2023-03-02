#pragma once
#include "Connection.h"

namespace aaa
{
	class UDPConnection : public Connection
	{
	public:
		UDPConnection(const char* ip, const int port);
		~UDPConnection() {};
		void Send(const char* buff) const override;
		void Recieve(char* buff, int size) const override;
	};
}