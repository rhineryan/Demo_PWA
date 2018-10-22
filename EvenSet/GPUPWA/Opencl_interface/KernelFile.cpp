#include "KernelFile.h"

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <cassert>

#define GETCWD ::getcwd

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::fstream;

string getCurrentDir() {
    const   size_t  pathSize = 4096;
    char    currentDir[pathSize];

    // Check if we received the path
    if (GETCWD(currentDir, pathSize) != NULL) {
        return string(currentDir);
    }
    return  string("");
}

bool KernelFile::open( const char* fileName){
    size_t      size;
    char*       str;

    // Open file stream
    fstream f(fileName, (std::fstream::in | std::fstream::binary));

    // Check if we have opened file stream
    if (f.is_open()) {
        size_t  sizeFile;
        // Find the stream size
        f.seekg(0, std::fstream::end);
        size = sizeFile = f.tellg();
        f.seekg(0, std::fstream::beg);

        str = new char[size + 1];
        if (!str) {
            f.close();
            return  false;
        }

        // Read file
        f.read(str, sizeFile);
        f.close();
        str[size] = '\0';

        msource  = str;

        removeComments();
        removeout();
        makestandard();
        delete[] str;

        return true;
    }

    return false;
}

void KernelFile::removeComments(){
	msourcecleanout = "";
	size_t i=0;
	int lcomment = 0;
	int scomment = 0;
	bool instring = false;
	bool onswitch = false;
	while(i < msource.length()-1){
		onswitch = false;
		if(!lcomment && !scomment && msource[i] == '"')
			instring = !instring;
		if(!instring && msource[i] == '/' && msource[i+1] == '*')
			lcomment++;
		if(!instring && msource[i] == '/' && msource[i+1] == '/'){
			scomment++;
			onswitch = true;
		}
		if(!instring && lcomment && msource[i-2] == '*' && msource[i-1] == '/')
			lcomment--;
		if(!instring && scomment && !onswitch && (msource[i-1] == '\n' || (msource[i-2] == '\r' && msource[i-1] == '\n' )))
			scomment--;

	//	cout <<"i: " << i <<  "lcomment "  << lcomment << " ";
	//	cout << "scomment "  << scomment <<endl;

		if(!lcomment && !scomment)
			msourcecleanout.append(1,msource[i]);
		i++;
	}

//	cout << "lcomment "  << lcomment <<endl;
//	cout << "scomment "  << scomment <<endl;

//	cout << msource << endl << endl;
//	cout << "Cleaned: " << endl;
//	cout << msourcecleanout << endl << endl;
}

void KernelFile::makestandard(){

	 size_t foundHere;
	 std::string amdstring = "cl_amd_fp64";
	 std::string khrstring = "cl_khr_fp64";
	 std::string temp =  msourceclean;
	 if((foundHere = temp.find(amdstring, 0)) != string::npos)
	 {
		 mstandardsource = temp.replace(foundHere, amdstring.size(), khrstring);
		// cout << "REPLACED!" << endl;
	 } else {
		 mstandardsource =  msourceclean;
	 }

	// cout << mstandardsource << endl << endl << endl;
}



void KernelFile::removeout(){
	msourceclean = "";
	size_t i=0;
	size_t index =0;
	while(i < msourcecleanout.length()-1){
		// search for the next occurence of "__kernel"
		index = msourcecleanout.find("__kernel", index);
		if(index == string::npos){
	//		cout << "done" << endl;
			while(i < msourcecleanout.length()){
				msourceclean.append(1,msourcecleanout[i]);
				i++;
			}
			break;
		}
//		cout << "kernel found at " << index << endl;

		// copy all the text until there
		while(i < index){
			msourceclean.append(1,msourcecleanout[i]);
			i++;
		}
		// search for the bracket opening the argument list
		size_t nameend = msourcecleanout.find("(", index);
		index = nameend+1;
		// copy all the text until there
		while(i < index){
			msourceclean.append(1,msourcecleanout[i]);
			i++;
		}
	//	cout << "in bracket, " << index  << endl;
		// search for the bracket closing the argument list
		nameend = msourcecleanout.find(")", index);
		index = nameend+1;
	//	cout << "closing bracket at " << index  << endl;
		// copy all the text until there, except for the "out"
		while(i < index){
			if(msourcecleanout[i] == ' ' &&
			   msourcecleanout[i+1] == 'o' &&
			   msourcecleanout[i+2] == 'u' &&
			   msourcecleanout[i+3] == 't' &&
			   msourcecleanout[i+4] == ' '){
				//cout << "out found" << endl;
				i = i+4;
			}
			msourceclean.append(1,msourcecleanout[i]);
			i++;
		}

	}
//	cout << "OutCleaned: " << endl;
//	cout << msourceclean << endl << endl;
}



