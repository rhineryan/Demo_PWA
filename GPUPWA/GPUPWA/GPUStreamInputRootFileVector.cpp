#include "GPUStreamInputRootFileVector.h"
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>



GPUStreamInputRootFileVector::GPUStreamInputRootFileVector(GPUDataDependentObjectList *_list):GPUStreamInputVector(_list)
{
}
GPUStreamInputRootFileVector::GPUStreamInputRootFileVector(GPUDataDependentObjectList *_list, const char * _filename, const char * _treename, const char * _px, const char * _py, const char * _pz, const char * _E):
	GPUStreamInputVector(_list,_filename),mTreename(_list->GetNSets(),(char*)0),mpx(_px),mpy(_py),mpz(_pz),mE(_E)
{
	mTreename[0] = _treename;
	int nevents;
	if(TestFile(0,nevents))
	  exit(102);
	SetNevents(0,nevents);
	InitUsecount(0,nevents);
}

GPUStreamInputRootFileVector::~GPUStreamInputRootFileVector(void)
{
}

STATUS GPUStreamInputRootFileVector::TestFile(int index, int & length){
  const char * Treename =0;
  if(index >= (int)mFilename.size() || (int)mTreename.size() < 1){
    cout << "Filename and/or treename index not defined, aborting!" << endl;
    return FAILURE;
  }
  if((int)mTreename.size() <= index || !mTreename[index]){
    Treename = mTreename[0];
  } else {
    Treename = mTreename[index];
  }

  if(!mFilename[index] || !Treename){
    cout << "Filename and/or treename not defined, aborting!" << endl;
    return FAILURE;
  }


  TFile *f = new TFile(mFilename[index]);
  length =0;
  if(!f){
    cout << "Opening of file " << mFilename[index] << " failed - aborting!" << endl;
    return FAILURE;
  }

  TTree *t1 = (TTree*)f->Get(Treename);
  if(!t1){
    cout << "Opening of tree " << Treename << " failed - aborting!" << endl;
    return FAILURE;
    f->Close();
  }

  length = (int)t1->GetEntries();
  //cout << "Length is "  << length << endl;
  f->Close();
  return OK;
}

STATUS GPUStreamInputRootFileVector::ReadFile(int index){
	//cout << "In Read File!" << endl;
	const char * Treename =0;
	if(index >= (int)mFilename.size() || (int)mTreename.size() < 1){
		cout << "Filename and/or treename index not defined, aborting!" << endl;
 		return FAILURE;
	}
	if((int)mTreename.size() <= index || !mTreename[index]){
		Treename = mTreename[0];
	} else {
		Treename = mTreename[index];
	}

	if(!mFilename[index] || !Treename){
		cout << "Filename and/or treename not defined, aborting!" << endl;
 		return FAILURE;
	}
	if(!mpx || !mpy || !mpz || !mE){
		cout << "Branchnames not all set, aborting!" << endl;
 		return FAILURE;
	}


	TFile *f = new TFile(mFilename[index]);
	if(!f){
		cout << "Opening of file " << mFilename[index] << " failed - aborting!" << endl;
		return FAILURE;
	}

	TTree *t1 = (TTree*)f->Get(Treename);
	if(!t1){
		cout << "Opening of tree " << Treename << " failed - aborting!" << endl;
		return FAILURE;
		f->Close();
	}


	float px, py, pz, E;
	t1->SetBranchAddress(mpx,&px);
	t1->SetBranchAddress(mpy,&py);
	t1->SetBranchAddress(mpz,&pz);
	t1->SetBranchAddress(mE,&E);

	int nentries = (int)t1->GetEntries();

	// by wangjk
	//nentries = 1;
	//assert(nentries == GetNevents(index));
	//mlength[index] = GPUDataStream::memsize(nentries);
	if(mBuffer[index]){
		delete [] mBuffer[index];
		mBuffer[index] = 0;
	}
	mBuffer[index] = new float4[nentries];
	if(!mBuffer[index]){
		cout << "Failed to allocate memory for input data - aborting!" << endl;
		f->Close();
		return FAILURE;
	}
	for (Int_t i=0; i < nentries; i++) {
		t1->GetEntry(i);
		mBuffer[index][i] = mfloat4(px,py,pz,E);
	}
	f->Close();
	for(int i =0; i < (int)mstream[index].size(); i++){
		if(mstream[index][i]) delete mstream[index][i];
		mstream[index][i] =0;
	}
	mstream[index].clear();
	mlength[index].clear();

	mList->SetNevents(index, nentries);

//	int offset =0;
	while(nentries > 0){
		if(nentries > Blocksize){
		//	cout << "Pushing " << Blocksize <<endl;
			mlength[index].push_back(Blocksize);
			//mstream[index].push_back(new GPUDataStream<float4>(Blocksize));
			mstream[index].push_back(0);
		} else {
		//	cout << "Pushing " << nentries <<endl;
			mlength[index].push_back(nentries);
			//mstream[index].push_back(new GPUDataStream<float4>(nentries));
			mstream[index].push_back(0);
		}
		//cout << "Size: " << mlength[index].size() << " at index : " << index << endl;
		//mstream[index].back()->read(vectors+offset);
		//offset += Blocksize;
		nentries -= Blocksize;
	}
	//delete [] vectors;
	delete f;

	mfileread[index] = true;
	return OK;
}
