#include "gstring.h"

namespace gsystem { // gsystem

const GObject *GString::Boxing() const
{
	return dynamic_cast<const GObject *>(this);
}

guint GString::ClassCode() const
{
	return GString::CLASS_CODE;
}

GString GString::ToString() const
{
	return GString(m_tString);
}

} // namespace gsystem