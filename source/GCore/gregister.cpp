#include "gregister.h"
#include "gstring.h"
#include "gclasscode.h"

namespace gsystem { // gsystem

gbool GRegister::Register(const GString &sClassName, guint nClassCode)
{
	GLockGuard<GMutex> lock(m_tLock);
	/*
	if (!m_tClassName_ClassCode.Contains(sClassName) &&
		!m_tClassCode_ClassName.Contains(nClassCode))
	{
		m_tClassName_ClassCode.Insert(sClassName, nClassCode);
		m_tClassCode_ClassName.Insert(nClassCode, sClassName);
		return true;
	}
	*/
	return false;
}

gvoid GRegister::Initialize()
{
	
}

} // namespace gsystem
