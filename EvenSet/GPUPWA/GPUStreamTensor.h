/// \file GPUStreamTensor.h
#pragma once
#include "GPUTensor.h"
#include "float44.h"
#include "float444.h"
#include "float4444.h"
#include "GPUDataDependentObjectType.h"
#include "GPUDataDependentObjectList.h"
#include "GPUDataStream.h"
#include "GPUFileTable.h"
#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include <cassert>
#include <vector>

using std::cout;
using std::endl;


/// Base Class for streams of Tensors on the GPU
/** Tensor where data are a stream for/on the GPU
the data can either be raw input data or computed data
on the GPU/ data to be computed on the GPU. The fact
that this class can be used in Tensor calculations makes
it a GPUTensor, whilst the caching mechanism requires it
to be a GPUDataDependentObject. This is one of the very few
places where we use multiple inheritance in GPUPWA**/
template <typename T, typename LT = T>
class GPUStreamTensor :
public GPUTensor, public GPUDataDependentObjectType<T>
{
public:
  /// Default constructor
  GPUStreamTensor(GPUDataDependentObjectList *_list, ///< GPUDataDependentObjectList where this tensor is to be registered for caching
				  bool init = true                   ///< init the streams with 0; set to false for streams with their own init
  );
  /// Constructor for a GPUStreamTensor taking its contents from a GPUFileTable
  GPUStreamTensor(GPUDataDependentObjectList *_list,   ///< GPUDataDependentObjectList where this tensor is to be registered for caching
				 std::vector<GPUFileTable<LT> *> _tables,    ///< Vector of GPUFileTable objects holding the information represented by this Tensor, usually with two elements, one for data, one for MC
				 std::vector<unsigned int> _columns         ///< Vector of columns in the GPUFileTable to take the data from
  );
  /// Destructor
  virtual ~GPUStreamTensor(void) =0;
  /// () operator; performs the actual calculation, if necessary
  virtual GPUDataStream<T> * operator()(int index =0, int block =0);
  /// Copy data from a GPUFileTable to the GPU
  virtual void CopyBuffer(int index, int block);
  /// Get the rank of this tensor
 static int GetRank() {
	  unsigned int nelements = sizeof(T)/sizeof(float);
	  switch (nelements){
	  case 1:
		  return 0;
	  case 4:
		  return 1;
	  case 16:
		  return 2;
	  case 64:
		  return 3;
	  case 256:
		  return 4;
	  default:
		  assert(0);
		  return -1;
	  }
  };


  /// Read the stream to memory and print contents
  /** This function is implemented by derived classes, when the size of a stream element is known **/
  virtual void Print(int nelemnets = 0, ///< Number of elements to print
		     std::ostream & output = std::cout, ///< Stream to write to, default is cout
		     int index =0, ///< Index to read
		     int block =0)=0; ///< Block to read


 protected:
  /// Protected constructor; allows derived objects to implement their
  /// own registration mechanism
  GPUStreamTensor();
  /// Pointers to GPUFileTables for objects taking their data from a file
  std::vector<GPUFileTable<LT> *> mtables;
  /// Columns in the file tables object
  std::vector<unsigned int> mcolumns;
};

/// GPUStreamTensor holding a scalar
/** Note that scalar here implies a single number and not necessarily a scalar under Lorentz transformations.
    The latter condition should however be fulfilled if the object is to be used in the covariant tensor
    formalism. For plots etc, non-invariant quantities can however use the same data structure */
