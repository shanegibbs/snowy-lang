AM_CFLAGS = $(GLIB_CFLAGS)
AM_CFLAGS += -I$(top_srcdir)/src/lib/common

LEX=flex
AM_YFLAGS = -d -v

if DEBUG
	AM_CFLAGS += @OPAL_DEBUG_CFLAGS@
else
	AM_CFLAGS += @OPAL_CFLAGS@
endif

noinst_LIBRARIES = libopal.a

libopal_a_SOURCES = parser.y tokens.l nodes.c nodes_desc.c
