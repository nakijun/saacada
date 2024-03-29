/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**********/
// "liveMedia"
// Copyright (c) 1996-2007 Live Networks, Inc.  All rights reserved.
// A RTSP server
// C++ header

#ifndef _RTSP_SERVER_HH
#define _RTSP_SERVER_HH

#ifndef _SERVER_MEDIA_SESSION_HH
#include "ServerMediaSession.hh"
#endif
#ifndef _NET_ADDRESS_HH
#include <NetAddress.hh>
#endif
#ifndef _DIGEST_AUTHENTICATION_HH
#include "DigestAuthentication.hh"
#endif

#include <string>

// A data structure used for optional user/password authentication:

class UserAuthenticationDatabase {
public:
  UserAuthenticationDatabase(char const* realm = NULL,
			     Boolean passwordsAreMD5 = False);
    // If "passwordsAreMD5" is True, then each password stored into, or removed from,
    // the database is actually the value computed
    // by md5(<username>:<realm>:<actual-password>)
  virtual ~UserAuthenticationDatabase();

  virtual void addUserRecord(char const* username, char const* password);
  virtual void removeUserRecord(char const* username);

  virtual char const* lookupPassword(char const* username);
      // returns NULL if the user name was not present

  char const* realm() { return fRealm; }
  Boolean passwordsAreMD5() { return fPasswordsAreMD5; }

protected:
  HashTable* fTable;
  char* fRealm;
  Boolean fPasswordsAreMD5;
};

#define RTSP_BUFFER_SIZE 10000 // for incoming requests, and outgoing responses

class RTSPServer: public Medium {
public:
  class RTSPClientSession;

  class IRTSPClientSessionObserver
  {
  public:
	virtual ~IRTSPClientSessionObserver() {}

	virtual void clientSessionEnded(RTSPClientSession* clientSession) = 0;
	virtual void requestHandled(RTSPClientSession* clientSession, int statusCode) = 0;
  };

  // The state of each individual session handled by a RTSP server:
  class RTSPClientSession {
  public:
    RTSPClientSession(RTSPServer& ourServer, unsigned sessionId,
		      int clientSocket, struct sockaddr_in clientAddr, bool isAttached = false, IRTSPClientSessionObserver* observer = NULL);
    virtual ~RTSPClientSession();

	bool handleRequest(char* request);
	void closeClientSession();

  private:
    void incomingRequestHandler1();
    UsageEnvironment& envir() { return fOurServer.envir(); }
    void reclaimStreamStates();
    void resetRequestBuffer();
    static void incomingRequestHandler(void*, int /*mask*/);
    bool handleRequest();
    void handleCmd_bad(char const* cseq);
    void handleCmd_notSupported(char const* cseq);
    void handleCmd_notFound(char const* cseq);
    void handleCmd_unsupportedTransport(char const* cseq);
    void handleCmd_OPTIONS(char const* cseq);
    void handleCmd_DESCRIBE(char const* cseq, char const* urlSuffix,
			 char const* fullRequestStr);
    void handleCmd_SETUP(char const* cseq,
			 char const* urlPreSuffix, char const* urlSuffix,
			 char const* fullRequestStr);
    void handleCmd_withinSession(char const* cmdName,
				 char const* urlPreSuffix, char const* urlSuffix,
				 char const* cseq, char const* fullRequestStr);
    void handleCmd_TEARDOWN(ServerMediaSubsession* subsession,
			    char const* cseq);
    void handleCmd_PLAY(ServerMediaSubsession* subsession,
			char const* cseq, char const* fullRequestStr);
    void handleCmd_PAUSE(ServerMediaSubsession* subsession,
			 char const* cseq);
    void handleCmd_GET_PARAMETER(ServerMediaSubsession* subsession,
				 char const* cseq, char const* fullRequestStr);
    Boolean authenticationOK(char const* cmdName, char const* cseq,
                             char const* urlSuffix,
                             char const* fullRequestStr);
    void noteLiveness();
    Boolean isMulticast() const { return fIsMulticast; }
    static void noteClientLiveness(RTSPClientSession* clientSession);
    static void livenessTimeoutTask(RTSPClientSession* clientSession);
    static void handleRequestTask(RTSPClientSession* clientSession);
    static void closeClientSessionTask(RTSPClientSession* clientSession);

