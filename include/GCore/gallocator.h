/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gallocator.h
** @brief	空间分配器
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-24
** @version	0.1
**
** 包含两个操作：
** 分配内存操作：allocate
** 释放内存操作：deallocate
**
****************************************************************************/
#ifndef _CORE_ALLOCATOR_H_
#define _CORE_ALLOCATOR_H_

#include "gmemory.h"

namespace gsystem { // gsystem

// 全局的空间分配器，相当于GMalloc、GCalloc和GRealloc
template <typename ClassT> ClassT *GAllocate(gsize n = 1) GEXCEPT(false);
template <typename ClassT> gvoid GDeallocate(ClassT *ptr) GNOEXCEPT;
template <typename ClassT> ClassT *GReallocate(ClassT *oldptr, gsize newsize) GEXCEPT(false);

// 一个默认的空间分配器
template <typename ClassT>
class GAllocator
{
public:
	ClassT *Allocate(gsize n = 1) GEXCEPT(false);
	gvoid Deallocate(ClassT *ptr) GNOEXCEPT;
	ClassT *Reallocate(ClassT *oldptr, gsize newsize) GEXCEPT(false);
};

} // namespace gsystem

#include "gallocator.inl"

#endif // _CORE_ALLOCATOR_H_
