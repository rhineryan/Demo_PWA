#include "GPUStreamTensor.h"
#include <cassert>
#include <iostream>

//#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
//#define _CRT_SECURE_NO_DEPRECATE 1
template <typename T, typename LT>
GPUStreamTensor<T, LT>::GPUStreamTensor(GPUDataDependentObjectList *_list, bool init):
	GPUTensor(GetRank()),
	GPUDataDependentObjectType<T>(_list, init)

{

}


// Constructor for a GPUStreamTensor taking its contents from a GPUFileTable
template <typename T, typename LT>
GPUStreamTensor<T, LT>::GPUStreamTensor(GPUDataDependentObjectList *_list,
				 std::vector<GPUFileTable<LT> *> _tables,
				 std::vector<unsigned int> _columns):
					GPUTensor(GetRank()),
					 GPUDataDependentObjectType<T>(_list, false),
					 mtables(_tables),
					 mcolumns(_columns){

	assert(_list->GetNSets() == (int)_tables.size());
	assert(_list->GetNSets() == (int)_columns.size());
	for(int index =0; index < _list->GetNSets(); index++){
		int nentries = mtables[index]->nevents();
		while(nentries > 0){
			if(nentries > GPUDataDependentObject::Blocksize){
				this->mstream[index].push_back(0);
			} else {
				this->mstream[index].push_back(0);
			}
			nentries -= GPUDataDependentObject::Blocksize;
		}
	}

  }

template <typename T, typename LT>
GPUStreamTensor<T, LT>::GPUStreamTensor():GPUTensor(GetRank()),GPUDataDependentObjectType<T>(0, false)
{
}



template <typename T, typename LT>
GPUDataStream<T> * GPUStreamTensor<T, LT>::operator()(int index, int block)
{
	assert(index < (int)this->mstream.size());
	assert(block < (int)this->mstream[index].size());
	if(!mtables.size()){
		assert(this->mstream[index][block]);
		return this->mstream[index][block];
	} else {
		if(this->mstream[index][block]){
			return this->mstream[index][block];
		} else {
			CopyBuffer(index,block);
			return this->mstream[index][block];
		}

	}
}

template <typename T, typename LT>
void GPUStreamTensor<T, LT>::CopyBuffer(int index, int block){
	 assert(index < (int)this->mstream.size());
	 assert(block < (int)this->mstream[index].size());

	 this->mstream[index][block] = new GPUDataStream<T>(this->mList->GetDeviceInterface(), this->GetLength(index,block));
	 this->mstream[index][block]->Write((*mtables[index])(mcolumns[index])+block*GPUDataDependentObject::Blocksize);
 }


template <>
void GPUStreamTensor<float44, float4444>::CopyBuffer(int index, int block){
	 assert(index < (int)this->mstream.size());
	 assert(block < (int)this->mstream[index].size());
	 cout << "Warning, reading of float4444 objects not implemented, aborting!" << endl;
	 assert(0);
	// for(int i= 0 ; i < 16; i++){
	//	this->mstream[index][block](i) = new GPUDataStream<float44>(this->mList->GetDeviceInterface(), this->GetLength(index,block));
	//	 this->mstream[index][block](i)->Read((*mtables[index])(mcolumns[index])+block*GPUDataDependentObject::Blocksize);

//	 }
 }



GPUStreamScalar::GPUStreamScalar(GPUDataDependentObjectList *_list, float value):GPUStreamTensor<float>(_list, false), mResetable(false)
{
  int maxindex = _list->GetNSets();
  this->mstream.clear();

  musecount.clear();
  for(int j=0; j < maxindex; j++){
    this->mstream.push_back(std::vector<GPUDataStream<float> *>());
    int length = _list->GetNevents(j);
    //cout << length << endl;
    float * data = new float[length];
    for(int i =0; i < length; i++){
      data[i] = value;
    }
    Write(data, length,j);
    this->mstream[j].back()->GetEvent().wait();
    delete [] data;
    InitUsecount(j,length);
  }
}

