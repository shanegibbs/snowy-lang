#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#
# http://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/html_node/index.html

AC_PREREQ([2.68])
AC_INIT([snowy], [0.1], [shane@gibbsdevops.com])
AC_CONFIG_SRCDIR([src/bin/main.cpp])
AC_CONFIG_HEADERS([config.h])

# 'serial-tests' option is prefered
AM_INIT_AUTOMAKE([subdir-objects])
#LT_INIT

# Remember externally set CFLAGS
EXTERNAL_CXXFLAGS="$CXXFLAGS"

# Use the C language and compiler for the following checks
AC_LANG([C++])

# Checks for programs.
AC_PROG_CXX
AC_PROG_RANLIB

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

# Check for flex
AM_PROG_LEX
AC_CHECK_PROG([FLEX], [flex lex], [flex])
# AC_CHECK_HEADERS([FlexLexer.h], [],
#   AC_MSG_ERROR([FlexLexer.h mising]),
#   [[extern "C" {
# #include <FlexLexer.h>
# }]]
# )

# Check for bison
AC_PROG_YACC

# Check for LLVM
AC_CHECK_PROG([LLVM_CONFIG], [llvm-config], [llvm-config])
AC_CHECK_PROG([LLVM_CONFIG], [llvm-config-3.6], [llvm-config-3.6])
if test x"${LLVM_CONFIG}" == x"" ; then
  AC_MSG_ERROR([unable to find llvm-config command])
fi

LLVM_CPPFLAGS=`${LLVM_CONFIG} --cxxflags`
LLVM_LIBS=`${LLVM_CONFIG} --system-libs |sed '/^ *$/d'`
LLVM_LIBDIR=-L`${LLVM_CONFIG} --libdir`

AC_MSG_CHECKING([for llvm shared lib])

CPPFLAGS_SAVED="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $LLVM_CPPFLAGS"
LDFLAGS_SAVED="$LDFLAGS"
LDFLAGS="$LDFLAGS -lLLVM-`${LLVM_CONFIG} --version`"
export CPPFLAGS
export LDFLAGS

AC_LINK_IFELSE([AC_LANG_PROGRAM([[@%:@include <llvm/IR/LLVMContext.h>]], [[llvm::getGlobalContext(); return 0;]])], [
  AC_MSG_RESULT([yes])
  LLVM_LIBS="-lLLVM-`${LLVM_CONFIG} --version` ${LLVM_LIBS}"
],[
  AC_MSG_RESULT([using static libs])
  LLVM_LIBS="`${LLVM_CONFIG} --libs core mcjit native bitwriter` ${LLVM_LIBS}"
])

CPPFLAGS="$CPPFLAGS_SAVED"
LDFLAGS="$LDFLAGS_SAVED"
export CPPFLAGS
export LDFLAGS

AC_SUBST([LLVM_CPPFLAGS])
AC_SUBST([LLVM_LIBS])
AC_SUBST([LLVM_LIBDIR])

# Reset the externally set CFLAGS after calling AC_PROG*
CXXFLAGS="$EXTERNAL_CXXFLAGS"

AC_SUBST([SNOWY_CXXFLAGS], ["-std=c++11 -DG_DISABLE_ASSERT"])
AC_SUBST([SNOWY_DEBUG_CXXFLAGS], ["-g -std=c++11 -Wall -Werror -fno-omit-frame-pointer"])
# Clang memory check flag: -fsanitize=address

# debug flag
AC_ARG_ENABLE([debug],
[  --enable-debug    Turn on debugging],
[case "${enableval}" in
  yes) debug=true ;;
  no)  debug=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],[debug=false])
AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])

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
