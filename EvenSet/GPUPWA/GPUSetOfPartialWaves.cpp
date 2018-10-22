#include "GPUSetOfPartialWaves.h"
#include "GPUPartialWaveAnalysis.h"


GPUSetOfPartialWaves::GPUSetOfPartialWaves(GPUPartialWaveAnalysis* _list):GPUDataDependentObjectList(_list),mAnalysis(_list)
{
}


GPUSetOfPartialWaves::~GPUSetOfPartialWaves(void)
{
}

// Handling constituent partial waves
unsigned int GPUSetOfPartialWaves::AddPartialWave(GPUPartialWave & _wave){
	unsigned int parcount =0;
	const ConfigFile * pf = mAnalysis->GetParameterFile();
	const ConfigFile * rf = mAnalysis->GetResonanceFile();
	if(_wave.GetMagnitudeParameter() == 999){
		ParaCfg pcf;
		char * pname = _wave.GetParameterName(0);
		//cout << "Looking for " << pname << endl;
		if(!pf->readInto(pcf, pname)){
			cout << "Input value for " << pname << " not found, aborting!" << endl;
			exit(-1);
		}
		int index = mAnalysis->AddParameter(pname, pcf.v, pcf.e);
		if(pcf.e < 0){
			mAnalysis->FixParameter(index);
			if(pcf.v == 0.0)
				_wave.SetActive(false);
		}
		else {
			if(pcf.l != 999 && pcf.u != 999){
				mAnalysis->LimitParameter(index,pcf.l , pcf.u);
			} else  if(pcf.l != 999) {
				mAnalysis->LimitParameterLow(index, pcf.l);
			} else if(pcf.u != 999){
				mAnalysis->LimitParameterHigh(index, pcf.u);
			}
		}
		_wave.SetMagnitudeParameter(index);
		parcount++;
	}
	//cout << "After mag" << parcount << endl;
	if(_wave.GetPhaseParameter() == 999)	{
		ParaCfg pcf;
		char * pname = _wave.GetParameterName(1);
		//cout << "Looking for " << pname << endl;
		if(!pf->readInto(pcf, pname)){
			cout << "Input value for " << pname << " not found, aborting!" << endl;
			exit(-1);
		}
		int index = mAnalysis->AddParameter(pname, pcf.v, pcf.e);
		if(pcf.e < 0)
			mAnalysis->FixParameter(index);
		else {
			if(pcf.l != 999 && pcf.u != 999){
				mAnalysis->LimitParameter(index,pcf.l , pcf.u);
			} else  if(pcf.l != 999) {
				mAnalysis->LimitParameterLow(index, pcf.l);
			} else if(pcf.u != 999){
				mAnalysis->LimitParameterHigh(index, pcf.u);
			}
		}
		//cout << "Phase parameter set to " << index << endl;
		_wave.SetPhaseParameter(index);
		parcount++;
	}
	//cout << "After phase" << parcount << endl;
	//std::vector<unsigned int *> dpars;
	//cout << "size: " << _wave.GetDynamicParameters().size() << endl;
	for(unsigned int i =0; i < _wave.GetDynamicParameters().size(); i++){
		//cout << _wave.GetPropagator().GetParameterName(i) << endl;
		if(_wave.GetDynamicParameter(i) == 999){
			char * pname = _wave.GetDynamicParameterName(i);
			std::map<std::string,int>::iterator it = mResonanceDynamicParameters.find(pname);
			if(it != mResonanceDynamicParameters.end()){
				unsigned int parnum = it->second;
				_wave.SetDynamicParameter(i,parnum);
				//unsigned int * x = new unsigned int;
				//*x = parnum;
				//dpars.push_back(x);
				//dpars.push_back(_wave.GetDynamicParameters()[i]);
			} else {
				//char name[20];
				//sprintf(name,"%.15s%s", _wave.GetPropagator().GetParameterName(i),"_m");
				//char fname[64];
				//sprintf(fname,"%s%s", _wave.GetPropagator().GetName(i),"_mass");
				ParaCfg pcf;
				if(!rf->readInto(pcf, pname)){
					cout << "Input value for " << pname << " not found, aborting!" << endl;
					exit(-1);
				}
				int index = mAnalysis->AddParameter(pname, pcf.v, pcf.e);
				if(pcf.e < 0)
					mAnalysis->FixParameter(index);
				else {
					if(pcf.l != 999 && pcf.u != 999){
						mAnalysis->LimitParameter(index,pcf.l , pcf.u);
					} else  if(pcf.l != 999) {
						mAnalysis->LimitParameterLow(index, pcf.l);
					} else if(pcf.u != 999){
						mAnalysis->LimitParameterHigh(index, pcf.u);
					}
				}
				//unsigned int * x = new unsigned int;
				//*x = index;
				_wave.SetDynamicParameter(i, index);
				//dpars.push_back(_wave.GetDynamicParameters()[i]);
				mResonanceDynamicParameters.insert(
						std::map<std::string,int>::value_type(pname,index));
				parcount++;
			}
		} else {
			//dpars.push_back(_wave.GetDynamicParameters()[i]);
		}
	}
	//cout << "After mass" << parcount << endl;
	//_wave.SetDynamicParameters(dpars);
	//mAnalysis->SetParameter(mAnalysis->GetParameters()->Index(name), _wave.GetPropagator().GetMass());
	//cout << "After set dynamic parameters..." << endl;
	//for(int i =0; i< _wave.GetDynamicParameters().size(); i++)
	//	cout << _wave.GetDynamicParameters()[i] << endl;

	//cout << "size: " << _wave.GetWidthParameters().size() << endl;
	//for(unsigned int i =0; i < _wave.GetWidthParameters().size(); i++){
		//cout << _wave.GetWidthParameters()[i] << endl;

	//}
	//cout << "After width" << parcount << endl;
	// This wave is the result of a calculation - different cache behaviour
	//_wave.GetTensor().SetResult();
	//cout << mAnalysis->GetParameters()->Params().size() << endl;
	mPartialWaves.push_back(&_wave);

	return parcount;
}


