/// \file ResCfg.h
// load resonance parameters
// Operators << and >> are defined to allow writing to and reading from files
#pragma once

#include <iostream>

/// Structure holding the information about a resonance read from a configuration file
/** Works in conjunction with the ConfigFile class, which uses the std::ostream& operator<<( std::ostream& os, const ResCfg& res ) and 
std::istream& operator>>( std::istream& is, ResCfg& inp ) operators.
**/
struct ResCfg
{
  float m; ///< Mass of the resonance
  float w; ///< Width of the resonance
  int t;   ///< type of the resonance

  /// Default constructor
  ResCfg() {} 
  /// Constructor initializing members
  ResCfg( float _m, ///< Mass of the resonance
	  float _w, ///< Width of the resonance
	  int _t    ///< type of the resonance
	  ) : m(_m), w(_w), t(_t) {}
  /// Copy Constructor
  ResCfg( const ResCfg& orig ) : m(orig.m), w(orig.w), t(orig.t) {}
  /// Assignment operator
  ResCfg& operator=( const ResCfg& orig );
};

/// Write a ResCfg to a stream
std::ostream& operator<<( std::ostream& os, const ResCfg& res );

/// Read a ResCfg from a stream
std::istream& operator>>( std::istream& is, ResCfg& inp );
