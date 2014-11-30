AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += `llvm-config --cxxflags`
AM_CXXFLAGS += -I$(top_srcdir)/src/lib
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Compiler

if DEBUG
AM_CXXFLAGS += @SNOWY_DEBUG_CXXFLAGS@
else
AM_CXXFLAGS += @SNOWY_CXXFLAGS@
endif

noinst_LIBRARIES = libsnowy-nodes.a

libsnowy_nodes_a_SOURCES = Node.cpp Expression.cpp Ident.cpp Tuple.cpp Operator.cpp IntLiteral.cpp StringLiteral.cpp DeclareVar.cpp Call.cpp Args.cpp