void GPUSetOfPartialWaves::RemovePartialWave(int _n){
	mPartialWaves.erase(mPartialWaves.begin()+_n);
}


void GPUSetOfPartialWaves::RemovePartialWave(char * _name){
	int index = FindPartialWave(_name);
	if(index >= 0)
		mPartialWaves.erase(mPartialWaves.begin()+index);
}


GPUPartialWave * GPUSetOfPartialWaves::GetPartialWave(int _n) const{
	return mPartialWaves[_n];
}


GPUPartialWave * GPUSetOfPartialWaves::GetPartialWave(char * _name) const{
	int index = FindPartialWave(_name);
	if(index >= 0)
		return mPartialWaves[index];
	else
		return 0;
}

int GPUSetOfPartialWaves::FindPartialWave(char * _name) const{
	int n =0;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		if(! strcmp(_name, (*it)->GetName()))
			return n;
		n++;
	}
	cout << "Partial wave " << _name << " not found!" << endl;
	return -1;
}


void GPUSetOfPartialWaves::SetActive(int _n, bool _active){
	mPartialWaves[_n]->SetActive(_active);
}

void GPUSetOfPartialWaves::SetInactive(int _n){
	mPartialWaves[_n]->SetActive(false);
}

void GPUSetOfPartialWaves::SetActive(char * _name, bool _active){
	int index = FindPartialWave(_name);
	if(index >= 0)
		mPartialWaves[index]->SetActive(_active);
}

void GPUSetOfPartialWaves::SetInactive(char * _name){
	int index = FindPartialWave(_name);
	if(index >= 0)
		mPartialWaves[index]->SetActive(false);
}

bool GPUSetOfPartialWaves::Active(int _n) const{
	return mPartialWaves[_n]->Active();
}

bool GPUSetOfPartialWaves::Active(char * _name) const{
	int index = FindPartialWave(_name);
	if(index >= 0)
		return mPartialWaves[index]->Active();
	return false;
}

int GPUSetOfPartialWaves::GetNWaves() const {
	return (int)mPartialWaves.size();
}

int GPUSetOfPartialWaves::GetNActiveWaves() const{
	int n = 0;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		if((*it)->Active())
			n++;
	}
	return n;
}

int GPUSetOfPartialWaves::GetNInactiveWaves() const{
	int n = 0;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		if(!((*it)->Active()))
			n++;
	}
	return n;
}

vector<GPUPartialWave *> GPUSetOfPartialWaves::GetWaves() const{
	return mPartialWaves;
}

