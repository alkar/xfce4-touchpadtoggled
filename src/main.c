/*
 *  xfce4-touchpadtoggled - Touchpad Toggle management daemon for XFCE 4
 *
 *  Copyright © 2009 Steve Dodier <sidnioulz@gmail.com>
 *  Copyright © 2012 Lionel Le Folgoc <lionel@lefolgoc.net>
 *  Copyright © 2015 Dimitrios Karagiannis <dhkarag@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif

#include <gtk/gtk.h>

#include "xttd_data_types.h"
#include "xttd_keys.h"
#include "xttd_notify.h"

static XttdInstance *Inst = NULL;

static gboolean opt_version = FALSE;
static gboolean opt_no_daemon = FALSE;
static GOptionEntry option_entries[] =
{
    { "version", 'v', 0, G_OPTION_ARG_NONE, &opt_version, "Version information", NULL },
    { "no-daemon", 0, 0, G_OPTION_ARG_NONE, &opt_no_daemon, "Do not fork to the background", NULL },
    { NULL }
};


static gint
xttd_daemonize(void)
{
#ifdef HAVE_DAEMON
	return daemon (1, 1);
#else
	pid_t pid;

	pid = fork ();
	if (pid < 0)
		return -1;

	if (pid > 0)
		_exit (EXIT_SUCCESS);

#ifdef HAVE_SETSID
	if (setsid () < 0)
		return -1;
#endif

	return 0;
#endif
}

static void
xttd_shutdown(void)
{
	xttd_notify_uninit (Inst);

	xttd_keys_release (Inst);
}

static void
xttd_instance_init(XttdInstance *i)
{
	i->notification	= NULL;
}

gint
main(gint argc, gchar **argv)
{
	GError         *error = NULL;
	GOptionContext *context;

	context = g_option_context_new (NULL);
	g_option_context_add_main_entries (context, option_entries, NULL);
	g_option_context_add_group (context, gtk_get_option_group (FALSE));

	gtk_init (&argc, &argv);

	/* parse options */
	if (!g_option_context_parse (context, &argc, &argv, &error))
	{
		g_print ("%s: %s.\n", G_LOG_DOMAIN, error->message);
		g_print ("Type '%s --help' for usage.", G_LOG_DOMAIN);
		g_print ("\n");

		g_error_free (error);
		g_option_context_free (context);

		return EXIT_FAILURE;
	}
	g_option_context_free (context);

	/* check if we should print version information */
	if (G_UNLIKELY (opt_version))
	{
		g_print ("%s %s\n\n", G_LOG_DOMAIN, PACKAGE_VERSION);
		g_print ("Please report bugs to <%s>.", PACKAGE_BUGREPORT);
		g_print ("\n");

		return EXIT_SUCCESS;
	}

	Inst = g_malloc (sizeof (XttdInstance));
	xttd_instance_init (Inst);

	/* daemonize the process */
	if (!opt_no_daemon)
	{
		if (xttd_daemonize () == -1)
		{
			/* show message and continue in normal mode */
			g_warning ("Failed to fork the process: %s. Continuing in non-daemon mode.", g_strerror (errno));
		}
	}

	/* Grab the keys */
	xttd_keys_init (Inst);

	/* Libnotify init and idle till ready for the main loop */
	g_set_application_name (XTTD_APPNAME);

	xttd_notify_init (Inst, XTTD_APPNAME);

	Inst->loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (Inst->loop);

	xttd_shutdown ();
	return 0;
}

