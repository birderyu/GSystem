#include "gmemory.h"
#include "dlmalloc.h"

namespace gsystem { // gsystem

gptr GMalloc(gsize size)
{
	return dlmalloc(size);
}

gptr GCalloc(gsize n, gsize size)
{
	return dlcalloc(n, size);
}

gptr GRealloc(gptr oldptr, gsize newsize)
{
	return dlrealloc(oldptr, newsize);
}

gvoid GFree(gptr pfree)
{
	dlfree(pfree);
}

gptr GMemCopy(gptr dst, gcptr src, gsize size)
{
	return memcpy(dst, src, size);
}

gptr GMemMove(gptr dst, gcptr src, gsize size)
{
	return memmove(dst, src, size);
}

gptr GMemSet(gptr dst, gbyte value, gsize size)
{
	return memset(dst, (gint)value, size);
}

} // namespace gsystem