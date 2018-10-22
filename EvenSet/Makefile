
all: OpenCL_interface GPUPWA GammaKK

OpenCL_interface: force_look
		cd GPUPWA/Opencl_interface; make all


GPUPWA: force_look
		cd GPUPWA; make all
		
GammaKK: force_look
		cd GammaKK; make all
		
		
clean: force_look
		cd GPUPWA; make clean; cd ..; cd GammaKK; make clean; cd ..;


clobber: force_look
		cd GPUPWA; make clobber; make cleansumkernels; cd ..; cd GammaKK; make clobber; cd ..;
		
force_look :
		true
