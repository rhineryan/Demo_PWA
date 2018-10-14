
#include "float444.h"


//#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.VC80.CRT' version='8.0.50608.0' processorArchitecture='X86' publicKeyToken='1fc8b3b9a1e18e3b' language='*'\"")

// add components of a float 444
double addcomponents(float444 & x){
	double aa,ab,ac,ad, ba, bb, bc, bd, ca,cb,cc,cd,da,db,dc,dd;
	aa = (double)x.cc.x + (double)x.cc.y + (double)x.cc.z + (double)x.cc.w;
	ab = (double)x.cd.x + (double)x.cd.y + (double)x.cd.z + (double)x.cd.w;
	ac = (double)x.ce.x + (double)x.ce.y + (double)x.ce.z + (double)x.ce.w;
	ad = (double)x.cf.x + (double)x.cf.y + (double)x.cf.z + (double)x.cf.w;

	ba = (double)x.dc.x + (double)x.dc.y + (double)x.dc.z + (double)x.dc.w;
	bb = (double)x.dd.x + (double)x.dd.y + (double)x.dd.z + (double)x.dd.w;
	bc = (double)x.de.x + (double)x.de.y + (double)x.de.z + (double)x.de.w;
	bd = (double)x.df.x + (double)x.df.y + (double)x.df.z + (double)x.df.w;

	ca = (double)x.ec.x + (double)x.ec.y + (double)x.ec.z + (double)x.ec.w;
	cb = (double)x.ed.x + (double)x.ed.y + (double)x.ed.z + (double)x.ed.w;
	cc = (double)x.ee.x + (double)x.ee.y + (double)x.ee.z + (double)x.ee.w;
	cd = (double)x.ef.x + (double)x.ef.y + (double)x.ef.z + (double)x.ef.w;

	da = (double)x.fc.x + (double)x.fc.y + (double)x.fc.z + (double)x.fc.w;
	db = (double)x.fd.x + (double)x.fd.y + (double)x.fd.z + (double)x.fd.w;
	dc = (double)x.fe.x + (double)x.fe.y + (double)x.fe.z + (double)x.fe.w;
	dd = (double)x.ff.x + (double)x.ff.y + (double)x.ff.z + (double)x.ff.w;

	return aa + ab + ac + ad +
		   ba + bb + bc + bd +
		   ca + cb + cc + cd +
		   da + db + dc + dd;
}


float444 operator + (const float444& lhs, const float444 &rhs){
	float444 r;
	r.cc = lhs.cc + rhs.cc;
    r.cd = lhs.cd + rhs.cd;
    r.ce = lhs.ce + rhs.ce;
    r.cf = lhs.cf + rhs.cf;

    r.dc = lhs.dc + rhs.dc;
    r.dd = lhs.dd + rhs.dd;
    r.de = lhs.de + rhs.de;
    r.df = lhs.df + rhs.df;

	r.ec = lhs.ec + rhs.ec;
    r.ed = lhs.ed + rhs.ed;
    r.ee = lhs.ee + rhs.ee;
    r.fc = lhs.fc + rhs.fc;

	r.fc = lhs.fc + rhs.fc;
    r.fd = lhs.fd + rhs.fd;
    r.fe = lhs.fe + rhs.fe;
    r.ff = lhs.ff + rhs.ff;

	return r;

}

float444 operator - (const float444 & lhs, const float444 &rhs){
	float444 r;

    r.cc = lhs.cc - rhs.cc;
    r.cd = lhs.cd - rhs.cd;
    r.ce = lhs.ce - rhs.ce;
    r.cf = lhs.cf - rhs.cf;

    r.dc = lhs.dc - rhs.dc;
    r.dd = lhs.dd - rhs.dd;
    r.de = lhs.de - rhs.de;
    r.df = lhs.df - rhs.df;

	r.ec = lhs.ec - rhs.ec;
    r.ed = lhs.ed - rhs.ed;
    r.ee = lhs.ee - rhs.ee;
    r.fc = lhs.fc - rhs.fc;

	r.fc = lhs.fc - rhs.fc;
    r.fd = lhs.fd - rhs.fd;
    r.fe = lhs.fe - rhs.fe;
    r.ff = lhs.ff - rhs.ff;
    return r;
}



