#include "gstringpool.h"

namespace gsystem { // gsystem

GStringPool::GStringPool(gsize nInitSzie, gsize nMaxSize)
:m_tStore(nInitSzie, nInitSzie)
{

}

gptr GStringPool::Alloc(gsize size)
{
	GMap<gsize, GVector<gaddress>>::ConstIterator citer = m_tRecycle.ConstFind(size);
	if (citer != m_tRecycle.ConstEnd())
	{
		// TODO：从内存回收站中获取一块内存
	}
	return m_tStore.Alloc(size);
}

gvoid GStringPool::Free(gptr)
{

}

} // namespace gsystem
