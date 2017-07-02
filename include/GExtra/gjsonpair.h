/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gjsonpair.h
** @brief	Json����/ֵ�����͵Ķ���
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		GJsonPair
**
** Json���ݵ���д��ʽ�ǣ�����/ֵ�ԡ�
** ����/ֵ�԰����ֶ����ƣ���˫�����У�������дһ��ð�ţ�Ȼ����ֵ��
**	"firstName" : "John"
**
****************************************************************************/

#ifndef _CORE_JSON_PAIR_H_
#define _CORE_JSON_PAIR_H_

#include "gstring.h"
#include "gjsonvalue.h"

namespace gsystem { // gsystem
	namespace json { // gsystem.json
		class GJsonParserMessage;
	} // namespace gsystem.json
} // namespace gsystem

namespace gsystem { // gsystem
namespace json { // gsystem.json

class GAPI GJsonPair
	: public GObject
{
public:
	GJsonPair();
	~GJsonPair();

	gbool Valid() const;

	GString &Key();
	const GString &Key() const;
	GJsonValue *Value();
	const GJsonValue *Value() const;

	GString ToString() const;

	gbool Parse(const GString &jsonStr, gsize *cursor = GNULL, GJsonParserMessage *msg = GNULL);
	
private:
	gvoid Destroy();
	GString m_sKey;
	GJsonValue *m_pValue;
};

} // namespace gsystem.json
} // namespace gsystem

#endif // _CORE_JSON_PAIR_H_