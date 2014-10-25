AM_CFLAGS = $(GLIB_CFLAGS)
AM_CFLAGS += -I$(top_srcdir)/src/lib
AM_CFLAGS += @OPAL_DEBUG_CFLAGS@

TESTS=$(check_PROGRAMS)
check_PROGRAMS=nodes_test

nodes_test_SOURCES = nodes_test.c
nodes_test_LDADD = $(top_builddir)/src/lib/libopal.a
