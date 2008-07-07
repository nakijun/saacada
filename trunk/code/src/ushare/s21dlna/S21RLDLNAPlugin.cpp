#include "common/S21System.h"
#include "S21RLError.h"
#include "S21RLDLNAPlugin.h"
#include "S21RLMediaServer.h"
#include "S21RLDLNAConfigParser.h"
#include <Poco/ClassLibrary.h>
#include "common/MemLeakFinder/MemLeakFinder.h"

DEFINE_PLUGIN_VERSION(S21RLDLNAPlugin)

POCO_BEGIN_MANIFEST(IS21RLPlugin)
POCO_EXPORT_SINGLETON(S21RLDLNAPlugin)
POCO_END_MANIFEST

class S21RLDLNAPluginPrivate
{
public:
	std::string m_ConfigFile;

	S21RLDLNAPluginPrivate()
	{
	}
	~S21RLDLNAPluginPrivate()
	{
		delete m_pMediaServer;
	}

	bool Init(IS21RLServer& relayServer, const char* configInfo = "")
	{
		m_pRelayServer = &relayServer;
		m_pMediaServer = new S21RLMediaServer(relayServer);
		//TODO: process configInfo and relayServer
		if (!m_pMediaServer)
		{
			//TODO: error log
			return false;
		}

		if(m_Parser.Parse(configInfo))
		{
			return m_pMediaServer->Init(m_Parser);
		}
		else
			return false;
	}

	bool Start()
	{
		const S21RLDLNAConfigParser::ChannelList& channelList = m_Parser.GetChannelList();
		S21RLDLNAConfigParser::ChannelList::const_iterator it;

		for (it = channelList.begin(); it != channelList.end(); it++)
		{
			const char* pURI = it->m_Source.c_str();
			const char* pName = it->m_Name.c_str();
			const char* pCastingURI = it->m_CastingURI.empty() ? NULL : it->m_CastingURI.c_str();
			const char* pServingAddress = it->m_ServingAddress.empty() ? NULL : it->m_ServingAddress.c_str();
			const char* pArchivingURI = it->m_Archive.empty() ? NULL : it->m_Archive.c_str();

			m_pRelayServer->GetChannelMgr().AddChannel(pURI,
				pName,
				pCastingURI,
				pServingAddress,
				pArchivingURI);
		}

		return m_pMediaServer->Start();
	}

	bool Stop()
	{
		return m_pMediaServer->Stop();
	}

protected:
	S21RLMediaServer* m_pMediaServer;
	IS21RLServer* m_pRelayServer;
	S21RLDLNAConfigParser m_Parser;
};

S21RLDLNAPlugin::S21RLDLNAPlugin() : m_pPrivate(new S21RLDLNAPluginPrivate)
{
}

bool S21RLDLNAPlugin::Init(IS21RLServer& relayServer, const char* configInfo)
{
	m_pPrivate->m_ConfigFile = configInfo;
	return m_pPrivate->Init(relayServer, configInfo);
}

bool S21RLDLNAPlugin::Start()
{
	return m_pPrivate->Start();
}

bool S21RLDLNAPlugin::Stop()
{
	return m_pPrivate->Stop();
}

S21RLDLNAPlugin::~S21RLDLNAPlugin()
{
	delete m_pPrivate;
}

