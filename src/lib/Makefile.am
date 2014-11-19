AM_CFLAGS = $(GLIB_CFLAGS)

LEX=flex++
AM_YFLAGS = -d -v

if DEBUG
	AM_CFLAGS += @OPAL_DEBUG_CFLAGS@
else
	AM_CFLAGS += @OPAL_CFLAGS@
endif

noinst_LIBRARIES = libopal.a

libopal_a_SOURCES = parser.yy tokens.ll
