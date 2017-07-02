#ifndef _CORE_ARRAYS_INLINE_
#define _CORE_ARRAYS_INLINE_

#include "gallocator.h"
#include "gconstructor.h"

namespace gsystem { // gsystem
namespace detail { // gsystem.detail
namespace arrays { // gsystem.detail.arrays

/// DataT�������õĹ��캯�������蹹�죬�������ڴ�
template <typename DataT> GINLINE 
DataT *_GArrayCreate(gsize size, GTrueType) GEXCEPT(false)
{
	/// ������������Ҫ����
	return GAllocate<DataT>(size);
}

/// DataT���������õĹ��캯���������ڴ�֮�����ε���Ԫ�صĹ��캯��
template <typename DataT> GINLINE 
DataT *_GArrayCreate(gsize size, GFalseType) GEXCEPT(false)
{
	DataT *arr = GAllocate<DataT>(size);
	for (gsize i = 0; i < size; i++)
	{
		GDefaultConstruct<DataT>(arr + i);
	}
	return arr;
}

/// DataT���������ͣ�ֱ��ʹ���ڴ濽��������ɿ��������߼�
template <typename DataT> GINLINE 
DataT *_GArrayCreate(const DataT *copy_arr, gsize copy_start, gsize copy_size, GTrueType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(copy_size);
	GMemCopy(new_arr, copy_arr + copy_start, sizeof(DataT) * copy_size);
	return new_arr;
}

/// DataT�����������ͣ����ÿ����������캯������
template <typename DataT> GINLINE 
DataT *_GArrayCreate(const DataT *copy_arr, gsize copy_start, gsize copy_size, GFalseType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(copy_size);
	for (gsize i = 0; i < copy_size; i++)
	{
		GCopyConstruct<DataT>(new_arr + i, copy_arr[i + copy_start]);
	}
	return new_arr;
}

/// DataT���������ͣ�ֱ��ʹ���ڴ濽��������ɿ��������߼�������Ԫ�����蹹�죬�������ڴ�
template <typename DataT> GINLINE 
DataT *_GArrayCreate(gsize size, gsize start, const DataT *copy_arr, gsize copy_start, gsize copy_size, GTrueType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(size);
	gsize new_copy_size = size - start;
	gsize real_copy_size = copy_size < new_copy_size ? copy_size : new_copy_size;
	GMemCopy(new_arr + start, copy_arr + copy_start, sizeof(DataT) * real_copy_size);
	return new_arr;
}

/// DataT�����������ͣ����ÿ����������캯������
template <typename DataT> GINLINE 
DataT *_GArrayCreate(gsize size, gsize start, const DataT *copy_arr, gsize copy_start, gsize copy_size, GFalseType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(size);
	gsize new_copy_size = size - start;

	for (gsize i = 0; i < start; i++)
	{
		GDefaultConstruct<DataT>(new_arr + i);
	}

	if (copy_size < new_copy_size)
	{
		for (gsize i = start; i < start + copy_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, copy_arr[i + copy_start]);
		}
		for (gsize i = start + copy_size; i < size; i++)
		{
			GDefaultConstruct<DataT>(new_arr + i);
		}
	}
	else
	{
		for (gsize i = start; i < size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, copy_arr[i + copy_start]);
		}
	}

	return new_arr;
}

/// DataT�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�ֱ�ӵ����ڴ�����������Ԫ����Ŀ�ĵ���
template <typename DataT> GINLINE 
DataT *__GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, GTrueType) GEXCEPT(false)
{
	return GReallocate<DataT>(old_arr, new_size);
}

/// DataT�������õ��ƶ����캯�����ҵ�ǰ�����ǲ��������ͣ�ʹ�ÿ������������ƶ�����
template <typename DataT> GINLINE 
DataT *__GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, GFalseType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(new_size);
	if (old_size < new_size)
	{
		for (gsize i = 0; i < old_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, old_arr[i]);
		}
		for (gsize i = old_size; i < new_size; i++)
		{
			GDefaultConstruct<DataT>(new_arr + i);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, old_arr[i]);
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(old_arr, old_size);
	return new_arr;
}

/// DataT�������õ��ƶ����캯��������Ҫ����Ԫ�أ���ʱ�������������
template <typename DataT> GINLINE 
DataT *_GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, GTrueType) GEXCEPT(false)
{
	/// ����DataT�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
	return __GArrayResize(old_arr, old_size, new_size,
		GTypeTraits<DataT>::Arithmetic());
}

