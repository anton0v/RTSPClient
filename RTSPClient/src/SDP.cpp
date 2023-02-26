#include "include/SDP.h"

namespace aaa
{
	MediaInfo ParseMedia(const std::string& s)
	{
		int portBegin = s.find(' ') + 1;
		int portEnd = s.find(' ', portBegin + 1);
		return MediaInfo(
			s.substr(2, s.find(' ') - 2),
			atoi(s.substr(portBegin, portEnd).c_str()),
			(FORMAT)atoi(s.substr(s.rfind(' ')).c_str())
		);
	}

	SDP::SDP(std::string& in)
	{
		std::regex reg(PATTERN);
		auto begin = std::sregex_iterator(in.begin(), in.end(), reg);
		auto end = std::sregex_iterator();
		bool isMedia = false;
		MediaInfo* currentMedia;

		for(std::sregex_iterator it = begin; it != end; it++)
		{
			std::smatch match = *it;
			std::string sMatch = match.str();
			switch (sMatch[0])
			{
			case 'v':
				_version = atoi(sMatch.c_str() + 2);
				break;
			case 'o':
				_id.assign(sMatch);
				break;
			case 's':
				_name.assign(sMatch);
				break;
			case 'm':
				isMedia = true;
				_media.push_back(ParseMedia(sMatch));
				break;
			case 'a':
				if (!isMedia)
					continue;
				_media.back().attributes.push_back(sMatch);
				break;
			default:
				break;
			}
		}
	}
}