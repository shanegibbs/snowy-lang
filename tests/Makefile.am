AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += -I$(top_srcdir)/src/lib
AM_CXXFLAGS += -I$(top_builddir)/src/lib
AM_CXXFLAGS += @OPAL_DEBUG_CFLAGS@

TESTS=$(check_PROGRAMS)
check_PROGRAMS=nodes_test

nodes_test_SOURCES = nodes_test.cpp
nodes_test_LDADD = $(top_builddir)/src/lib/Parser/libsnowy-parser.a
nodes_test_LDADD += $(top_builddir)/src/lib/Nodes/libsnowy-nodes.a
