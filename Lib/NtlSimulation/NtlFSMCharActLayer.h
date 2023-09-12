/*****************************************************************************
 *
 * File			: NtlFSMCharActLayer.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2006. 2. 9	
 * Abstract		: fsm character act layer
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_FSM_CAHRACT_LAYER_H__
#define __NTL_FSM_CAHRACT_LAYER_H__

#include "NtlFSMLayer.h"

class CNtlBehaviorCharPush;
class CNtlBehaviorCharShock;
class CNtlBehaviorCharKnockDown;

class CNtlFSMCharActLayer : public CNtlFSMLayer
{
	DECLEAR_MEMORY_POOL(CNtlFSMCharActLayer, NTL_DEFAULT_MEMORY_POOL)

private:

	CNtlBehaviorCharPush *m_pBePush;
	CNtlBehaviorCharShock *m_pBeShock;
	CNtlBehaviorCharKnockDown *m_pKnownDown;

private:

	void CreateController(RwUInt32 uiController);

public:

	CNtlFSMCharActLayer();
	~CNtlFSMCharActLayer();

	/**
    *  �� class�� ������ �� �ٷ� ȣ���ϴ� �Լ�
    *
    */
	virtual RwBool Create(RwUInt32 uiController);

	/**
    *  �� class�� �Ҹ�Ǳ� ���� ȣ���ϴ� �Լ�
    *
    */
	virtual void Destroy(void);

	/**
    *  layer update �Լ�.
    *
    */
	virtual void Update(RwReal fElapsed);

	/**
    *  layer event handler �Լ�.
    *
    */
	virtual RwUInt32 HandleEvents(RWS::CMsg &pMsg);
};

#endif
