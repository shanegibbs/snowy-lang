#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#
# http://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/html_node/index.html

AC_PREREQ([2.68])
AC_INIT([snowy], [0.1], [shane@gibbsdevops.com])
AC_CONFIG_SRCDIR([src/bin/main.cpp])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([subdir-objects])
#LT_INIT

# Remember externally set CFLAGS
EXTERNAL_CXXFLAGS="$CXXFLAGS"

# Checks for programs.
AC_PROG_CXX
AC_PROG_RANLIB
AM_PROG_LEX
AC_PROG_YACC

AC_CHECK_PROG([FLEX], [flex lex], [flex])

# llvm setup
AC_CHECK_PROG([LLVM_CONFIG], [llvm-config], [llvm-config])
AC_CHECK_PROG([LLVM_CONFIG], [llvm-config-3.5], [llvm-config-3.5])
if test x"${LLVM_CONFIG}" == x"" ; then
  AC_MSG_ERROR([unable to find llvm-config command])
fi

LLVM_LIBS=`${LLVM_CONFIG} --system-libs |sed 'N;s/\n/ /'`
LLVM_LIBS="$LLVM_LIBS -lLLVM-`${LLVM_CONFIG} --version`"
#LLVM_LIBS="$LLVM_LIBS `${LLVM_CONFIG} --libs core jit native bitwriter`"
LLVM_LIBDIR=-L`${LLVM_CONFIG} --libdir`

AC_SUBST([LLVM_LIBS])
AC_SUBST([LLVM_LIBDIR])

# Reset the externally set CFLAGS after calling AC_PROG*
CXXFLAGS="$EXTERNAL_CXXFLAGS"

# Use the C language and compiler for the following checks
AC_LANG([C++])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

# Checks for standard header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h])
AC_CHECK_HEADERS([stdlib.h])

# Check for math
AC_CHECK_HEADERS([math.h], [], [
  AC_MSG_ERROR([Error, math.h is missing])
])
AC_SEARCH_LIBS([pow], [m], [], [
  AC_MSG_ERROR([unable to find the pow() function])
])

AC_CHECK_HEADERS([FlexLexer.h], [],
  AC_MSG_ERROR([FlexLexer.h mising])
)

# Checks for glib
PKG_CHECK_MODULES([GLIB], [glib-2.0], [LIBS="-lglib-2.0 $LIBS"], [
  AC_MSG_ERROR([no glib-2.0 libs found])
])

# Checks for gobject
PKG_CHECK_MODULES([GOBJECT], [gobject-2.0], [LIBS="-lgobject-2.0 $LIBS"], [
  AC_MSG_FAILURE([no gobject-2.0 libs found])
])

AC_SUBST([SNOWY_CXXFLAGS], ["-std=c++11 -DG_DISABLE_ASSERT"])
AC_SUBST([SNOWY_DEBUG_CXXFLAGS], ["-std=c++11 -Wall -Werror"]) # -Wno-deprecated-register

# debug flag
AC_ARG_ENABLE([debug],
[  --enable-debug    Turn on debugging],
[case "${enableval}" in
  yes) debug=true ;;
  no)  debug=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],[debug=false])
AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])

#AC_MSG_ERROR([wtf DEBUG])

# Make AC_OUTPUT create each file by copying an input file (by default
# file.in), substituting the output variable values
AC_CONFIG_FILES([
                 Makefile
                 src/lib/Common/Makefile
                 src/lib/Nodes/Makefile
                 src/lib/Compiler/Makefile
                 src/lib/Parser/Makefile
                 src/lib/Makefile
                 src/bin/Makefile
                 tests/Makefile
                 ])

# Generate config.status and launch it. Call this macro once, at the
# end of configure.ac
AC_OUTPUT
