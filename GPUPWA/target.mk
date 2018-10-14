# Makefile include for differentaiting between architectures...

.SUFFIXES:

ifndef _ARCH
    _ARCH := $(shell arch)
    export _ARCH
endif

ifdef GPUPWADEBUG
    _DEBUG := DEBUG
    export _DEBUG
endif

ifdef CPUPWA
	_DIRCPU := CPU
	export _DIRCPU
endif

OBJDIR := _$(_ARCH)$(_DEBUG)$(_DIRCPU)

RUNDIR := $(OBJDIR)
export RUNDIR

MAKETARGET = $(MAKE) --no-print-directory -C $@ -f$(CURDIR)/Makefile \
		SRCDIR=$(CURDIR) $(MAKECMDGOALS)

EXTRATARGETS := $(wildcard _common)

.PHONY: $(OBJDIR) $(EXTRATARGETS)
$(OBJDIR) $(EXTRATARGETS):
	+@[ -d $@ ] || mkdir -p $@
	+@$(MAKETARGET)

$(OBJDIR) : $(EXTRATARGETS)

Makefile : ;
%.mk :: ;

% :: $(EXTRATARGETS) $(OBJDIR) ; :

.PHONY: clean
clean:
	rm -rf $(OBJDIR)

.PHONY: cleankernels
cleankernels:
	$(if $(EXTRATARGETS), rm -rf $(EXTRATARGETS)/*)