const vector<Signature *> KernelFile::signatures() const{
	vector<Signature *> result;
	if(msourcecleanout == ""){
		cout << "KernelFile::signatures: Kernel file not open or empty - aborting!" << endl;
		return result;
	}

	/// find "global" kernels - those returning void
	size_t index =0;
	while(true){
		// find "__kernel"
		index = msourcecleanout.find("__kernel", index);
		if(index == string::npos)
			break;

		// move past "__kernel" and any spaces following it
		index += 8;
		while(msourcecleanout[index]==' ')
			index++;

		// there should be a "void" now
		size_t vindex = msourcecleanout.find("void", index);
		if(vindex != index)
			break;

		// move past the void and any following spaces
		index+= 4;
		while(msourcecleanout[index]==' ' || msourcecleanout[index]=='\n' || msourcecleanout[index]=='\r'||  msourcecleanout[index]=='\t')
				index++;

		// we should now be at the function name
		size_t namestart = index;

		// search for the bracket opening the argument list
		size_t nameend = msourcecleanout.find("(", index);
		index = nameend+1;

		// there might be spaces before the bracket
		while(msourcecleanout[nameend] == ' '|| msourcecleanout[index]=='\n' || msourcecleanout[index]=='\r'||  msourcecleanout[index]=='\t')
			nameend--;

		// ensure that there is something...
		assert(nameend-namestart >0);

		// and copy it to name
		string name = msourcecleanout.substr(namestart, nameend-namestart);
		//cout <<"-" <<name << "-" <<endl;


		vector<string> vqualifier;
		vector<string> vtype;
		vector<string> vname;
		vector<bool> output;
		// Now for the arguments....
		while(true){
			string qualifier = "";
			string type = "";
			string aname = "";
			bool oput = false;
			//skip any spaces or newlines
			while(msourcecleanout[index]==' ' || msourcecleanout[index]=='\n' || msourcecleanout[index]=='\r'||  msourcecleanout[index]=='\t')
				index++;
			// check if there is a qualifier; they start with "__"
			if(msourcecleanout[index] == '_' && msourcecleanout[index+1] == '_'){
				// assume we get the qualifier here
				while(msourcecleanout[index]!=' ' &&
						msourcecleanout[index]!='\n' &&
						msourcecleanout[index]!='\r' &&
						msourcecleanout[index]!='\t'){
					qualifier.append(1,msourcecleanout[index]);
					index++;
				}
				// check whether we get an "out" qualifyer here
				//skip any spaces or newlines
				while(msourcecleanout[index]==' ' || msourcecleanout[index]=='\n' || msourcecleanout[index]=='\r' ||  msourcecleanout[index]=='\t')
					index++;
				if(msourcecleanout[index] =='o' &&
				   msourcecleanout[index+1] =='u' &&
				   msourcecleanout[index+2] =='t' &&
				   (msourcecleanout[index+3]==' ' || msourcecleanout[index+3]=='\n' || msourcecleanout[index+3]=='\r' ||  msourcecleanout[index+3]=='\t')){
					oput = true;
					index = index+3;
				}
			}
			//cout << qualifier << endl;
			//skip any spaces or newlines
			while(msourcecleanout[index]==' ' || msourcecleanout[index]=='\n' || msourcecleanout[index]=='\r' ||  msourcecleanout[index]=='\t')
				index++;
			// assume we get the type here
			while(msourcecleanout[index]!=' ' &&
				  msourcecleanout[index]!='\n' &&
				  msourcecleanout[index]!='\r' &&
				  msourcecleanout[index]!='\t'){
				type.append(1,msourcecleanout[index]);
				index++;
			}
			//skip any spaces or newlines
			while(msourcecleanout[index]==' ' || msourcecleanout[index]=='\n' || msourcecleanout[index]=='\r'||  msourcecleanout[index]=='\t')
				index++;
			//there might be the little asterisk for a pointer type
			if(msourcecleanout[index]=='*'){
				type.append(1,msourcecleanout[index]);
				index++;
				//skip any spaces or newlines
				while(msourcecleanout[index]==' ' || msourcecleanout[index]=='\n' || msourcecleanout[index]=='\r'||  msourcecleanout[index]=='\t')
					index++;
			}
			//cout << type << endl;
			// assume we get the name here
			while(msourcecleanout[index]!=' ' &&
				  msourcecleanout[index]!='\n' &&
				  msourcecleanout[index]!='\r' &&
				  msourcecleanout[index]!=',' &&
				  msourcecleanout[index]!='\t'&&
				  msourcecleanout[index]!=')' ){
				aname.append(1,msourcecleanout[index]);
				index++;
			}
			//cout << aname << endl;
			//skip any spaces or newlines
			while(msourcecleanout[index]==' ' || msourcecleanout[index]=='\n' || msourcecleanout[index]=='\r' ||  msourcecleanout[index]=='\t')
				index++;
			//ensure we get a comma or a closing bracket here
			if(msourcecleanout[index] == ',' || msourcecleanout[index] == ')'){
				vqualifier.push_back(qualifier);
				vtype.push_back(type);
				vname.push_back(aname);
				output.push_back(oput);
				if(msourcecleanout[index] == ')'){
					index++;
					break;
				}
				index++;
			} else {
				cout << "Error, badly formatted argument list in fuction" << name << " aborting!" << endl;
				cout << msourcecleanout[index] << endl;
				assert(0);
			}
		}
		Signature * sig = new Signature(name, vname, vtype, vqualifier,output);
		result.push_back(sig);
	}



	return result;
}


KernelFile::~KernelFile()
{
    
}

