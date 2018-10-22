/// \file GPURuncounter.h
/*
 * GPURuncounter.h
 *
 *  Created on: Dec 3, 2008
 *      Author: nberger
 */

#ifndef GPURUNCOUNTER_H_
#define GPURUNCOUNTER_H_

/// Class to provide a counter of runs e.g. for numbering output files
/** This is a singleton class, i.e. there can be only one instance of it per program.
 * The class does not provide a locking mechanism to ensure consistency in case of multiple
 * program instances running in the same directory*/
class GPURuncounter {
public:
	/// Destructor
	virtual ~GPURuncounter();
	/// Get a pointer to the single instance
	static GPURuncounter * GetInstance(char * name);
	/// Get the number of fits performed up to now
	int GetFitCounter() const {
			ReadFile();
			return mfitcounter;};
	/// Get the number of program runs up to now
	int GetRunCounter() const {
		ReadFile();
		return mruncounter;};
	/// Increment the Fit counter
	int IncrementFitCounter(){
		ReadFile();
		mfitcounter++;
		WriteFile();
		return mfitcounter;
	};


protected:
	/// Protected constructor
	GPURuncounter(char * name);

	/// Non-implemented Copy Constructor to prevent copying
	GPURuncounter(const GPURuncounter& other);
	/// Non-implemented assignment operator to prevent copying
	GPURuncounter& operator = (const GPURuncounter& other);

	/// Write the file
	void WriteFile();
	/// Read the file
	void ReadFile() const;

	/// Count runs
	mutable int mruncounter;
	/// Count fits
	mutable int mfitcounter;
	/// Name
	char * mname;

	/// Singleton pointer
	static GPURuncounter * minstance;
};

#endif /* GPURUNCOUNTER_H_ */