/// DataT���������õ��ƶ����캯���������ƶ������������Ԫ�صĹ��죬�������Ԫ�ص���Ĭ�Ϲ��캯��
template <typename DataT> GINLINE 
DataT *_GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, GFalseType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(new_size);
	if (old_size < new_size)
	{
		for (gsize i = 0; i < old_size; i++)
		{
			GMoveConstruct<DataT>(new_arr + i, GMove(old_arr[i]));
		}
		for (gsize i = old_size; i < new_size; i++)
		{
			GDefaultConstruct<DataT>(new_arr + i);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_size; i++)
		{
			GMoveConstruct<DataT>(new_arr + i, GMove(old_arr[i]));
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(old_arr, old_size);
	return new_arr;
}

/// DataT�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�����ʹ���ڴ����
template <typename DataT> GINLINE 
DataT *__GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable, GTrueType) GEXCEPT(false)
{
	DataT *new_arr = GReallocate<DataT>(old_arr, new_size);
	if (old_size < new_size)
	{
		for (gsize i = old_size; i < new_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, copyable);
		}
	}
	return new_arr;
}

/// DataT�������õ��ƶ����캯�����ҵ�ǰ�����ǲ��������ͣ�ʹ�ÿ������������ƶ�����
template <typename DataT> GINLINE
DataT *__GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable, GFalseType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(new_size);
	if (old_size < new_size)
	{
		for (gsize i = 0; i < old_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, old_arr[i]);
		}
		for (gsize i = old_size; i < new_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, copyable);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, old_arr[i]);
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(old_arr, old_size);
	return new_arr;
}

/// DataT�������õ��ƶ����캯������ʱ�������������
template <typename DataT> GINLINE 
DataT *_GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable, GTrueType) GEXCEPT(false)
{
	/// ����DataT�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
	return __GArrayResize(old_arr, old_size, new_size, copyable,
		GTypeTraits<DataT>::Arithmetic());
}

/// DataT���������õ��ƶ����캯����ʹ���ƶ�����
template <typename DataT> GINLINE 
DataT *_GArrayResize(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable, GFalseType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(new_size);
	if (old_size < new_size)
	{
		for (gsize i = 0; i < old_size; i++)
		{
			GMoveConstruct<DataT>(new_arr + i, GMove(old_arr[i]));
		}
		for (gsize i = old_size; i < new_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, copyable);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_size; i++)
		{
			GMoveConstruct<DataT>(new_arr + i, GMove(old_arr[i]));
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(old_arr, old_size);
	return new_arr;
}

/// DataT�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�����ʹ�õȺŲ���
template <typename DataT> GINLINE 
DataT *__GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GTrueType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(new_size);
	gsize new_real_size = new_start + old_size;

	gsize j = old_start;
	if (new_real_size < new_size)
	{
		for (gsize i = new_start; i < new_real_size; i++)
		{
			new_arr[i] = old_arr[j++];
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = new_start; i < new_size; i++)
		{
			new_arr[i] = old_arr[j++];
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(old_arr, old_start + old_size);
	return new_arr;
}

/// DataT�������õ��ƶ����캯�����ҵ�ǰ�����ǲ��������ͣ�ʹ�ÿ������������ƶ�����
template <typename DataT> GINLINE 
DataT *__GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GFalseType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(new_size);
	gsize new_real_size = new_start + old_size;

	gsize j = old_start;
	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GDefaultConstruct<DataT>(new_arr + i);
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, old_arr[j++]);
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			GDefaultConstruct<DataT>(new_arr + i);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GDefaultConstruct<DataT>(new_arr + i);
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, old_arr[j++]);
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(old_arr, old_start + old_size);
	return new_arr;
}

/// DataT�������õ��ƶ����캯������ʱ�������������
template <typename DataT> GINLINE 
DataT *_GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GTrueType) GEXCEPT(false)
{
	/// ����DataT�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
	return __GArrayResize(old_arr, old_start, old_size, new_size, new_start,
		GTypeTraits<DataT>::Arithmetic());
}

