#include "S21RLMediaServer.h"
#include "ushare.c"
#include "S21RLDLNAConfigParser.h"

class S21MediaServerPrivate
{
public:

	S21MediaServerPrivate(IS21RLServer& relayServer):m_RLServer(relayServer)
	{
	}

	~S21MediaServerPrivate()
	{
	}

	bool Init(const S21RLDLNAConfigParser& config)
	{
		m_pMediaServerPrivate = ushare_new ();
		//TODO: process configInfo and relayServer
		if (!m_pMediaServerPrivate)
		{
			//TODO: error log
			return false;
		}

		if(!(m_pMediaServerPrivate->m_pRLServer = &m_RLServer))
		{
			return false;
		}

		setup_i18n ();
		setup_iconv ();

		/* Parse args before cfg file, as we may override the default file */
		//if (parse_config_file (m_pMediaServerPrivate) < 0)
		//{
		//	/* fprintf here, because syslog not yet ready */
		//	fprintf (stderr, _("Warning: can't parse file \"%s\".\n"),
		//		m_pMediaServerPrivate->cfg_file ? m_pMediaServerPrivate->cfg_file : SYSCONFDIR SLASH_STR USHARE_CONFIG_FILE);
		//}
		const S21RLDLNAConfigParser::DirectoryList& directoryList = config.GetDirectoryList();
		S21RLDLNAConfigParser::DirectoryList::const_iterator it;

		for (it = directoryList.begin(); it != directoryList.end(); it++)
		{
			m_pMediaServerPrivate->contentlist = content_add(m_pMediaServerPrivate->contentlist,
				it->m_Path.c_str());
		}

		if (m_pMediaServerPrivate->name)
			free(m_pMediaServerPrivate->name);
		m_pMediaServerPrivate->name = strdup("S21 DLNA DMS");

		//m_pMediaServerPrivate->dlna_enabled = true;
		m_pMediaServerPrivate->dlna_enabled = false;

		if (m_pMediaServerPrivate->xbox360)
		{
			char *name;

			name = (char *)malloc (strlen (XBOX_MODEL_NAME) + strlen (m_pMediaServerPrivate->model_name) + 4);
			sprintf (name, "%s (%s)", XBOX_MODEL_NAME, m_pMediaServerPrivate->model_name);
			free (m_pMediaServerPrivate->model_name);
			m_pMediaServerPrivate->model_name = strdup (name);
			free (name);

			m_pMediaServerPrivate->starting_id = STARTING_ENTRY_ID_XBOX360;
		}

		if (m_pMediaServerPrivate->daemon)
		{
			/* starting syslog feature as soon as possible */
			start_log ();
		}

		if (!m_pMediaServerPrivate->contentlist)
		{
			log_error (_("Error: no content directory to be shared.\n"));
			ushare_free (m_pMediaServerPrivate);
			return EXIT_FAILURE;
		}

		if (!has_iface (m_pMediaServerPrivate->interface_))
		{
			ushare_free (m_pMediaServerPrivate);
			return EXIT_FAILURE;
		}

		m_pMediaServerPrivate->udn = create_udn (m_pMediaServerPrivate->interface_);
		if (!m_pMediaServerPrivate->udn)
		{
			ushare_free (m_pMediaServerPrivate);
			return EXIT_FAILURE;
		}

		m_pMediaServerPrivate->ip = get_iface_address (m_pMediaServerPrivate->interface_);
		if (!m_pMediaServerPrivate->ip)
		{
			ushare_free (m_pMediaServerPrivate);
			return EXIT_FAILURE;
		}

		if (m_pMediaServerPrivate->daemon)
		{
#ifndef WIN32
			int err;
			err = daemon (0, 0);
			if (err == -1)
			{
				log_error (_("Error: failed to daemonize program : %s\n"),
					strerror (err));
				ushare_free (m_pMediaServerPrivate);
				return EXIT_FAILURE;
			}
#endif
		}
		else
		{
			display_headers ();
		}

		ut = m_pMediaServerPrivate;

		return true;
	}

	bool Start()
	{
		signal (SIGINT, UPnPBreak);
#ifndef WIN32
		signal (SIGHUP, reload_config);
#endif

		if (m_pMediaServerPrivate->use_telnet)
		{
			if (ctrl_telnet_start (m_pMediaServerPrivate->telnet_port) < 0)
			{
				ushare_free (m_pMediaServerPrivate);
				return EXIT_FAILURE;
			}

			ctrl_telnet_register ("kill", ushare_kill,
				_("Terminates the uShare server"));
		}

		if (init_upnp (m_pMediaServerPrivate) < 0)
		{
			finish_upnp (m_pMediaServerPrivate);
			ushare_free (m_pMediaServerPrivate);
			return EXIT_FAILURE;
		}

		build_metadata_list (m_pMediaServerPrivate);

		/* Let main sleep until it's time to die... */
		//pthread_mutex_lock (&m_pMediaServerPrivate->termination_mutex);
		//pthread_cond_wait (&m_pMediaServerPrivate->termination_cond, &m_pMediaServerPrivate->termination_mutex);
		//pthread_mutex_unlock (&m_pMediaServerPrivate->termination_mutex);


		return true;
	}

	bool Stop()
	{
		if (m_pMediaServerPrivate->use_telnet)
			ctrl_telnet_stop ();
		finish_upnp (m_pMediaServerPrivate);
		free_metadata_list (m_pMediaServerPrivate);
		ushare_free (m_pMediaServerPrivate);
		finish_iconv ();

		return true;
	}

protected:
	IS21RLServer& m_RLServer;
	struct ushare_t* m_pMediaServerPrivate;
};

S21RLMediaServer::S21RLMediaServer(IS21RLServer& relayServer):m_RLServer(relayServer)
{
	m_pPrivate = new S21MediaServerPrivate(m_RLServer);
}

S21RLMediaServer::~S21RLMediaServer(void)
{
	delete m_pPrivate;
}

bool S21RLMediaServer::Init(const S21RLDLNAConfigParser& config)
{
	return m_pPrivate->Init(config);
}
bool S21RLMediaServer::Start(void)
{
	return m_pPrivate->Start();
}
bool S21RLMediaServer::Stop(void)
{
	return m_pPrivate->Stop();
}
