#include "GPUConstTensor.h"
#include <iostream>

using std::cout;
using std::endl;

template<> GPUConstTensor<float>::GPUConstTensor(void):GPUTensor(0),mdata(1,0)
{
	mdata[0] =0;
//	mlength[0] = -1;
}
template<> GPUConstTensor<float4>::GPUConstTensor(void):GPUTensor(1),mdata(1,float4())
{
	mdata[0].w =0;
	mdata[0].x =0;
	mdata[0].y =0;
	mdata[0].z =0;
//	mlength[0] = -1;
}
template<> GPUConstTensor<float44>::GPUConstTensor(void):GPUTensor(2)
{
	float44 temp;
	float4 zero;
	zero.w =0;
	zero.x =0;
	zero.y =0;
	zero.z =0;
	temp.c = zero;
	temp.d = zero;
	temp.e = zero;
	temp.f = zero;
	mdata.push_back(temp);
//	mlength[0] = -1;
}

template<> GPUConstTensor<float444>::GPUConstTensor(void):GPUTensor(3)
{
	float444 temp;
	float4 zero;
	zero.w =0;
	zero.x =0;
	zero.y =0;
	zero.z =0;
	temp.cc = zero;
	temp.cd = zero;
	temp.ce = zero;
	temp.cf = zero;
	temp.dc = zero;
	temp.dd = zero;
	temp.de = zero;
	temp.df = zero;
	temp.ec = zero;
	temp.ed = zero;
	temp.ee = zero;
	temp.ef = zero;
	temp.fc = zero;
	temp.fd = zero;
	temp.fe = zero;
	temp.ff = zero;
	mdata.push_back(temp);
//	mlength[0] = -1;
}

template<> GPUConstTensor<float4444>::GPUConstTensor(void):GPUTensor(4)
{
  float4444 temp;// = new float4444;
  float4 zero;
  zero.w =0;
  zero.x =0;
  zero.y =0;
  zero.z =0;
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      temp(i,j).c = zero;
      temp(i,j).d = zero;
      temp(i,j).e = zero;
      temp(i,j).f = zero;
    }
    }
  /*for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      cout << temp(i,j).c.x << endl;
    }
    }*/
  mdata.push_back(temp);
//	mlength[0] = -1;
}



template<> GPUConstTensor<float>::GPUConstTensor(float _t):GPUTensor(0),mdata(1,_t)
{
	//mdata[0] = _t;
//	mlength[0] = -1;
}
template<> GPUConstTensor<float4>::GPUConstTensor(float4 _t):GPUTensor(1),mdata(1,_t)
{
	//mdata[0] = _t;
//	mlength[0] = -1;
}
template<> GPUConstTensor<float44>::GPUConstTensor(float44 _t):GPUTensor(2)
{
	mdata.push_back( _t);
//	mlength[0] = -1;
}
template<> GPUConstTensor<float444>::GPUConstTensor(float444 _t):GPUTensor(3)
{
	mdata.push_back( _t);
//	mlength[0] = -1;
}

template<> GPUConstTensor<float4444>::GPUConstTensor(float4444 _t):GPUTensor(4)
{
	mdata.push_back( _t);
//	mlength[0] = -1;
}


template<> void GPUConstTensor<float>::Print(){
  cout << mdata[0] << endl;
}

template<> void GPUConstTensor<float4>::Print(){
  cout <<"(" << mdata[0].x << ", "
       << mdata[0].y << ", " 
       << mdata[0].z << ", "  
       << mdata[0].w << ")" << endl;
}


template<> void GPUConstTensor<float44>::Print(){
  cout <<"((" << mdata[0].c.x << ", "
       << mdata[0].c.y << ", " 
       << mdata[0].c.z << ", "  
       << mdata[0].c.w << ")," << endl;
  cout <<" (" << mdata[0].d.x << ", "
       << mdata[0].d.y << ", " 
       << mdata[0].d.z << ", "  
       << mdata[0].d.w << ")," << endl;
  cout <<" (" << mdata[0].e.x << ", "
       << mdata[0].e.y << ", " 
       << mdata[0].e.z << ", "  
       << mdata[0].e.w << ")," << endl;
  cout <<" (" << mdata[0].f.x << ", "
       << mdata[0].f.y << ", " 
       << mdata[0].f.z << ", "  
       << mdata[0].f.w << "))" << endl;
}