template <typename T, typename LT>
GPUStreamTensor<T, LT>::~GPUStreamTensor(void)
{
}

float * GPUStreamScalar::ReadBlock(int index, int block){
	assert(index < (int)this->mstream.size());
	bool uc = false;
	if(!this->mstream[index][block]){
		(*this)(index,block);
		uc = true;
	}
	assert(this->mstream[index][block]);
	float * temp = new float[GetLength(index,block)];
	this->mstream[index][block]->Read(temp);
	if(uc)
		DecreaseUsecount(index,block);
	return temp;
}

float4 * GPUStreamVector::ReadBlock(int index, int block){
	assert(index < (int)this->mstream.size());
	bool uc = false;
	if(!this->mstream[index][block]){
		(*this)(index,block);
		uc = true;
	}
	assert(this->mstream[index][block]);
	float4 * temp = new float4[GetLength(index,block)];
	this->mstream[index][block]->Read(temp);
	if(uc)
		DecreaseUsecount(index,block);
	return temp;
}

float44 * GPUStreamTensor2::ReadBlock(int index, int block){
	assert(index < (int)this->mstream.size());
	bool uc = false;
	if(!this->mstream[index][block]){
		(*this)(index,block);
		uc = true;
	}
	assert(this->mstream[index][block]);
	float44 * temp = new float44[GetLength(index,block)];
		this->mstream[index][block]->Read(temp);
	if(uc)
		DecreaseUsecount(index,block);
	return temp;
}

float444 * GPUStreamTensor3::ReadBlock(int index, int block){
	assert(index < (int)this->mstream.size());
	bool uc = false;
	if(!this->mstream[index][block]){
		(*this)(index,block);
		uc =true;
	}
	assert(this->mstream[index][block]);
	float444 * temp = new float444[GetLength(index,block)];
	this->mstream[index][block]->Read(temp);
	if(uc)
		DecreaseUsecount(index,block);
	return temp;
}

float4444 * GPUStreamTensor4::ReadBlock(int index, int block){
	assert(index < (int)this->mstream.size());
	bool uc =false;
	if(!this->mstream[index][block]){
		(*this)(index,block);
		uc =true;
	}
	assert(this->mstream[index][block]);
	float4444 * result = new float4444[GetLength(index,block)];
	float44 * temp = new float44[GetLength(index,block)];
	for(int i=0; i < 4; i++){
	  for(int j=0; j < 4; j++){
	    (*this->mstream[index][block])(i,j)->Read(temp);
	    for(int k=0; k < GetLength(index,block); k++){
	      result[k](i,j) = temp[k];
	    }
	  }
	}
	if(uc)
		DecreaseUsecount(index,block);
	delete [] temp;
	return result;
}


void GPUStreamScalar::Print(int nelements, std::ostream & output, int index, int block){
	float * data;
	IncreaseUsecount(index,block);
	if(nelements < 1)
			nelements = GetLength(index,block);
	data = ReadBlock(index, block);
	output << "_______________________" << endl;
	for(int i=0; i < nelements; i++)
		output << "   " << data[i] << endl;
	output << "_______________________" << endl;
	delete [] data;
}

void GPUStreamVector::Print(int nelements, std::ostream & output, int index, int block){
	float4 * data;
	IncreaseUsecount(index,block);
	if(nelements < 1)
		nelements = GetLength(index,block);
	data = ReadBlock(index, block);
	output << "_______________________" << endl;
	for(int i=0; i < nelements; i++)
		output << "    (" << data[i].x << ", " << data[i].y << ", "<< data[i].z << ", "<< data[i].w << ")" << endl;
	output << "_______________________" << endl;
	delete [] data;
}

