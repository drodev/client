#include "precomp_ntlcore.h"
#include "NtlCoreLogic.h"
#include "NtlDebug.h"

/**
*
*  constructor for CNtlLogic
*
*/
CNtlCoreLogic::CNtlCoreLogic() : m_bEnabled(true) ,
							 m_fFreeElapsed(0.0f),	
							 m_fSync30Elapsed(0.0f),	
							 m_fSync20Elapsed(0.0f),	
							 m_fSync10Elapsed(0.0f)
{
}

/**
*
*  ���� tick�� ���� event�� ����Ѵ�.
*
*/
bool CNtlCoreLogic::Create(void)
{
	NTL_FUNCTION("CNtlCoreLogic::Create");

	RWS::CEventHandler::RegisterMsg (g_EventUpdateTick, "g_EventUpdateTickStr", "float");
	RWS::CEventHandler::RegisterMsg (g_EventQueueProcessFilter, "g_EventQueueProcessFilterStr", "EventQueueProcessFilterStr");
	RWS::CEventHandler::RegisterMsg (g_EventToggleFullScreen, "g_EventToggleFullScreen", "bool");
		
	NTL_RETURN(true);
	
}

/**
*
*  ���� tick�� ���� ��ϵ� event�� �����Ѵ�.
*
*/
void CNtlCoreLogic::Destroy(void)
{
	NTL_FUNCTION("CNtlCoreLogic::Destroy");

    RWS::CEventHandler::UnRegisterMsg ( g_EventUpdateTick );
	RWS::CEventHandler::UnRegisterMsg ( g_EventQueueProcessFilter );
	RWS::CEventHandler::UnRegisterMsg ( g_EventToggleFullScreen );
	
	NTL_RETURNVOID();
}

/**
*
*  simulation object�� update tick evnet�� ������.
*  ���� 30, 20, 10 frame�� sync�� tick�� ����Ͽ� ������.
*
*/
void CNtlCoreLogic::Update(float fElapsed)
{
	if(!m_bEnabled)
		return;

	g_MsgTick.Id = g_EventUpdateTick;
	m_fFreeElapsed = fElapsed;

	g_MsgTick.pData = reinterpret_cast<void*>(&m_fFreeElapsed);
	SendMsg(g_MsgTick);

	// input�� ���´�.
	// logic�� update �Ѵ�. (������ ��ü ����)
}