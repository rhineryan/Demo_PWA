#include "GPUStreamInputVector.h"
#include <cmath>

GPUStreamInputVector::GPUStreamInputVector
(GPUDataDependentObjectList *_list ):
  GPUStreamVector(_list, false),mFilename(_list->GetNSets(),(char*)0),
  mBuffer(_list->GetNSets(),(float4*)0),mlength(_list->GetNSets()),mfileread(_list->GetNSets(),false){};

GPUStreamInputVector::GPUStreamInputVector
(GPUDataDependentObjectList *_list, const char * _filename):
  GPUStreamVector(_list, false),mFilename(_list->GetNSets(),(char*)0),
  mBuffer(_list->GetNSets(),(float4*)0),mlength(_list->GetNSets()),mfileread(_list->GetNSets(),false){
  mFilename[0] =_filename;
};


 void GPUStreamInputVector::CopyBuffer(int index, int block){
	 if(!mBuffer[index]){
		 ReadFile(index);
	}
	 assert(index < (int)mstream.size());
	 assert(block < (int)mstream[index].size());
	 assert(mlength[index][block] <= GPUDataDependentObject::Blocksize);
	// cout << "Creating vector of size " << mlength[index][block] << " at index " << index << " block " << block << endl;
	/* for(int i=0; i < 2;i++)
		 cout << "("<<(*(mBuffer[index]+block*Blocksize+i)).x << ","
		 	 	 	<<(*(mBuffer[index]+block*Blocksize+i)).y << ","
		 	 	 	<<(*(mBuffer[index]+block*Blocksize+i)).z << ","
		 	 	 	<<(*(mBuffer[index]+block*Blocksize+i)).w << ")"<< endl;*/
	 mstream[index][block] = new GPUDataStream<float4>(mList->GetDeviceInterface(), mlength[index][block]);
	 //cout << "Pointer: " << mstream[index][block] <<endl;
	 mstream[index][block]->Write(mBuffer[index]+block*Blocksize);
/*	 double x =1;
	 for(int i=0; i < 1000000; i++)
		 x+=sin( x);
	 cout << x << endl;
	 mstream[index][block]->Read(mBuffer[index]+block*Blocksize);
	 cout << "Readback: " << endl;
	 for(int i=0; i < 2;i++)
		 cout << "("<<(*(mBuffer[index]+block*Blocksize+i)).x << ","
		 	        <<(*(mBuffer[index]+block*Blocksize+i)).y << ","
		 	        <<(*(mBuffer[index]+block*Blocksize+i)).z << ","
		 	        <<(*(mBuffer[index]+block*Blocksize+i)).w << ")"<< endl;
	 float4* test = mstream[index][block]->AllocateRead();
	 cout << test[0].x << endl;*/
	// cout << "____________________" << endl;
 }
