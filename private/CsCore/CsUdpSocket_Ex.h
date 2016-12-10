﻿#ifndef _CSCORE_CSUDPSOCKET_PRIVATE_H_
#define _CSCORE_CSUDPSOCKET_PRIVATE_H_

#include "CsSocket_Ex.h"

class CsUdpSocket_Ex 
	: public CsSocket_Ex
{
public:
	cs_int Open(cs_bool nResue);
	cs_int Open(CsSockAddress_Ex *pSockAddr, cs_bool nResue);
	cs_void Close();

	cs_int SendTo(const cs_char *pBufData, cs_int nLen, CsSockAddress_Ex *pPeer);
	cs_int RecvFrom(cs_char *pBufData, cs_int nMaxLen, CsSockAddress_Ex *pPeer);
};

#endif // _CSCORE_CSUDPSOCKET_PRIVATE_H_