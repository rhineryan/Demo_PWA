#========================================================
#       Multi-Architecture makefile...
#========================================================

ifeq (,$(filter _%,$(notdir $(CURDIR))))
include $(GPUPWA)/target.mk
else
ifeq (_common, $(notdir $(CURDIR)))

VPATH = $(SRCDIR)

.DEFAULT: ; @:

COMPILEKERNELS = $(GPUPWA)/GPUPWA/Opencl_interface/$(RUNDIR)/compilekernels

all:: binfiles; @:

binfiles:
		@if [[ -f binfiles ]]; \
		then \
		  echo "binfile directory exists"; \
		else \
		  echo "Creating binfile directory"; \
		  mkdir binfiles;\
		fi

testkernels.h: binfiles testkernels.cl $(COMPILEKERNELS)
		$(COMPILEKERNELS) GPU $(SRCDIR)/testkernels.cl

testkernels.cpp: testkernels.h

else

VPATH = $(SRCDIR):$(SRCDIR)/_common

.SUFFIXES : .o .c .C .h .cl .cpp .cxx


include $(GPUPWA)/paths.mk

include $(GPUPWA)/flags.mk


all: depend compilekernels makesumkernels #opencltest

include $(GPUPWA)/depends.mk



OPENCLTEST_OBJS= KernelFile.o DeviceInterface.o Stream.o testkernels.o vector_operators.o

opencltest: opencltest.o $(OPENCLTEST_OBJS)
		$(CC) opencltest.o $(LDFLAGS) $(OPENCLTEST_OBJS) \
		-o opencltest -gstabs+

COMPILEKERNELS_OBJS= KernelFile.o DeviceInterface.o Stream.o vector_operators.o

compilekernels: Compiler.o $(COMPILEKERNELS_OBJS)
		$(CC) Compiler.o $(LDFLAGS) $(COMPILEKERNELS_OBJS) \
		-o compilekernels -gstabs+

MAKESUMKERNELS_OBJS= 

makesumkernels: Makesumkernels.o $(MAKESUMKERNELS_OBJS)
		$(CC) Makesumkernels.o $(LDFLAGS) $(MAKESUMKERNELS_OBJS) \
		-o makesumkernels -gstabs+

include $(GPUPWA)/commands.mk

endif
endif
