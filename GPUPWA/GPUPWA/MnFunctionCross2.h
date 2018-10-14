// @(#)root/minuit2:$Id: MnFunctionCross2.h,v 1.2 2008/12/19 05:36:23 nberger Exp $
// Authors: M. Winkler, F. James, L. Moneta, A. Zsenei   2003-2005  

/**********************************************************************
 *                                                                    *
 * Copyright (c) 2005 LCG ROOT Math team,  CERN/PH-SFT                *
 *                                                                    *
 **********************************************************************/

#ifndef ROOT_Minuit2_MnFunctionCross
#define ROOT_Minuit2_MnFunctionCross

#include "Minuit2/MnConfig.h"
#include <vector>

namespace ROOT {

   namespace Minuit2 {



class FCNBase;
class MnUserParameterState;
class MnStrategy;
class MnCross;

/*
   MnFunctionCross2 
*/

class MnFunctionCross2 {

public:
  
  MnFunctionCross2(const FCNBase& fcn, const MnUserParameterState& state, double fval, const MnStrategy& stra) : fFCN(fcn), fState(state), fFval(fval), fStrategy(stra) {} 
  
  ~MnFunctionCross2() {}
  
  MnCross operator()(const std::vector<unsigned int>&, const std::vector<double>&, const std::vector<double>&, double, unsigned int) const;

private:

  const FCNBase& fFCN;
  const MnUserParameterState& fState;
  double fFval;
  const MnStrategy& fStrategy;
};

  }  // namespace Minuit2

}  // namespace ROOT

#endif  // ROOT_Minuit2_MnFunctionCross
