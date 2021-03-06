/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gqueue.h
** @brief 队列接口
** @author birderyu
** @contact https://github.com/birderyu
** @date 2017-1-24
** @version 1.0.0
**
** 该文件包含了队列的接口声明，队列是一种限定操作的列表，其元素是先进先出（FIFO）的。
**
********************************************************************************/

#ifndef _CORE_QUEUE_H_
#define _CORE_QUEUE_H_

#include "gobject.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 队列
** @template T {type} 队列元素的类型
**
********************************************************************************/
template<typename T>
class GQueue
	: virtual public GObject
{
public:
	/****************************************************************************
	**
	** @name ~GQueue
	** @brief 析构函数（destructor）
	**
	****************************************************************************/
	virtual ~GQueue() = 0 {}

	/****************************************************************************
	**
	** @name Size
	** @brief 获取队列元素的数量
	** @return {gsize} 元素的数量
	**
	****************************************************************************/
	virtual gsize Size() const = 0;

	/****************************************************************************
	**
	** @name IsEmpty
	** @brief 判断队列是否为空
	** @return {gbool} 若元素的数量为0，则返回true，否则返回false
	**
	****************************************************************************/
	virtual gbool IsEmpty() const = 0;

	/****************************************************************************
	**
	** @name Destroy
	** @brief 销毁队列
	**
	****************************************************************************/
	virtual gvoid Destroy() = 0;

	/****************************************************************************
	**
	** @name Clear
	** @brief 清空队列
	**
	****************************************************************************/
	virtual gvoid Clear() = 0;

	/****************************************************************************
	**
	** @name EnQueue
	** @brief 入队
	** @param [in] value {const T &} 值
	**
	** 值将被拷贝一份入队
	**
	****************************************************************************/
	virtual gvoid EnQueue(const T &value) = 0;

	/****************************************************************************
	**
	** @name EnQueue
	** @brief 入队
	** @param [in] value {T &&} 值
	**
	** 值将被优先使用移动入队，若无法移动则使用拷贝
	**
	****************************************************************************/
	virtual gvoid EnQueue(T &&data) = 0;

	/****************************************************************************
	**
	** @name DeQueue
	** @brief 出队
	** @param [out] value {T *} 用于接受出队的值
	** @return {gbool} 若出队成功，则返回true，否则（队列为空）返回false
	**
	** 若参数为空（GNULL），则不会接受出队的值，否则会优先将出队的值移动到value中
	**
	****************************************************************************/
	virtual gbool DeQueue(T *value = GNULL) = 0;

	/****************************************************************************
	**
	** @name Head
	** @brief 获取队首元素
	** @return {const T &} 队首元素的引用
	**
	****************************************************************************/
	virtual const T &Head() const = 0;

	/****************************************************************************
	**
	** @name Head
	** @brief 获取队首元素
	** @return {T &} 队首元素的引用
	**
	****************************************************************************/
	virtual T &Head() = 0;
};

} // namespace gsystem

#endif // _CORE_QUEUE_H_