void GPUStreamTensor2::Print(int nelements, std::ostream & output, int index, int block){
	float44 * data;
	IncreaseUsecount(index,block);
	if(nelements < 1)
		nelements = GetLength(index,block);
	data = ReadBlock(index, block);
	output << "_______________________" << endl;
	for(int i=0; i < nelements; i++){
		output << "    (" << data[i].c.x << ", " << data[i].c.y << ", "<< data[i].c.z << ", "<< data[i].c.w << "," << endl;
		output << "     " << data[i].d.x << ", " << data[i].d.y << ", "<< data[i].d.z << ", "<< data[i].d.w << "," << endl;
		output << "     " << data[i].e.x << ", " << data[i].e.y << ", "<< data[i].e.z << ", "<< data[i].e.w << "," << endl;
		output << "     " << data[i].f.x << ", " << data[i].f.y << ", "<< data[i].f.z << ", "<< data[i].f.w << ")" << endl << endl;
	}
	output << "_______________________" << endl;
	delete [] data;
}

void GPUStreamTensor3::Print(int nelements, std::ostream & output, int index, int block){
	float444 * data;
	IncreaseUsecount(index,block);
	if(nelements < 1)
		nelements = GetLength(index,block);
	data = ReadBlock(index, block);
	output << "_______________________" << endl;
	for(int i=0; i < nelements; i++){
		output << "_____" << endl;
		output << "    (" << data[i].cc.x << ", " << data[i].cc.y << ", "<< data[i].cc.z << ", "<< data[i].cc.w << "," << endl;
		output << "     " << data[i].cd.x << ", " << data[i].cd.y << ", "<< data[i].cd.z << ", "<< data[i].cd.w << "," << endl;
		output << "     " << data[i].ce.x << ", " << data[i].ce.y << ", "<< data[i].ce.z << ", "<< data[i].ce.w << "," << endl;
		output << "     " << data[i].cf.x << ", " << data[i].cf.y << ", "<< data[i].cf.z << ", "<< data[i].cf.w << ")" << endl;

		output << "    (" << data[i].dc.x << ", " << data[i].dc.y << ", "<< data[i].dc.z << ", "<< data[i].dc.w << "," << endl;
		output << "     " << data[i].dd.x << ", " << data[i].dd.y << ", "<< data[i].dd.z << ", "<< data[i].dd.w << "," << endl;
		output << "     " << data[i].de.x << ", " << data[i].de.y << ", "<< data[i].de.z << ", "<< data[i].de.w << "," << endl;
		output << "     " << data[i].df.x << ", " << data[i].df.y << ", "<< data[i].df.z << ", "<< data[i].df.w << ")" << endl;

		output << "    (" << data[i].ec.x << ", " << data[i].ec.y << ", "<< data[i].ec.z << ", "<< data[i].ec.w << "," << endl;
		output << "     " << data[i].ed.x << ", " << data[i].ed.y << ", "<< data[i].ed.z << ", "<< data[i].ed.w << "," << endl;
		output << "     " << data[i].ee.x << ", " << data[i].ee.y << ", "<< data[i].ee.z << ", "<< data[i].ee.w << "," << endl;
		output << "     " << data[i].ef.x << ", " << data[i].ef.y << ", "<< data[i].ef.z << ", "<< data[i].ef.w << ")" << endl;

		output << "    (" << data[i].fc.x << ", " << data[i].fc.y << ", "<< data[i].fc.z << ", "<< data[i].fc.w << "," << endl;
		output << "     " << data[i].fd.x << ", " << data[i].fd.y << ", "<< data[i].fd.z << ", "<< data[i].fd.w << "," << endl;
		output << "     " << data[i].fe.x << ", " << data[i].fe.y << ", "<< data[i].fe.z << ", "<< data[i].fe.w << "," << endl;
		output << "     " << data[i].ff.x << ", " << data[i].ff.y << ", "<< data[i].ff.z << ", "<< data[i].ff.w << ")" << endl;

	}
	output << "_______________________" << endl;
	delete [] data;
}

