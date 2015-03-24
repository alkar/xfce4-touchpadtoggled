/*
 *  xfce4-touchpadtoggled - Touchpad Toggle management daemon for XFCE 4
 *
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

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <X11/Xatom.h>
#include <X11/extensions/XInput.h>

#include "xttd_xinput.h"


static void
xttd_set_property(Display *dpy, XDevice* dev, const char* property_name,
                  unsigned int val);

static void
xttd_get_property(Display *dpy, XDevice* dev, const char* property_name,
                  int *value);


static void
xttd_set_property(Display *dpy, XDevice* dev, const char* property_name,
                  unsigned int val)
{
    Atom prop = XInternAtom(dpy, property_name, True);

    XChangeDeviceProperty(dpy, dev, prop, XA_INTEGER, 8, PropModeReplace,
                          ((const unsigned char*)&val), 1);
}

static void
xttd_get_property(Display *dpy, XDevice* dev, const char* property_name,
                  int *value)
{
    Atom                act_type;
    int                 act_format;
    unsigned long       nitems, bytes_after;
    unsigned char       *data;

	Atom property = XInternAtom(dpy, property_name, True);

    if (XGetDeviceProperty(dpy, dev, property, 0, 1000, False,
                           AnyPropertyType, &act_type, &act_format,
                           &nitems, &bytes_after, &data) == Success)
    {
    	*value = (int)(*data);

        XFree(data);
    } else {
        g_error ("Could not get device attribute");
    }
}

void
xttd_toggle_device(const char *name, int *state)
{
    Display     *dpy;
    XDeviceInfo	*devices;
    XDevice     *dev;
    int			i, num_devices;
    int         current_state = -1;

    dpy = XOpenDisplay(NULL);

    devices = XListInputDevices(dpy, &num_devices);

    for (i=0; i<num_devices; i++)
    {
		if (strcmp(devices[i].name, name) == 0)
        {
		    dev = XOpenDevice(dpy, devices[i].id);
		    if (!dev)
		    {
		        g_warning ("unable to open device '%s'", devices[i].name);
		        continue;
		    }

		    xttd_get_property(dpy, dev, "Device Enabled", &current_state);

            if (current_state != -1)
            {
    		    xttd_set_property(dpy, dev, "Device Enabled", !current_state);

    		    g_debug ("Device '%s': %s\n", devices[i].name,
                                              !current_state ? "on" : "off");
            }

    		XCloseDevice(dpy, dev);

            if (current_state != -1) break;
		}
    }

    *state = !current_state;

	XFreeDeviceList(devices);
    XCloseDisplay(dpy);
}
