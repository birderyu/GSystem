#ifndef _CORE_STOP_WATCH_H_
#define _CORE_STOP_WATCH_H_

#include "gtype.h"

namespace gsystem { // gsystem

class GAPI GStopWatch
{
public:
	gvoid Start();
	gint Pause() const;
	gint Stop();

private:
	gulong Tick() const;

private:
	gulong m_nStart;
};

} // namespace gsystem

#endif // _CORE_STOP_WATCH_H_