/*****************************************************************************
 *
 * File			: PacketProc.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 9. 14	
 * Abstract		: packet process 
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __PACKET_PROC_H__
#define __PACKET_PROC_H__

#include "NtlClientNet.h"

void NetworkLogCallback(const char *pNetLog);
void NetworkEventHander(HSERVER hServer, int nEvent);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CPacketProc;
class CClientRecvPacketProc : public CRecvPacketProcess
{
public:

	CClientRecvPacketProc( const HSERVER hServer );

public:

	virtual bool RecvPacketProcess( void* const pData );

	virtual bool IsActivePop( void );
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//

class CPacketProc
{
private:

	typedef std::list<void*> ListVirtualPacket;

	RwBool m_bPop;
	ListVirtualPacket m_listPacket;    

private:

	void PopPacket(HSERVER hSocketId);
	void PopVirutalPacket(void);
	
public:

	CPacketProc();
	~CPacketProc();

	static CPacketProc* GetInstance(void);

	/**
	* network���� �� packet data
	*/
	void RecvPacketProc(void);

	/**
	* virtual server���� �� packet
	*/
	void RecvVirualPackProc(void *pPacket);

	/**
	* packet �����͸� ���� ���ΰ�?
	*/
	void ActivePop(RwBool bPop);

	/**
	* packet �����͸� ���� ���ΰ�?
	*/
	RwBool IsActivePop(void) const;

};


inline RwBool CPacketProc::IsActivePop(void) const
{
	return m_bPop;
}


#endif