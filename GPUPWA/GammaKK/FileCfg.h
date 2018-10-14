// FileCfg.h
// load Fileonance parameters
// Operators << and >> are defined to allow writing to and reading from files


#include <iostream>

struct FileCfg
{

	char* path;//

	
	FileCfg() {}
	FileCfg( char* p ) : path(p) {}
	FileCfg( const FileCfg& orig ) : path(orig.path) {}
	
	FileCfg& operator=( const FileCfg& orig )
		{ path = orig.path;  return *this; }
};


std::ostream& operator<<( std::ostream& os, const FileCfg& res )
{
	// Save a FileCfg to os
	os <<  res.path ;
	return os;
}


std::istream& operator>>( std::istream& is, FileCfg& inp )
{
	// Load a FileCfg from is
	is >> inp.path;
	return is;
}
