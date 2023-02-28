#include <iostream>
#include <WinSock2.h>
#include "include/TCPConnection.h"
#include "include/UDPConnection.h"
#include "include/SDP.h"

#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")

#define RTSP_PORT 554
#define RTP_PORT 1124

int main()
{
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup function failed with error: %d\n", iResult);
        return 1;
    }

    aaa::TCPConnection conn("127.0.0.1", RTSP_PORT);

    std::string answer;

    answer = conn.Send("DESCRIBE rtsp://127.0.0.1/live RTSP/1.0\r\nCSeq: 1\r\nAccept: application/sdp\r\nUser-Agent: Agent 007\r\n");
    
    if (answer.empty())
    {
        WSACleanup();
        return 1;
    }

    std::cout << "Message:\n" << answer << std::endl;

    std::string sdpString(answer);

    aaa::SDP sdp(sdpString);

    const std::vector<aaa::MediaInfo>& info = sdp.GetMedia();

    for (int i = 0; i < info.size(); i++)
    {
        printf("Name:%s\r\nPort:%d\r\n", info[i].name.c_str(), info[i].port);
    }

    answer = conn.Send("SETUP rtsp://127.0.0.1/live/track0 RTSP/1.0\r\n"
        "CSeq: 2\r\n"
        "Transport: RTP/AVP;unicast;client_port=1124-1125\r\n"
        "User-Agent: Agent 007\r\n");

    if (answer.empty())
    {
        WSACleanup();
        return 1;
    }

    std::cout << "Message:\n" << answer << std::endl;

    std::string session = answer.substr(answer.find("Session"));
    session.erase(session.find('\r\n') + 1);
    answer.assign("PLAY rtsp://127.0.0.1/live/track0 RTSP/1.0\r\n"
        "CSeq: 3\r\n");
    answer.append(session);
    answer.append("Range: npt = 0.000 -\r\n"
        "User-Agent: Agent 007\r\n");

    answer = conn.Send(answer.c_str());

    if (answer.empty())
    {
        WSACleanup();
        return 1;
    }

    std::cout << "Message:\n" << answer << std::endl;

    aaa::UDPConnection mediaData("127.0.0.1", info[0].port == 0 ? RTP_PORT : info[0].port);

    char* buff = new char[500];
    buff = mediaData.Recieve();

    if (buff == nullptr)
    {
        WSACleanup();
        return 1;
    }

    std::cout << "Data:\n[" << buff << "]\n";

    answer = conn.Send("TEARDOWN rtsp://127.0.0.1/live RTSP/1.0\r\n"
        "CSeq: 4\r\n"
        "Session: 1\r\n"
        "User-Agent: Agent 007\r\n");

    if (answer.empty())
    {
        WSACleanup();
        return 1;
    }

    std::cout << "Message:\n" << answer << std::endl;

    conn.Close();
    mediaData.Close();

    WSACleanup();
    return 0;
}

