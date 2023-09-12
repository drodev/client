/*****************************************************************************
* File			: PacketTracer.h
* Author		: woosung
* Copyright	: (��)NTL
* Date			: 2009. 08. 04
* Abstract		: 
*****************************************************************************
* Desc			:��Ŷ������ ���� ��Ŷ�� ��Ŷ��� �ð��� dump
*****************************************************************************/

#pragma once

#include "NtlPacketCommon.h"
#include "ceventhandler.h"
#include <string>
#include <map>

using namespace	std;

#ifdef _DEBUG		/// ������ġ					
//#define	_ENABLE_PACKET_TRACE_		/// Defalut�� Disable /// ���������� ����ɼ��ִ�. �ڵ����尡 ������ �� ����
#endif

class CPacketTracer : public RWS::CEventHandler
{
public:
	CPacketTracer();
	~CPacketTracer();

	enum TRACE_MODE
	{
		CAPTURE_ALL,
		CAPTURE_RECEIVE,
		CAPTURE_SEND,
	};

	void	Create();
	void	Destroy();
	void	SetRangeOpCode(int iMin, int iMax = -1);
	void	SetTraceMode(TRACE_MODE eTraceMode);
	const char*	GetPacketName(int iOpCode);

	void	Activate();
	void	Deactivate();
	void	Process(sNTLPACKETHEADER* pPacket, RwBool bReceive);
	//! Event
	virtual VOID HandleEvents( RWS::CMsg& msg );

	//! �̱��� ����/���� 
	static	void	CreateInstance();
	static	void	DeleteInstance();
	static CPacketTracer*	GetInstance();						///< �̱��� �ν��Ͻ� ��ü

private:
	RwBool m_bAvtivate;
	TRACE_MODE m_eTraceMode;

    typedef map< RwUInt32, string > PacketEnumNameMap;
	PacketEnumNameMap m_mapPacketName;

	int m_iMinOpCode;
	int m_iMaxOpCode;

	static CPacketTracer*	m_pInstance;

};