template<> void GPUConstTensor<float444>::Print(){
  cout <<"((" << mdata[0].cc.x << ", "
       << mdata[0].cc.y << ", " 
       << mdata[0].cc.z << ", "  
       << mdata[0].cc.w << ")," << endl;
  cout <<" (" << mdata[0].cd.x << ", "
       << mdata[0].cd.y << ", " 
       << mdata[0].cd.z << ", "  
       << mdata[0].cd.w << ")," << endl;
  cout <<" (" << mdata[0].ce.x << ", "
       << mdata[0].ce.y << ", " 
       << mdata[0].ce.z << ", "  
       << mdata[0].ce.w << ")," << endl;
  cout <<" (" << mdata[0].cf.x << ", "
       << mdata[0].cf.y << ", " 
       << mdata[0].cf.z << ", "  
       << mdata[0].cf.w << "))" << endl;

  cout <<"((" << mdata[0].dc.x << ", "
       << mdata[0].dc.y << ", " 
       << mdata[0].dc.z << ", "  
       << mdata[0].dc.w << ")," << endl;
  cout <<" (" << mdata[0].dd.x << ", "
       << mdata[0].dd.y << ", " 
       << mdata[0].dd.z << ", "  
       << mdata[0].dd.w << ")," << endl;
  cout <<" (" << mdata[0].de.x << ", "
       << mdata[0].de.y << ", " 
       << mdata[0].de.z << ", "  
       << mdata[0].de.w << ")," << endl;
  cout <<" (" << mdata[0].df.x << ", "
       << mdata[0].df.y << ", " 
       << mdata[0].df.z << ", "  
       << mdata[0].df.w << "))" << endl;

  cout <<"((" << mdata[0].ec.x << ", "
       << mdata[0].ec.y << ", " 
       << mdata[0].ec.z << ", "  
       << mdata[0].ec.w << ")," << endl;
  cout <<" (" << mdata[0].ed.x << ", "
       << mdata[0].ed.y << ", " 
       << mdata[0].ed.z << ", "  
       << mdata[0].ed.w << ")," << endl;
  cout <<" (" << mdata[0].ee.x << ", "
       << mdata[0].ee.y << ", " 
       << mdata[0].ee.z << ", "  
       << mdata[0].ee.w << ")," << endl;
  cout <<" (" << mdata[0].ef.x << ", "
       << mdata[0].ef.y << ", " 
       << mdata[0].ef.z << ", "  
       << mdata[0].ef.w << "))" << endl;

  cout <<"((" << mdata[0].fc.x << ", "
       << mdata[0].fc.y << ", " 
       << mdata[0].fc.z << ", "  
       << mdata[0].fc.w << ")," << endl;
  cout <<" (" << mdata[0].fd.x << ", "
       << mdata[0].fd.y << ", " 
       << mdata[0].fd.z << ", "  
       << mdata[0].fd.w << ")," << endl;
  cout <<" (" << mdata[0].fe.x << ", "
       << mdata[0].fe.y << ", " 
       << mdata[0].fe.z << ", "  
       << mdata[0].fe.w << ")," << endl;
  cout <<" (" << mdata[0].ff.x << ", "
       << mdata[0].ff.y << ", " 
       << mdata[0].ff.z << ", "  
       << mdata[0].ff.w << "))" << endl;

}

template<> void GPUConstTensor<float4444>::Print(){
  for(int i=0; i < 16; i++){
    cout <<"((" << mdata[0](i).c.x << ", "
       << mdata[0](i).c.y << ", " 
       << mdata[0](i).c.z << ", "  
       << mdata[0](i).c.w << ")," << endl;
  cout <<" (" << mdata[0](i).d.x << ", "
       << mdata[0](i).d.y << ", " 
       << mdata[0](i).d.z << ", "  
       << mdata[0](i).d.w << ")," << endl;
  cout <<" (" << mdata[0](i).e.x << ", "
       << mdata[0](i).e.y << ", " 
       << mdata[0](i).e.z << ", "  
       << mdata[0](i).e.w << ")," << endl;
  cout <<" (" << mdata[0](i).f.x << ", "
       << mdata[0](i).f.y << ", " 
       << mdata[0](i).f.z << ", "  
       << mdata[0](i).f.w << "))" << endl;
  }
}
