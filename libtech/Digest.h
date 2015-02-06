/*
 * 产生摘要信息，包含sum摘要信息和MD5摘要信息
 *@author wisfern
 */
#ifndef NIT_BASE_DIGEST_H
#define NIT_BASE_DIGEST_H

#include <copyable.h>
#include <libdefs.h>
#include <fstream>

__NIT_NAMESPACE_BEGIN

class NIT_API Digest : public copyable
{
protected:
	Digest(){}

public:
	virtual void init() = 0;
	virtual ~Digest(){}
};

class NIT_API MD5Digest : public Digest
{
public:
	MD5Digest(); // simple initializer
	MD5Digest(FILE *file);            	   // digest file, close, finalize
	MD5Digest(std::istream& stream);       // digest stream, finalize
	MD5Digest(std::ifstream& stream);      // digest stream, close, finalize
	MD5Digest(const char *string,unsigned int string_length); 	 // digest string, finalize
	MD5Digest(unsigned char *string,unsigned int string_length); // digest string, finalize
	virtual ~MD5Digest(){}
  
protected:
	void  update (FILE *file);
	void  update (std::istream& stream);
	void  update (std::ifstream& stream);
	void  update (unsigned char *input, unsigned int input_length);
	void  finalize();
	
public:
	// methods to acquire finalized result
	unsigned char *raw_digest ();  // digest as a 16-byte binary array
	std::string   hex_digest ();   // digest as a 33-byte ascii-hex string
	
private:
	// first, some types:
	typedef unsigned       int uint4; // assumes integer is 4 words long
	typedef unsigned short int uint2; // assumes short integer is 2 words long
	typedef unsigned      char uint1; // assumes char is 1 word long

	// next, the private data:
	uint4 state[4];
	uint4 count[2];     // number of *bits*, mod 2^64
	uint1 buffer[64];   // input buffer
	uint1 digest[16];
	uint1 finalized;
	
	// last, the private methods, mostly static:
	void init();               		// called by all constructors
	void transform(uint1 *buffer);  // does the real update work.  Note
                                    // that length is implied to be 64.
                                    
	static void encode(uint1 *dest, uint4 *src, uint4 length);
	static void decode(uint4 *dest, uint1 *src, uint4 length);
	static void memcpy(uint1 *dest, uint1 *src, uint4 length);
	static void memset(uint1 *start, uint1 val, uint4 length);
};

class NIT_API ChecksumDigest : public Digest
{
};


//returns md5 for a given file
std::string getMD5(std::ifstream& stream);
std::string getMD5(const char* str,unsigned int str_len);
std::string getMD5(const char* str);

//compares md5's for two files
//returns -1 if unable ot open file
//returns 0 if files are different
//returns 1 if files are same
bool filesMatch(std::ifstream& stream, std::string oldMD5);

__NIT_NAMESPACE_END

#endif /* #ifndef NIT_BASE_DIGEST_H */
