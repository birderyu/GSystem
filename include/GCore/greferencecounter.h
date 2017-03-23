// ���ü�����
#ifndef _CORE_REFERENCE_COUNTER_H_
#define _CORE_REFERENCE_COUNTER_H_

#include "gnew.h"

namespace gsystem { // gsystem

template <typename ClassT>
class GReferenceCounter 
	: public GNewT<GReferenceCounter<ClassT>>
{
public:
	// count: ��ʼ���ü�����Ĭ��Ϊ1
	GReferenceCounter(ClassT *ptr, gsize count = 1);
	~GReferenceCounter();
	gsize Add();
	gvoid Release();
	gsize Count() const;
	ClassT *Pointer();
	const ClassT *Pointer() const;

private:
	gsize m_nCount;
	ClassT *m_pPointer;
};

} // namespace gsystem

#include "greferencecounter.inl"

#endif // _CORE_REFERENCE_COUNTER_H_