#ifndef _CSGEO_CSCOORDINATE_H_
#define _CSGEO_CSCOORDINATE_H_

#include "CsGeoGlobal.h"
#include "CsObject.h"

class CsGeo_Export CsCoordinate :public CsObject
{
public:
	CsCoordinate();
	CsCoordinate(const cs_real nX, const cs_real nY);
	CsCoordinate(const cs_real nX, const cs_real nY, const cs_real nZ);
	CsCoordinate(const CsCoordinate &tCoord);
	~CsCoordinate();
	CsString ToString() const;

	cs_real GetX() const;
	cs_bool SetX(const cs_real nX);
	cs_real GetY() const;
	cs_bool SetY(const cs_real nY);
	cs_real GetZ() const;
	cs_bool SetZ(const cs_real nZ);
};

#endif // _CSGEO_CSCOORDINATE_H_