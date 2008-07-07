#ifndef _S21RL_DLNA_CONFIG_PARSER_H
#define _S21RL_DLNA_CONFIG_PARSER_H

#include <string>
#include <list>

using std::string;
using std::list;

class S21RLDLNAConfigParser
{
public:
	struct Channel
	{
		string m_Name;
		string m_Source;
		string m_Archive;
		string m_CastingURI;
		string m_ServingAddress;
	};

	typedef list<Channel> ChannelList;

	enum Protocol
	{
		RTSP,
		HTTP
	};

	struct Directory
	{
		string m_Name;
		string m_Path;
		Protocol m_Protocol;
	};

	typedef list<Directory> DirectoryList;

	bool Parse(const char* configFilePath);

	const ChannelList& GetChannelList() const { return m_ChannelList; }
	const DirectoryList& GetDirectoryList() const { return m_DirectoryList; }

protected:
	ChannelList m_ChannelList;
	DirectoryList m_DirectoryList;
};

#endif //_S21RL_DLNA_CONFIG_PARSER_H
