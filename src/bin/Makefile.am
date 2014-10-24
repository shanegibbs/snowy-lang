AM_CFLAGS = $(GLIB_CFLAGS)
AM_CFLAGS += -I$(top_srcdir)/src/lib
LEX=flex
AM_YFLAGS = -d -v

if DEBUG
  AM_CFLAGS += @BAB_DEBUG_CFLAGS@
else
  AM_CFLAGS += @BAB_CFLAGS@
endif

bin_PROGRAMS = opal

opal_SOURCES = opal.c
opal_LDADD = $(top_builddir)/src/lib/libopal.a
