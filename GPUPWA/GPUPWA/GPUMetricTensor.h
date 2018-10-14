/// \file GPUMetricTensor.h

#pragma once
#include "GPUConstTensor.h"

///Class representing the metric tensor
/** In GPUPWA, we use a convention where the metric tensor is \f$ g_{\mu\nu} 
    = \left(\begin{array}{cccc} -1 & 0 & 0 & 0 \\
                      0 &-1 & 0 & 0 \\
		      0 & 0 &-1 & 0 \\
		      0 & 0 & 0 & 1 \end{array}\right)
\f$

*/
class GPUMetricTensor:
	public GPUConstTensor2
{
public:
  ///Constructor, setting up the metric tensor
  GPUMetricTensor();
  /// Destructor     
  virtual ~GPUMetricTensor();
};
