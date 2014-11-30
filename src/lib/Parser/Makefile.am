AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += -I$(top_srcdir)/src/lib
AM_CXXFLAGS += -I$(top_srcdir)/src/lib/Nodes
AM_CXXFLAGS += -I$(top_builddir)/src/lib/Parser

if DEBUG
	AM_CXXFLAGS += @OPAL_DEBUG_CFLAGS@
else
	AM_CXXFLAGS += @OPAL_CFLAGS@
endif

noinst_LIBRARIES = libsnowy-parser.a

libsnowy_parser_a_SOURCES = ProgramParser.cpp Lexer.cc Driver.cpp Parser.cpp

Lexer.cc: Lexer.l ProgramParser.cpp
	flex++ $(top_srcdir)/src/lib/Parser/Lexer.l

ProgramParser.cpp: ProgramParser.ypp
	bison -v --defines=ProgramParser.h --output=ProgramParser.cpp ../../../../src/lib/Parser/ProgramParser.ypp

CLEANFILES = Lexer.cc ProgramParser.cpp ProgramParser.h ProgramParser.output stack.hh
