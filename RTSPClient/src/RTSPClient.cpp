#include <iostream>
#include <WinSock2.h>
#include <atomic>
#include <thread>
#include "include/Connection.h"
#include "include/TCPConnection.h"
#include "include/UDPConnection.h"
#include "include/SDP.h"

#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")

#define BUFF_SIZE 5000

#define RTSP_PORT 554
#define RTP_PORT 1124

std::atomic<bool> exitFlag(false);

void simpleRTP(int port)
{
    aaa::UDPConnection mediaData("127.0.0.1", port == 0 ? RTP_PORT : port);

    char buff[BUFF_SIZE]{ '\0' };

    do
    {
        memset(buff, '\0', BUFF_SIZE);
        mediaData.Recieve(buff, BUFF_SIZE);
    } while (!exitFlag);

    mediaData.Close();
}

void simpleRTCP()
{

}

int main()
{
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup function failed with error: %d\n", iResult);
        return 1;
    }

    char buff[BUFF_SIZE] {'\0'};

    aaa::TCPConnection conn("127.0.0.1", RTSP_PORT);

    std::string answer;

    conn.Send("DESCRIBE rtsp://127.0.0.1/live RTSP/1.0\r\n"
        "CSeq: 1\r\n"
        "Accept: application/sdp\r\n"
        "User-Agent: Agent 007\r\n");

    conn.Recieve(buff, BUFF_SIZE);
    answer.assign(buff);
    
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

    conn.Send("SETUP rtsp://127.0.0.1/live/track0 RTSP/1.0\r\n"
        "CSeq: 2\r\n"
        "Transport: RTP/AVP;unicast;client_port=1124-1125\r\n");

    memset(buff, '\0', BUFF_SIZE);
    conn.Recieve(buff, BUFF_SIZE);
    answer.assign(buff);

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

    conn.Send(answer.c_str());

    memset(buff, '\0', BUFF_SIZE);
    conn.Recieve(buff, BUFF_SIZE);
    answer.assign(buff);

    if (answer.empty())
    {
        WSACleanup();
        return 1;
    }

    std::cout << "Message:\n" << answer << std::endl;

    std::thread RTP(simpleRTP, info[0].port);

    int a;

    std::cin >> a;

    exitFlag = true;

    RTP.join();

    conn.Send("TEARDOWN rtsp://127.0.0.1/live RTSP/1.0\r\n"
        "CSeq: 4\r\n"
        "Session: 1\r\n"
        "User-Agent: Agent 007\r\n");

    memset(buff, '\0', BUFF_SIZE);
    conn.Recieve(buff, BUFF_SIZE);
    answer.assign(buff);

    if (answer.empty())
    {
        WSACleanup();
        return 1;
    }

    std::cout << "Message:\n" << answer << std::endl;

    conn.Close();

    WSACleanup();
    return 0;
}

