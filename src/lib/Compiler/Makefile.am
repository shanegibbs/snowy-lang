AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Nodes
AM_CXXFLAGS += `llvm-config --cxxflags`

if DEBUG
	AM_CXXFLAGS += @OPAL_DEBUG_CFLAGS@
else
	AM_CXXFLAGS += @OPAL_CFLAGS@
endif

noinst_LIBRARIES = libsnowy-compiler.a

libsnowy_compiler_a_SOURCES = Compiler.cpp
