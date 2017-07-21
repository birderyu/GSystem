/// �Ƕ������ڴ��
/// ������Ƕ������ڴ�
/// �����ȥ���ڴ治����
/// �̲߳���ȫ

#ifndef _CORE_MEMORY_STORE_H_
#define _CORE_MEMORY_STORE_H_

#include "gblock.h"

namespace gsystem { // gsystem

class GAPI GMemoryStore
{
	// �ڴ�ص�Ԫ
	struct GMemCell
	{
		//�ڴ��
		GBlock m_tBlock;

		//���
		gsize m_nCursor;

		//ָ����һ���ڴ��
		GMemCell *m_pNext;

		GMemCell(gsize nSize);
		~GMemCell();
	};

public:
	GMemoryStore(gsize nInitSzie = 2048, gsize nGrowSize = 1024);
	~GMemoryStore();

	// �����ڴ棬����ʧ���򷵻�NULL
	gptr Alloc(gsize);

private:
	gsize m_nInitSize;		// ��ʼ��С
	gsize m_nGrowSize;		// ������С
	GMemCell *m_pList;		// �ڴ������
};

} // namespace gsystem

#endif // _CORE_MEMORY_STORE_H_