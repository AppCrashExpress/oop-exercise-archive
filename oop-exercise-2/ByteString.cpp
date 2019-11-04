#include <string>
#include <exception>
#include "ByteString.h"

const unsigned long long L_BYTE = 9223372036854775808U; // Value of last bit of ULLong type 
const size_t B_STR_SIZE = 128;

//==========================================================In-class functions

  //Operations on bytes, returning the copy
ByteString ByteString::operator & (const ByteString& rhs) const
{
	ByteString res(msp & rhs.msp, lsp & rhs.lsp);
	return res;
}

ByteString ByteString::operator | (const ByteString& rhs) const
{
	ByteString res(msp | rhs.msp, lsp | rhs.lsp);
	return res;
}

ByteString ByteString::operator ^ (const ByteString& rhs) const
{
	ByteString res(msp ^ rhs.msp, lsp ^ rhs.lsp);
	return res;
}

ByteString ByteString::operator >> (const size_t& by) const
{
	ByteString res = *this;
	if (by > 63)
	{
		res.lsp = res.msp;
		res.msp = 0;
		res.lsp >>= by - 64;
	}
	else
	{
		res.lsp >>= by;
		res.lsp |= res.msp << (64 - by);
		res.msp >>= by;
	}
	return res;
}

ByteString ByteString::operator << (const size_t& by) const
{
	ByteString res = *this;
	if (by > 63)
	{
		res.msp = res.lsp;
		res.lsp = 0;
		res.msp <<= by - 64;
	}
	else
	{
		res.msp <<= by;
		res.msp |= res.lsp >> (64 - by);
		res.lsp <<= by;
	}
	return res;
}


	//Operations on existing ByteString
ByteString& ByteString::operator &= (const ByteString& rhs)
{
	msp &= rhs.msp;
	lsp &= rhs.lsp;
	return *this;
}

ByteString& ByteString::operator |= (const ByteString& rhs)
{
	msp |= rhs.msp;
	lsp |= rhs.lsp;
	return *this;
}

ByteString& ByteString::operator ^= (const ByteString& rhs)
{
	msp ^= rhs.msp;
	lsp ^= rhs.lsp;
	return *this;
}

ByteString& ByteString::operator >>= (const size_t& by)
{
  if (by > 63)
  {
    lsp = msp;
    msp = 0;
    lsp >>= by - 64;
  }
  else
  {
    lsp >>= by;
    lsp |= msp << (64 - by);
    msp >>= by;
  }
  return *this;
}

ByteString& ByteString::operator <<= (const size_t& by)
{
  if (by > 63)
  {
    msp = lsp;
    lsp = 0;
    msp <<= by - 64;
  }
  else
  {
    msp <<= by;
    msp |= lsp >> (64 - by);
    lsp <<= by;
  }
  return *this;
}

ByteString& ByteString::operator ~ (void)
{
	msp = ~msp;
  lsp = ~lsp;
	return *this;
}


	//Comparison
bool ByteString::operator < (const ByteString& other) const
{
  if (msp != other.msp) return msp < other.msp;
  return lsp < other.lsp;
}

bool ByteString::operator > (const ByteString& other) const
{
  if (msp != other.msp) return msp > other.msp;
  return lsp > other.lsp;
}

bool ByteString::operator == (const ByteString& other) const 
{ return msp == other.msp && lsp == other.lsp; }

bool ByteString::includes(const ByteString& rhs) const
{
	for (size_t i = 0; i < 64; ++i)
		if (( (rhs.msp >> i & 1) == 1 ) && ( (msp >> i & 1) != 1 )) return false;

	for (size_t i = 0; i < 64; ++i)
		if (( (rhs.lsp >> i & 1) == 1 ) && ( (lsp >> i & 1) != 1 )) return false;

	return true;
}

	//Calculating amount of 1's
size_t ByteString::Ones() const
{
	size_t ones{ 0 };
	for (size_t i = 0; i < 64; ++i)
		if ((msp >> i & 1) == 1) ++ones;

	for (size_t i = 0; i < 64; ++i)
		if ((lsp >> i & 1) == 1) ++ones;

	return ones;
}
//==========================================================Outside class

bool CompareOnes(const ByteString& lhs, const ByteString& rhs)
{
	if (lhs.Ones() == rhs.Ones()) return true;
	return false;
}

std::istream& operator >> (std::istream& is, ByteString& rhs)
{
	std::string str;
	is >> str;
	if (str.size() > B_STR_SIZE) throw std::runtime_error("Input ByteString overflow");
	if (str.size() == 0)
	{
		rhs.msp = rhs.lsp = 0;
		return is;
	}
	size_t size = str.size();
	unsigned long long msp{ 0 }, lsp{ 0 };
	if (size <= B_STR_SIZE / 2)
	{
		for (size_t i = 0; i < size; ++i)
		{
			lsp <<= 1;
			if (str[i] - '0') lsp |= 1;
		}
	}
	else
	{
		size_t i;
		for (i = 0; i < size - B_STR_SIZE / 2; ++i)
		{
			msp <<= 1;
			if (str[i] - '0') msp |= 1;
		}
		for (; i < size; ++i)
		{
			lsp <<= 1;
			if (str[i] - '0') lsp |= 1;
		}
	}
	rhs.msp = msp;
	rhs.lsp = lsp;
	return is;
}

std::ostream& operator << (std::ostream& os, ByteString& rhs)
{
  for (size_t i = 0; i < 64; ++i)
  {
	  if (!(i % 8) && i) os << " " << std::flush;
	  os << ( (rhs.msp << i) & L_BYTE ? 1 : 0);
  }

  std::cout << std::endl;

  for (size_t i = 0; i < 64; ++i)
  {
	  if (!(i % 8) && i) os << " " << std::flush;
	  os << ((rhs.lsp << i) & L_BYTE ? 1 : 0);
  }
  return os;
}

std::ostream& operator << (std::ostream& os, ByteString&& rhs)
{
	for (size_t i = 0; i < 64; ++i)
	{
		os << ((rhs.msp << i) & L_BYTE ? 1 : 0);
		if (!(i % 8) && i) os << " " << std::flush;
	}

	std::cout << std::endl;

	for (size_t i = 0; i < 64; ++i)
	{
		os << ((rhs.lsp << i) & L_BYTE ? 1 : 0);
		if (!(i % 8) && i) os << " " << std::flush;
	}
	return os;
}

ByteString operator "" _b(const char* str, std::size_t size) //find out the difference with std:: and without
{
	if (size > B_STR_SIZE) throw std::runtime_error("Input ByteString overflow");
  ByteString res;
	if (size == 0)
	{
		return res;
	}
	if (size <= B_STR_SIZE / 2)
	{
		for (size_t i = 0; i < size; ++i)
		{
			res.lsp <<= 1;
			if (str[i] - '0') res.lsp |= 1;
		}
	}
	else
	{
		size_t i;
		for (i = 0; i < size - B_STR_SIZE / 2; ++i)
		{
			res.msp <<= 1;
			if (str[i] - '0') res.msp |= 1;
		}
		for (; i < size; ++i)
		{
			res.lsp <<= 1;
			if (str[i] - '0') res.lsp |= 1;
		}
	}
	return res;
}
