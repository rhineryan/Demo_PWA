# Compile flags

FLAG64BIT=
ifeq "$(_ARCH)" "x86_64"
FLAG64BIT=-DDEF_64_BIT
endif

ifdef _NVIDIA
FLAGNOCPU=-DDEF_NO_CPU
endif

FLAGCPU=
DIRCPU=
ifdef CPUPWA
FLAGCPU=-DDEF_USECPU
DIRCPU=CPU 
endif

ifndef _DEBUG
CC = g++ -pg -O3 -Wall $(FLAG64BIT) $(FLAGNOCPU) $(FLAGCPU)
else
CC = g++ -pg -g -Wall $(FLAG64BIT) $(FLAGNOCPU) $(FLAGCPU)
endif
CFLAGS= -I $(ROOTINCL) -I $(MINUIT2INCL) -I $(GPUPWADIR) -I $(OPENCLINCL)\
		 -I $(OPENCLIFDIR) -I $(GPUPWADIR)/_common -I $(OPENCLIFDIR)/_common
CLIBS= -L$(ROOTLIBS) -lCore -lCint -lRIO -lNet -lHist -lGraf \
		-lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics \
		-lMathCore -lThread -pthread -lm -ldl -rdynamic -lMinuit2 -lFumili \
		-L$(OPENCLLIBS) -lOpenCL \
		-L/lib -lc
LDFLAGS= $(CFLAGS)  `$(ROOTSYS)/bin/root-config --libs` $(CLIBS)
FLIBS= -lg2c -lm
F77=g77
