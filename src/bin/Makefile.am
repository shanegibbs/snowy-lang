AM_CXXFLAGS = -I$(top_srcdir)/src/lib/Common
AM_CXXFLAGS += -I$(top_srcdir)/src/lib

if DEBUG
AM_CXXFLAGS += @SNOWY_DEBUG_CXXFLAGS@
else
AM_CXXFLAGS += @SNOWY_CXXFLAGS@
endif

bin_PROGRAMS = snowy

snowy_SOURCES = main.cpp

snowy_LDFLAGS = @LLVM_LIBDIR@
snowy_LDFLAGS += $(GLIB_LIBS)

snowy_LDADD = $(top_builddir)/src/lib/libsnowy.a
snowy_LDADD += $(top_builddir)/src/lib/Parser/libsnowy-parser.a
snowy_LDADD += $(top_builddir)/src/lib/Compiler/libsnowy-compiler.a
snowy_LDADD += $(top_builddir)/src/lib/Nodes/libsnowy-nodes.a
snowy_LDADD += $(top_builddir)/src/lib/Common/libsnowy-common.a
snowy_LDADD += @LLVM_LIBS@

