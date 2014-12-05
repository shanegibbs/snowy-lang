AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += -I`$(LLVM_CONFIG) --includedir`
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Common
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Nodes
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Parser
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Compiler
AM_CXXFLAGS += -I$(top_srcdir)/src/lib

if DEBUG
AM_CXXFLAGS += @SNOWY_DEBUG_CXXFLAGS@
else
AM_CXXFLAGS += @SNOWY_CXXFLAGS@
endif

bin_PROGRAMS = snowy

snowy_SOURCES = main.cpp

snowy_LDADD = $(top_builddir)/src/lib/Common/libsnowy-common.a
snowy_LDADD += $(top_builddir)/src/lib/Nodes/libsnowy-nodes.a
snowy_LDADD += $(top_builddir)/src/lib/Parser/libsnowy-parser.a
snowy_LDADD += $(top_builddir)/src/lib/Compiler/libsnowy-compiler.a
snowy_LDADD += $(top_builddir)/src/lib/libsnowy.a

snowy_LDFLAGS = -L`$(LLVM_CONFIG) --libdir` `$(LLVM_CONFIG) --libs core jit native bitwriter --system-libs`
