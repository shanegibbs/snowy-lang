AM_CXXFLAGS = $(GLIB_CFLAGS)

if DEBUG
	AM_CFLAGS += @OPAL_DEBUG_CFLAGS@
else
	AM_CFLAGS += @OPAL_CFLAGS@
endif

noinst_LIBRARIES = libsnowy-nodes.a

libsnowy_nodes_a_SOURCES = Node.cpp Expression.cpp Ident.cpp Tuple.cpp Operator.cpp IntLiteral.cpp StringLiteral.cpp DeclareVar.cpp