float444 operator - (const float444 &lhs){
    float444 r; 
	r.cc = -lhs.cc;
    r.cd = -lhs.cd;
    r.ce = -lhs.ce;
    r.cf = -lhs.cf;

    r.dc = -lhs.dc;
    r.dd = -lhs.dd;
    r.de = -lhs.de;
    r.df = -lhs.df;

	r.ec = -lhs.ec;
    r.ed = -lhs.ed;
    r.ee = -lhs.ee;
    r.fc = -lhs.fc;

	r.fc = -lhs.fc;
    r.fd = -lhs.fd;
    r.fe = -lhs.fe;
    r.ff = -lhs.ff;

	return r;
}


float444 operator * (const float444 & lhs, const float &rhs){

	float444 r;

	r.cc = rhs*lhs.cc;
    r.cd = rhs*lhs.cd;
    r.ce = rhs*lhs.ce;
    r.cf = rhs*lhs.cf;

    r.dc = rhs*lhs.dc;
    r.dd = rhs*lhs.dd;
    r.de = rhs*lhs.de;
    r.df = rhs*lhs.df;

	r.ec = rhs*lhs.ec;
    r.ed = rhs*lhs.ed;
    r.ee = rhs*lhs.ee;
    r.ef = rhs*lhs.ef;

	r.fc = rhs*lhs.fc;
    r.fd = rhs*lhs.fd;
    r.fe = rhs*lhs.fe;
    r.ff = rhs*lhs.ff;

    return r;

}

float444 operator * (const float & rhs, const float444 &lhs){
	
	float444 r;

	r.cc = rhs*lhs.cc;
    r.cd = rhs*lhs.cd;
    r.ce = rhs*lhs.ce;
    r.cf = rhs*lhs.cf;

    r.dc = rhs*lhs.dc;
    r.dd = rhs*lhs.dd;
    r.de = rhs*lhs.de;
    r.df = rhs*lhs.df;

	r.ec = rhs*lhs.ec;
    r.ed = rhs*lhs.ed;
    r.ee = rhs*lhs.ee;
    r.ef = rhs*lhs.fc;

	r.fc = rhs*lhs.fc;
    r.fd = rhs*lhs.fd;
    r.fe = rhs*lhs.fe;
    r.ff = rhs*lhs.ff;
   

	return r;
}



float444 operator / (const float444 &lhs, const float& rhs){
 
	float444 r;
 
	r.cc = lhs.cc/rhs;
    r.cd = lhs.cd/rhs;
    r.ce = lhs.ce/rhs;
    r.cf = lhs.cf/rhs;

    r.dc = lhs.dc/rhs;
    r.dd = lhs.dd/rhs;
    r.de = lhs.de/rhs;
    r.df = lhs.df/rhs;

	r.ec = lhs.ec/rhs;
    r.ed = lhs.ed/rhs;
    r.ee = lhs.ee/rhs;
    r.fc = lhs.fc/rhs;

	r.fc = lhs.fc/rhs;
    r.fd = lhs.fd/rhs;
    r.fe = lhs.fe/rhs;
    r.ff = lhs.ff/rhs;
   
	
	return r;
}



