// 简单表
// 使用一整块连续的内存存储表结构
// 仅支持基本类型，不支持任何复杂类型

#ifndef _CORE_SIMPLE_TABLE_H_
#define _CORE_SIMPLE_TABLE_H_

#include "CsVirtualTable.h"

class CsSimpleTable :public CsVirtualTable
{
public:
	CsSimpleTable();
	virtual ~CsSimpleTable();

public:

};

#endif // _CORE_SIMPLE_TABLE_H_