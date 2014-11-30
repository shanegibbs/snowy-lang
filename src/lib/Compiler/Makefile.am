AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += `$(LLVM_CONFIG) --cxxflags`
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Common
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Nodes

if DEBUG
AM_CXXFLAGS += @SNOWY_DEBUG_CXXFLAGS@
else
AM_CXXFLAGS += @SNOWY_CXXFLAGS@
endif

noinst_LIBRARIES = libsnowy-compiler.a

libsnowy_compiler_a_SOURCES = Compiler.cpp Execer.cpp
