CC       = gcc
CXX      = g++
MK       = make
GCOV     = gcov
LCOV     = lcov
GENHTML  = genhtml
GCOVR    = gcovr
CPPCHECK = cppcheck

CMACRO   := -DUNIT_TEST
CXXMACRO := -DUNIT_TEST

buildtype :=

CFLAGS := -g -MD -Wall
CFLAGS += -MMD
CFLAGS += -MP
ifeq ($(buildtype), coverage)
  CFLAGS += -fprofile-arcs
  CFLAGS += -ftest-coverage
else

endif

CXXFLAGS := -g -Wall
CXXFLAGS += 


CPPCHECKOPT := --enable=all
CPPCHECKOPT += --inconclusive
CPPCHECKOPT += --xml
CPPCHECKOPT += --xml-version=2
CPPCHECK_EXCLUDE := $(UTROOT)


# Command Macro each OS
ifeq ($(OS),Windows_NT)
  # not in a bash-like shell
  ifeq ($(shell uname -s),)
    CLEANUP = del /F /Q
    MV      = move
    MKDIR   = mkdir
    # in a bash-like shell, like msys
  else
    CLEANUP = rm -f
    MV      = mv
    MKDIR   = mkdir -p
  endif
    TARGET_EXTENSION=.exe
else
  CLEANUP = rm -f -r
  MV      = mv 
  MKDIR   = mkdir -p
  CP      = cp
  TARGET_EXTENSION=out
endif

LDFLAGS := 
ifeq ($(buildtype), coverage)
  LDFLAGS += -fprofile-arcs
else

endif

# edit source directory
SRCROOT = ./src/ecofishy_arduino_micro
ifeq "$(strip $(SRCROOT))" ""
  SRCROOT = .
endif

OBJROOT     = ./obj
ifeq "$(strip $(OBJROOT))" ""
	OBJROOT = .
endif


BINDIR_NAME      = bin
LIBDIR_NAME      = lib
LISTINGDIR_NAME  = listing
TARGETDIR_NAME   = debug
TESTDIR_NAME     = unit_test
TESTBINDIR_NAME  = bin
CPPCHECKDIR_NAME = CppCheck
GCOVDIR_NAME     = gcov_output

BINDIR     = ./$(BINDIR_NAME)
LIBDIR     = ./$(LIBDIR_NAME)
LISTINGDIR = ./$(LISTINGDIR_NAME)
TARGETDIR  = ./$(TARGETDIR_NAME)
TESTDIR    = ./$(TESTDIR_NAME)
TESTBINDIR = $(TESTDIR)/$(TESTBINDIR_NAME)
GTEST_ROOT    = ./googletest/googletest
GTESTDIR      = $(GTEST_ROOT)/include
GTEST_ODR_DIR = $(GTEST_ROOT)/src
CPPCHECKDIR   = ./$(CPPCHECKDIR_NAME)
GCOVDIR       = ./$(GCOVDIR_NAME)

#TARGET     ?= $(shell basename `readlink -f .`)
#TESTTARGET ?= test_$(shell basename `readlink -f .`)
TARGET     ?= ecofishy_sensor_node
TESTTARGET ?= test_$(TARGET)
GCOV_TARGET = $(GCOVDIR)/$(TARGET)_gcovtest

GTEST_ARG = --gtest_output=xml:$(TARGET)_googletest.xml


INCLUDE := -I.
INCLUDE += -I$(SRCROOT)
INCLUDE += -I$(GTESTDIR)
INCLUDE += -I$(GTEST_ODR_DIR)
INCLUDE += -I$(GTEST_ROOT)
INCLUDE += -I$(TESTDIR)

# edit .c files to compile
#CSRCS   := $(SRCROOT)/system.cpp
CSRCS   += $(SRCROOT)/main.c

# edit .cpp test files compile
CXXSRCS := $(SRCROOT)/system.cpp
CXXSRCS += $(SRCROOT)/LED_lib.cpp
CXXSRCS += $(TESTDIR)/stub_arduino.cpp
CXXSRCS += $(TESTDIR)/test_system.cpp
CXXSRCS += $(TESTDIR)/test_led.cpp

CUTOBJLIST := $(SRCROOT)/main.c

TEMPOBJLIST = $(filter-out $(OBJROOT)/main.o, $(COBJS))

GTESTSRC := $(GTEST_ODR_DIR)/gtest_main.cc 
GTESTSRC += $(GTEST_ODR_DIR)/gtest-all.cc

COBJS   := $(addprefix $(OBJROOT)/, $(notdir $(CSRCS:.c=.o)))
CXXOBJS := $(addprefix $(OBJROOT)/, $(notdir $(CXXSRCS:.cpp=.o)))
ASEMBS   = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.s)))
GCNOS    = $(addprefix $(OBJROOT)/, $(notdir $(SRCS:.c=.gcno)))
GCDAS    = $(addprefix $(OBJROOT)/, $(notdir $(SRCS:.c=.gcda)))

DEPENDS := $(COBJS:.o=.d)
DEPENDS += $(CXXOBJS:.o=.d)

LIBS    :=
ifeq ($(buildtype), googletest)
  LIBS    +=-lpthread
