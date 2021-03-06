/****************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file gjsonobject.h
** @brief Json对象类型的定义
** @author birderyu
** @contact https://github.com/birderyu
** @date 2017-1-3
** @version 0.5.0
**
** Json对象在花括号中书写：
** 对象可以包含多个名称 / 值对：
** { "firstName": "John", "lastName": "Doe" }
**
****************************************************************************/

#ifndef _CORE_JSON_OBJECT_H_
#define _CORE_JSON_OBJECT_H_

#include "gstring.h"
#include "gmap.h"

namespace gsystem { // gsystem
	namespace json { // gsystem.json
		class GJsonPair;
		class GJsonParserMessage;
	} // namespace gsystem.json
} // namespace gsystem

namespace gsystem { // gsystem
namespace json { // gsystem.json

class GAPI GJsonObject
	: public GObject
{
public:
	GJsonObject();
	GJsonObject(const GString &jsonStr);
	GJsonObject(const GJsonObject &jsonObj);
	~GJsonObject();

	gbool test(GJsonPair &p) const;

	gbool Valid() const;
	GString ToString() const;

	// 字符串解析，cursor为游标
	gbool Parse(const GString &jsonStr, gsize *cursor = GNULL, GJsonParserMessage *msg = GNULL);

private:
	gvoid Destroy();
	GMap<GString, GJsonPair*> m_tJsonPairs;
};

} // namespace gsystem.json
} // namespace gsystem

#endif // _CORE_JSON_OBJECT_H_