void GPUStreamTensor4::Print(int nelements, std::ostream & output, int index, int block){
	float4444 * data;
	IncreaseUsecount(index,block);
	if(nelements < 1)
		nelements = GetLength(index,block);
	data = ReadBlock(index, block);
	output << "_______________________" << endl;
	for(int i=0; i < nelements; i++){
	  output << "_____" << endl;
	  for(int j = 0; j < 16; j++){
	    output << "   (" << data[i](j).c.x << ", " << data[i](j).c.y << ", "<< data[i](j).c.z << ", "<< data[i](j).c.w << "," << endl;
	    output << "    " << data[i](j).d.x << ", " << data[i](j).d.y << ", "<< data[i](j).d.z << ", "<< data[i](j).d.w << "," << endl;
	    output << "    " << data[i](j).e.x << ", " << data[i](j).e.y << ", "<< data[i](j).e.z << ", "<< data[i](j).e.w << "," << endl;
	    output << "    " << data[i](j).f.x << ", " << data[i](j).f.y << ", "<< data[i](j).f.z << ", "<< data[i](j).f.w << ")" << endl;
	  }
	}
	output << "_______________________" << endl;
	delete [] data;
}




vector<TH1F*> GPUStreamScalar::Plot(char * id, char * title,
									int nbins, double min, double max,
									float ** dcs, int nwaves, bool dooffdiagonal, float * weights,
									int dataindex, int mcindex,  int nblocks){
	// Extract possible axis labels from the Histo title
	ResetUsecount(dataindex);
	ResetUsecount(mcindex);
	IncreaseUsecount(dataindex);
	IncreaseUsecount(mcindex);
	char * axis = (char *)memchr(title, ';',strlen(title));
	char * mytitle;
	if(axis){
		size_t titlen = axis - title +1;
		mytitle = new char[titlen];
		strncpy (mytitle,title, titlen-1);
		mytitle[titlen-1] = 0;
	} else {
		mytitle = title;
	}
	char idtext[256];
	char titletext[256];
	sprintf(idtext, "%s%s",id,"_Data");
	sprintf(titletext, "%s%s",mytitle,"_Data");
	TH1F * datahist = new TH1F(idtext, titletext, nbins, min, max);
	sprintf(idtext, "%s%s",id,"_MC");
	sprintf(titletext, "%s%s",title,"_MC");
	TH1F * mchist = new TH1F(idtext, titletext, nbins, min, max);
	int datacounter =0;
	for(int block =0; block < GetNBlocks(dataindex); block++){
		int length = GetLength(dataindex, block);
		float * data = ReadBlock(dataindex, block);
		for(int i =0; i < length; i++){
			if(!weights){
				datahist->Fill(data[i]);
			} else {
				datahist->Fill(data[i],weights[datacounter]);
				datacounter++;
			}
		}
		delete [] data;
		Reset(dataindex,block);
	}

	TH1F * mchistx[nwaves+2];
	if(nwaves){
		for(int j = 1; j < nwaves+2; j++){
			if(j == 1){
				sprintf(idtext, "%s%s",id,"_MC_phsp");
				sprintf(titletext, "%s%s",mytitle,"_MC phasespace");
			} else {
				sprintf(idtext, "%s%s%i",id,"_MC_wave_",j-2);
				sprintf(titletext, "%s%s%i",mytitle,"_MC wave ", j-2);
			}
			mchistx[j] = new TH1F(idtext, titletext, nbins, min, max);
		}
	}

	TH1F * mchistxx[nwaves+2][nwaves+2];
	if(nwaves && dooffdiagonal){
	  //int index = nwaves+2;
		for(int j = 2; j < nwaves+2; j++){
			for(int k = j+1; k < nwaves+2; k++){
				sprintf(idtext, "%s%s%i_%i",id,"_MC_interference_",j-2, k-2);
				sprintf(titletext, "%s%s%i %i",mytitle,"_MC interference ", j-2, k-2);

				mchistxx[j][k] = new TH1F(idtext, titletext, nbins, min, max);
			}
		}
	}


	int maxblock = GetNBlocks(mcindex);
	if(maxblock > nblocks && nblocks > 0)
		maxblock = nblocks;

	for(int block =0; block < maxblock; block++){
		int mclength = GetLength(mcindex, block);
		float * mc = ReadBlock(mcindex, block);
		//cout << "In plot: " <<  block << " : " << mclength << endl;
		while(mclength%4)
			mclength--;
		for(int i =0; i < mclength; i++){
			if(dcs[0][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize] > 0){
				mchist->Fill(mc[i],dcs[0][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize]);
				//cout << "DCS1 " << dcs[0][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize] <<endl;
				//cout << "DCS1 " << dcs[0][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize] << " at " << i << " of " << mclength << " in block " << block <<endl;
			} else {
				//cout << "DCS2 " << dcs[0][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize] << " at " << i << " of " << mclength << " in block " << block <<endl;
			}
		}
		if(nwaves){
			for(int j = 1; j < nwaves+2; j++){
				for(int i =0; i < mclength; i++){
				mchistx[j]->Fill(mc[i],dcs[j][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize]);
				//cout << "DCS3 " << dcs[j][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize] << " at " << i << " of " << mclength << " in block " << block <<endl;
			        //mchistx[j]->Fill(mc[i],dcs[j][i+block*10000]);

				}
			}
		}
		if(nwaves && dooffdiagonal){
			int index = nwaves+2;
			for(int j = 2; j < nwaves+2; j++){
				for(int k = j+1; k < nwaves+2; k++){
					for(int i =0; i < mclength; i++){
						mchistxx[j][k]->Fill(mc[i],dcs[index][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize]);
				//cout << "DCS4 " << dcs[index][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize] << " at " << i << " of " << mclength << " in block " << block <<endl;
					}
					index++;
				}
			}
		}
		delete [] mc;
		Reset(mcindex, block);
	}

	double scalefactor;
	if(mchist->Integral() != 0){
		scalefactor = datahist->Integral()/mchist->Integral();
		cout << "Scalefactor: " << scalefactor << endl;
	} else {
		std::cout << "Warning: MC histogram integral is zero!" << endl;
		scalefactor = 1.0;
	}
	mchist->Scale(scalefactor);

	if(axis){
		axis++;
		datahist->GetXaxis()->SetTitle(axis);
		mchist->GetXaxis()->SetTitle(axis);
	}

	vector<TH1F *> result;
	result.push_back(datahist);
	result.push_back(mchist);

	if(nwaves){
		for(int j = 1; j < nwaves+2; j++){
			mchistx[j]->Scale(scalefactor);
			if(axis)
				mchistx[j]->GetXaxis()->SetTitle(axis);
			result.push_back(mchistx[j]);
		}
	}


	if(nwaves && dooffdiagonal){
		int index = nwaves+2;
		for(int j = 2; j < nwaves+2; j++){
			for(int k = j+1; k < nwaves+2; k++){
				mchistxx[j][k]->Scale(scalefactor);
				if(axis)
					mchistxx[j][k]->GetXaxis()->SetTitle(axis);
				result.push_back(mchistxx[j][k]);
				index++;
			}
		}

	}

	delete [] mytitle;

	return result;
}



