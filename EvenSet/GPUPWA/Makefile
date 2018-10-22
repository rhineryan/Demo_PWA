#========================================================
#       Multi-Architecture makefile...
#========================================================

ifeq (,$(filter _%,$(notdir $(CURDIR))))
include $(GPUPWA)/target.mk
else

ifdef _NVIDIA
	NV=-nv
endif

all::
  .PHONY: all

ifeq (_common, $(notdir $(CURDIR)))

VPATH = $(SRCDIR)

.DEFAULT: ; @:

MAKESUMKERNELS = $(GPUPWA)/GPUPWA/Opencl_interface/$(RUNDIR)/makesumkernels

COMPILEKERNELS = $(GPUPWA)/GPUPWA/Opencl_interface/$(RUNDIR)/compilekernels



all:: binfiles Summing.cl Analysis.cpp Contractions.cpp Propagators.cpp Tensors.cpp Orbitals.cpp \
	Complex.cpp Summing.cpp Analysis_cpu.cpp Contractions_cpu.cpp Propagators_cpu.cpp \
	Tensors_cpu.cpp Orbitals_cpu.cpp Complex_cpu.cpp Summing_cpu.cpp ; @:

binfiles: force_look
	@if [[ -d $(CURDIR)/binfiles ]]; \
		then \
		  echo ""; \
		else \
		  echo "Creating binfile directory"; \
		  mkdir $(CURDIR)/binfiles;\
		fi

Summing.cl: $(MAKESUMKERNELS) binfiles
		$(MAKESUMKERNELS) Summing.cl

Analysis.cpp: Analysis.cl binfiles
		$(COMPILEKERNELS) GPU $(SRCDIR)/Analysis.cl -ev $(NV)

Contractions.cpp: Contractions.cl binfiles
		$(COMPILEKERNELS) GPU $(SRCDIR)/Contractions.cl $(NV)

Propagators.cpp: Propagators.cl binfiles
		$(COMPILEKERNELS) GPU $(SRCDIR)/Propagators.cl $(NV)

Tensors.cpp: Tensors.cl binfiles
		$(COMPILEKERNELS) GPU $(SRCDIR)/Tensors.cl $(NV)

Orbitals.cpp: Orbitals.cl binfiles
		$(COMPILEKERNELS) GPU $(SRCDIR)/Orbitals.cl $(NV)

Complex.cpp: Complex.cl binfiles
		$(COMPILEKERNELS) GPU $(SRCDIR)/Complex.cl $(NV)

Summing.cpp: Summing.cl binfiles
		$(COMPILEKERNELS) GPU Summing.cl -ev $(NV)

ifndef _NVIDIA

Analysis_cpu.cpp: Analysis.cl binfiles
		$(COMPILEKERNELS) CPU $(SRCDIR)/Analysis.cl -ev $(NV)

Contractions_cpu.cpp: Contractions.cl binfiles
		$(COMPILEKERNELS) CPU $(SRCDIR)/Contractions.cl $(NV)

Propagators_cpu.cpp: Propagators.cl binfiles
		$(COMPILEKERNELS) CPU $(SRCDIR)/Propagators.cl $(NV)

Tensors_cpu.cpp: Tensors.cl binfiles
		$(COMPILEKERNELS) CPU $(SRCDIR)/Tensors.cl $(NV)

Orbitals_cpu.cpp: Orbitals.cl binfiles
		$(COMPILEKERNELS) CPU $(SRCDIR)/Orbitals.cl $(NV)

Complex_cpu.cpp: Complex.cl binfiles
		$(COMPILEKERNELS) CPU $(SRCDIR)/Complex.cl $(NV)

Summing_cpu.cpp: Summing.cl binfiles
		$(COMPILEKERNELS) CPU Summing.cl -ev $(NV)

endif

else

VPATH = $(SRCDIR):$(SRCDIR)/_common

.SUFFIXES :  .c .C .h .br .cpp .cxx

include $(GPUPWA)/paths.mk

include $(GPUPWA)/flags.mk

all:: openclinterface depend lib

openclinterface: force_look
		cd $(GPUPWA)/GPUPWA/Opencl_interface; make all



include $(GPUPWA)/depends.mk


