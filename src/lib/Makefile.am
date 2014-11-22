AM_CFLAGS = $(GLIB_CFLAGS)

#LEX=flex++
# AM_YFLAGS = -d -v
# AM_YFLAGS = --c++ -o lex.yy.c -L

if DEBUG
	AM_CFLAGS += @OPAL_DEBUG_CFLAGS@
else
	AM_CFLAGS += @OPAL_CFLAGS@
endif

noinst_LIBRARIES = libopal.a

libopal_a_SOURCES = Parser.cpp Lexer.cc Parser/Driver.cpp

Lexer.cc: Parser/Lexer.l Parser.cpp
	flex++ $(top_srcdir)/src/lib/Parser/Lexer.l

Parser.cpp: Parser/Parser.ypp
	bison -v --defines=Parser.h --output=Parser.cpp ../../../src/lib/Parser/Parser.ypp