///
float operator | (const float444 &A, const float444 &B){
 
	return -A.cc.x*B.cc.x - A.dc.x*B.dc.x - A.ec.x*B.ec.x + A.fc.x*B.fc.x
		   -A.cd.x*B.cd.x - A.dd.x*B.dd.x - A.ed.x*B.ed.x + A.fd.x*B.fd.x
           -A.ce.x*B.ce.x - A.de.x*B.de.x - A.ee.x*B.ee.x + A.fe.x*B.fe.x
           +A.cf.x*B.cf.x + A.df.x*B.df.x + A.fc.x*B.fc.x - A.ff.x*B.ff.x
		   
		   -A.cc.y*B.cc.y - A.dc.y*B.dc.y - A.ec.y*B.ec.y + A.fc.y*B.fc.y
		   -A.cd.y*B.cd.y - A.dd.y*B.dd.y - A.ed.y*B.ed.y + A.fd.y*B.fd.y
		   -A.ce.y*B.ce.y - A.de.y*B.de.y - A.ee.y*B.ee.y + A.fe.y*B.fe.y
		   +A.cf.y*B.cf.y + A.df.y*B.df.y + A.fc.y*B.fc.y - A.ff.y*B.ff.y
  
           -A.cc.z*B.cc.z - A.dc.z*B.dc.z - A.ec.z*B.ec.z + A.fc.z*B.fc.z
		   -A.cd.z*B.cd.z - A.dd.z*B.dd.z - A.ed.z*B.ed.z + A.fd.z*B.fd.z
		   -A.ce.z*B.ce.z - A.de.z*B.de.z - A.ee.z*B.ee.z + A.fe.z*B.fe.z
		   +A.cf.z*B.cf.z + A.df.z*B.df.z + A.fc.z*B.fc.z - A.ff.z*B.ff.z
  
		   +A.cc.w*B.cc.w + A.dc.w*B.dc.w + A.ec.w*B.ec.w - A.fc.w*B.fc.w
		   +A.cd.w*B.cd.w + A.dd.w*B.dd.w + A.ed.w*B.ed.w - A.fd.w*B.fd.w
		   +A.ce.w*B.ce.w + A.de.w*B.de.w + A.ee.w*B.ee.w - A.fe.w*B.fe.w
		   -A.cf.w*B.cf.w - A.df.w*B.df.w - A.fc.w*B.fc.w + A.ff.w*B.ff.w;

}




float44 operator | (const float444 &A, const float4 &B){

	float44 output;
    output.c.x = -A.cc.x*B.x - A.cc.y*B.y - A.cc.z*B.z + A.cc.w*B.w; 
    output.c.y = -A.cd.x*B.x - A.cd.y*B.y - A.cd.z*B.z + A.cd.w*B.w;
    output.c.z = -A.ce.x*B.x - A.ce.y*B.y - A.ce.z*B.z + A.ce.w*B.w;
    output.c.w = -A.cf.x*B.x - A.cf.y*B.y - A.cf.z*B.z + A.cf.w*B.w;

	output.d.x = -A.dc.x*B.x - A.dc.y*B.y - A.dc.z*B.z + A.dc.w*B.w; 
    output.d.y = -A.dd.x*B.x - A.dd.y*B.y - A.dd.z*B.z + A.dd.w*B.w; 
    output.d.z = -A.de.x*B.x - A.de.y*B.y - A.de.z*B.z + A.de.w*B.w; 
    output.d.w = -A.df.x*B.x - A.df.y*B.y - A.df.z*B.z + A.df.w*B.w; 

	output.e.x = -A.ec.x*B.x - A.ec.y*B.y - A.ec.z*B.z + A.ec.w*B.w; 
    output.e.y = -A.ed.x*B.x - A.ed.y*B.y - A.ed.z*B.z + A.ed.w*B.w; 
    output.e.z = -A.ee.x*B.x - A.ee.y*B.y - A.ee.z*B.z + A.ee.w*B.w; 
    output.e.w = -A.fc.x*B.x - A.fc.y*B.y - A.fc.z*B.z + A.fc.w*B.w; 


    output.f.x = -A.fc.x*B.x - A.fc.y*B.y - A.fc.z*B.z + A.fc.w*B.w; 
    output.f.y = -A.fd.x*B.x - A.fd.y*B.y - A.fd.z*B.z + A.fd.w*B.w; 
    output.f.z = -A.fe.x*B.x - A.fe.y*B.y - A.fe.z*B.z + A.fe.w*B.w; 
    output.f.w = -A.ff.x*B.x - A.ff.y*B.y - A.ff.z*B.z + A.ff.w*B.w; 


	return output;

}



