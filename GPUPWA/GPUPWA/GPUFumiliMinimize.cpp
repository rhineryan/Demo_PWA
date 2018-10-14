#include "GPUFumiliMinimize.h"
#include "GPUPartialWaveAnalysis.h"

GPUFumiliMinimize* gThisIsWrappedThis = NULL;
extern void FitLikelihoodFumili(int &npar, double *gin, double &f, double *u, int flag);
GPUFumiliMinimize::GPUFumiliMinimize(GPUPWACalculator * _calc): TFumili((int)_calc->GetAnalysis()->GetParameters()->Params().size()),mCalc(_calc)
{

    InitAndReset((int)mCalc->GetAnalysis()->GetParameters()->Params().size());

}

GPUFumiliMinimize::~GPUFumiliMinimize(void)
{
}
void GPUFumiliMinimize::SetFitMethod()
{
    // if(gThisIsWrappedThis == NULL)
    gThisIsWrappedThis = this;
    // else
    //  printf("Can't assign 'this' - other object trying to fit\n");
    SetFCN(FitLikelihoodFumili);
}
void GPUFumiliMinimize::SetParameters()
{
    vector<ROOT::Minuit2::MinuitParameter> initpars;
    initpars=mCalc->GetAnalysis()->GetParameters()->Parameters() ;
    for(int i=0;i<(int)mCalc->GetAnalysis()->GetParameters()->Params().size();i++)
    {
        SetParameter(i,initpars[i].Name(),initpars[i].Value(),initpars[i].Error(),initpars[i].UpperLimit(),initpars[i].LowerLimit());
        if(mCalc->GetAnalysis()->GetParameters()->Parameter(i).IsFixed())FixParameter(i);
        //	printf("%d,%f,%f,%f,%f,%d\n",i,initpars[i].Value(),initpars[i].Error(),initpars[i].UpperLimit(),initpars[i].LowerLimit(),mCalc->GetAnalysis()->GetParameters()->Parameter(i).IsFixed());
    }
}
const ROOT::Minuit2::MnUserParameters GPUFumiliMinimize::GetParameters() const
{
    //	TFumili::GetParameter(Int_t ipar,char *cname,Double_t &value,Double_t &verr,Double_t &vlow, Double_t &vhigh)
    char cname[255];
    double value;
    double verr;
    double vlow;
    double vhigh;
    ROOT::Minuit2::MnUserParameters resultpars;
    for(int i=0;i<(int)mCalc->GetAnalysis()->GetParameters()->Params().size();i++)
    {
        GetParameter(i,cname,value,verr,vlow, vhigh);
        resultpars.Add(cname  , value, verr, vlow, vhigh);
    }
    return resultpars;
}
double GPUFumiliMinimize::EvalTFN(double * /*df*/, double *X)
{
    // Evaluate theoretical function
    // df: array of partial derivatives
    // X:  vector of theoretical function argument

    // for the time being disable possibility to compute derivatives
    //if(fTFN)
    //  return (*fTFN)(df,X,fA);
    //else if(fTFNF1) {

    for(int i=0;i<(int)mNpar;i++)
    {
        mPara[i]=X[i];
        //printf("para[%d]= %f\n",i,mPara[i]);
    }
    return mCalc->Likelihood(mPara);
    //}
    //return 0.;
}


void GPUFumiliMinimize::FitLikelihood(int &npar, double *gin, double &f, double *u, int flag)
{


    double *zik = GetZ();
    double *pl0 = GetPL0();




    for(int i=0;i<(int)mNpar;i++)
    {
        mPara[i]=u[i];
        //printf("para[%d]= %f\n",i,mPara[i]);
    }
    if(flag == 9) return;
    if (flag == 2) for (int j=0;j<(int)mNpar;j++) gin[j] = 0;

    f=mCalc->LikelihoodGradientHessian(mPara,mGrad, mHess);
    int l=0;
    for(int i=0;i<(int)mNpar;i++)
    {
        gin[i]=mGrad[i];
        //printf("grad= %f\n",mGrad[i]);
        //	for(unsigned int j =i; j < mNpar; j++){
        for(int j =0; j <=i; j++){
            //	printf("i,j= %d, %d, %d, ",i,j,j+i*(i+1)/2);
            //	printf("hess= %f ",mHess[j+i*(i+1)/2]);
            //printf("Hess= %f\n",GetCovarianceMatrix() [i+j*(j+1)/2]);
            //		zik[i+j*(j+1)/2]=mHess[i+j*(j+1)/2];
            if(pl0[i]>0&&pl0[j]>0){
                zik[l++]=mHess[j+i*(i+1)/2];
            }

        }
        //	printf("\n");
    }
    //for(int i=0;i<l;i++)
    //printf("zik[%d]= %f\n",i,zik[i]);
    //double amin; double edm; double errdef; int nvpar; int nparx;
    //GetStats(amin, edm, errdef, nvpar, nparx);
    //printf("stats: %f, %f, %f, %d, %d \n",amin, edm, errdef, nvpar, nparx);
}
void FitLikelihoodFumili(int &npar, double *gin, double &f, double *u, int flag)
{

    // use the global variable to access the object.
    gThisIsWrappedThis->FitLikelihood(npar, gin, f, u, flag);
    // free global, so that other objects
    //can use it.
    // gThisIsWrappedThis = NULL;
}
//void GPUFumiliMinimize::EvaluateAll(const std::vector<double> & par){
//	EvaluateConst(par);
//
//}


//void GPUFumiliMinimize::EvaluateConst(const std::vector<double> & par) const{
//	fValue = mCalc->LikelihoodGradientHessian(par,fGradient, fHessian);
//
//}

//double GPUFumiliMinimize::operator() (const vector<double> & x) const{
//	EvaluateConst(x);
//	//cout << fValue << endl;
//	return fValue;
//}
