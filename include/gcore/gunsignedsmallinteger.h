#ifndef _CORE_UNSIGNED_SMALL_INTEGER_H_
#define _CORE_UNSIGNED_SMALL_INTEGER_H_

#include "gunsignedcharacter.h"

namespace gsystem { // gsystem

class GAPI GUnsignedSmallInteger 
	: public GNumber<gusmall>
{
public:
	static gusmall MaxValue();
	static gusmall MinValue();
	static GUnsignedSmallInteger ValueOf(const GString &);

public:
	GUnsignedSmallInteger(gusmall val = 0);
	GUnsignedSmallInteger(const GUnsignedSmallInteger &);
	virtual ~GUnsignedSmallInteger();

	virtual guint ClassCode() const GNOEXCEPT;
};

typedef GUnsignedSmallInteger GUnsignedSmallInt;
typedef GUnsignedSmallInteger GUSmallInteger;
typedef GUnsignedSmallInteger GUSmallInt;
typedef GUnsignedSmallInteger GUSmall;
typedef GUnsignedSmallInteger GUnsignedInteger8;
typedef GUnsignedSmallInteger GUInteger8;
typedef GUnsignedSmallInteger GUnsignedInt8;
typedef GUnsignedSmallInteger GUInt8;

} // namespace gsystem

#endif // _CORE_UNSIGNED_SMALL_INTEGER_H_