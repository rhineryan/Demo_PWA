/// \file GPUStreamInputTextFileVector.h
#pragma once
#include "GPUStreamInputVector.h"
#include "Status.h"
/// Class for streams that contain data that is read from a text file
/** As the input to PWAs is always 4-vectors, this class is derived of
   GPUStreamVector and not the more general GPUStreamTensor. Usually,
   GPUStreamTensor objects contain intermediate results of calculations
   and thus cached values have to be invalidated, when parameters change.
   Here, the values are read from a file, so the cache only has to be
   invalidated either to free memory or if the input file changes. The
   class is currently set up to either read different sets of four vectors
   from different files or two sets of vectors from a file using the ODD/
   EVEN mechanism
*/
class GPUStreamInputTextFileVector :
	public GPUStreamInputVector
{
public:
  /// Types of file reads
  /** File read types for different storage options, more to be added if needed for three+ particle decays (or use root files) **/
  enum READTYPE {ALL, /*!< Read all lines (one file for every four-vector **/
		 ODD, /*!< Read odd lines only (even lines contain "the other" four vector **/
		 EVEN /*!< Read even lines only (odd lines contain "the other" four vector **/
  };

  /// Create a Stream Vector to be fed from a textfile
  /** \param _list Object where to register this vector (usually the Partial Wave Analysis Object)
      \param _type: type of file organisation
  **/
  GPUStreamInputTextFileVector(GPUDataDependentObjectList *_list, READTYPE _type = ALL);
  /// Create a Stream Vector to be fed from a textfile
  /** \param _list Object where to register this vector (usually the Partial Wave Analysis Object)
      \param _filename: Name of the text file for index 0
      \param _type: Type of file organisation
  **/
  GPUStreamInputTextFileVector(GPUDataDependentObjectList *_list,const char * _filename, READTYPE _type = ALL);
  /// Destructor
  virtual ~GPUStreamInputTextFileVector(void);
  /// Get the type of data organisation in the file
  READTYPE GetReadtype(){return mReadtype;};
  /// Test whether the file exists and write its length to length
  virtual STATUS TestFile(int index, int & length);
  /// Read the file and write its contents to a GPU Stream
  virtual STATUS ReadFile(int index =0);



private:
  /// Type of file reading
  const READTYPE mReadtype;

};
