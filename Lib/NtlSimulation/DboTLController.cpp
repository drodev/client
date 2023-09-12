#include "precomp_ntlsimulation.h"
#include "DboTLController.h"

// simulation
#include "DboTLEntity.h"
#include "NtlSLEvent.h"


CDboTLController::CDboTLController( void )
:m_bEnableSkip(FALSE)
,m_bSkipping(FALSE)
{
	m_itCurGroup = m_defGroupList.end();
}


CDboTLController::~CDboTLController( void )
{
	m_defGroupList.clear();
	m_itCurGroup = m_defGroupList.end();
}


void CDboTLController::PushTLSyncGroup( CDboTLSyncGroup* pTLSyncGroup )
{
	m_defGroupList.push_back( pTLSyncGroup );
}


RwBool CDboTLController::IsFinish( void )
{
	return m_defGroupList.empty() ? TRUE : FALSE;
}


void CDboTLController::Update( RwReal fElapsedTime )
{
	if ( m_defGroupList.empty() )
	{
		return;
	}

	if ( m_itCurGroup == m_defGroupList.end() )
	{
		ChangeCurGroup();
	}
	else
	{
		CDboTLSyncGroup* pSyncGroup = *m_itCurGroup;

		if ( pSyncGroup->IsFinish() )
		{
			ChangeCurGroup();
		}
		else
		{
			// Update
			pSyncGroup->Update( fElapsedTime );
		}
	}
}


void CDboTLController::Skip()
{
	// g_EventTLEnableSkip�̺�Ʈ�� �߻��Ͽ� m_bEnableSkip �÷��װ� FALSE�� �� ������ �ݺ��Ѵ�
	while ( m_bEnableSkip && m_itCurGroup != m_defGroupList.end() )
	{
		m_bSkipping = TRUE;
		ChangeCurGroup();
	}

	m_bSkipping = FALSE;
}


RwBool CDboTLController::IsSkipping()
{
	return m_bSkipping;
}


void CDboTLController::HandleEvents( RWS::CMsg &pMsg )
{
	if ( pMsg.Id == g_EventTLEnableSkip )
	{
		SNtlEventTLEnableSkip* pEvent = reinterpret_cast<SNtlEventTLEnableSkip*>( pMsg.pData );

		m_bEnableSkip = pEvent->bEnableSkip;
	}
	else
	{
		if ( m_itCurGroup != m_defGroupList.end() )
		{
			(*m_itCurGroup)->HandleEvents( pMsg );
		}
	}
}


void CDboTLController::ChangeCurGroup( void )
{
	// �ʱ� ������ ���� �׷쿡 ���� Enter
	if ( m_itCurGroup == m_defGroupList.end() )
	{
		m_itCurGroup = m_defGroupList.begin();
		(*m_itCurGroup)->Enter();
	}
	// �ʱ� ���� ���� �׷� Leave �� ���� �׷쿡 ���� Enter
	else
	{
		(*m_itCurGroup)->Leave();
		++m_itCurGroup;
		if ( m_itCurGroup != m_defGroupList.end() )
		{
			(*m_itCurGroup)->Enter();
		}
		else
		{
			m_defGroupList.clear();
			m_itCurGroup = m_defGroupList.end();
		}
	}
}
