#pragma once

// share
#include "NtlTimeQuest.h"

// simulation
#include "NtlWorldConceptController.h"

/**
 * \ingroup NtlSimulation
 * \brief Time machine quest ���� ���� Ŭ����
 * \date 2007-07-20
 * \author avooo
 */
class CNtlWorldConceptTMQ : public CNtlWorldConceptController
{
public:
	CNtlWorldConceptTMQ(void);
	~CNtlWorldConceptTMQ(void);

	virtual RwBool		IsEnableAction(EAvatarAction eAction);
	virtual void		ChangeState(RwInt32 iState);

	void				BeforeLoadingDirect(void);
	void				AfterLoadingDirect(void);

	RwBool				IsBeforeLoadingDirect(void);
	RwBool				IsAfterLoadingDirect(void);

	
	void					SetTMQState(eTIMEQUEST_GAME_STATE eState);	// ������ ���� ���°� �����´�	
	void					SetTMQState_from_Cleint(RwUInt8 byState);	// Ŭ���̾�Ʈ ��ü������ ���¸� �����Ѵ�

	void					NotifyTMQStateUpdate();
	RwUInt8					GetTMQState();


protected:
	RwUInt8				m_byTMQState;
};

inline RwUInt8 CNtlWorldConceptTMQ::GetTMQState()
{
	return m_byTMQState;
}