else

endif

-include $(DEPENDS)


LDFLAGS += -Wl,-Map=$(TARGET).map

# execute coverage test
gcov: clean_gcov
	$(MAKE) $(GCOV_TARGET) "buildtype=coverage"
	@if [ ! -e $(GCOVDIR) ]; then mkdir -p $(GCOVDIR); fi
	./$(GCOV_TARGET)
	$(MV) $(OBJROOT)/*.gcno $(OBJROOT)/*.gcda $(GCOVDIR)
	$(GCOV) -b -c -f -d $(GCOVDIR)/*.gcda
	$(MV) *.gcov $(GCOVDIR)
	$(LCOV) -c -d $(GCOVDIR) -o $(GCOV_TARGET).info
	$(GENHTML) $(GCOV_TARGET).info -o $(GCOVDIR)
	$(GCOVR) --xml --output=$(TARGET)_coverage.xml $(GCOVDIR)

# Create gcov exe
$(GCOV_TARGET): $(COBJS) $(LIBS)
	@if [ ! -e $(GCOVDIR) ]; then mkdir -p $(GCOVDIR); fi
	@if [ ! -e $(TARGETDIR) ]; then mkdir -p $(TARGETDIR); fi
	$(CC) -o $@ $^ $(LDFLAGS)

$(TARGETDIR)/$(TARGET): $(COBJS)
	@if [ ! -e $(TARGETDIR) ]; then $(MKDIR) $(TARGETDIR); fi
	$(CC) -o $@  $(LIBS) $^ $(LDFLAGS)

$(TESTBINDIR)/$(TESTTARGET): $(TEMPOBJLIST) $(CXXOBJS)
	@if [ ! -e $(TESTBINDIR) ]; then $(MKDIR) $(TESTBINDIR); fi
	$(CXX) $(INCLUDE) -o $@ $(GTESTSRC) $(LIBS) $^ $(LDFLAGS)

$(OBJROOT)/%.o: $(SRCROOT)/%.c
	@if [ ! -e $(OBJROOT) ]; then $(MKDIR) $(OBJROOT); fi
	$(CC) $(CFLAGS) $(INCLUDE) $(CMACRO) -o $@ -c $<

$(OBJROOT)/%.o :$(TESTDIR)/%.cpp
	@if [ ! -e $(OBJROOT) ]; then $(MKDIR) $(OBJROOT); fi
	-mkdir -p $(OBJROOT)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(CXXMACRO) -o $@ -c $<

$(OBJROOT)/%.o :$(SRCROOT)/%.cpp
	@if [ ! -e $(OBJROOT) ]; then $(MKDIR) $(OBJROOT); fi
	-mkdir -p $(OBJROOT)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(CXXMACRO) -o $@ -c $<

.PHONY: clean
.PHONY: clean_gtest
.PHONY: clean_gcov
.PHONY: clean_cppcheck
.PHONY: run
.PHONY: cppcheck
.PHONY: run_gtest
.PHONY: cppcheck_misra


debug: $(TARGETDIR)/$(TARGET)

gtest: clean
	$(MAKE) $(TESTBINDIR)/$(TESTTARGET) "buildtype=googletest"
	

all: clean $(TARGETDIR)/$(TARGET)

all_gtest: clean_gtest gtest

clean:
	$(CLEANUP) $(GCOVDIR)/* $(OBJROOT)/* $(TARGETDIR)/$(TARGET) *.map

clean_gtest:
	$(CLEANUP) $(OBJROOT)/* $(TESTBINDIR)/$(TESTTARGET) *_googletest.xml

clean_gcov:
	$(CLEANUP) $(OBJROOT)/* $(GCOVDIR) $(TARGET)_coverage.xml

clean_cppcheck:
	$(CLEANUP) $(OBJROOT)/* $(TARGET)_cppcheck.xml

cppcheck:
	-$(CPPCHECK) $(CPPCHECKOPT) $(SRCROOT) 2> $(TARGET)_cppcheck.xml
	

cppcheck_misra:
	cppcheck --dump $(SRCROOT)
	$(MV) $(SRCROOT)/*.dump $(OBJROOT)
	python $(CPPCHECKDIR)/addons/misra.py --rule-texts=MISRA_C_2012_Rules.txt $(OBJROOT)/*.dump 
#	2> $(TARGET)_cppcheck.xml
#	$(CPPCHECK) $(CPPCHECKOPT) $(SRCROOT) 2> $(TARGET)_cppcheck.xml
#	$(MV) $(TARGET)_cppcheck.xml

buildlog:
	make all 2>&1 | tee build.log

buildlog_gtest:
	make all_gtest 2>&1 | tee build_gtest.log

run:
	./$(TARGETDIR)/$(TARGET)

run_gtest: clean gtest
	-./$(TESTDIR_NAME)/$(TESTBINDIR_NAME)/$(TESTTARGET)

run_gtest_output: clean
	$(MAKE) gtest "buildtype=googletest"
	-./$(TESTDIR_NAME)/$(TESTBINDIR_NAME)/$(TESTTARGET) ${GTEST_ARG}
