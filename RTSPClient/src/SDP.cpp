#include "include/SDP.h"

namespace aaa
{
	SDP::SDP(std::string& in)
	{
		std::regex reg(PATTERN);
		auto begin = std::sregex_iterator(in.begin(), in.end(), reg);
		auto end = std::sregex_iterator();

		for(std::sregex_iterator it = begin; it != end; it++)
		{
			std::smatch match = *it;
			switch (match.str()[0])
			{
			}
		}
	}
}