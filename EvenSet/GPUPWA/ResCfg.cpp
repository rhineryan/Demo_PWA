#include "ResCfg.h"

ResCfg& ResCfg::operator=( const ResCfg& orig )
		{ m = orig.m;  w = orig.w;  t = orig.t;  return *this; }


std::ostream& operator<<( std::ostream& os, const ResCfg& res )
{
	// Save a ResCfg to os
	os << res.m << " " << res.w << " " << res.t;
	return os;
}


std::istream& operator>>( std::istream& is, ResCfg& inp )
{
	// Load a ResCfg from is
	is >> inp.m >> inp.w >> inp.t;
	return is;
}
