AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += `$(LLVM_CONFIG) --cppflags`
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Common

if DEBUG
AM_CXXFLAGS += @SNOWY_DEBUG_CXXFLAGS@
else
AM_CXXFLAGS += @SNOWY_CXXFLAGS@
endif

noinst_LIBRARIES = libsnowy-nodes.a

libsnowy_nodes_a_SOURCES = Node.cpp Expression.cpp Type.cpp Ident.cpp Tuple.cpp Operator.cpp IntLiteral.cpp StringLiteral.cpp DeclareVar.cpp Call.cpp Args.cpp FuncDecl.cpp FuncDef.cpp ArgsDecl.cpp DeclareClass.cpp
