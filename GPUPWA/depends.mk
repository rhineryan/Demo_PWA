# Makefile include to produce dependencies

$(CURDIR)/Makefile.dep: $(SRCDIR)/*.cpp 
		touch $(CURDIR)/Makefile.dep
		gcc -MM -MG -I`$(ROOTSYS)/bin/root-config --incdir` -I $(MINUIT2INCL) -I $(MINUIT2INCLM2) -I $(OPENCLINCL) -I$(GPUPWADIR)/_common -I$(GPUPWADIR)/Opencl_interface $(SRCDIR)/*.cpp $(FLAGNOCPU) >Makefile.dep

depend: $(CURDIR)/Makefile.dep

include $(CURDIR)/Makefile.dep
