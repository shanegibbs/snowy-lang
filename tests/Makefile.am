AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += -I$(top_srcdir)/src/lib
AM_CXXFLAGS += -I$(top_builddir)/src/lib
AM_CXXFLAGS += @OPAL_DEBUG_CFLAGS@

TESTS=$(check_PROGRAMS)
check_PROGRAMS=NodeTestSuite ParserTest

ParserTest_SOURCES = ParserTest.cpp
ParserTest_LDADD = $(top_builddir)/src/lib/Parser/libsnowy-parser.a
ParserTest_LDADD += $(top_builddir)/src/lib/Nodes/libsnowy-nodes.a

NodeTestSuite_SOURCES = NodeTestSuite.cpp NodeTest/IntLiteralTest.cpp NodeTest/NodeTest.cpp NodeTest/StringLiteralTest.cpp
NodeTestSuite_LDADD = $(top_builddir)/src/lib/Nodes/libsnowy-nodes.a
