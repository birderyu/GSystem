/********************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file gmacro.h
** @brief 全局宏定义
** @author birderyu
** @contact https://github.com/birderyu/GSystem
** @date 2015-12-31
** @version 0.5.0
**
********************************************************************************/

#ifndef _CORE_MACRO_H_
#define _CORE_MACRO_H_

#if defined (_WIN32) || defined(_WIN64)
/********************************************************************************
**
** @name G_SYSTEM_WINDOWS
** @brief Windows操作系统
**
********************************************************************************/
#	define G_SYSTEM_WINDOWS
#endif // _WIN32 or _WIN64

#ifdef _LINUX
/********************************************************************************
**
** @name G_SYSTEM_LINUX
** @brief Linux操作系统
**
********************************************************************************/
#	define G_SYSTEM_LINUX
#endif // _LINUX

#ifdef _MSC_VER
/********************************************************************************
**
** @name G_COMPILER_MSVC
** @brief MSVC编译器
**
********************************************************************************/
#	define G_COMPILER_MSVC _MSC_VER
#endif // _MSC_VER

#ifdef __GNUC__
/********************************************************************************
**
** @name G_COMPILER_GCC
** @brief GCC编译器
**
********************************************************************************/
#	define G_COMPILER_GCC
#endif // __GNUC__

#ifdef G_SYSTEM_WINDOWS
#	ifdef _WIN64
#		define G_64_BIT
#	else
#		define G_32_BIT
#	endif // _WIN64
#endif // G_SYSTEM_WINDOWS

#ifdef _DLL
/********************************************************************************
**
** @name GDLL
** @brief 动态链接库
**
********************************************************************************/
#	define GDLL
#endif // _DLL

#ifdef G_COMPILER_MSVC
#	ifdef GDLL
/********************************************************************************
**
** @name GAPI
** @brief API
**
********************************************************************************/
#		define GAPI __declspec(dllexport)
#	else // !GDLL 
/********************************************************************************
**
** @name GAPI
** @brief API
**
********************************************************************************/
#		define GAPI __declspec(dllimport)
#	endif // GDLL
#else
#	define GAPI
#endif // G_COMPILER_MSVC

/********************************************************************************
**
** @name G_CXX_11
** @brief 版本C++11
**
********************************************************************************/
#define G_CXX_11

/********************************************************************************
**
** @name GNULL
** @brief 空指针
**
********************************************************************************/
#define GNULL nullptr

/********************************************************************************
**
** @name GNOEXCEPT
** @brief 不抛出异常
**
********************************************************************************/
#define GNOEXCEPT noexcept
//#define GNOEXCEPT throw ()

/********************************************************************************
**
** @name GEXCEPT
** @brief 根据参数抛出异常
** @param x 布尔参数，其值为true则说明会抛出异常，值为false时相当于GNOEXCEPT
**
********************************************************************************/
#define GEXCEPT(x) noexcept(x)
//#define GEXCEPT(x)

#ifdef _DEBUG
/********************************************************************************
**
** @name GDEBUG
** @brief 调试模式
**
********************************************************************************/
#	define GDEBUG
#endif

#ifdef GDEBUG
#	include <assert.h>
/********************************************************************************
**
** @name GASSERT
** @brief 断言
**
********************************************************************************/
#	define GASSERT(e) assert(e)
#else // !GDEBUG
/********************************************************************************
**
** @name GASSERT
** @brief 断言
**
********************************************************************************/
#	define GASSERT(e) do { } while ((false) && (e))
#endif // GDEBUG

/********************************************************************************
**
** @name GFILE
** @brief 文件名
**
********************************************************************************/
#define GFILE __FILE__

/********************************************************************************
**
** @name GLINE
** @brief 行号
**
********************************************************************************/
#define GLINE __LINE__

/********************************************************************************
**
** @name GENDIAN_LITTLE
** @brief 小端存储
**
********************************************************************************/
#define GENDIAN_LITTLE 0x0123

/********************************************************************************
**
** @name GENDIAN_BIG
** @brief 大端存储
**
********************************************************************************/
#define GENDIAN_BIG 0x3210

#if defined (i386) || defined (__i386__) || defined (_M_IX86) || \
	defined (vax) || defined (__alpha) || defined (__LITTLE_ENDIAN__) || \
	defined (ARM) || defined (_M_IA64) || defined (_M_AMD64) || \
	defined (__amd64) || \
	((defined (__ia64__) || defined (__ia64)) && !defined (__hpux))
/********************************************************************************
**
** @name G_BYTE_ORDER
** @brief 字节存储顺序
**
********************************************************************************/
#	define G_BYTE_ORDER GENDIAN_LITTLE
#else
/********************************************************************************
**
** @name G_BYTE_ORDER
** @brief 字节存储顺序
**
********************************************************************************/
#	define G_BYTE_ORDER GENDIAN_BIG
#endif

/********************************************************************************
**
** @name G_POINTER_ADDRESS_SIZE
** @brief 指针值所占字节数
**
********************************************************************************/
#define G_POINTER_ADDRESS_SIZE sizeof(gsystem::gvoid*)

/********************************************************************************
**
** @name G_INT8_MAX
** @brief 8位整形最大值
**
********************************************************************************/
#define G_INT8_MAX 0x7f

/********************************************************************************
**
** @name G_INT8_MIN
** @brief 8位整形最小值
**
********************************************************************************/
#define G_INT8_MIN (-0x80)

/********************************************************************************
**
** @name G_UINT8_MAX
** @brief 8位无符号整形最大值
**
********************************************************************************/
#define G_UINT8_MAX 0xff

