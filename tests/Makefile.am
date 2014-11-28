AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += -I$(top_srcdir)/src/lib
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Compiler
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Nodes
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Parser
AM_CXXFLAGS += @OPAL_DEBUG_CFLAGS@

TESTS=$(check_PROGRAMS)
check_PROGRAMS=NodeTestSuite ParserTestSuite

ParserTestSuite_SOURCES = ParserTestSuite.cpp
ParserTestSuite_LDADD = $(top_builddir)/src/lib/Parser/libsnowy-parser.a
ParserTestSuite_LDADD += $(top_builddir)/src/lib/Nodes/libsnowy-nodes.a
ParserTestSuite_LDADD += $(top_builddir)/src/lib/libsnowy.a
ParserTestSuite_LDFLAGS = `llvm-config --libs core jit native --system-libs`

NodeTestSuite_SOURCES = NodeTestSuite.cpp NodeTest/IntLiteralTest.cpp NodeTest/NodeTest.cpp NodeTest/StringLiteralTest.cpp NodeTest/CallTest.cpp
NodeTestSuite_LDADD = $(top_builddir)/src/lib/Nodes/libsnowy-nodes.a
NodeTestSuite_LDADD += $(top_builddir)/src/lib/libsnowy.a
NodeTestSuite_LDFLAGS = `llvm-config --libs core jit native --system-libs`
