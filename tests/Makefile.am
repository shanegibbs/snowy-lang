AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += -I$(top_srcdir)/src/lib
AM_CXXFLAGS += -I$(top_builddir)/src/lib
AM_CXXFLAGS += @OPAL_DEBUG_CFLAGS@

TESTS=$(check_PROGRAMS)
check_PROGRAMS=NodeTest ParserTest

ParserTest_SOURCES = ParserTest.cpp
ParserTest_LDADD = $(top_builddir)/src/lib/Parser/libsnowy-parser.a
ParserTest_LDADD += $(top_builddir)/src/lib/Nodes/libsnowy-nodes.a

NodeTest_SOURCES = IntLiteral_Test.cpp
NodeTest_LDADD = $(top_builddir)/src/lib/Nodes/libsnowy-nodes.a
