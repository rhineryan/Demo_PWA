

#include "GPUAntisymmetricTensor.h"

GPUAntisymmetricTensor::GPUAntisymmetricTensor(void)
{
  mdata[0].xy().e = mfloat4(0.0f,0.0f,0.0f,1.0f);
  mdata[0].xy().f = mfloat4(0.0f,0.0f,-1.0f,0.0f);
  mdata[0].xz().d = mfloat4(0.0f,0.0f,0.0f,-1.0f);
  mdata[0].xz().f = mfloat4(0.0f,1.0f,0.0f,0.0f);
  mdata[0].xw().d = mfloat4(0.0f,0.0f,1.0f,0.0f);
  mdata[0].xw().e = mfloat4(0.0f,-1.0f,0.0f,0.0f);
 
  mdata[0].yx().e = mfloat4(0.0f,0.0f,0.0f,-1.0f);
  mdata[0].yx().f = mfloat4(0.0f,0.0f,1.0f,0.0f);
  mdata[0].yz().c = mfloat4(0.0f,0.0f,0.0f,1.0f);
  mdata[0].yz().f = mfloat4(-1.0f,0.0f,0.0f,0.0f);
  mdata[0].yw().c = mfloat4(0.0f,0.0f,-1.0f,0.0f);
  mdata[0].yw().e = mfloat4(1.0f,0.0f,0.0f,0.0f);

  mdata[0].zx().d = mfloat4(0.0f,0.0f,0.0f,1.0f);
  mdata[0].zx().f = mfloat4(0.0f,-1.0f,0.0f,0.0f);
  mdata[0].zy().c = mfloat4(0.0f,0.0f,0.0f,-1.0f);
  mdata[0].zy().f = mfloat4(1.0f,0.0f,0.0f,0.0f);
  mdata[0].zw().c = mfloat4(0.0f,1.0f,0.0f,0.0f);
  mdata[0].zw().d = mfloat4(-1.0f,0.0f,0.0f,0.0f);

  mdata[0].wx().d = mfloat4(0.0f,0.0f,-1.0f,0.0f);
  mdata[0].wx().e = mfloat4(0.0f,1.0f,0.0f,0.0f);
  mdata[0].wy().c = mfloat4(0.0f,0.0f,1.0f,0.0f);
  mdata[0].wy().e = mfloat4(-1.0f,0.0f,0.0f,0.0f);
  mdata[0].wz().c = mfloat4(0.0f,-1.0f,0.0f,0.0f);
  mdata[0].wz().d = mfloat4(1.0f,0.0f,0.0f,0.0f);

}


GPUAntisymmetricTensor::~GPUAntisymmetricTensor(void)
{
}


GPUAntisymmetricTensorZeroComponent::GPUAntisymmetricTensorZeroComponent(void)
{


  mdata[0].de = mfloat4(0.0f,0.0f,0.0f,1.0f);
  mdata[0].df = mfloat4(0.0f,0.0f,-1.0f,0.0f);

  mdata[0].ed = mfloat4(0.0f,0.0f,0.0f,-1.0f);
  mdata[0].ef = mfloat4(0.0f,1.0f,0.0f,0.0f);

  mdata[0].fd = mfloat4(0.0f,0.0f,1.0f,0.0f);
  mdata[0].fe = mfloat4(0.0f,-1.0f,0.0f,0.0f);

}


GPUAntisymmetricTensorZeroComponent::~GPUAntisymmetricTensorZeroComponent(void)
{
}
