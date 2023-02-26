#include <iostream>
#include <WinSock2.h>
#include "include/TCPConnection.h"
#include "include/SDP.h"

#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_PORT 554

int main()
{
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup function failed with error: %d\n", iResult);
        return 1;
    }

    aaa::TCPConnection conn("127.0.0.1", DEFAULT_PORT);

    char* answer;

    answer = conn.Send("DESCRIBE rtsp://127.0.0.1/live RTSP/1.0\r\nCSeq: 1\r\nAccept: application/sdp\r\nUser-Agent: Agent 007\r\n");
    
    if (answer != nullptr)
    {
        printf("Message:\n%s\n", answer);

        std::string sdpString(answer);

        aaa::SDP sdp(sdpString);

        const std::vector<aaa::MediaInfo>& info = sdp.GetMedia();

        for (int i = 0; i < info.size(); i++)
        {
            printf("Name:%s\r\nPort:%d\r\n", info[i].name.c_str(), info[i].port);
        }
    }

    conn.Close();

    WSACleanup();

    delete[] answer;
    return 0;
}