float44 operator | (const float4 &A, const float444 &B){
	return B|A;
}


float4 operator | (const float444 &A, const float44 &B){

	float4 output;

    output.x = A.cc.x*B.c.x + A.cd.x*B.d.x + A.ce.x*B.e.x - A.cf.x*B.f.x
              +A.cc.y*B.c.y + A.cd.y*B.d.y + A.ce.y*B.e.y - A.cf.y*B.f.y
              +A.cc.z*B.c.z + A.cd.z*B.d.z + A.ce.z*B.e.z - A.cf.z*B.f.z
              -A.cc.w*B.c.w - A.cd.w*B.d.w - A.ce.w*B.e.w + A.cf.w*B.f.w;

    output.y = A.dc.x*B.c.x + A.dd.x*B.d.x + A.de.x*B.e.x - A.df.x*B.f.x
              +A.dc.y*B.c.y + A.dd.y*B.d.y + A.de.y*B.e.y - A.df.y*B.f.y
              +A.dc.z*B.c.z + A.dd.z*B.d.z + A.de.z*B.e.z - A.df.z*B.f.z
              -A.dc.w*B.c.w - A.dd.w*B.d.w - A.de.w*B.e.w + A.df.w*B.f.w;

    output.z = A.ec.x*B.c.x + A.ed.x*B.d.x + A.ee.x*B.e.x - A.fc.x*B.f.x
              +A.ec.y*B.c.y + A.ed.y*B.d.y + A.ee.y*B.e.y - A.fc.y*B.f.y
              +A.ec.z*B.c.z + A.ed.z*B.d.z + A.ee.z*B.e.z - A.fc.z*B.f.z
              -A.ec.w*B.c.w - A.ed.w*B.d.w - A.ee.w*B.e.w + A.fc.w*B.f.w;

    output.w = A.fc.x*B.c.x + A.fd.x*B.d.x + A.fe.x*B.e.x - A.ff.x*B.f.x
              +A.fc.y*B.c.y + A.fd.y*B.d.y + A.fe.y*B.e.y - A.ff.y*B.f.y
              +A.fc.z*B.c.z + A.fd.z*B.d.z + A.fe.z*B.e.z - A.ff.z*B.f.z
              -A.fc.w*B.c.w - A.fd.w*B.d.w - A.fe.w*B.e.w + A.ff.w*B.f.w;

 
	return output;
}



float4 operator | (const float44 &lhs, const float444 &rhs){
	return (rhs|lhs);
}




