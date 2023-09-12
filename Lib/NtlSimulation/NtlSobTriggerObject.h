/*****************************************************************************
 *
 * File			: NtlSobTriggerObject.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 11. 16	
 * Abstract		: Simulation trigger object
 *****************************************************************************
 * Desc         : trigger�� �����Ǿ� �ִ� object ���� ����� �������ָ�, 
 *				  ������ ���⸦ �̷��.
 *				  handle�� �Ϲ����� simulation object ���ó�� ������ ���� handle 
 *                �Ҵ� ����� �ƴ϶�, ������ Ŭ���̾�Ʈ���� ������ �˰�����
 *                ����Ͽ�, Ŭ���̾�Ʈ ��ü������ handle�� �Ҵ��Ѵ�.
 *****************************************************************************/

#ifndef __NTL_SOB_TRIGGEROBJECT_H__
#define __NTL_SOB_TRIGGEROBJECT_H__

#include "NtlSobActor.h"

struct SNtlEventTObjectUpdateState;

struct SNtlSobTriggerObjectState
{
	RwUInt8			byMainState;
	RwUInt8			bySubState;
};

class CNtlSobTriggerObject : public CNtlSobActor
{
	DECLEAR_MEMORY_POOL( CNtlSobTriggerObject, NTL_DEFAULT_MEMORY_POOL )

protected:

	RwReal			m_fTime;
	RwUInt8			m_byQuestMark;
	RwBool			m_bActiveQuestMark;
	RwUInt16		m_tID;

	// Ʈ���� ������Ʈ�� ����
	RwUInt8						m_byStateType;
	SNtlSobTriggerObjectState	m_sPreState;
	SNtlSobTriggerObjectState	m_sCurState;

protected:

	void	QeustMarkCheck(RwReal fElapsed);

public:

	CNtlSobTriggerObject(VOID);
	virtual ~CNtlSobTriggerObject(VOID);

	virtual RwBool Create(VOID);
	virtual void Destroy(VOID);

	virtual CNtlFSMLayer* CreateFSM(void);

	virtual CNtlSobInfluence* CreateSobInfluence(void);

	virtual void Update( RwReal fElapsed );

	virtual void HandleEvents( RWS::CMsg& pMsg );

	virtual void SetDirection(const RwV3d *pDir);

public:

	RwBool CanClicked(void);

	RwBool IsScouterObject( void );

	RwBool IsTLQObject( void );

	RwBool IsPIDObject( void );

	RwBool IsDojoSealObject( void );

	void ActiveQuestMark(RwBool bQuestMark);

	RwBool ShowTOForSCT( RwBool bShow );

	SNtlSobTriggerObjectState GetCurrentTriggerObject(void) { return m_sCurState; }

protected:

	void InitState( void );
	void UpdateState( SNtlEventTObjectUpdateState *pSobTObjUpdateState );

	void PlayClickSound( void );
};

#endif