/// DataT���������õ��ƶ����캯����ʹ���ƶ�����
template <typename DataT> GINLINE 
DataT *_GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, GFalseType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(new_size);
	gsize new_real_size = new_start + old_size;
	gsize j = old_start;

	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GDefaultConstruct<DataT>(new_arr + i);
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			GMoveConstruct<DataT>(new_arr + i, GMove(old_arr[j++]));
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			GDefaultConstruct<DataT>(new_arr + i);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GDefaultConstruct<DataT>(new_arr + i);
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			GMoveConstruct<DataT>(new_arr + i, GMove(old_arr[j++]));
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(old_arr, old_start + old_size);
	return new_arr;
}

/// DataT�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�����ʹ�õȺŲ���
template <typename DataT> GINLINE 
DataT *__GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable, GTrueType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(new_size);
	gsize new_real_size = new_start + old_size;

	gsize j = old_start;
	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			new_arr[i] = copyable;
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			new_arr[i] = old_arr[j++];
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			new_arr[i] = copyable;
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			new_arr[i] = copyable;
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			new_arr[i] = old_arr[j++];
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(old_arr, old_start + old_size);
	return new_arr;
}

/// DataT�������õ��ƶ����캯�����ҵ�ǰ�����ǲ��������ͣ�ʹ�ÿ������������ƶ�����
template <typename DataT> GINLINE 
DataT *__GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable, GFalseType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(new_size);
	gsize new_real_size = new_start + old_size;

	gsize j = old_start;
	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, copyable);
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, old_arr[j++]);
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, copyable);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, copyable);
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, old_arr[j++]);
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(old_arr, old_start + old_size);
	return new_arr;
}

/// DataT�������õ��ƶ����캯������ʱ�������������
template <typename DataT> GINLINE 
DataT *_GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable, GTrueType) GEXCEPT(false)
{
	/// ����DataT�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
	return __GArrayResize(old_arr, old_start, old_size, new_size, new_start, copyable,
		GTypeTraits<DataT>::Arithmetic());
}

/// DataT���������õ��ƶ����캯����ʹ���ƶ�����
template <typename DataT> GINLINE 
DataT *_GArrayResize(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable, GFalseType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(new_size);
	gsize new_real_size = new_start + old_size;
	gsize j = old_start;

	if (new_real_size < new_size)
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, copyable);
		}
		for (gsize i = new_start; i < new_real_size; i++)
		{
			GMoveConstruct<DataT>(new_arr + i, GMove(old_arr[j++]));
		}
		for (gsize i = new_real_size; i < new_size; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, copyable);
		}
	}
	else // old_size >= new_size
	{
		for (gsize i = 0; i < new_start; i++)
		{
			GCopyConstruct<DataT>(new_arr + i, copyable);
		}
		for (gsize i = new_start; i < new_size; i++)
		{
			GMoveConstruct<DataT>(new_arr + i, GMove(old_arr[j++]));
		}
	}

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(old_arr, old_start + old_size);
	return new_arr;
}

/// DataT�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�ʹ���ڴ濽��
template <typename DataT> GINLINE 
DataT *__GArrayRemoveAt(DataT *arr, gsize size, gsize pos, GTrueType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(size - 1);
	if (pos > 0)
	{
		GMemCopy(new_arr, arr, sizeof(DataT) * pos);
	}
	GMemCopy(new_arr + pos, arr + pos + 1, sizeof(DataT) * (size - pos - 1));

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(arr, size);
	return new_arr;
}

/// DataT�������õ��ƶ����캯�����ҵ�ǰ�������������ͣ�ʹ�ÿ�������
template <typename DataT> GINLINE 
DataT *__GArrayRemoveAt(DataT *arr, gsize size, gsize pos, GFalseType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(size - 1);
	for (gsize i = 0; i < pos; i++)
	{
		GCopyConstruct<DataT>(new_arr + i, arr[i]);
	}
	for (gsize i = pos + 1; i < size; i++)
	{
		GCopyConstruct<DataT>(new_arr + i - 1, arr[i]);
	}

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(arr, size);
	return new_arr;
}

/// DataT�������õ��ƶ����캯������ʱ�������������
template <typename DataT> GINLINE 
DataT *_GArrayRemoveAt(DataT *arr, gsize size, gsize pos, GTrueType) GEXCEPT(false)
{
	/// ����DataT�Ƿ����������ͣ����ò�ͬ�Ĵ����߼�
	return __GArrayRemoveAt(arr, size, pos,
		GTypeTraits<DataT>::Arithmetic());
}

