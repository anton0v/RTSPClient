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
		const int& GetVersion() const { return _version; }
		const std::string& GetId() const { return _id; }
		const std::string& GetName() const { return _name; }
		const std::vector<MediaInfo> GetMedia() const { return _media; }
	private:
		int _version;
		std::string _id;
		std::string _name;
		std::string _title;
		std::string _uri;
		std::string _connection;
		std::vector<MediaInfo> _media;
	};
}