// out product of rank2 const and vector const
float444 operator % (const float44 &lhs, const float4 &rhs){

    float444 output;
	output.cc.x = lhs.c.x*rhs.x; 
	output.cc.y = lhs.c.x*rhs.y; 
	output.cc.z = lhs.c.x*rhs.z; 
	output.cc.w = lhs.c.x*rhs.w;
    output.cd.x = lhs.c.y*rhs.x; 
	output.cd.y = lhs.c.y*rhs.y; 
	output.cd.z = lhs.c.y*rhs.z; 
	output.cd.w = lhs.c.y*rhs.w;
	output.ce.x = lhs.c.z*rhs.x; 
	output.ce.y = lhs.c.z*rhs.y; 
	output.ce.z = lhs.c.z*rhs.z; 
	output.ce.w = lhs.c.z*rhs.w;
    output.cf.x = lhs.c.w*rhs.x; 
	output.cf.y = lhs.c.w*rhs.y; 
	output.cf.z = lhs.c.w*rhs.z; 
	output.cf.w = lhs.c.w*rhs.w;

    output.dc.x = lhs.d.x*rhs.x; 
	output.dc.y = lhs.d.x*rhs.y; 
	output.dc.z = lhs.d.x*rhs.z; 
	output.dc.w = lhs.d.x*rhs.w;
    output.dd.x = lhs.d.y*rhs.x; 
	output.dd.y = lhs.d.y*rhs.y; 
	output.dd.z = lhs.d.y*rhs.z; 
	output.dd.w = lhs.d.y*rhs.w;
	output.de.x = lhs.d.z*rhs.x; 
	output.de.y = lhs.d.z*rhs.y; 
	output.de.z = lhs.d.z*rhs.z; 
	output.de.w = lhs.d.z*rhs.w;
    output.df.x = lhs.d.w*rhs.x; 
	output.df.y = lhs.d.w*rhs.y; 
	output.df.z = lhs.d.w*rhs.z; 
	output.df.w = lhs.d.w*rhs.w;

   	output.ec.x = lhs.e.x*rhs.x; 
	output.ec.y = lhs.e.x*rhs.y; 
	output.ec.z = lhs.e.x*rhs.z; 
	output.ec.w = lhs.e.x*rhs.w;
    output.ed.x = lhs.e.y*rhs.x; 
	output.ed.y = lhs.e.y*rhs.y; 
	output.ed.z = lhs.e.y*rhs.z; 
	output.ed.w = lhs.e.y*rhs.w;
	output.ee.x = lhs.e.z*rhs.x; 
	output.ee.y = lhs.e.z*rhs.y; 
	output.ee.z = lhs.e.z*rhs.z; 
	output.ee.w = lhs.e.z*rhs.w;
    output.ef.x = lhs.e.w*rhs.x; 
	output.ef.y = lhs.e.w*rhs.y; 
	output.ef.z = lhs.e.w*rhs.z; 
	output.ef.w = lhs.e.w*rhs.w;
 
	output.fc.x = lhs.f.x*rhs.x; 
	output.fc.y = lhs.f.x*rhs.y; 
	output.fc.z = lhs.f.x*rhs.z; 
	output.fc.w = lhs.f.x*rhs.w;
    output.fd.x = lhs.f.y*rhs.x; 
	output.fd.y = lhs.f.y*rhs.y; 
	output.fd.z = lhs.f.y*rhs.z; 
	output.fd.w = lhs.f.y*rhs.w;
	output.fe.x = lhs.f.z*rhs.x; 
	output.fe.y = lhs.f.z*rhs.y; 
	output.fe.z = lhs.f.z*rhs.z; 
	output.fe.w = lhs.f.z*rhs.w;
    output.ff.x = lhs.f.w*rhs.x; 
	output.ff.y = lhs.f.w*rhs.y; 
	output.ff.z = lhs.f.w*rhs.z; 
	output.ff.w = lhs.f.w*rhs.w;


	return output; 

}

// out product of rank2 const and vector const
float444 operator % (const float4 &lhs, const float44 &rhs){

    float444 output;
	output.cc = lhs.x*rhs.c;
	output.cd = lhs.x*rhs.d;
	output.ce = lhs.x*rhs.e;
	output.cf = lhs.x*rhs.f;

	output.dc = lhs.y*rhs.c;
	output.dd = lhs.y*rhs.d;
	output.de = lhs.y*rhs.e;
	output.df = lhs.y*rhs.f;

	output.ec = lhs.z*rhs.c;
	output.ed = lhs.z*rhs.d;
	output.ee = lhs.z*rhs.e;
	output.ef = lhs.z*rhs.f;

	output.fc = lhs.w*rhs.c;
	output.fd = lhs.w*rhs.d;
	output.fe = lhs.w*rhs.e;
	output.ff = lhs.w*rhs.f;

	return output;

}


