#include "precomp_ntlframework.h"
#include "NtlRender.h"
#include "NtlDebug.h"

/**
*
*  constructor for CNtlRender
*
*/
CNtlRender::CNtlRender() : m_bEnabled(false) 
{
}


bool CNtlRender::Create(void)
{
	NTL_FUNCTION("CNtlRender::Create");

	NTL_RETURN(true);
}

void CNtlRender::Destroy(void)
{
	NTL_FUNCTION("CNtlRender::Destroy");

	NTL_RETURNVOID();
}

/**
*
*  rendering ��ü update �Լ�.
*  \param fElapsed�� ���� tick���� ���� tick�� delta time�̴�.
*
*/
void CNtlRender::Update(float fElapsed)
{
	NTL_FUNCTION("CNtlRender::Update");

	// input�� ���´�.
	// logic�� update �Ѵ�. (������ ��ü ����)

	g_MsgTick.Id = g_EventRenderTick;
	m_fFreeElapsed = fElapsed;

	g_MsgTick.pData = reinterpret_cast<void*>(&m_fFreeElapsed);
	SendMsg(g_MsgTick);
	
	NTL_RETURNVOID();
}

