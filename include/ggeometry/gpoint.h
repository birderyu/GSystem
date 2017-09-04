#ifndef _GEOMETRY_POINT_H_
#define _GEOMETRY_POINT_H_

#include "ggeometry.h"

namespace gsystem { // gsystem
namespace geom { // gsystem.geom

class GAPI GPoint
	: virtual public GGeometry
{
public:
	virtual ~GPoint() = 0;

	virtual greal &X() = 0;
	virtual greal  X() const = 0;
	virtual greal &Y() = 0;
	virtual greal  Y() const = 0;
	virtual greal &Z() = 0;
	virtual greal  Z() const = 0;

	virtual gvoid SetX(greal x) = 0;
	virtual gvoid SetY(greal y) = 0;
	virtual gvoid SetZ(greal z) = 0;
};

typedef GSharedPtr<GPoint> GPointPtr;

}
}

#endif // _GEOMETRY_POINT_H_