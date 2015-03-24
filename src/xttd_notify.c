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
#include <config.h>
#endif

#include <libnotify/notify.h>

#include "xttd_notify.h"


void
xttd_notify_notification(XttdInstance *Inst,
						 gchar* icon,
						 gint value)
{
	GError* error = NULL;
	gchar*  title = NULL;
	gchar*  body  = NULL;

	if (value) {
		title = g_strdup (TOUCHPAD_NAME);
		body = g_strdup ("Device Enabled");
	}
	else {
		title = g_strdup (TOUCHPAD_NAME);
		body = g_strdup ("Device Disabled");
	}

	notify_notification_update (Inst->notification,
				title,
				body,
				icon);

	g_free (title);
	g_free (body);

	if (!notify_notification_show (Inst->notification, &error))
	{
		g_warning ("Error while sending notification : %s\n", error->message);
		g_error_free (error);
	}
}

void
xttd_toggle_notification(XttdInstance *Inst, int state)
{
	if (state) {
		xttd_notify_notification (Inst, "input-touchpad-symbolic", state);
	} else {
		xttd_notify_notification (Inst, "touchpad-disabled-symbolic", state);
	}
}

void
xttd_notify_init(XttdInstance *Inst,
				const gchar *appname)
{
	GList *caps_list = NULL;

	notify_init (appname);

	caps_list = notify_get_server_caps ();

	if (caps_list)
	{
		GList *node;

		node = g_list_find_custom (caps_list, LAYOUT_ICON_ONLY, (GCompareFunc) g_strcmp0);

/*		node = g_list_find_custom (caps_list, SYNCHRONOUS, (GCompareFunc) g_strcmp0);*/

		g_list_free (caps_list);
	}

#ifdef NOTIFY_CHECK_VERSION
#if NOTIFY_CHECK_VERSION (0, 7, 0)
	Inst->notification = notify_notification_new ("Xfce4-TouchpadToggled", NULL, NULL);
#else
	Inst->notification = notify_notification_new ("Xfce4-TouchpadToggled", NULL, NULL, NULL);
#endif
#else
	Inst->notification = notify_notification_new ("Xfce4-TouchpadToggled", NULL, NULL, NULL);
#endif
}

void
xttd_notify_uninit (XttdInstance *Inst)
{
	g_object_unref (G_OBJECT (Inst->notification));
	Inst->notification = NULL;
	notify_uninit ();
}
