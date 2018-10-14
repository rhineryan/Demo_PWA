#====================================================
# Paths to libraries etc. for inclusion in makefiles
#====================================================

ifndef _NVIDIA
OPENCLINCL=$(AMDAPPSDKROOT)/include/
else
OPENCLINCL=$(CUDAROOT)/include/
endif

ifndef _NVIDIA
ifeq "$(_ARCH)" "x86_64"
OPENCLLIBS=$(AMDAPPSDKROOT)/lib/x86_64
else
OPENCLLIBS=$(AMDAPPSDKROOT)/lib/x86
endif
else
OPENCLLIBS=usr/lib
endif

OPENCLLIB = $(OPENCLLIBS)/libOpenCL.so
ROOTINCL = $(ROOTSYS)/include
ROOTLIBS = $(ROOTSYS)/lib
MINUIT2INCL = $(ROOTSYS)/math/minuit2/inc
MINUIT2INCLM2 = $(ROOTSYS)/math/minuit2/inc/Minuit2
MINUIT2LIB = $(ROOTLIBS)/libMinuit2.so
GPUPWALIB=$(GPUPWA)/GPUPWA/$(RUNDIR)/libgpupwa.a
GPUPWADIR=$(GPUPWA)/GPUPWA/
OPENCLIFDIR=$(GPUPWA)/GPUPWA/Opencl_interface
