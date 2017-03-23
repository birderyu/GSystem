#ifndef _CORE_FILE_H_
#define _CORE_FILE_H_

#include "gtype.h"

namespace gsystem { // gsystem
	class GString;
	namespace detail { // gsystem.detail
		class GFile_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

/****************************************************************************
**
** gfile.h
**
** @class		GFile
** @brief		�ļ�
**
** GFile��ʾһ���ļ�����һ�������࣬���ľ��幦��ȡ������������ʵ�֣��ı��ļ���GTextFile����
** �������ļ���GBinaryFile����GFile������֧�ֻ��棬����Ҫ����һ���ļ����棬����ʹ����Ӧ����
** ���͡�
**
****************************************************************************/
class GAPI GFile
{
public:
	/****************************************************************************
	**
	** @name		OPEN_MODE
	** @brief		�ļ��Ĵ�ģʽ
	**
	****************************************************************************/
	enum OPEN_MODE
	{
		NO_OPEN = 0x0000,						/// ����
		ONLY_READ = 0x0001,						/// ֻ��ģʽ
		ONLY_WIRTE = 0x0002,					/// ֻдģʽ
		READ_WIRTE = ONLY_READ | ONLY_WIRTE,	/// ��дģʽ
		APPEND = 0x0004,						/// ��β������
	};

	enum FILE_FORMAT
	{
		BINARY_FILE,
		TEXT_FILE
	};

	enum SEEK_MODE
	{
		SEEK_MODE_START		= 0,
		SEEK_MODE_CURRENT	= 1,
		SEEK_MODE_END		= 2,
	};

public:
	virtual ~GFile() = 0;

	FILE_FORMAT Format() const;

	gbool Valid() const;
	gbool EndOfFile() const;	

	const GString &FileName() const;
	GString &FileName();
	gvoid SetFileName(const GString &);

	gbool Open(OPEN_MODE mode);
	gvoid Close();

	gbool Seek(glong offset, SEEK_MODE);
	glong Tell() const; // ��ֵ���ʾ��ȡλ��ʧ��
	gvoid Rewind();

	// ��ȡ�ļ��Ĵ�С����λ���ֽ�
	gsize Size() const;

protected:
	GFile(detail::GFile_Ex *);
	detail::GFile_Ex *m_pFileEx;
};

} // namespace gsystem

#endif _CORE_FILE_H_