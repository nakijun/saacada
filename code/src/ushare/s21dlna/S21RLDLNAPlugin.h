#ifndef _S21RL_DLNA_PLUGIN_H
#define _S21RL_DLNA_PLUGIN_H

#include "IS21RLPlugin.h"

class S21RLDLNAPluginPrivate;

class S21RLDLNAPlugin : public IS21RLPlugin
{
public:
	S21RLDLNAPlugin();

	virtual ~S21RLDLNAPlugin();

	virtual const char* GetVersion();

	virtual bool Init(IS21RLServer& relayServer, const char* configInfo = "");

	virtual bool Start();

	virtual bool Stop();

private: // redefined virtual functions
	S21RLDLNAPluginPrivate* m_pPrivate;
};

#endif