class GPUStreamScalar: public GPUStreamTensor<float> {
public:
  /// Constructor for a constant scalar stream (same number for all events)
  GPUStreamScalar(GPUDataDependentObjectList *_list, ///<GPUDataDependentObjectList where the scalar is registered for cache handling
		  float value ///< Value to be filled in
		 );
  /// Constructor for a scalar based on GPUFileTable data
  GPUStreamScalar(GPUDataDependentObjectList *_list, ///<GPUDataDependentObjectList where the scalar is registered for cache handling
		  std::vector<GPUFileTable<float> *> _tables,    ///< Vector of GPUFileTable objects holding the information represented by this Tensor, usually with two elements, one for data, one for MC
		  std::vector<unsigned int> _columns         ///< Vector of columns in the GPUFileTable to take the data from
  ):GPUStreamTensor<float>(_list, _tables, _columns),mResetable(true){};
  /// Constructor
  GPUStreamScalar(GPUDataDependentObjectList *_list, bool init=true): GPUStreamTensor<float>(_list, init), mResetable(true){};
  /// Destructor
  virtual ~GPUStreamScalar(void){};
  /// Read the stream to memory and print contents
  /** Print nelements, for nelements < 1, all elemnts are printed, in the second argument,
      a different output stream can be specified, default is cout */
  virtual void Print(int nelemnets = 0, std::ostream & output = std::cout, int index =0, int block =0);
  // Read the stream to memory
  //virtual float * Read(int index =0);
  /// Write the stream from an array
  void Write(float * _data, int elements, int index =0){
    assert((int)mstream.size() > index);
    //mlength[index].clear();
    for(int i=0; i < (int)mstream[index].size(); i++){
      if(mstream[index][i])
    	  delete mstream[index][i];
      mstream[index][i]=0;
    }
    mstream[index].clear();
    int offset =0;
    int block =0;
    while(elements > 0){
      if(elements > Blocksize){
    	  //mlength[index].push_back(Blocksize);
    	  mstream[index].push_back( new GPUDataStream<float>(mList->GetDeviceInterface(), Blocksize));
    	  elements -= Blocksize;
      } else {
	//mlength[index].push_back(elements);
    	  GetLength(index, block);
    //	  cout << GetLength(index, block) << " elements " << elements << endl;
    	  assert(GetLength(index, block) == elements);

    	  mstream[index].push_back(new GPUDataStream<float>(mList->GetDeviceInterface(),elements));
    	  elements -= Blocksize;
      }
      (mstream[index].back())->Write(_data+offset);
      offset += Blocksize;
      block++;
    }
  }
  ///Create a vector of plots of this scalar
  /** The vector returned will contain:
      - the data histogram at index 0
      - the MC histogram (phase space weighted with the differential cross sections from dcs and normalized to data
      at index 1

      If nwaves is > 0
      - The contribution of each wave (MC) at index waveindex+2

      If dooffdiagonal == true
      - The interference terms (MC) at indices starting from nwaves+2 in upper diagonal form ( (0,0), (0,1), (0,2) ...
      (1,1), (1,2) ... (2,2)... )*/
  virtual vector<TH1F*> Plot(char * id, ///< Histogram ID for Root
			     char * title, ///< Histogram title. Can contain axis labels after semicolons ("Momentumplot;p[Gev];Events")
			     int nbins, ///< Number of bins in Histogram
			     double min, ///< Left edge of x axis
			     double max, ///< Right edge of x axis
			     float ** dcs, ///< Array with differential x-sections
			     int nwaves =0, ///< Number of waves, if 0, just the integrated result is plotted
			     bool dooffdiagonal = false, ///< Plot interference terms or not
			     float * weights = 0, ///< Event weigths to use in the plots
			     int dataindex =0, ///< Stream containig the data
			     int mcindex =1,  ///<Stream with the phase space MC
			     int nblocks = -1 ///< Maximum number of MC blocks to plot
			     );