GPUPWA_OBJSX = Analysis.o Propagators.o Tensors.o Contractions.o Orbitals.o Summing.o Complex.o\
			ConfigFile.o float44.o float444.o float4444.o GPUComputedTensor.o Complex.o\
			GPUConstTensor.o GPUDataDependentObject.o GPUDataDependentObjectList.o GPUDataDependentObjectType.o\
			GPUDataStream.o GPUFumiliFCN.o GPUFumiliMinimize.o\
			GPUParameterDependentObject.o\
			GPUIndexStream.o\
			GPUMetricTensor.o GPUAntisymmetricTensor.o GPUMinuitFCN.o GPUOrbitalTensors.o\
			GPUPartialWave.o GPUFactorizedPartialWave.o GPUUnFactorizedPartialWave.o\
			GPUFactorizedRadiativePartialWave.o GPUUnFactorizedRadiativePartialWave.o GPUGPerpStreamContainer.o\
			GPUPartialWaveAnalysis.o GPUPlotset.o GPUPropagator.o  GPUPropagatorBreitWigner.o \
			GPUPropagatorMassDependentBreitWigner.o GPUPropagatorFile.o GPUBasicPropagator.o \
			GPUPropagatorType.o GPUPropagatorDerivative.o\
			GPUDynamicalFunctionPVector.o\
			GPUDynamicalSumBW.o\
			GPUPropagatorComBW.o\
			GPUPWAAmplitudeCalculator.o GPUPWACalculator.o GPUPWAFreeCalculator.o GPUStreamInputVector.o \
			GPUSetOfPartialWaves.o GPUStreamInputRootFileVector.o \
			GPUStreamInputTextFileVector.o GPUStreamTensor.o GPUTensor.o MnFunctionCross2.o \
			ParaCfg.o ResCfg.o\
			GPUMinimizationHistory.o GPUMinosMinimizationHistory.o GPURuncounter.o\
			GPUFitConstraint.o GPUFitConstraintList.o GPUChi2FitConstraint.o\
			GPUFileTable.o GPUComputedPropagator.o \
			PrepareKernels.o\
			GPULookupTable.o GPUMainMemoryLookupTable.o GPUPartialWaveLookupTable.o\
			GPUPropagatorFlatte2.o\
			GPUPropagatorFlatte3.o\
			GPUPropagatorFlatte4.o\
			GPUPropagatorSigma.o\
			GPUPropagatorA980.o\
			GPUPropagatorGaussian.o\

# GPURadiativeMesonsPartialWaveAnalysis.o GPUScalarTestPartialWaveAnalysis.o \
# GPURadiative3MesonsPartialWaveAnalysis.o \
# GPUComplexTensor2PartialWave.o GPUMesonPartialWaveAnalysis.o\
# GPUPartialWaveAnalysisType.o\
#

ifndef _NVIDIA			
GPUPWA_OBJS= $(GPUPWA_OBJSX) Analysis_cpu.o Propagators_cpu.o Tensors_cpu.o Contractions_cpu.o Orbitals_cpu.o Summing_cpu.o Complex_cpu.o
else
GPUPWA_OBJS= $(GPUPWA_OBJSX)
endif

OPENCL_INTERFACE_OBJS =  $(SRCDIR)/Opencl_interface/$(RUNDIR)/Stream.o $(SRCDIR)/Opencl_interface/$(RUNDIR)/vector_operators.o $(SRCDIR)/Opencl_interface/$(RUNDIR)/DeviceInterface.o

lib: $(GPUPWA_OBJS)
		ar r libgpupwa.a $(GPUPWA_OBJS) $(OPENCL_INTERFACE_OBJS)

.C.o:
		$(CC) $< $(CFLAGS) -c -gstabs+ -o $@

.cxx.o:
		$(CC) $< $(CFLAGS) -c -gstabs+ -o $@      

.cpp.o:
		$(CC) $< $(CFLAGS) -c -gstabs+ -o $@

.C :
		$(CC) $< $(LDFLAGS) $(CLIBS) $(FLIBS) -gstabs+ -o $@

.cxx :
		$(CC) $< $(LDFLAGS) $(CLIBS) $(FLIBS) -gstabs+ -o $@		

.cpp :
		$(CC) $< $(LDFLAGS) $(CLIBS) $(FLIBS) -gstabs+ -o $@

.f.o :
		$(F77) $< -c -gstabs+ -o $@

.cl.cpp: $(GPUPWA)/GPUPWA/Opencl_interface/compilekernels GPU $<        

force_look :
		true

endif
endif
