#include "precomp_ntlframework.h"
#include "NtlLogic.h"
#include "NtlDebug.h"

/**
*
*  constructor for CNtlLogic
*
*/
CNtlLogic::CNtlLogic() : m_bEnabled(false) ,
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
bool CNtlLogic::Create(void)
{
	NTL_FUNCTION("CNtlLogic::Create");

	RWS::CEventHandler::RegisterMsg (g_EventUpdateTick, "g_EventUpdateTickStr", "float");
		
	NTL_RETURN(true);
	
}

/**
*
*  ���� tick�� ���� ��ϵ� event�� �����Ѵ�.
*
*/
void CNtlLogic::Destroy(void)
{
	NTL_FUNCTION("CNtlLogic::Destroy");

    RWS::CEventHandler::UnRegisterMsg ( g_EventUpdateTick );
	
	NTL_RETURNVOID();
}

/**
*
*  simulation object�� update tick evnet�� ������.
*  ���� 30, 20, 10 frame�� sync�� tick�� ����Ͽ� ������.
*
*/
void CNtlLogic::Update(float fElapsed)
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

