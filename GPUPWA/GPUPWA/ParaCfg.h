/// \file ParaCfg.h
// load paratial wave parameters
// Operators << and >> are defined to allow writing to and reading from files
#pragma once
#include <iostream>
/// Structure holding the information about a resonance read from a configuration file
/** Works in conjunction with the ConfigFile class, which uses the std::ostream& operator<<( std::ostream& os, const ParaCfg& res ) and 
std::istream& operator>>( std::istream& is, ParaCfg& inp ) operators.
**/
struct ParaCfg
{
  float v; ///< Starting value for the parameter
  float e; ///< Error estimate for the parameter. GPUPWA fixes parameters with nexative e input
  float l; ///< Lower bound for the parameter. If l == 999, no bound will be set in GPUPWA
  float u; ///< Upper bound for the parameter. If u == 999, no bound will be set in GPUPWA

  /// Default constructor
  ParaCfg() {}
  /// Constructor initializing members
  ParaCfg( float _v, ///< Initial value of the parameter
	   float _e, ///< Error estimate for the parameter. GPUPWA fixes parameters with nexative e input
	   float _l, ///< Lower bound for the parameter. If _l == 999, no bound will be set in GPUPWA
	   float _u ///< Upper bound for the parameter. If _u == 999, no bound will be set in GPUPWA
	   ) : v(_v), e(_e), l(_l), u(_u) {}
     /// Copy Constructor
    ParaCfg( const ParaCfg& orig ) : v(orig.v), e(orig.e), l(orig.l), u(orig.u) {}
      /// Assignment operator	
      ParaCfg& operator=( const ParaCfg& orig );
};

/// Write a ParaCfg to a stream
std::ostream& operator<<( std::ostream& os, const ParaCfg& res );

/// Read a ParaCfg from a stream
std::istream& operator>>( std::istream& is, ParaCfg& inp );
