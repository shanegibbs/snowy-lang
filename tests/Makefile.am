AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Common
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Compiler
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Nodes
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Parser
AM_CXXFLAGS += -I$(top_srcdir)/src/lib
AM_CXXFLAGS += @SNOWY_DEBUG_CXXFLAGS@

LDFLAGS = -L`$(LLVM_CONFIG) --libdir` `llvm-config --libs core jit native bitwriter --system-libs`

LDADD = $(top_builddir)/src/lib/Common/libsnowy-common.a
LDADD += $(top_builddir)/src/lib/Nodes/libsnowy-nodes.a
LDADD += $(top_builddir)/src/lib/Parser/libsnowy-parser.a
LDADD += $(top_builddir)/src/lib/Compiler/libsnowy-compiler.a
LDADD += $(top_builddir)/src/lib/libsnowy.a

TESTS=$(check_PROGRAMS)
check_PROGRAMS=NodeTestSuite ParserTestSuite ITSuite

ParserTestSuite_SOURCES = ParserTestSuite.cpp
NodeTestSuite_SOURCES = NodeTestSuite.cpp NodeTest/IntLiteralTest.cpp NodeTest/NodeTest.cpp NodeTest/StringLiteralTest.cpp NodeTest/CallTest.cpp
ITSuite_SOURCES = ITSuite.cpp
