#include "precomp_ntlsimulation.h"
#include "NtlWorldConceptController.h"

// simulation
#include "NtlSLEvent.h"
#include "NtlSLEventFunc.h"
#include "NtlWorldConcept.h"

#include "NtlSob.h"
#include "NtlSobGroup.h"
#include "NtlSobManager.h"


CNtlWorldConceptController::CNtlWorldConceptController(void)
{
	m_fStateTime	= 0.0f;
	m_iWorldState	= WORLD_STATE_NONE;
	m_eType			= WORLD_PLAY_NONE;
	m_bPause		= FALSE;
}

CNtlWorldConceptController::~CNtlWorldConceptController(void)
{
}

/**
 * ����Ʈ�� ��� �׼��� ������ �����̴�. �� ������ ���� �ϸ� �ȵǴ� �׼��� �ִ� ��쿡�� �������̵��Ѵ�.
 * \param eAction �׼� ���� ���� �Ǻ� �÷���
 * return �׼� ���� ����
 */
RwBool CNtlWorldConceptController::IsEnableAction( EAvatarAction eAction ) 
{
	return TRUE;
}

/**
 * ����Ʈ�� �ƹ��͵� ���� �ʴ´�. ������ ���� ���� Ŭ�������� �������̵��Ѵ�. 
 */
void CNtlWorldConceptController::Update( RwReal fElapsedTime ) 
{
	switch(m_iWorldState)
	{
		case WORLD_STATE_ENTER:
		case WORLD_STATE_IDLE:
			break;
		case WORLD_STATE_EXIT:
			ChangeState(WORLD_STATE_NONE);		
			break;
	}
}

void CNtlWorldConceptController::ChangeState( RwInt32 iState ) 
{
	m_fStateTime = 0.0f;
	m_iWorldState = iState;

	CNtlSLEventGenerator::ChangeWorldConceptState(m_eType, iState);
}

void CNtlWorldConceptController::SetConceptType(EWorldPlayConcept eType)
{
	m_eType = eType;
}

EWorldPlayConcept CNtlWorldConceptController::GetConceptType(void)
{
	return m_eType;
}

void CNtlWorldConceptController::Pause(RwBool bPause)
{
	m_bPause = bPause;
}

