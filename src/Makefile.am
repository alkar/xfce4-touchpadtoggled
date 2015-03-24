package_exec = `echo $(PACKAGE) | sed '$(program_transform_name)'`

INCLUDES = \
	-I${top_srcdir} \
	-DG_LOG_DOMAIN=\"$(package_exec)\" \
	$(PLATFORM_CPPFLAGS)

bin_PROGRAMS = \
	xfce4-touchpadtoggled

xfce4_touchpadtoggled_SOURCES = \
	main.c \
	xttd_data_types.h \
	xttd_keys.c \
	xttd_keys.h \
	xttd_xinput.c \
	xttd_xinput.h \
	xttd_notify.c \
	xttd_notify.h

xfce4_touchpadtoggled_CFLAGS = \
	$(GLIB_CFLAGS) \
	$(GTK_CFLAGS) \
	$(LIBKEYBINDER_CFLAGS) \
	$(LIBX11_CFLAGS) \
	$(LIBXI_CFLAGS) \
	$(LIBNOTIFY_CFLAGS) \
	$(PLATFORM_CFLAGS)

xfce4_touchpadtoggled_LDFLAGS = \
	-no-undefined \
	$(PLATFORM_LDFLAGS)

xfce4_touchpadtoggled_LDADD = \
	$(GLIB_LIBS) \
	$(GTK_LIBS) \
	$(LIBKEYBINDER_LIBS) \
	$(LIBNOTIFY_LIBS) \
	$(LIBX11_LIBS) \
	$(LIBXI_LIBS)

# vi:set ts=8 sw=8 noet ai nocindent syntax=automake:
