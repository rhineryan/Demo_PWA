#include "GPUStreamInputTextFileVector.h"
#include <fstream>

using std::ifstream;
using std::ios;


GPUStreamInputTextFileVector::GPUStreamInputTextFileVector(GPUDataDependentObjectList *_list, READTYPE _type):GPUStreamInputVector(_list), mReadtype(_type)
{
}
GPUStreamInputTextFileVector::GPUStreamInputTextFileVector(GPUDataDependentObjectList *_list, const char * _filename, READTYPE _type):GPUStreamInputVector(_list,_filename), mReadtype(_type)
{
  int nevents;
  if(TestFile(0,nevents)){
    exit(102);
  }
  SetNevents(0,nevents);
  InitUsecount(0,nevents);
}

GPUStreamInputTextFileVector::~GPUStreamInputTextFileVector(void)
{
}

STATUS GPUStreamInputTextFileVector::TestFile(int index, int & length){
  length =0;
  assert((int)mFilename.size() > index);
  if(!mFilename[index]){
    cout << "No filename specified!" << endl;
    return FAILURE;
  }
  ifstream f(mFilename[index],ios::in);
  if(f.bad()){
    cout << "Opening of file " << mFilename[index] << " failed!" << endl;
    return FAILURE;
  }

  int eventnumber = -1;
  f >> eventnumber;
  if(f.bad() || eventnumber < 0){
    cout << "Reading of number of events from file " << mFilename[index] << " failed!" << endl;
    f.close();
    return FAILURE;
  }
  length = eventnumber;
  f.close();
  return OK;
}

STATUS GPUStreamInputTextFileVector::ReadFile(int index){
	assert((int)mFilename.size() > index);
	if(!mFilename[index]){
		cout << "No filename specified!" << endl;
		return FAILURE;
	}
	ifstream f(mFilename[index],ios::in);
	if(f.bad()){
		cout << "Opening of file " << mFilename[index] << " failed!" << endl;
		return FAILURE;
	}

	int eventnumber = -1;
	f >> eventnumber;
	if(f.bad() || eventnumber < 0){
		cout << "Reading of number of events from file " << mFilename[index] << " failed!" << endl;
		return FAILURE;
	}
	char dummy[1024];
	//float4 * vectors = 0;
	switch(mReadtype){
		case ALL:
			{}
			break;
		case EVEN:
			f.getline(dummy,1024);
		case ODD:
			{}
			break;
		default:
			cout << "Something went very wrong, not reading file "<< mFilename[index] << endl;
			f.close();
			return FAILURE;
	}
	int size = eventnumber;
	if(mBuffer[index]){
		delete [] mBuffer[index];
		mBuffer[index] = 0;
	}
	mBuffer[index] = new float4[size];
	if(!mBuffer[index]){
		cout << "Failed to allocate memory for input data - aborting!" << endl;
		f.close();
		return FAILURE;
	}
	float px,py,pz,E;
	for(int i = 0; i < size; i++){
		f >> px >> py >> pz >> E;
		mBuffer[index][i] = mfloat4(px,py,pz,E);
		if(mReadtype == EVEN || mReadtype == ODD){
			f.getline(dummy,1024);
		}
	}
	if(f.bad()){
		cout << "Reading vectors from file " << mFilename[index] << " failed!" << endl;
		f.close();
		return FAILURE;
	}
	f.close();

	for(int i =0; i < (int)mstream[index].size(); i++){
		if(mstream[index][i]) delete mstream[index][i];
		mstream[index][i]=0;
	}
	mstream[index].clear();
	mlength[index].clear();
	int offset =0;
	assert(size == GetNevents(index));
	mList->SetNevents(index, size);
	while(size > 0){
	  if(size > Blocksize){
	    mlength[index].push_back(Blocksize);
	    mstream[index].push_back(0);
	//    mstream[index].push_back(new GPUDataStream<float4>(Blocksize));
	  } else {
	    mlength[index].push_back(size);
	    mstream[index].push_back(0);
	 //   mstream[index].push_back(new GPUDataStream<float4>(size));
	  }
	 // mstream[index].back()->read(vectors+offset);
	  offset += Blocksize;
	  size -= Blocksize;
	}

	mfileread[index] = true;

	return OK;

}