  ///Create a vector of 2D plots of this scalar
   /** The vector returned will contain:
       - the data histogram at index 0
       - the MC histogram (phase space weighted with the differential cross sections from dcs and normalized to data
       at index 1

       If nwaves is > 0
       - The contribution of each wave (MC) at index waveindex+2

       If dooffdiagonal == true
       - The interference terms (MC) at indices starting from nwaves+2 in upper diagonal form ( (0,0), (0,1), (0,2) ...
       (1,1), (1,2) ... (2,2)... )*/
  virtual vector<TH2F*> Plot(char * id, ///< Histogram ID for Root
  			     char * title, ///< Histogram title. Can contain axis labels after semicolons ("Momentumplot;p[Gev];Events")
  			     int nbinsx, ///< Number of x bins in Histogram
  			     double xmin, ///< Left edge of x axis
  			     double xmax, ///< Right edge of x axis
  			     int nbinsy, ///< Number of y bins in Histogram
  			  	 double ymin, ///< Left edge of y axis
  			  	 double ymax, ///< Right edge of y axis
  			  	 GPUStreamScalar & yvar, ///< second variable for 2D histo
  			     float ** dcs, ///< Array with differential x-sections
  			     int nwaves =0, ///< Number of waves, if 0, just the integrated result is plotted
  			     bool dooffdiagonal = false, ///< Plot interference terms or not
  			     float * weights = 0, ///< Event weigths to use in the plots
  			     int dataindex =0, ///< Stream containig the data
  			     int mcindex =1,  ///<Stream with the phase space MC
  			     int nblocks = -1 ///< Maximum number of MC blocks to plot
  			     );


  /// Reset the Stream
  virtual void Reset(int index, int block = -1){
	if(block == -1)
		ResetUsecount(index);
    if(mResetable){
     if(block == -1){
    	  if((int)mstream.size() > index){
    		  for(int j=0; j < (int)mstream[index].size(); j++){
    			  if(mstream[index][j])
    				  delete mstream[index][j];
    			  mstream[index][j] =0;
    			  //mlength[index][j] =0;
    		  }
    		  ResetUsecount(index);
    	  }
      } else {
    	  if((int)mstream.size() > index){
    		  if((int)mstream[index].size() > block){
    			  if(mstream[index][block])
    				  delete mstream[index][block];
    			  mstream[index][block] =0;
    			 // mlength[index][block] =0;
    			  ResetUsecount(index,block);
    		  }
    	  }
      }
    }
  };

 protected:
  /// Protected constructor; allows derived objets to implement their
  /// own registration mechanism
  GPUStreamScalar():GPUStreamTensor<float>(),mResetable(true){};
    /// Read a block to memory
    virtual float * ReadBlock(int index, int block);
    ///Save whether we can reset this stream or not
      const bool mResetable;
};


/// Class represnting a stream of four-vectors (float4s)
/** As you might have seen, there is no public constructor, i.e. you as the user are not allowed to
    create GPUStreamVectors. This is in order to ensure that only derived objects, which also know
    how to calculate the contents of the vector are actually instantiated.

    Note that four-vector here implies just four numbers and not necessarily a vector or covector under
    Lorentz transformations. The latter condition should however be fulfilled if the object is to be
    used in the covariant tensor formalism. Forother purposes, non-Lorentzian quantities can however use
    the same data structure. */
class GPUStreamVector: public GPUStreamTensor<float4> {
public:
	/// Constructor for a vector based on GPUFileTable data
	 GPUStreamVector(GPUDataDependentObjectList *_list, ///<GPUDataDependentObjectList where the vector is registered for cache handling
			  std::vector<GPUFileTable<float4> *> _tables,    ///< Vector of GPUFileTable objects holding the information represented by this Tensor, usually with two elements, one for data, one for MC
			  std::vector<unsigned int> _columns         ///< Vector of columns in the GPUFileTable to take the data from
	  ):GPUStreamTensor<float4>(_list, _tables, _columns){};;
  /// Destructor
  virtual ~GPUStreamVector(void){};
  /// Read the stream to memory and print contents
  /** Print nelements, for nelements < 1, all elemnts are printed, in the second argument,
      a different output stream can be specified, default is cout */
  virtual void Print(int nelemnets = 0, std::ostream & output = std::cout, int index =0, int block=0);
  // Read the stream to memory
  //virtual float4 * Read(int index =0);
  /// Write the stream from an array
  void Write(float4 * _data, int elements, int index =0){
    assert((int)mstream.size() > index);
    //mlength[index].clear();
    for(int i=0; i < (int)mstream[index].size(); i++){
      if(mstream[index][i])
    	  delete mstream[index][i];
      mstream[index][i] =0;
    }
    mstream[index].clear();
    musecount[index].clear();
    int offset =0;
    while(elements > 0){
      if(elements > Blocksize){
	//mlength[index].push_back(Blocksize);
	mstream[index].push_back(new GPUDataStream<float4>(mList->GetDeviceInterface(),Blocksize));
	musecount[index].push_back(0);
	elements -= Blocksize;
      } else {
	//mlength[index].push_back(elements);
    assert(GetLength(index) == elements);
	mstream[index].push_back(new GPUDataStream<float4>(mList->GetDeviceInterface(),elements));
	musecount[index].push_back(0);
	elements -= Blocksize;
      }
      (mstream[index].back())->Write(_data+offset);
      offset += Blocksize;
    }

  }
 protected:
  /// Protected constructor; allows derived objets to implement their
  /// own registration mechanism
  GPUStreamVector():GPUStreamTensor<float4>(){};
    /// Constructor
    GPUStreamVector(GPUDataDependentObjectList *_list, bool init=true): GPUStreamTensor<float4>(_list, init){};
    /// Read a block of the stream to memory
   	 virtual float4 * ReadBlock(int index =0, int block =0);
};