float444 transpose(const float444 &A, std::string sequence){

	float444 B;
	
	if("213" == sequence){
	  
        /*
		B121 = A211;
		B211 = A121;
		B131 = A311;
		B311 = A131;
        B141 = A411;
		B411 = A141;
        B231 = A321;
		B321 = A231;
		B241 = A421;
        B421 = A241;
		B341 = A431;
		B431 = A341;
        */

 
		B = A;

		B.cd.x = A.dc.x;
		B.dc.x = A.cd.x;
		B.ce.x = A.ec.x;
		B.ec.x = A.ce.x;
		B.cf.x = A.fc.x;
		B.fc.x = A.cf.x;
		B.de.x = A.ed.x;
		B.ed.x = A.de.x;
		B.df.x = A.fd.x;
        B.fd.x = A.df.x;
		B.ef.x = A.fe.x;
		B.fe.x = A.ef.x;
	    
		B.cd.y = A.dc.y;
		B.dc.y = A.cd.y;
		B.ce.y = A.ec.y;
		B.ec.y = A.ce.y;
		B.cf.y = A.fc.y;
		B.fc.y = A.cf.y;
		B.de.y = A.ed.y;
		B.ed.y = A.de.y;
		B.df.y = A.fd.y;
        B.fd.y = A.df.y;
		B.ef.y = A.fe.y;
		B.fe.y = A.ef.y;

		B.cd.z = A.dc.z;
		B.dc.z = A.cd.z;
		B.ce.z = A.ec.z;
		B.ec.z = A.ce.z;
		B.cf.z = A.fc.z;
		B.fc.z = A.cf.z;
		B.de.z = A.ed.z;
		B.ed.z = A.de.z;
		B.df.z = A.fd.z;
        B.fd.z = A.df.z;
		B.ef.z = A.fe.z;
		B.fe.z = A.ef.z;


		B.cd.w = A.dc.w;
		B.dc.w = A.cd.w;
		B.ce.w = A.ec.w;
		B.ec.w = A.ce.w;
		B.cf.w = A.fc.w;
		B.fc.w = A.cf.w;
		B.de.w = A.ed.w;
		B.ed.w = A.de.w;
		B.df.w = A.fd.w;
        B.fd.w = A.df.w;
		B.ef.w = A.fe.w;
		B.fe.w = A.ef.w;

	
	}
	else if("132" == sequence){

		/*
		B112 = A121;
		B121 = A112;
		B113 = A131;
		B131 = A113;
        B114 = A141;
		B141 = A114;
        B123 = A132;
		B132 = A123;
		B124 = A142;
        B142 = A124;
		B134 = A143;
		B143 = A134;
        */

		B = A;

		B.cc.y = A.cd.x; 
        B.cd.x = A.cc.y;
        B.cc.z = A.ce.x; 
        B.ce.x = A.cc.z;
		B.cc.w = A.cf.x; 
        B.cf.x = A.cc.w;
		B.cd.z = A.ce.y;
		B.ce.y = A.cd.z;
		B.cd.w = A.cf.y;
		B.cf.y = A.cd.w;
		B.ce.w = A.cf.z;
		B.cf.z = A.ce.w; 

		B.dc.y = A.dd.x; 
        B.dd.x = A.dc.y;
        B.dc.z = A.de.x; 
        B.de.x = A.dc.z;
		B.dc.w = A.df.x; 
        B.df.x = A.dc.w;
		B.dd.z = A.de.y;
		B.de.y = A.dd.z;
		B.dd.w = A.df.y;
		B.df.y = A.dd.w;
		B.de.w = A.df.z;
		B.df.z = A.de.w; 

		B.ec.y = A.dd.x; 
        B.ed.x = A.dc.y;
        B.ec.z = A.de.x; 
        B.ee.x = A.dc.z;
		B.ec.w = A.df.x; 
        B.ef.x = A.dc.w;
		B.ed.z = A.de.y;
		B.ee.y = A.dd.z;
		B.ed.w = A.df.y;
		B.ef.y = A.dd.w;
		B.ee.w = A.df.z;
		B.ef.z = A.de.w; 

		B.fc.y = A.dd.x; 
        B.fd.x = A.dc.y;
        B.fc.z = A.de.x; 
        B.fe.x = A.dc.z;
		B.fc.w = A.df.x; 
        B.ff.x = A.dc.w;
		B.fd.z = A.de.y;
		B.fe.y = A.dd.z;
		B.fd.w = A.df.y;
		B.ff.y = A.dd.w;
		B.fe.w = A.df.z;
		B.ff.z = A.de.w; 
	
	} 

	return B;

}   


