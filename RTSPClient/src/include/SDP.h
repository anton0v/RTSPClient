#pragma once
#include <string>
#include <vector>
#include <regex>

#define PATTERN ".*=.*\r\n"

namespace aaa
{
	enum FORMAT
	{
		MJPEG = 26,
		H264 = 96
	};

	typedef struct MediaInfo
	{
		std::string name;
		int port;
		FORMAT format;
		std::vector<std::string> attributes;
	} MediaInfo;

	class SDP
	{
	public:
		SDP(std::string &in);
		~SDP() {};
	private:
		int version;
		int id;
		std::string name;
		std::string title;
		std::string uri;
		std::string connection;
		std::vector<MediaInfo> media;
	};
}