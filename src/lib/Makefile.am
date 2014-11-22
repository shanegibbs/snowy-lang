AM_CFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS = -I$(top_srcdir)/src/lib/Parser
AM_CXXFLAGS = -I$(top_srcdir)/src/lib/Nodes

if DEBUG
	AM_CFLAGS += @OPAL_DEBUG_CFLAGS@
else
	AM_CFLAGS += @OPAL_CFLAGS@
endif

noinst_LIBRARIES = libsnowy.a

libsnowy_a_SOURCES = Engine.cpp