/// Class represnting a stream of second rank tensors
/** As you might have seen, there is no public constructor, i.e. you as the user are not allowed to
    create GPUStreamTensor2. This is in order to ensure that only derived objects, which also know
    how to calculate the contents of the tensor are actually instantiated.

    The sixteen elements of the second rank tensor are internally represented as 4 float4s in a float44
    structure.

    Note that tensor here implies just sixteen numbers and not necessarily a tensor under
    Lorentz transformations. The latter condition should however be fulfilled if the object is to be
    used in the covariant tensor formalism. For other purposes, non-Lorentzian quantities can however use
    the same data structure. */
class GPUStreamTensor2: public GPUStreamTensor<float44> {
public:
	/// Constructor for a vector based on GPUFileTable data
	GPUStreamTensor2(GPUDataDependentObjectList *_list, ///<GPUDataDependentObjectList where the tensor is registered for cache handling
				  std::vector<GPUFileTable<float44> *> _tables,    ///< Vector of GPUFileTable objects holding the information represented by this Tensor, usually with two elements, one for data, one for MC
				  std::vector<unsigned int> _columns         ///< Vector of columns in the GPUFileTable to take the data from
		  ):GPUStreamTensor<float44>(_list, _tables, _columns){};;
	/// Destructor
	virtual ~GPUStreamTensor2(void){};
	/// Read the stream to memory and print contents
	/** Print nelements, for nelements < 1, all elemnts are printed, in the second argument,
	a different output stream can be specified, default is cout */
	virtual void Print(int nelemnets = 0, std::ostream & output = std::cout, int index =0, int block=0);
	// Read the stream to memory
	//virtual float44 * Read(int index =0);
	/// Write the stream from an array
	void Write(float44 * _data, int elements, int index =0){
		assert((int)mstream.size() > index);
		//mlength[index].clear();
		for(int i=0; i < (int)mstream[index].size(); i++){
			if(mstream[index][i])
				delete mstream[index][i];
			mstream[index][i] =0;
		}
		mstream[index].clear();
		musecount[index].clear();
		int offset =0;
		while(elements > 0){
			if(elements > Blocksize){
				//mlength[index].push_back(Blocksize);
				mstream[index].push_back(new GPUDataStream<float44>(mList->GetDeviceInterface(),Blocksize));
				musecount[index].push_back(0);
				elements -= Blocksize;
			} else {
				assert(GetLength(index) == elements);
				//mlength[index].push_back(elements);
				mstream[index].push_back(new GPUDataStream<float44>(mList->GetDeviceInterface(),elements));
				musecount[index].push_back(0);
				elements -= Blocksize;
			}
			(mstream[index].back())->Write(_data+offset);
			offset += Blocksize;
		}
	}
protected:
	/// Protected constructor; allows derived objets to implement their
	/// own registration mechanism
	GPUStreamTensor2():GPUStreamTensor<float44>(){};
	/// Constructor
	GPUStreamTensor2(GPUDataDependentObjectList *_list, bool init=true): GPUStreamTensor<float44>(_list, init){};
	/// Read a block of the stream to memory
	virtual float44 * ReadBlock(int index =0, int block =0);
};

