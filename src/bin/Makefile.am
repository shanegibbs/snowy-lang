#AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS = -I$(top_srcdir)/src/lib
AM_CXXFLAGS += `llvm-config --cxxflags`
#AM_CXXFLAGS += `llvm-config --cxxflags --libs --system-libs --ldflags core`

#AM_LDFLAGS = abc

if DEBUG
	AM_CXXFLAGS += @OPAL_DEBUG_CFLAGS@
else
	AM_CXXFLAGS += @OPAL_CFLAGS@
endif

bin_PROGRAMS = opal

opal_SOURCES = opal.cpp
opal_LDADD = $(top_builddir)/src/lib/libopal.a
opal_LDFLAGS = `llvm-config --libs core jit native --system-libs`
