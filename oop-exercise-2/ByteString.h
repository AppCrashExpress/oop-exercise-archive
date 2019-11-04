#ifndef BYTE_STRING_H
#define BYTE_STRING_H

#include <string>
#include <iostream>

class ByteString
{
public:
	friend bool CompareOnes(const ByteString&, const ByteString&);
	friend std::istream& operator >> (std::istream&, ByteString& );
	friend std::ostream& operator << (std::ostream&, ByteString& );
	friend std::ostream& operator << (std::ostream&, ByteString&&);
	friend ByteString    operator "" _b(const char*, std::size_t);

	ByteString() : msp(0), lsp(0) {}
	ByteString(long long a, long long b) : msp(a), lsp(b) {}

  // = operator is default initialized
  //Operations on bytes, returning the copy
	ByteString operator &  (const ByteString&) const;
	ByteString operator |  (const ByteString&) const;
	ByteString operator ^  (const ByteString&) const;
	ByteString operator >> (const size_t&) const;
	ByteString operator << (const size_t&) const;

  //Operations on existing ByteString
	ByteString& operator &=  (const ByteString&);
	ByteString& operator |=  (const ByteString&);
	ByteString& operator ^=  (const ByteString&);
	ByteString& operator ~   (void);
	ByteString& operator >>= (const size_t&);
	ByteString& operator <<= (const size_t&);

  //Comparison
	bool operator <  (const ByteString&) const;
	bool operator >  (const ByteString&) const;
	bool operator == (const ByteString&) const;
	bool includes (const ByteString&) const;
 
  //Calculating amount of 1's
	size_t Ones() const;

private:
	unsigned long long msp, lsp; // As in - Most Significant Part, Least Significant Part;
};

bool CompareOnes(const ByteString&, const ByteString&);

std::istream& operator >> (std::istream& is, ByteString& rhs);
std::ostream& operator << (std::ostream&, ByteString&);
std::ostream& operator << (std::ostream&, ByteString&&);
ByteString    operator "" _b(const char*, std::size_t);

#endif