/// Class representing a stream of third rank tensors
/** As you might have seen, there is no public constructor, i.e. you as the user are not allowed to
    create GPUStreamTensor3. This is in order to ensure that only derived objects, which also know
    how to calculate the contents of the tensor are actually instantiated.

    Note that tensor here implies just sixty four numbers and not necessarily a tensor under
    Lorentz transformations. The latter condition should however be fulfilled if the object is to be
    used in the covariant tensor formalism. For other purposes, non-Lorentzian quantities can however use
    the same data structure. */
class GPUStreamTensor3: public GPUStreamTensor<float444> {
public:
	/// Constructor for a vector based on GPUFileTable data
	GPUStreamTensor3(GPUDataDependentObjectList *_list, ///<GPUDataDependentObjectList where the tensor is registered for cache handling
					  std::vector<GPUFileTable<float444> *> _tables,    ///< Vector of GPUFileTable objects holding the information represented by this Tensor, usually with two elements, one for data, one for MC
					  std::vector<unsigned int> _columns         ///< Vector of columns in the GPUFileTable to take the data from
			  ):GPUStreamTensor<float444>(_list, _tables, _columns){};
	/// Destructor
	virtual ~GPUStreamTensor3(void){};
	/// Read the stream to memory and print contents
	/** Print nelements, for nelements < 1, all elemnts are printed, in the second argument,
	a different output stream can be specified, default is cout */
	virtual void Print(int nelemnets = 0, std::ostream & output = std::cout, int index =0, int block =0);
	// Read the stream to memory
	//virtual float444 * Read(int index =0);
	/// Write the stream from an array
	void Write(float444 * _data, int elements, int index =0){
		assert((int)mstream.size() > index);
		//mlength[index].clear();
		for(int i=0; i < (int)mstream[index].size(); i++){
			if(mstream[index][i])
				delete mstream[index][i];
			mstream[index][i] =0;
		}
		mstream[index].clear();
		musecount[index].clear();
		int offset =0;
		while(elements > 0){
			if(elements > Blocksize){
				//mlength[index].push_back(Blocksize);
				mstream[index].push_back(new GPUDataStream<float444>(mList->GetDeviceInterface(),Blocksize));
				musecount[index].push_back(0);
				elements -= Blocksize;
			} else {
				assert(GetLength(index) == elements);
				//mlength[index].push_back(elements);
				mstream[index].push_back(new GPUDataStream<float444>(mList->GetDeviceInterface(),elements));
				musecount[index].push_back(0);
				elements -= Blocksize;
			}
			(mstream[index].back())->Write(_data+offset);
			offset += Blocksize;
		}
	}
protected:
	/// Protected constructor; allows derived objets to implement their
	/// own registration mechanism
	GPUStreamTensor3():GPUStreamTensor<float444>(){};
	/// Constructor
	GPUStreamTensor3(GPUDataDependentObjectList *_list, bool init=true): GPUStreamTensor<float444>(_list,init){};
	/// Read a block of the stream to memory
	virtual float444 * ReadBlock(int index =0, int block =0);

};

/// Class represnting a stream of fourth rank tensors
/** As you might have seen, there is no public constructor, i.e. you as the user are not allowed to
    create GPUStreamTensor4. This is in order to ensure that only derived objects, which also know
    how to calculate the contents of the tensor are actually instantiated.

    The 256 elements of the fourth rank tensor are internally represented as 64 float4s in 16 float44
    structures. This represntation is faster than a float4444 structure with 64 float4s.

    Note that tensor here implies just 256 numbers and not necessarily a tensor under
    Lorentz transformations. The latter condition should however be fulfilled if the object is to be
    used in the covariant tensor formalism. For other purposes, non-Lorentzian quantities can however use
    the same data structure. */
