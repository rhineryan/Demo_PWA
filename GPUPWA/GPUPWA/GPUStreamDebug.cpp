#include "GPUStreamDebug.h"
#include "float44.h"

/// Print a stream (used for debugging)
void printStream(Stream<float> * _stream, int m, int n){
		cout << "*********************************" << endl;
		float * data = new float[m];
		streamWrite(*_stream, data);
		for(int i =0; i < n; i++){
				cout << i << ": " << data[i] << endl;
		}
		cout << "*********************************" << endl;
		delete [] data;
	}

	/// Print a 2-stream (used for debugging)
void print2Stream(Stream<float2> * _stream, int m, int n){
		cout << "*********************************" << endl;
		float2 * data = new float2[m];
		streamWrite(*_stream, data);
		for(int i =0; i < n; i++){
			cout << i << ":  (" << data[i].x <<"," << data[i].y << ")" << endl;
		}
		cout << "*********************************" << endl;
		delete [] data;
	}

	/// Print a 4-stream (used for debugging)
         void print4Stream(Stream<float4> * _stream, int m, int n){
		cout << "*********************************" << endl;
		float4 * data = new float4[m];
		streamWrite(*_stream, data);
		for(int i =0; i < n; i++){
			cout << data[i].x <<" " << data[i].y <<" " << data[i].z <<" " << data[i].w << endl;
		}
		cout << "*********************************" << endl;
		delete [] data;
	}


/// Print a 4-stream (used for debugging)
         void print44Stream(Stream<float44> * _stream, int m, int n){
		cout << "*********************************" << endl;
		float44 * data = new float44[m];
		streamWrite(*_stream, data);
		for(int i =0; i < n; i++){
		  cout << "( " <<data[i].c.x <<" " << data[i].c.y <<" " << data[i].c.z <<" " << data[i].c.w << endl;
			cout << data[i].d.x <<" " << data[i].d.y <<" " << data[i].d.z <<" " << data[i].d.w << endl;
			cout << data[i].e.x <<" " << data[i].e.y <<" " << data[i].e.z <<" " << data[i].e.w << endl;
			cout << data[i].f.x <<" " << data[i].f.y <<" " << data[i].f.z <<" " << data[i].f.w << " ) " << endl;
		}
		cout << "*********************************" << endl;
		delete [] data;
	}

	double2 sum2Stream(Stream<float2> * _stream, int m){
		float2 * data = new float2[m];
		streamWrite(*_stream, data);
		double x =0;
		double y =0;
		double maxx =0;
		double maxy =0;
		int maxind =0;
		for(int i =0; i < m; i++){
			x += data[i].x;
			y += data[i].y;
			if(data[i].y > maxx){
				maxx = data[i].y;
				maxind = i;
			}
			if(data[i].y > maxy)
				maxy = data[i].y;
		}
		cout << "Sum: (" << x << ", " << y << ")" << endl;
		cout << "Maximum at index "<< maxind << ": " << maxx << endl;
		delete [] data;
		return double2(x,y);
	}

	double sumStream(Stream<float> * _stream, int m){
		float * data = new float[m];
		streamWrite(*_stream, data);
		double x =0;
		double maxx =0;
		int maxind =0;
		for(int i =0; i < m; i++){
			x += data[i];
			if(data[i] > maxx){
				maxx = data[i];
				maxind = i;
			}
		}
		cout << "Sum: " << x << endl;
		cout << "Maximum at index "<< maxind << ": " << maxx << endl;
		delete [] data;
		return x;
	}


	double min(double a, double b){
		if(a > b)
			return b;
		return a;
	}
