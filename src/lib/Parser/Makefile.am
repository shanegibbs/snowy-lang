AM_CFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS = -I$(top_srcdir)/src/lib
AM_CXXFLAGS += -I$(top_builddir)/src/lib

if DEBUG
	AM_CFLAGS += @OPAL_DEBUG_CFLAGS@
else
	AM_CFLAGS += @OPAL_CFLAGS@
endif

noinst_LIBRARIES = libsnowy-parser.a

libsnowy_parser_a_SOURCES = Parser.cpp Lexer.cc Driver.cpp

Lexer.cc: Lexer.l Parser.cpp
	flex++ $(top_srcdir)/src/lib/Parser/Lexer.l

Parser.cpp: Parser.ypp
	bison -v --defines=Parser.h --output=Parser.cpp ../../../../src/lib/Parser/Parser.ypp
