#ifndef KERNELFILE_H_
#define KERNELFILE_H_

#include <vector>
#include <string>
#include <fstream>

class Signature;

/// Get the current directory
extern std::string getCurrentDir();

/// KernelFile for the opencl kernel file handling
class KernelFile
{
public:
    /// Default constructor
    KernelFile(): msource(""), msourceclean(""), mstandardsource("") {}

    /// Destructor
    ~KernelFile();

    //! Opens the CL kernel file
    bool open(const char* fileName);

    //! Returns a pointer to the string object with the source code
    const std::string&  source() const { return msource; }

    //! Returns a pointer to the string object with the source code cleaned of comments and out qulifyers
    const std::string&  cleansource() const { return msourceclean; }

    //! Returns a pointer to the string object with the source code cleaned of comments
    const std::string&  cleansourceout() const { return msourcecleanout; }

    /// Return a vector with the signatures of the kernels in the file
    const std::vector<Signature *>  signatures() const;

    /// Replace the amd double precision extension with the standard one
    const std::string& standardsource() const {return mstandardsource;}

private:
    //! Disable copy constructor
    KernelFile(const KernelFile&);

    //! Disable operator=
    KernelFile& operator=(const KernelFile&);

    //! Remove comments from the source file
    void removeComments();

    //! Remove out qulifyers from the source file
    void removeout();

    //! Change the amd 64 bit pragma to the khronos one
    void makestandard();


    std::string     msource;         //!< source code of the CL program
    std::string     msourceclean;    //!< source code of the CL program w/o comments and out qualifyers
    std::string     msourcecleanout; //!< source code of the CL program w/o comments
    std::string     mstandardsource; //!< source code of the CL program w/o comments, qualifyers and the standard double
};




/// A class for holding kernel signatures
class Signature
{
public:
	/// Constructor
	Signature(	std::string name,
				std::vector<std::string> arguments,
				std::vector<std::string> types,
				std::vector<std::string> qualifiers,
				std::vector<bool> output):
				mname(name), marguments(arguments),mtypes(types),mqualifiers(qualifiers), moutput(output){};
	/// Destructor
	~Signature(){};
	/// Get the function name
	const std::string & GetName() const {return mname;};
	/// Get the arguments
	const std::vector<std::string> & GetArguments() const {return marguments;};
	/// Get one of the arguments
	const std::string & GetArgument(int i) const {return marguments[i];};
	/// Get the types
	const std::vector<std::string> & GetTypes() const {return mtypes;};
	/// Get one of the types
	const std::string & GetType(int i) const {return mtypes[i];};
	/// Get the qualifiers
	const std::vector<std::string> & GetQulaifiers() const {return mqualifiers;};
	/// Get one of the qualifiers
	const std::string & GetQualifier(int i) const {return mqualifiers[i];};
	/// Get the output truth values
	const std::vector<bool> & GetOutput() const {return moutput;};
	/// Is the current argument an output?
	const bool IsOutput(int i) const {return moutput[i];};

protected:
	std::string mname;				      //!< function name
	std::vector<std::string> marguments;    //!< argument names
	std::vector<std::string> mtypes;        //!< argument types
	std::vector<std::string> mqualifiers;   //!< argument qualifiers
	std::vector<bool> 	     moutput;       //!< argument is an output
};

#endif
