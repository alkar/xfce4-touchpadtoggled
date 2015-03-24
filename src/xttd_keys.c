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

#include <keybinder.h>

#include "xttd_keys.h"
#include "xttd_xinput.h"
#include "xttd_notify.h"


static
void xttd_toggle_handler (const char *keystring, void *Inst)
{
  int state = -1;

  g_debug ("The TouchpadToggle key was pressed.");

  xttd_toggle_device(TOUCHPAD_NAME, &state);

  if (state == -1)
  {
    g_error ("No Touchpad found");
  }
  else
    xttd_toggle_notification(Inst, state);
}

void
xttd_keys_init(XttdInstance *Inst)
{
    keybinder_init();

    keybinder_bind ("XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Ctrl>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Alt>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Super>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Shift>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Ctrl><Shift>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Ctrl><Alt>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Ctrl><Super>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Alt><Shift>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Alt><Super>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Shift><Super>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Ctrl><Shift><Super>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Ctrl><Shift><Alt>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Ctrl><Alt><Super>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Shift><Alt><Super>XF86TouchpadToggle", xttd_toggle_handler, Inst);
    keybinder_bind ("<Ctrl><Shift><Alt><Super>XF86TouchpadToggle", xttd_toggle_handler, Inst);
}

void
xttd_keys_release (XttdInstance *Inst)
{
    keybinder_unbind ("XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Ctrl>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Alt>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Super>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Shift>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Ctrl><Shift>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Ctrl><Alt>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Ctrl><Super>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Alt><Shift>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Alt><Super>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Shift><Super>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Ctrl><Shift><Super>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Ctrl><Shift><Alt>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Ctrl><Alt><Super>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Shift><Alt><Super>XF86TouchpadToggle", xttd_toggle_handler);
    keybinder_unbind ("<Ctrl><Shift><Alt><Super>XF86TouchpadToggle", xttd_toggle_handler);

}