class GPUStreamTensor4: public GPUStreamTensor<float44, float4444> {
public:
	/// Constructor for a tensor based on GPUFileTable data
	GPUStreamTensor4(GPUDataDependentObjectList *_list, ///<GPUDataDependentObjectList where the tensor is registered for cache handling
					  std::vector<GPUFileTable<float4444> *> _tables,    ///< Vector of GPUFileTable objects holding the information represented by this Tensor, usually with two elements, one for data, one for MC
					  std::vector<unsigned int> _columns         ///< Vector of columns in the GPUFileTable to take the data from
			  ):GPUStreamTensor<float44, float4444>(_list, _tables, _columns){};
	/// Destructor
	virtual ~GPUStreamTensor4(void){};
	/// () operator; performs the actual calculation, if necessary
	virtual GPUDataStream<float44> * operator()(int index =0, int block =0);
	 /// Copy data from a GPUFileTable to the GPU
	virtual void CopyBuffer(int index, int block);
	/// Read the stream to memory and print contents
	/** Print nelements, for nelements < 1, all elemnts are printed, in the second argument,
	a different output stream can be specified, default is cout */
	virtual void Print(int nelemnets = 0, std::ostream & output = std::cout, int index =0, int block =0);
	// Read the stream to memory
	//virtual float4444 * Read(int index =0);
	// Write the stream from an array
/*	void Write(float4444 * _data, int elements, int index =0){
		assert((int)mlength.size() > index);
		mlength[index].clear();
		for(int i=0; i < (int)mstream[index].size(); i++){
			if(mstream[index][i])
				delete mstream[index][i];
		}
		int offset =0;
		while(elements > 0){
			if(elements > Blocksize){
				mlength[index].push_back(Blocksize);
				mstream[index].push_back(new GPUDataStream(getStreamType(( float4444 *)0), Blocksize));
				elements -= Blocksize;
			} else {
				mlength[index].push_back(elements);
				mstream[index].push_back(new GPUDataStream(getStreamType(( float4444 *)0), elements));
				elements -= Blocksize;
			}
			streamRead(*(mstream[index].back()), _data+offset);
			offset += Blocksize;
		}
	}*/
	/// Reset the Stream
	  virtual void Reset(int index, int block = -1){

	     if(block == -1){
	    	 ResetUsecount(index);
	    	  if((int)mstream.size() > index){
	    		  for(int j=0; j < (int)mstream[index].size(); j++){
	    			  if(mstream[index][j]){
	    				  for(int k=0; k < 16; k++){
	    					  if((*(mstream[index][j]))(k))
	    						  delete (*(mstream[index][j]))(k);
	    					  (*(mstream[index][j]))(k) =0;
	    				  }//mlength[index][j] =0;
	    				  delete mstream[index][j];
	    				  mstream[index][j] =0;
	    			  }
	    		  }
	    		  ResetUsecount(index);
	    	  }
	      } else {
	    	  if((int)mstream.size() > index){
	    		  if((int)mstream[index].size() > block){
	    			  if(mstream[index][block]){
	    				  for(int k=0; k < 16; k++){
	    					  if((*(mstream[index][block]))(k))
	    						  delete (*(mstream[index][block]))(k);
	    					  (*(mstream[index][block]))(k) =0;
	    					  // mlength[index][block] =0;
	    				  }
	    				  delete mstream[index][block];
	    				  mstream[index][block] =0;
	    			  }
	    			  ResetUsecount(index,block);
	    		  }
	    	  }
	    }
	  };



protected:
	/// Protected constructor; allows derived objets to implement their
	/// own registration mechanism
	GPUStreamTensor4():GPUStreamTensor<float44, float4444>(){};
	/// Constructor
	GPUStreamTensor4(GPUDataDependentObjectList *_list, bool init=true): GPUStreamTensor<float44, float4444>(_list, init){};
	/// Read the stream to memory
	virtual float4444 * ReadBlock(int index =0, int block =0);
};