float444  transpose_213(float444 &A){
	
	float444 B;
	B = transpose(A,"213");
    return B;
}

 
float444  transpose_132(float444 &A){

	float444 B;
	B = transpose(A,"132");
    return B;
}


float444  transpose_231(float444 &A){
	
	float444 B;
	B = transpose(transpose(A,"213"),"132");
    return B;
}


float444  transpose_312(float444 &A){
	
	float444 B;
	B = transpose(transpose(A,"132"),"213");
    return B;

}


float444  transpose_321(float444 &A){

	float444 B;
	B = transpose(transpose(transpose(A,"132"),"213"),"132");
    return B;
}

float444  moveindices(const float444 &A){
	float444 output, temp;
	output = movelastindex(A);
	temp = movemiddleindex(output);
	output = movefirstindex(temp);
	return output;
}


float444 movelastindex(const float444 &input){
	float444 output;
	output.cc   = -input.cc;
	output.cc.w =  input.cc.w;
	output.cd   = -input.cd;
	output.cd.w =  input.cd.w;
	output.ce   = -input.ce;
	output.ce.w =  input.ce.w;
	output.cf   = -input.cf;
	output.cf.w =  input.cf.w;
	output.dc   = -input.dc;
	output.dc.w =  input.dc.w;
	output.dd   = -input.dd;
	output.dd.w =  input.dd.w;
	output.de   = -input.de;
	output.de.w =  input.de.w;
	output.df   = -input.df;
	output.df.w =  input.df.w;
	output.ec   = -input.ec;
	output.ec.w =  input.ec.w;
	output.ed   = -input.ed;
	output.ed.w =  input.ed.w;
	output.ee   = -input.ee;
	output.ee.w =  input.ee.w;
	output.ef   = -input.ef;
	output.ef.w =  input.ef.w;
	output.fc   = -input.fc;
	output.fc.w =  input.fc.w;
	output.fd   = -input.fd;
	output.fd.w =  input.fd.w;
	output.fe   = -input.fe;
	output.fe.w =  input.fe.w;
	output.ff   = -input.ff;
	output.ff.w =  input.ff.w;

	return output;
}

float444 movemiddleindex(const float444 &input){
	float444 output;
	output.cc = - input.cc;
	output.cd = - input.cd;
	output.ce = - input.ce;
	output.cf =  input.cf;

	output.dc = - input.dc;
	output.dd = - input.dd;
	output.de = - input.de;
	output.df =  input.df;

	output.ec = - input.ec;
	output.ed = - input.ed;
	output.ee = - input.ee;
	output.ef =  input.ef;

	output.fc = - input.fc;
	output.fd = - input.fd;
	output.fe = - input.fe;
	output.ff =  input.ff;

	return output;
}

float444 movefirstindex(const float444 &input){
	float444 output;
	output.cc = - input.cc;
	output.cd = - input.cd;
	output.ce = - input.ce;
	output.cf = - input.cf;

	output.dc = - input.dc;
	output.dd = - input.dd;
	output.de = - input.de;
	output.df = - input.df;

	output.ec = - input.ec;
	output.ed = - input.ed;
	output.ee = - input.ee;
	output.ef = - input.ef;

	output.fc =  input.fc;
	output.fd =  input.fd;
	output.fe =  input.fe;
	output.ff =  input.ff;

	return output;
}