  private:
    RTSPServer& fOurServer;
	bool fIsAttached;
	IRTSPClientSessionObserver* fObserver;
    unsigned fOurSessionId;
    ServerMediaSession* fOurServerMediaSession;
    int fClientSocket;
    struct sockaddr_in fClientAddr;
    TaskToken fHandleRequestTask;
	TaskToken fCloseClientSessionTask;
    TaskToken fLivenessCheckTask;
    unsigned char fRequestBuffer[RTSP_BUFFER_SIZE];
    unsigned fRequestBytesAlreadySeen, fRequestBufferBytesLeft;
    unsigned char* fLastCRLF;
    unsigned char fResponseBuffer[RTSP_BUFFER_SIZE];
    Boolean fIsMulticast, fSessionIsActive, fStreamAfterSETUP;
    Authenticator fCurrentAuthenticator; // used if access control is needed
    unsigned char fTCPStreamIdCount; // used for (optional) RTP/TCP
    unsigned fNumStreamStates; 
    struct streamState {
      ServerMediaSubsession* subsession;
      void* streamToken;
    } * fStreamStates;
  };

public:
  static RTSPServer* createNew(UsageEnvironment& env, Port ourPort = 554,
			       UserAuthenticationDatabase* authDatabase = NULL,
			       unsigned reclamationTestSeconds = 45);
      // If ourPort.num() == 0, we'll choose the port number
      // Note: The caller is responsible for reclaiming "authDatabase"
      // If "reclamationTestSeconds" > 0, then the "RTSPClientSession" state for
      //     each client will get reclaimed (and the corresponding RTP stream(s)
      //     torn down) if no RTSP commands - or RTCP "RR" packets - from the
      //     client are received in at least "reclamationTestSeconds" seconds.

  static Boolean lookupByName(UsageEnvironment& env, char const* name,
			      RTSPServer*& resultServer);

  void addServerMediaSession(ServerMediaSession* serverMediaSession);
  virtual ServerMediaSession* lookupServerMediaSession(char const* streamName);
  void removeServerMediaSession(ServerMediaSession* serverMediaSession);
  void removeServerMediaSession(char const* streamName);

  char* rtspURL(ServerMediaSession const* serverMediaSession, int clientSocket = -1) const;
      // returns a "rtsp://" URL that could be used to access the
      // specified session (which must already have been added to
      // us using "addServerMediaSession()".
      // This string is dynamically allocated; caller should delete[]
      // (If "clientSocket" is non-negative, then it is used (by calling "getsockname()") to determine
      //  the IP address to be used in the URL.)
  char* rtspURLPrefix(int clientSocket = -1) const;
      // like "rtspURL()", except that it returns just the common prefix used by
      // each session's "rtsp://" URL.
      // This string is dynamically allocated; caller should delete[]

protected:
  RTSPServer(UsageEnvironment& env,
	     int ourSocket, Port ourPort,
	     UserAuthenticationDatabase* authDatabase,
	     unsigned reclamationTestSeconds);
      // called only by createNew();
  virtual ~RTSPServer();

  RTSPClientSession* attachClientSession(int clientSocket, IRTSPClientSessionObserver* observer);

  static int setUpOurSocket(UsageEnvironment& env, Port& ourPort);
  virtual Boolean specialClientAccessCheck(int clientSocket, struct sockaddr_in& clientAddr,
					   char const* urlSuffix);
      // a hook that allows subclassed servers to do server-specific access checking
      // on each client (e.g., based on client IP address), without using
      // digest authentication.

private: // redefined virtual functions
  virtual Boolean isRTSPServer() const;

private:
  static void incomingConnectionHandler(void*, int /*mask*/);
  void incomingConnectionHandler1();

private:
  friend class RTSPClientSession;
  int fServerSocket;
  Port fServerPort;
  UserAuthenticationDatabase* fAuthDB;
  unsigned fReclamationTestSeconds;
  HashTable* fServerMediaSessions;
  unsigned fSessionIdCounter;
};

#endif
