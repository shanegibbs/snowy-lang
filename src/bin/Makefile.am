#AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS = -I$(top_srcdir)/src/lib
AM_CXXFLAGS += -I$(top_builddir)/src/lib
AM_CXXFLAGS += `llvm-config --cxxflags`
#AM_CXXFLAGS += `llvm-config --cxxflags --libs --system-libs --ldflags core`

#AM_LDFLAGS = abc

if DEBUG
	AM_CXXFLAGS += @OPAL_DEBUG_CFLAGS@
else
	AM_CXXFLAGS += @OPAL_CFLAGS@
endif

bin_PROGRAMS = snowy test_program

snowy_SOURCES = main.cpp
snowy_LDADD = $(top_builddir)/src/lib/libsnowy.a
snowy_LDADD += $(top_builddir)/src/lib/Nodes/libsnowy-nodes.a
snowy_LDADD += $(top_builddir)/src/lib/Parser/libsnowy-parser.a
snowy_LDADD += $(top_builddir)/src/lib/Compiler/libsnowy-compiler.a
snowy_LDFLAGS = `llvm-config --libs core jit native --system-libs`

test_program_SOURCES = test_program.cpp
test_program_LDFLAGS = `llvm-config --libs core jit native --system-libs`
