AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Parser
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Nodes
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Compiler

if DEBUG
	AM_CXXFLAGS += @SNOWY_DEBUG_CXXFLAGS@
else
	AM_CXXFLAGS += @SNOWY_CXXFLAGS@
endif

noinst_LIBRARIES = libsnowy.a

libsnowy_a_SOURCES = Engine.cpp Log.cpp
