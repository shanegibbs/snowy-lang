AM_CFLAGS = $(GLIB_CFLAGS)
LEX=flex
AM_YFLAGS = -d -v

if DEBUG
  AM_CFLAGS += @BAB_DEBUG_CFLAGS@
else
  AM_CFLAGS += @BAB_CFLAGS@
endif

bin_PROGRAMS = opal

opal_SOURCES = opal.c nodes.c parser.y tokens.l

#BUILT_SOURCES = calc_bison.h
