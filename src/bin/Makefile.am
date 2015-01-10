AM_CXXFLAGS = -I$(top_srcdir)/src/lib/Common
AM_CXXFLAGS += -I$(top_srcdir)/src/lib

AM_CPPFLAGS = @LLVM_CPPFLAGS@

if DEBUG
AM_CXXFLAGS += @SNOWY_DEBUG_CXXFLAGS@
else
AM_CXXFLAGS += @SNOWY_CXXFLAGS@
endif

LDFLAGS = @LLVM_LIBDIR@

LDADD = $(top_builddir)/src/lib/libsnowy.a
LDADD += $(top_builddir)/src/lib/Parser/libsnowy-parser.a
LDADD += $(top_builddir)/src/lib/Compiler/libsnowy-compiler.a
LDADD += $(top_builddir)/src/lib/Nodes/libsnowy-nodes.a
LDADD += $(top_builddir)/src/lib/Common/libsnowy-common.a
LDADD += @LLVM_LIBS@

bin_PROGRAMS = snowy snowy-default

snowy_SOURCES = main.cpp
snowy_default_SOURCES = default.cpp
