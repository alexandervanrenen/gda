## -------------------------------------------------------------------------------------------------
##
## This file is part of the gda cpp utility library.
## Copyright (c) 2012 Alexander van Renen. All rights reserved.
##
## Purpose - Used to build the project.
## -------------------------------------------------------------------------------------------------
## Define constants
all: libgda

GTEST_INCLUDE := gtest/include
GTEST_LIB := gtest/libgtest.a
TARGET_DIR := bin

CF := -g0 -O2 -std=c++11 -Werror -Wextra -Wall -funroll-all-loops -ffast-math -Iinclude $(addprefix -I,$(GTEST_INCLUDE))
LF := -g0 -O2 -Werror -Wextra -Wall -funroll-all-loops -ffast-math

CCCACHE_USE?=
CXX?= g++
CXX:= $(CCCACHE_USE) $(CXX)

BUILD_DIR = @mkdir -p $(dir $@)

## -------------------------------------------------------------------------------------------------
## Track dependencies
-include $(TARGET_DIR)/*.P
-include $(TARGET_DIR)/*/*.P
-include $(TARGET_DIR)/*/*/*.P
-include $(TARGET_DIR)/*/*/*/*.P
## -------------------------------------------------------------------------------------------------
## Grab all files relevant for the build
src_obj  := $(patsubst src/%,$(TARGET_DIR)/src/%, $(patsubst %.cpp,%.o,$(shell find src -name "*.cpp")))
test_obj := $(patsubst test/%,$(TARGET_DIR)/test/%, $(patsubst %.cpp,%.o,$(shell find test -name "*.cpp")))
## -------------------------------------------------------------------------------------------------
## Build the library itself
libgda: $(src_obj)
	@rm -rf libgda.a
	@for f in `find bin -name *.o`; do \
	   if [ `nm $$f 2> /dev/null | wc -l` != 0 ]; then \
	      ar -r libgda.a $$f; \
	   fi \
	 done
## -------------------------------------------------------------------------------------------------
## Build tests for the library
tester: libgda $(test_obj)
	$(CXX) -o tester libgda.a $(test_obj) $(GTEST_LIB) $(LF)
## -------------------------------------------------------------------------------------------------
## Build individual files and track dependencies
$(TARGET_DIR)/%.o: %.cpp
	$(BUILD_DIR)
	@if [ $(VERBOSE) ]; then echo $(CXX) -MD -c -o $@ $< $(CF); else echo $(CXX) $@; fi
	@$(CXX) -MD -c -o $@ $< $(CF)
	@cp $(TARGET_DIR)/$*.d $(TARGET_DIR)/$*.P; \
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
			-e '/^$$/ d' -e 's/$$/ :/' < $(TARGET_DIR)/$*.d >> $(TARGET_DIR)/$*.P; \
		rm -f $(objDir)$*.d
## -------------------------------------------------------------------------------------------------
## Clean up the hole mess
clean:
	rm -rf $(TARGET_DIR)
	find . -name '*.o' -delete -o -name 'libgda.a' -delete -o -name 'tester' -delete
## -------------------------------------------------------------------------------------------------
