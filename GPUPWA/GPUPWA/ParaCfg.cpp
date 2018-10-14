#include "ParaCfg.h"

ParaCfg& ParaCfg::operator=( const ParaCfg& orig )
		{ v = orig.v;  e = orig.e;  l = orig.l; u = orig.u; return *this; }


std::ostream& operator<<( std::ostream& os, const ParaCfg& res )
{
	// Save a ParaCfg to os
	os << res.v << " " << res.e << " " << res.l<< " " << res.u;
	return os;
}


std::istream& operator>>( std::istream& is, ParaCfg& inp )
{
	// Load a ParaCfg from is
	is >> inp.v >> inp.e >> inp.l >> inp.u;
	return is;
}
