/********************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gfile.h
** @brief 文件接口
** @author birderyu
** @contact https://github.com/birderyu
** @date 2016-12-31
** @version 1.0.0
**
********************************************************************************/

#ifndef _CORE_FILE_H_
#define _CORE_FILE_H_

#include "gglobal.h"

namespace gsystem { // gsystem
	namespace detail { // gsystem.detail
		class GFile_Ex;
	} // namespace gsystem.detail
} // namespace gsystem

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief 文件
**
** GFile表示一个文件，是一个抽象类，它的具体功能取决于它的两个实现：文本文件（GTextFile）和
** 二进制文件（GBinFile）。GFile本身不支持缓存，若需要构建一个文件缓存，可以使用相应的文件流。
**
********************************************************************************/
class GAPI GFile
{
public:
	/****************************************************************************
	**
	** @name OPEN_MODE
	** @brief 文件打开模式
	**
	****************************************************************************/
	enum OPEN_MODE
	{
		/************************************************************************
		**
		** 不打开
		**
		************************************************************************/
		NO_OPEN = 0x0000,

		/************************************************************************
		**
		** 只读模式
		**
		************************************************************************/
		ONLY_READ = 0x0001,

		/************************************************************************
		**
		** 只写模式
		**
		************************************************************************/
		ONLY_WIRTE = 0x0002,

		/************************************************************************
		**
		** 读写模式
		**
		************************************************************************/
		READ_WIRTE = ONLY_READ | ONLY_WIRTE,

		/************************************************************************
		**
		** 在尾部添加
		**
		************************************************************************/
		APPEND = 0x0004,
	};

	/****************************************************************************
	**
	** @name FILE_FORMAT
	** @brief 文件格式
	**
	****************************************************************************/
	enum FILE_FORMAT
	{
		/************************************************************************
		**
		** 二进制文件
		**
		************************************************************************/
		BINARY_FILE,

		/************************************************************************
		**
		** 文本文件
		**
		************************************************************************/
		TEXT_FILE
	};

	/****************************************************************************
	**
	** @name SEEK_MODE
	** @brief 文件定位基准
	**
	****************************************************************************/
	enum SEEK_MODE
	{
		/************************************************************************
		**
		** 文件开头
		**
		************************************************************************/
		SEEK_MODE_START		= 0,

		/************************************************************************
		**
		** 当前位置
		**
		************************************************************************/
		SEEK_MODE_CURRENT	= 1,

		/************************************************************************
		**
		** 文件尾部
		**
		************************************************************************/
		SEEK_MODE_END		= 2,
	};

public:
	/****************************************************************************
	**
	** @name ~GFile
	** @brief 析构函数（destructor）
	**
	****************************************************************************/
	virtual ~GFile() = 0;

	/****************************************************************************
	**
	** @name Format
	** @brief 获取文件的格式
	** @return {FILE_FORMAT} 文件格式
	**
	****************************************************************************/
	FILE_FORMAT Format() const;

	/****************************************************************************
	**
	** @name Valid
	** @brief 判断文件是否是有效的
	** @return {gbool} 若文件是有效的，则返回true，否则返回false
	**
	****************************************************************************/
	gbool Valid() const;

	/****************************************************************************
	**
	** @name EndOfFile
	** @brief 判断是否到达文件的末端（eof）
	** @return {gbool} 若到达文件的末端，则返回true，否则返回false
	**
	****************************************************************************/
	gbool EndOfFile() const;	

	/****************************************************************************
	**
	** @name FileName
	** @brief 获取文件全名
	** @return {const GString &} 文件全名，包含文件路径、文件名和文件后缀名
	**
	****************************************************************************/
	const GString &FileName() const;

	/****************************************************************************
	**
	** @name FileName
	** @brief 获取文件全名
	** @return {GString &} 文件全名，包含文件路径、文件名和文件后缀名
	**
	****************************************************************************/
	GString &FileName();

	/****************************************************************************
	**
	** @name SetFileName
	** @brief 设置文件全名
	** @param [in] filename {const GString &} 文件全名
	**
	****************************************************************************/
	gvoid SetFileName(const GString &filename);

	/****************************************************************************
	**
	** @name Open
	** @brief 打开文件
	** @param [in] mode {OPEN_MODE} 文件打开模式
	** @return {gbool} 若文件打开成功，则返回true，否则返回false
	**
	****************************************************************************/
	gbool Open(OPEN_MODE mode);

	/****************************************************************************
	**
	** @name Close
	** @brief 关闭文件
	**
	****************************************************************************/
	gvoid Close();

	/****************************************************************************
	**
	** @name Seek
	** @brief 定位到文件指定的位置
	** @param [in] offset {glong} 移动的字节数
	** @param [in] mode {SEEK_MODE} 文件定位基准
	** @return {gbool} 若文件定位成功，则返回true，否则返回false
	**
	** 从基准位置开始，移动offset个字节的位置，定位文件
	**
	****************************************************************************/
	gbool Seek(glong offset, SEEK_MODE mode);

	/****************************************************************************
	**
	** @name Tell
	** @brief 获取文件当前位置相对于文件首位的偏移字节数
	** @return {glong} 字节数，负值则表示获取失败
	**
	****************************************************************************/
	glong Tell() const;

	/****************************************************************************
	**
	** @name Rewind
	** @brief 将文件的位置回退到文件首位
	**
	****************************************************************************/
	gvoid Rewind();

	/****************************************************************************
	**
	** @name Size
	** @brief 获取文件的字节大小
	** @return {gsize} 字节数
	**
	****************************************************************************/
	gsize Size() const;

protected:
	/****************************************************************************
	**
	** @name GFile
	** @brief 构造函数（constructor）
	** @param [in] file {detail::GFile_Ex *} 文件私有实现体
	**
	****************************************************************************/
	GFile(detail::GFile_Ex *file);

protected:
	/****************************************************************************
	**
	** 文件私有实现体
	**
	****************************************************************************/
	detail::GFile_Ex *m_pFileEx;
};

} // namespace gsystem

#endif _CORE_FILE_H_