vector<TH2F*> GPUStreamScalar::Plot(char * id, // Histogram ID for Root
 			     char * title, // Histogram title. Can contain axis labels after semicolons ("Momentumplot;p[Gev];Events")
 			     int nbinsx, // Number of x bins in Histogram
 			     double xmin, // Left edge of x axis
 			     double xmax, // Right edge of x axis
 			     int nbinsy, // Number of y bins in Histogram
 			  	 double ymin, // Left edge of y axis
 			  	 double ymax, // Right edge of y axis
 			  	 GPUStreamScalar & yvar, // second variable for 2D histo
 			     float ** dcs, // Array with differential x-sections
 			     int nwaves, // Number of waves, if 0, just the integrated result is plotted
 			     bool dooffdiagonal, // Plot interference terms or not
 			     float * weights, // Event weigths to use in the plots
 			     int dataindex, // Stream containig the data
 			     int mcindex,  // Stream with the phase space MC
 			     int nblocks // Maximum number of MC blocks to plot
 			     ){

	ResetUsecount(dataindex);
	ResetUsecount(mcindex);
	IncreaseUsecount(dataindex);
	IncreaseUsecount(mcindex);

	yvar.ResetUsecount(dataindex);
	yvar.ResetUsecount(mcindex);
	yvar.IncreaseUsecount(dataindex);
	yvar.IncreaseUsecount(mcindex);

	// Extract possible axis labels from the Histo title
	char * axis = (char *)memchr(title, ';',strlen(title));
	char * mytitle;
	if(axis){
		size_t titlen = axis - title +1;
		mytitle = new char[titlen];
		strncpy (mytitle,title, titlen-1);
		mytitle[titlen-1] = 0;
	} else {
		mytitle = title;
	}
	char idtext[256];
	char titletext[256];
	sprintf(idtext, "%s%s",id,"_Data");
	sprintf(titletext, "%s%s",mytitle,"_Data");
	TH2F * datahist = new TH2F(idtext, titletext, nbinsx, xmin, xmax, nbinsy, ymin, ymax);
	sprintf(idtext, "%s%s",id,"_MC");
	sprintf(titletext, "%s%s",title,"_MC");
	TH2F * mchist = new TH2F(idtext, titletext, nbinsx, xmin, xmax, nbinsy, ymin, ymax);
	int datacounter =0;
	for(int block =0; block < GetNBlocks(dataindex); block++){
		int length = GetLength(dataindex, block);
		float * datax = ReadBlock(dataindex, block);
		float * datay = yvar.ReadBlock(dataindex, block);
		for(int i =0; i < length; i++){
			if(!weights){
				datahist->Fill(datax[i], datay[i]);
			} else {
				datahist->Fill(datax[i],datay[i],weights[datacounter]);
				datacounter++;
			}
		}
		delete [] datax;
		delete [] datay;
		Reset(dataindex, block);
		yvar.Reset(dataindex, block);
	}

	TH2F * mchistx[nwaves+2];
	if(nwaves){
		for(int j = 1; j < nwaves+2; j++){
			if(j == 1){
				sprintf(idtext, "%s%s",id,"_MC_phsp");
				sprintf(titletext, "%s%s",mytitle,"_MC phasespace");
			} else {
				sprintf(idtext, "%s%s%i",id,"_MC_wave_",j-2);
				sprintf(titletext, "%s%s%i",mytitle,"_MC wave ", j-2);
			}
			mchistx[j] = new TH2F(idtext, titletext, nbinsx, xmin, xmax, nbinsy, ymin, ymax);
		}
	}

	TH2F * mchistxx[nwaves+2][nwaves+2];
	if(nwaves && dooffdiagonal){
	  //int index = nwaves+2;
		for(int j = 2; j < nwaves+2; j++){
			for(int k = j+1; k < nwaves+2; k++){
				sprintf(idtext, "%s%s%i_%i",id,"_MC_interference_",j-2, k-2);
				sprintf(titletext, "%s%s%i %i",mytitle,"_MC interference ", j-2, k-2);

				mchistxx[j][k] = new TH2F(idtext, titletext, nbinsx, xmin, xmax, nbinsy, ymin, ymax);
			}
		}
	}


	int maxblock = GetNBlocks(mcindex);
	if(maxblock > nblocks && nblocks > 0)
		maxblock = nblocks;

	for(int block =0; block < maxblock; block++){
		int mclength = GetLength(mcindex, block);
		float * mcx = ReadBlock(mcindex, block);
		float * mcy = yvar.ReadBlock(mcindex, block);
		//cout << "In plot: " <<  block << " : " << mclength << endl;
		while(mclength%4)
			mclength--;
		for(int i =0; i < mclength; i++){
			if(dcs[0][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize] > 0){
				mchist->Fill(mcx[i],mcy[i], dcs[0][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize]);
			} else {
		//		cout << "DCS " << dcs[0][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize] << " at " << i << " of " << mclength << " in block " << block <<endl;
			}
		}
		if(nwaves){
			for(int j = 1; j < nwaves+2; j++){
				for(int i =0; i < mclength; i++){
				mchistx[j]->Fill(mcx[i],mcy[i],dcs[j][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize]);
			        //mchistx[j]->Fill(mc[i],dcs[j][i+block*10000]);

				}
			}
		}
		if(nwaves && dooffdiagonal){
			int index = nwaves+2;
			for(int j = 2; j < nwaves+2; j++){
				for(int k = j+1; k < nwaves+2; k++){
					for(int i =0; i < mclength; i++){
						mchistxx[j][k]->Fill(mcx[i],mcy[i], dcs[index][i+block*GPUStreamTensor<float>::GPUDataDependentObject::Blocksize]);
					}
					index++;
				}
			}
		}
		delete [] mcx;
		delete [] mcy;
		Reset(mcindex, block);
		yvar.Reset(mcindex,block);
	}

	double scalefactor;
	if(mchist->Integral() != 0){
		scalefactor = datahist->Integral()/mchist->Integral();
		cout << "Scalefactor: " << scalefactor << endl;
	} else {
		std::cout << "Warning: MC histogram integral is zero!" << endl;
		scalefactor = 1.0;
	}
	mchist->Scale(scalefactor);

	axis++;
	char * yaxis = (char *)memchr(axis, ';',strlen(axis));
	char * xaxis;
	if(yaxis){
		size_t titlen = yaxis - axis +1;
		xaxis = new char[titlen];
		strncpy (xaxis,axis, titlen-1);
		xaxis[titlen-1] = 0;
	} else {
		xaxis = axis;
	}



	if(yaxis){
		yaxis++;
		datahist->GetYaxis()->SetTitle(yaxis);
		mchist->GetYaxis()->SetTitle(yaxis);
	}

	if(xaxis){
		xaxis++;
		datahist->GetXaxis()->SetTitle(xaxis);
		mchist->GetXaxis()->SetTitle(xaxis);
	}

	vector<TH2F *> result;
	result.push_back(datahist);
	result.push_back(mchist);

	if(nwaves){
		for(int j = 1; j < nwaves+2; j++){
			mchistx[j]->Scale(scalefactor);
			if(xaxis)
				mchistx[j]->GetXaxis()->SetTitle(xaxis);
			if(yaxis)
				mchistx[j]->GetYaxis()->SetTitle(yaxis);
			result.push_back(mchistx[j]);
		}
	}


	if(nwaves && dooffdiagonal){
		int index = nwaves+2;
		for(int j = 2; j < nwaves+2; j++){
			for(int k = j+1; k < nwaves+2; k++){
				mchistxx[j][k]->Scale(scalefactor);
				if(xaxis)
					mchistxx[j][k]->GetXaxis()->SetTitle(xaxis);
				if(yaxis)
					mchistxx[j][k]->GetYaxis()->SetTitle(yaxis);
				result.push_back(mchistxx[j][k]);
				index++;
			}
		}

	}

	delete [] mytitle;

	return result;






}



