AM_CXXFLAGS = $(GLIB_CFLAGS)
AM_CXXFLAGS += -I`$(LLVM_CONFIG) --includedir`

if DEBUG
AM_CXXFLAGS += @SNOWY_DEBUG_CXXFLAGS@
else
AM_CXXFLAGS += @SNOWY_CXXFLAGS@
endif

noinst_LIBRARIES = libsnowy-common.a

libsnowy_common_a_SOURCES = Log.cpp CodeGen.cpp