/// DataT���������õ��ƶ����캯����ʹ���ƶ�����
template <typename DataT> GINLINE 
DataT *_GArrayRemoveAt(DataT *arr, gsize size, gsize pos, GFalseType) GEXCEPT(false)
{
	DataT *new_arr = GAllocate<DataT>(size - 1);
	for (gsize i = 0; i < pos; i++)
	{
		GMoveConstruct<DataT>(new_arr + i, GMove(arr[i]));
	}
	for (gsize i = pos + 1; i < size; i++)
	{
		GMoveConstruct<DataT>(new_arr + i - 1, GMove(arr[i]));
	}

	// ���پɵ�����
	GArrays::DestoryArray<DataT>(arr, size);
	return new_arr;
}

/// DataT���������õ�����������������
template <typename DataT> GINLINE 
gvoid _GArrayClear(DataT *arr, gsize size, GTrueType) GNOEXCEPT
{

}

/// DataT���������õ��������������ε�����������
template <typename DataT> GINLINE 
gvoid _GArrayClear(DataT *arr, gsize size, GFalseType) GNOEXCEPT
{
	if (!arr)
	{
		return;
	}
	for (gsize i = 0; i < size; i++)
	{
		arr[i].~DataT();
	}
}

/// DataT���������ͣ�������������ֱ��ʹ���ڴ濽��
template <typename DataT> GINLINE 
gvoid _GArrayCopyFrom(DataT *arr, gsize size, const DataT *copy_arr, GTrueType)
{
	GMemCopy(arr, copy_arr, sizeof(DataT) * size);
}

/// DataT�����������ͣ����������ڵ��ÿ�������
template <typename DataT> GINLINE 
gvoid _GArrayCopyFrom(DataT *arr, gsize size, const DataT *copy_arr, GFalseType) GEXCEPT(false)
{
	for (gsize i = 0; i < size; i++)
	{
		// ����ԭ��Ԫ��
		GDestruct<DataT>(arr + i);

		// ���������µ�Ԫ��
		GCopyConstruct<DataT>(arr + i, copy_arr[i]);
	}
}

/// DataT���������ͣ�������������ֱ��ʹ���ڴ濽��
template <typename DataT> GINLINE 
DataT *_GArrayCopyFrom(DataT *arr, gsize size, const DataT *copy_arr, gsize copy_size, GTrueType) GEXCEPT(false)
{
	if (size != copy_size)
	{
		GDeallocate<DataT>(arr);
		arr = GAllocate<DataT>(copy_size);
	}

	GMemCopy(arr, copy_arr, sizeof(DataT) * copy_size);
	return arr;
}

/// DataT�����������ͣ����������ٵ��ÿ�������
template <typename DataT> GINLINE 
DataT *_GArrayCopyFrom(DataT *arr, gsize size, const DataT *copy_arr, gsize copy_size, GFalseType) GEXCEPT(false)
{
	for (gsize i = 0; i < size; i++)
	{
		GDestruct<DataT>(arr + i);
	}
	if (size != copy_size)
	{
		GDeallocate<DataT>(arr);
		arr = GAllocate<DataT>(copy_size);
	}
	for (gsize i = 0; i < copy_size; i++)
	{
		GCopyConstruct<DataT>(arr + i, copy_arr[i]);
	}
	return arr;
}

} // namespace gsystem.detail.arrays
} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

template <typename DataT> GINLINE
DataT *GArrays::CreateArray(gsize size) GEXCEPT(false)
{
	GASSERT(size > 0);

	/// ����DataT�Ƿ�������õ�Ĭ�Ϲ��캯����ȥ���ò�ͬ�Ĵ����߼�
	return detail::arrays::_GArrayCreate<DataT>(size,
		GTypeTraits<DataT>::TrivialDefaultConstructible());
}

template <typename DataT> GINLINE
DataT *GArrays::CreateArray(gsize size, const DataT &copyable) GEXCEPT(false)
{
	GASSERT(size > 0);

	DataT *arr = GAllocate<DataT>(size);
	for (gsize i = 0; i < size; i++)
	{
		// ��GConstruct�ĵ��ù����У��Ѿ�����������������͵Ĵ����߼�
		GCopyConstruct<DataT>(arr + i, copyable);
	}
	return arr;
}

