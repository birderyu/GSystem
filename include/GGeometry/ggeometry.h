/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	ggeometry.h
** @brief	基础几何接口的定义
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
**
****************************************************************************/

#ifndef _GEOMETRY_GEOMETRY_H_
#define _GEOMETRY_GEOMETRY_H_

#include "GCore/gobject.h"
#include "ggeodef.h"

namespace gsystem { // gsystem
	namespace geom { // gsystem.geom
		class GGeometry;
		class GGeometryFactory;
		class GEnvelope;
		class GCoordinate;
		class GCoordinateSequence;
		typedef GSharedPointer<GGeometry> GGeometryPtr;
	} // namespace gsystem.geom
} // namespace gsystem

namespace gsystem { // gsystem
namespace geom { // gsystem.geom

/****************************************************************************
**
** @brief		基础几何接口
**
** 基础几何类型是所有几何对象接口的基类，采用要素模型的思想进行了一层接口封装。
**
****************************************************************************/
class GAPI GGeometry 
	: virtual public GObject
	, virtual public GSerializable
{
public:
	/****************************************************************************
	**
	** @name	~GGeometry
	** @brief	析构函数（destructor）
	**
	** 析构函数应该是虚拟的（virtual）。
	**
	****************************************************************************/
	virtual ~GGeometry() = 0;

	/****************************************************************************
	**
	** @name	Factory
	** @brief	获取当前几何对象的工厂
	** @return	{const GGeometryFactory *} 几何对象工厂
	**
	****************************************************************************/
	virtual const GGeometryFactory *Factory() const = 0;

	/****************************************************************************
	**
	** @name	Valid
	** @brief	当前实例是否有效
	** @return	{gbool} 有效则返回true，否则返回false
	**
	****************************************************************************/
	virtual gbool Valid() const = 0;

	/****************************************************************************
	**
	** @name	GeometryType
	** @brief	获取当前对象的几何类型
	** @return	{GGeometryType} 几何类型枚举
	**
	****************************************************************************/
	virtual GGeometryType GeometryType() const = 0;

	/****************************************************************************
	**
	** @name	Dimension
	** @brief	获取当前对象的维度
	** @return	{GDimension} 维度枚举
	**
	****************************************************************************/
	virtual GDimension Dimension() const = 0;

	/****************************************************************************
	**
	** @name	Envelope
	** @brief	生成当前几何对象的外包
	** @return	{GEnvelope} 外包
	**
	****************************************************************************/
	virtual GEnvelope Envelope() const = 0;

	/****************************************************************************
	**
	** @name	CoordinateSequence
	** @brief	生成当前几何对象的坐标序列
	** @return	{GCoordinateSequence} 坐标序列
	**
	****************************************************************************/
	virtual GCoordinateSequence CoordinateSequence() const = 0;

	virtual GDimension GetCoordinateDimension() const;
	virtual gbool IsEmpty() const;
	virtual gbool IsSimple() const;
	virtual gbool IsRing() const;

	virtual GGeometryPtr CloneGeometry() const;

	//virtual gbool Clear() = 0;
	//virtual GGeometryP Flatten() const = 0; // 从三维变成二维

	//virtual greal Distance(const GGeometry &geo) const = 0;
	//virtual gbool Touches(const GGeometry &geo) const = 0;
	//virtual gbool Intersects(const GGeometry &geo) const = 0;
	//virtual gbool Disjoint(const GGeometry &geo) const = 0;
	//virtual gbool Crosses(const GGeometry &geo) const = 0;
	//virtual gbool Within(const GGeometry &geo) const = 0;
	//virtual gbool Contains(const GGeometry &geo) const = 0;
	//virtual gbool Overlaps(const GGeometry &geo) const = 0;
	//virtual gbool Covers(const GGeometry &geo) const = 0;
	//virtual gbool CoveredBy(const GGeometry &geo) const = 0;

	//virtual GGeometryP Buffer() const = 0;
	//virtual GGeometryP Intersection(const GGeometry &geo) const = 0;
	//virtual GGeometryP Union(const GGeometry &geo) const = 0;
	//virtual GGeometryP Difference(const GGeometry &geo) const = 0;
};

}
}

#endif // _GEOMETRY_GEOMETRY_H_