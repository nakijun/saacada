#include "S21RLDLNAConfigParser.h"

#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/Exception.h"

#include <fstream>
#include <iostream>

using Poco::XML::DOMParser;
using Poco::XML::InputSource;
using Poco::XML::Document;
using Poco::XML::Element;
using Poco::XML::NodeList;
using Poco::XML::AutoPtr;
using Poco::Exception;

static const char *PREFERENCE_STREAMING21 = "Streaming21";
static const char *PREFERENCE_MEDIASERVER = "MediaServer";
static const char *PREFERENCE_CONTENT_DIRECTORY = "ContentDirectory";
static const char *PREFERENCE_CHANNEL_LIST = "ChannelList";
static const char *PREFERENCE_CHANNEL = "Channel";
static const char *PREFERENCE_NAME = "Name";
static const char *PREFERENCE_SOURCE = "Source";
static const char *PREFERENCE_ARCHIVE = "Archive";
static const char *PREFERENCE_CASTING_URI = "CastingURI";
static const char *PREFERENCE_SERVING_ADDRESS = "ServingAddress";
static const char *PREFERENCE_DIRECTORY_LIST = "DirectoryList";
static const char *PREFERENCE_DIRECTORY = "Directory";
static const char *PREFERENCE_PROTOCOL = "Protocol";
static const char *PREFERENCE_PATH = "Path";

bool S21RLDLNAConfigParser::Parse(const char* configFilePath)
{
	std::ifstream configFile(configFilePath);

	if (configFile.is_open())
	{
		try
		{
			InputSource src(configFile);
			DOMParser parser;
			AutoPtr<Document> pDoc = parser.parse(&src);

			Element* root = pDoc->documentElement();

			if (root->tagName() != PREFERENCE_STREAMING21)
			{
				return false;
			}

			Element* msElement = root->getChildElement(PREFERENCE_MEDIASERVER);
			if (!msElement)
			{
				return false;
			}

			Element* cdElement = msElement->getChildElement(PREFERENCE_CONTENT_DIRECTORY);
			if (!cdElement)
			{
				return false;
			}

			m_ChannelList.clear();
			m_DirectoryList.clear();

			Element* clElement = cdElement->getChildElement(PREFERENCE_CHANNEL_LIST);

			if (clElement)
			{
				AutoPtr<NodeList> cElementList = clElement->getElementsByTagName(PREFERENCE_CHANNEL);
				unsigned long length = cElementList->length();

				for (unsigned long i = 0; i < length; i++)
				{
					Element* cElement = static_cast<Element*>(cElementList->item(i));

					if (cElement)
					{
						Element* cnameElement = cElement->getChildElement(PREFERENCE_NAME);
						Element* srcElement = cElement->getChildElement(PREFERENCE_SOURCE);

						if (cnameElement && srcElement)
						{
							Channel channel;

							channel.m_Name = cnameElement->firstChild()->getNodeValue();
							channel.m_Source = srcElement->firstChild()->getNodeValue();

							if (channel.m_Source.find("http://") == string::npos &&
							        channel.m_Source.find("rtsp://") == string::npos)
							{
								channel.m_Source = "sdp:/" + channel.m_Source;
							}

							Element* archElement = cElement->getChildElement(PREFERENCE_ARCHIVE);
							if (archElement)
							{
								channel.m_Archive = "arch:/" + archElement->firstChild()->getNodeValue();
							}

							Element* castElement = cElement->getChildElement(PREFERENCE_CASTING_URI);

							if (castElement)
							{
								channel.m_CastingURI = castElement->firstChild()->getNodeValue();

								Element* servElement = cElement->getChildElement(PREFERENCE_SERVING_ADDRESS);
								if (servElement)
								{
									channel.m_ServingAddress = servElement->firstChild()->getNodeValue();
								}
							}

							m_ChannelList.push_back(channel);
						}
					}
				}
			}

			Element* dlElement = cdElement->getChildElement(PREFERENCE_DIRECTORY_LIST);

			if (dlElement)
			{
				AutoPtr<NodeList> dElementList = dlElement->getElementsByTagName(PREFERENCE_DIRECTORY);
				unsigned long length = dElementList->length();

				for (unsigned long i = 0; i < length; i++)
				{
					Element* dElement = static_cast<Element*>(dElementList->item(i));

					if (dElement)
					{
						Element* protElement = dElement->getChildElement(PREFERENCE_PROTOCOL);
						Element* dnameElement = dElement->getChildElement(PREFERENCE_NAME);
						Element* pathElement = dElement->getChildElement(PREFERENCE_PATH);

						if (protElement && dnameElement && pathElement)
						{
							Directory dir;

							dir.m_Name = dnameElement->firstChild()->getNodeValue();
							dir.m_Path = pathElement->firstChild()->getNodeValue();
							
							if (protElement->firstChild()->getNodeValue().compare("rtsp") == 0)
							{
								dir.m_Protocol = RTSP;
							}
							else
							{
								dir.m_Protocol = HTTP;
							}

							m_DirectoryList.push_back(dir);
						}
					}
				}
			}

			return true;
		}
		catch (Exception& exc)
		{
			std::cerr << exc.displayText() << std::endl;
		}
	}

	return false;
}