template <typename DataT> GINLINE 
DataT *GArrays::CreateArray(const DataT *copy_arr, gsize copy_start, gsize copy_size) GEXCEPT(false)
{
	// ��copy_arr�����ڣ�����copy_start�����˷�Χ����ᱨ��
	GASSERT(copy_arr && copy_start < copy_size);

	// ����DataT�Ƿ����������ͣ�ȥ���ò�ͬ�Ĵ����߼�
	return detail::arrays::_GArrayCreate<DataT>(copy_arr, copy_start, copy_size,
		GTypeTraits<DataT>::Arithmetic());
}

template <typename DataT> GINLINE
DataT *GArrays::CreateArray(gsize size, gsize start, const DataT *copy_arr, gsize copy_start, gsize copy_size) GEXCEPT(false)
{
	GASSERT(start < size && copy_arr && copy_start < copy_size);

	// ����DataT�Ƿ����������ͣ�ȥ���ò�ͬ�Ĵ����߼�
	return detail::arrays::_GArrayCreate(size, start, copy_arr, copy_start, copy_size,
		GTypeTraits<DataT>::Arithmetic());
}

template <typename DataT> GINLINE
DataT *GArrays::ResizeArray(DataT *old_arr, gsize old_size, gsize new_size) GEXCEPT(false)
{
	// �ж�DataT�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return detail::arrays::_GArrayResize<DataT>(old_arr, old_size, new_size,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT> GINLINE
DataT *GArrays::ResizeArray(DataT *old_arr, gsize old_size, gsize new_size, const DataT &copyable) GEXCEPT(false)
{
	// �ж�DataT�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return detail::arrays::_GArrayResize<DataT>(old_arr, old_size, new_size, copyable,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT> GINLINE
DataT *GArrays::ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start) GEXCEPT(false)
{
	GASSERT(old_start < old_size);

	// �ж�DataT�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return detail::arrays::_GArrayResize<DataT>(old_arr, old_start, old_size, new_size, new_start,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT> GINLINE
DataT *GArrays::ResizeArray(DataT *old_arr, gsize old_start, gsize old_size, gsize new_size, gsize new_start, const DataT &copyable) GEXCEPT(false)
{
	// �ж�DataT�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return detail::arrays::_GArrayResize<DataT>(old_arr, old_start, old_size, new_size, new_start, copyable,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT> GINLINE
DataT *GArrays::RemoveArrayElementAt(DataT *arr, gsize size, gsize pos) GEXCEPT(false)
{
	GASSERT(size > 0 && pos < size);

	// �ж�DataT�Ƿ�����ƶ����캯�������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return detail::arrays::_GArrayRemoveAt(arr, size, pos,
		GTypeTraits<DataT>::TrivialMoveConstructible());
}

template <typename DataT> GINLINE
gvoid GArrays::ClearArray(DataT *arr, gsize size) GNOEXCEPT
{
	detail::arrays::_GArrayClear(arr, size,
		GTypeTraits<DataT>::TrivialDestructible());
}

template <typename DataT> GINLINE
gvoid GArrays::DestoryArray(DataT *arr, gsize size) GNOEXCEPT
{
	// �ж�DataT�Ƿ�����������������ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	detail::arrays::_GArrayClear(arr, size,
		GTypeTraits<DataT>::TrivialDestructible());

	// �ͷ��ڴ�
	GDeallocate<DataT>(arr);
}

template <typename DataT> GINLINE
gvoid GArrays::CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr) GEXCEPT(false)
{
	GASSERT(arr && copy_arr);

	// �ж�DataT�Ƿ��ǻ������ͣ����ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	detail::arrays::_GArrayCopyFrom<DataT>(arr, size, copy_arr,
		GTypeTraits<DataT>::Arithmetic());
}

template <typename DataT> GINLINE 
DataT *GArrays::CopyArrayFrom(DataT *arr, gsize size, const DataT *copy_arr, gsize copy_size) GEXCEPT(false)
{
	GASSERT(arr && copy_arr);

	// �ж�DataT�Ƿ��ǻ������ͣ����ж��Ƿ���Ҫ���ò�ͬ�ĺ���
	return detail::arrays::_GArrayCopyFrom<DataT>(arr, size, copy_arr, copy_size,
		GTypeTraits<DataT>::Arithmetic());
}

}  // namespace gsystem

#endif // _CORE_ARRAYS_INLINE_