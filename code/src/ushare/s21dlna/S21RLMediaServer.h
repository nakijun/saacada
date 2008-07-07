#include "IS21RLServer.h"

class S21MediaServerPrivate;
class S21RLDLNAConfigParser;

class S21RLMediaServer
{
public:
	S21RLMediaServer(IS21RLServer& relayServer);
	~S21RLMediaServer(void);
	bool Init(const S21RLDLNAConfigParser& config);
	bool Start(void);
	bool Stop(void);

protected:
	IS21RLServer& m_RLServer;
	S21MediaServerPrivate* m_pPrivate;
};
