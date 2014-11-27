AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Parser
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Nodes
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Compiler

if DEBUG
	AM_CXXFLAGS += @OPAL_DEBUG_CFLAGS@
else
	AM_CXXFLAGS += @OPAL_CFLAGS@
endif

noinst_LIBRARIES = libsnowy.a

libsnowy_a_SOURCES = Engine.cpp Log.cpp