/********************************************************************************
**
** @name G_INT16_MAX
** @brief 16位整形最大值
**
********************************************************************************/
#define G_INT16_MAX 0x7fff

/********************************************************************************
**
** @name G_INT16_MIN
** @brief 16位整形最小值
**
********************************************************************************/
#define G_INT16_MIN (-0x8000)

/********************************************************************************
**
** @name G_UINT16_MAX
** @brief 16位无符号整形最大值
**
********************************************************************************/
#define G_UINT16_MAX 0xffff

/********************************************************************************
**
** @name G_INT32_MAX
** @brief 32位整形最大值
**
********************************************************************************/
#define G_INT32_MAX 0x7fffffff

/********************************************************************************
**
** @name G_INT32_MIN
** @brief 32位整形最小值
**
********************************************************************************/
#define G_INT32_MIN (-0x7fffffff - 1)

/********************************************************************************
**
** @name G_UINT32_MAX
** @brief 32位无符号整形最大值
**
********************************************************************************/
#define G_UINT32_MAX 0xffffffffU

/********************************************************************************
**
** @name G_INT32L_MAX
** @brief 32位长整形最大值
**
********************************************************************************/
#define G_INT32L_MAX 0x7fffffffL

/********************************************************************************
**
** @name G_INT32L_MIN
** @brief 32位长整形最小值
**
********************************************************************************/
#define G_INT32L_MIN (-0x7fffffffL - 1)

/********************************************************************************
**
** @name G_UINT32L_MAX
** @brief 32位无符号长整形最大值
**
********************************************************************************/
#define G_UINT32L_MAX 0xffffffffUL

/********************************************************************************
**
** @name G_INT64_MAX
** @brief 64位整形最大值
**
********************************************************************************/
#define G_INT64_MAX 0x7fffffffffffffffLL

/********************************************************************************
**
** @name G_INT64_MIN
** @brief 64位整形最小值
**
********************************************************************************/
#define G_INT64_MIN (-0x7fffffffffffffffLL - 1)

/********************************************************************************
**
** @name G_UINT64_MAX
** @brief 64位无符号整形最大值
**
********************************************************************************/
#define G_UINT64_MAX 0xffffffffffffffffULL

/********************************************************************************
**
** @name G_LIST_MAX_SIZE
** @brief 列表型数据结构的最大元素数量
**
********************************************************************************/
#define G_LIST_MAX_SIZE (G_UINT32_MAX - 1)

/********************************************************************************
**
** @name G_LIST_NULL_POS
** @brief 列表型数据结构的空元素位置
**
** 当列表型数据结构（如数组、字符串等）的元素位置为G_LIST_NULL_POS时，表示一个空位置
**
********************************************************************************/
#define G_LIST_NULL_POS G_UINT32_MAX

#define G_HAS_DECIMAL

#ifndef GINLINE
/********************************************************************************
**
** @name GINLINE
** @brief 内联
**
********************************************************************************/
#	define GINLINE	inline
#endif // !GINLINE

// 字符处理
#define GUCHAR(c)				((gsystem::guchar)(c))
#define G_CHAR_IS_ASCII(c)		(isascii(GUCHAR(c)) != 0)
#define G_CHAR_IS_ALNUM(c)		(isalnum(GUCHAR(c)) != 0)
#define G_CHAR_IS_ALPHA(c)		(isalpha(GUCHAR(c)) != 0)
#define G_CHAR_IS_BLANK(c)		(isblank(GUCHAR(c)) != 0)
#define G_CHAR_IS_CNTRL(c)		(iscntrl(GUCHAR(c)) != 0)
#define G_CHAR_IS_DIGIT(c)		(isdigit(GUCHAR(c)) != 0)
#define G_CHAR_IS_DIGIT_X(c)	(isxdigit(GUCHAR(c)) != 0)
#define G_CHAR_IS_GRAPH(c)		(isgraph(GUCHAR(c)) != 0)
#define G_CHAR_IS_LOWER(c)		(islower(GUCHAR(c)) != 0)
#define G_CHAR_IS_PRINT(c)		(isprint(GUCHAR(c)) != 0)
#define G_CHAR_IS_PUNCT(c)		(ispunct(GUCHAR(c)) != 0)
#define G_CHAR_IS_SPACE(c)		(isspace(GUCHAR(c)) != 0)
#define G_CHAR_IS_UPPER(c)		(isupper(GUCHAR(c)) != 0)
#define G_CHAR_TO_LOWER(c)		tolower(GUCHAR(c))
#define G_CHAR_TO_UPPER(c)		toupper(GUCHAR(c))

#define GGBK(cs)	(cs)		// gbk编码
#define GUTF8(cs)	(u8##cs)	// utf-8编码
#define GUTF16(cs)	(u##cs)		// utf-16编码
#define GUTF32(cs)	(U##cs)		// utf-32编码
#define GLOCALE(cs)	(L##cs)		// 

// 常用函数
#define G_CALL_AT_EXIT atexit
#define G_MAX(a,b)  (((a) > (b)) ? (a) : (b))
#define G_MIN(a,b)  (((a) < (b)) ? (a) : (b))

#define G_DATE_SIZE			8
#define G_TIME_SIZE			8
#define G_DATE_TIME_SIZE	(G_DATE_SIZE + G_TIME_SIZE)

// 若需要所有的功能，则应该定义如下的宏
//#define G_NEED_ALL_FUNCTION

#define G_CHAR_BYTE_8
#define G_CHAR_BYTE_16
#define G_CHAR_BYTE_32

#endif // _CORE_MACRO_H_