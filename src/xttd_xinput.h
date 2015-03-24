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

#ifndef _XTTD_XINPUT_H
#define _XTTD_XINPUT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "xttd_data_types.h"


void
xttd_toggle_device(const char *name, int *state);

#endif
