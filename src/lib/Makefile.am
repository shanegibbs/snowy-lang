AM_CFLAGS = $(GLIB_CFLAGS)
AM_CFLAGS += -I$(top_srcdir)/src/lib/common

if DEBUG
  AM_CFLAGS += @BAB_DEBUG_CFLAGS@
else
	  AM_CFLAGS += @BAB_CFLAGS@
endif

noinst_LIBRARIES = libopal.a

libopal_a_SOURCES = nodes.c parser.y tokens.l

AM_CFLAGS = $(GLIB_CFLAGS)
LEX=flex
AM_YFLAGS = -d -v