GPUDataStream<float44> * GPUStreamTensor4::operator()(int index, int block)
{
	assert(index < (int)this->mstream.size());
	assert(block < (int)this->mstream[index].size());
	if(!mtables.size()){
		assert(this->mstream[index][block]);
		return this->mstream[index][block];
	} else {
		if(this->mstream[index][block]){
			return this->mstream[index][block];
		} else {
			CopyBuffer(index,block);
			return this->mstream[index][block];
		}

	}
}

void GPUStreamTensor4::CopyBuffer(int index, int block){
	 assert(index < (int)this->mstream.size());
	 assert(block < (int)this->mstream[index].size());

	 //this->mstream[index][block] = new GPUDataStream<float44>(0,16,GetLength(index,block));
	 //for(unsigned int i=0; i < 16; i++)
	//	 (*this->mstream[index][block])(i)->Read((*mtables[index])(mcolumns[index]+i)+block*GPUDataDependentObject::Blocksize);
	 cout << "Error: Redaing fourth rank tensors from file not implemented, aborting" << endl;
	 assert(0);

}



template class GPUStreamTensor<float>;
template class GPUStreamTensor<float4>;
template class GPUStreamTensor<float44>;
template class GPUStreamTensor<float444>;
template class GPUStreamTensor<float44, float4444>;
