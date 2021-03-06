/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file garray.h
** @brief 数组接口
** @author birderyu
** @contact https://github.com/birderyu
** @date 2017-1-24
** @version 1.0.0
**
** 该文件包含了数组的接口声明，数组是一种同类型数据集合的数据结构，具有常量级的下标检索效率。
**
********************************************************************************/

#ifndef _CORE_ARRAY_H_
#define _CORE_ARRAY_H_

#include "gstruct.h"
#include "gobject.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 数组
** @template T {type} 数组元素的类型
**
********************************************************************************/
template <typename T>
class GArray
	: public GListT<GArray<T>>
	, virtual public GObject
{
public:
	/****************************************************************************
	**
	** @name ~GArray
	** @brief 析构函数（destructor）
	**
	****************************************************************************/
	virtual ~GArray() = 0 {}

	/****************************************************************************
	**
	** @name Size
	** @brief 获取数组元素的数量
	** @return {gsize} 元素的数量
	**
	****************************************************************************/
	virtual gsize Size() const = 0;

	/****************************************************************************
	**
	** @name IsEmpty
	** @brief 判断数组是否为空
	** @return {gbool} 若元素的数量为0，则返回true，否则返回false
	**
	****************************************************************************/
	virtual gbool IsEmpty() const = 0;

	/****************************************************************************
	**
	** @name GetAt
	** @brief 获取指定位置的元素
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {T &} 元素的引用
	**
	****************************************************************************/
	virtual T &GetAt(gsize pos) = 0;

	/****************************************************************************
	**
	** @name GetAt
	** @brief 获取指定位置的元素
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {const T &} 元素的引用
	**
	****************************************************************************/
	virtual const T &GetAt(gsize pos) const = 0;

	/****************************************************************************
	**
	** @name CursorAt
	** @brief 获取指定位置的元素的光标
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {T *} 元素的指针
	**
	****************************************************************************/
	virtual T *CursorAt(gsize pos) = 0;

	/****************************************************************************
	**
	** @name CursorAt
	** @brief 获取指定位置的元素的光标
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {const T *} 元素的指针
	**
	****************************************************************************/
	virtual const T *CursorAt(gsize pos) const = 0;

	/****************************************************************************
	**
	** @name First
	** @brief 获取第一个元素
	** @return {T &} 元素的引用
	**
	****************************************************************************/
	T &First();

	/****************************************************************************
	**
	** @name First
	** @brief 获取第一个元素
	** @return {const T &} 元素的引用
	**
	****************************************************************************/
	const T &First() const;

	/****************************************************************************
	**
	** @name Last
	** @brief 获取最后一个元素
	** @return {T &} 元素的引用
	**
	****************************************************************************/
	T &Last();

	/****************************************************************************
	**
	** @name Last
	** @brief 获取最后一个元素
	** @return {const T &} 元素的引用
	**
	****************************************************************************/
	const T &Last() const;

	/****************************************************************************
	**
	** @name FirstCursor
	** @brief 获取第一个元素的指针
	** @return {T *} 元素的引用
	**
	****************************************************************************/
	T *FirstCursor();

	/****************************************************************************
	**
	** @name FirstCursor
	** @brief 获取第一个元素的指针
	** @return {const T *} 元素的引用
	**
	****************************************************************************/
	const T *FirstCursor() const;
	
	/****************************************************************************
	**
	** @name LastCursor
	** @brief 获取最后一个元素的指针
	** @return {T *} 元素的引用
	**
	****************************************************************************/
	T *LastCursor();

	/****************************************************************************
	**
	** @name LastCursor
	** @brief 获取最后一个元素的指针
	** @return {const T *} 元素的引用
	**
	****************************************************************************/
	const T *LastCursor() const;

	/****************************************************************************
	**
	** @name Contains
	** @brief 判断数组是否包含值
	** @param [in] value {const T &} 值的引用
	** @return {gbool} 若包含该值，则返回true，否则返回false
	**
	****************************************************************************/
	gbool Contains(const T &value) const;

	/****************************************************************************
	**
	** @name Contains
	** @brief 获取数组第一次出现值的下标
	** @param [in] value {const T &} 值的引用
	** @return {gsize} 值的下标，从0开始计数，若无则返回NULL_POS
	**
	****************************************************************************/
	gsize FirstIndexOf(const T &value) const;

	/****************************************************************************
	**
	** @name LastIndexOf
	** @brief 获取数组从最后开始第一次出现值的下标
	** @param [in] value {const T &} 值的引用
	** @return {gsize} 值的下标，从0开始计数，若无则返回NULL_POS
	**
	****************************************************************************/
	gsize LastIndexOf(const T &value) const;

	/****************************************************************************
	**
	** @name CountOf
	** @brief 判断数组中值的次数
	** @param [in] value {const T &} 值的引用
	** @return {gsize} 返回该值在数组中出现的次数
	**
	****************************************************************************/
	gsize CountOf(const T &value) const;

	/****************************************************************************
	**
	** @name Shuffle
	** @brief 随机打乱数组中值的顺序
	**
	****************************************************************************/
	gvoid Shuffle();

	/****************************************************************************
	**
	** @name operator[]
	** @brief 获取指定位置的元素
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {T &} 元素的引用
	**
	** 此方法的实现依赖于GetAt，因此不要在GetAt的实现中调用此方法
	**
	****************************************************************************/
	T &operator[](gsize pos);

	/****************************************************************************
	**
	** @name operator[]
	** @brief 获取指定位置的元素
	** @param [in] pos {gsize} 元素的下标，从0开始计数
	** @return {const T &} 元素的引用
	**
	** 此方法的实现依赖于GetAt，因此不要在GetAt的实现中调用此方法
	**
	****************************************************************************/
	const T &operator[](gsize pos) const;
};

} // namespace gsystem

#include "inline/garray.inl"

#endif // _CORE_ARRAY_H_