vector<GPUPartialWave *> GPUSetOfPartialWaves::GetActiveWaves() const{
	vector<GPUPartialWave *> temp;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		if((*it)->Active())
			temp.push_back((*it));
	}
	return temp;
}

std::vector<char *> GPUSetOfPartialWaves::GetWaveNames() const{
	std::vector<char *> ret;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		ret.push_back((*it)->GetName());
	}
	return ret;
}

std::vector<char *> GPUSetOfPartialWaves::GetActiveWaveNames() const{
	std::vector<char *> ret;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		if((*it)->Active())
			ret.push_back((*it)->GetName());
	}
	return ret;
}


std::vector<unsigned int> GPUSetOfPartialWaves::GetMagnitudeParameters() const{
	std::vector<unsigned int> ret;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		ret.push_back((*it)->GetMagnitudeParameter());
	}
	return ret;
}

std::vector<unsigned int> GPUSetOfPartialWaves::GetPhaseParameters() const{
	std::vector<unsigned int> ret;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		ret.push_back((*it)->GetPhaseParameter());
	}
	return ret;
}


std::vector<unsigned int *> GPUSetOfPartialWaves::GetDynamicParameters() const{
	std::vector<unsigned int *> ret;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		std::vector<unsigned int *> pars = (*it)->GetDynamicParameters();
		for(unsigned int i =0; i < pars.size(); i++)
			ret.push_back(pars[i]);
	}
	return ret;
}

std::vector<unsigned int> GPUSetOfPartialWaves::GetNDynamicParameters() const{
	std::vector<unsigned int> ret;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		ret.push_back((*it)->GetNDynamicParameters());
	}
	return ret;
}



std::vector<unsigned int> GPUSetOfPartialWaves::GetActiveMagnitudeParameters() const{
	std::vector<unsigned int> ret;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		if((*it)->Active())
			ret.push_back((*it)->GetMagnitudeParameter());
	}
	return ret;
}

std::vector<unsigned int> GPUSetOfPartialWaves::GetActivePhaseParameters() const{
	std::vector<unsigned int> ret;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		if((*it)->Active())
			ret.push_back((*it)->GetPhaseParameter());
	}
	return ret;
}

std::vector<unsigned int *> GPUSetOfPartialWaves::GetActiveDynamicParameters() const{
	std::vector<unsigned int *> ret;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		if((*it)->Active()){
			std::vector<unsigned int *> pars = (*it)->GetDynamicParameters();
			for(unsigned int i =0; i < pars.size(); i++)
				ret.push_back(pars[i]);
		}
	}
	return ret;
}


std::vector<unsigned int> GPUSetOfPartialWaves::GetNActiveDynamicParameters() const{
	std::vector<unsigned int> ret = * new std::vector<unsigned int>();
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		if((*it)->Active()){
			ret.push_back( (*it)->GetNDynamicParameters());
		}
	}
	return ret;
}

std::vector<char **> GPUSetOfPartialWaves::GetActiveDynamicParameterNames() const{
	std::vector<char **> ret;
	vector<GPUPartialWave *>::const_iterator it;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		if((*it)->Active()){
			std::vector<char **> pars = (*it)->GetDynamicParameterNames();
			for(unsigned int i =0; i < pars.size(); i++)
				ret.push_back(pars[i]);
		}
	}
	return ret;
}


void GPUSetOfPartialWaves::SetUsecount(int index) {
	vector<GPUPartialWave *>::const_iterator it;
		for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
			if((*it)->Active()){
				(*it)->IncreaseUsecount(index);
			}
		}
}

void GPUSetOfPartialWaves::SetUsecountOrbital(int index) {
	vector<GPUPartialWave *>::const_iterator it;
		for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
			if((*it)->Active()){
				(*it)->IncreaseUsecountOrbital(index);
			}
		}
}

bool GPUSetOfPartialWaves::HasOrbitalContraction() {
	vector<GPUPartialWave *>::const_iterator it;
	vector<GPUPartialWave *>::const_iterator it2;
	bool contractable = true;
	for(it = mPartialWaves.begin(); it < mPartialWaves.end(); ++it){
		if((*it)->Active()){
			for(it2 = it; it2 < mPartialWaves.end(); ++it2){
				if((*it2)->Active()){
					contractable = contractable && (*it)->HasContractOrbital(*it2);
				}
			}
		}
	}
	return contractable;
}


