AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += `$(LLVM_CONFIG) --cxxflags`

if DEBUG
AM_CXXFLAGS += @SNOWY_DEBUG_CXXFLAGS@
else
AM_CXXFLAGS += @SNOWY_CXXFLAGS@
endif

noinst_LIBRARIES = libsnowy-common.a

libsnowy_common_a_SOURCES = Log.cpp CodeGen.cpp
