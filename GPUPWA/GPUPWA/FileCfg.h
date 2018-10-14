/// \FileCfg.h

// FileCfg.h
// load File name parameters
// Operators << and >> are defined to allow writing to and reading from files


#include <iostream>

/// Class to read file names from a file
struct FileCfg
{
	/// Path to the input file
	char * path;//

	/// Constructor
	FileCfg() {path = new char[1024];}
	/// Constructor taking a filename
	FileCfg( char* p ) : path(p) {}
	/// Copy constructor
	FileCfg( const FileCfg& orig ) : path(orig.path) {}
	/// Assignment operator
	FileCfg& operator=( const FileCfg& orig )
		{ path = orig.path;  return *this; }
};

/// Write the filename to os
std::ostream& operator<<( std::ostream& os, const FileCfg& res )
{
	// Save a FileCfg to os
	os <<  res.path ;
	return os;
}

/// Read the filename
std::istream& operator>>( std::istream& is, FileCfg& inp )
{
	// Load a FileCfg from is
	is >> inp.path;
	return is;
}
