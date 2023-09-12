/*****************************************************************************
 *
 * File			: NtlSobEventObject.h
 * Author		: agebreak
 * Copyright	: (��)NTL
 * Date			: 2007. 9. 4	
 * Abstract		: Simulation Event object
 *****************************************************************************
 * Desc         : Trigger Object ���� Ư���� Event�� ������ ������Ʈ�� �����Ѵ�.
 *				  (��. ����ǥ - ��Ŀ�̵ɶ� UI�� ǥ��)
 *				  ������ ����ȭ ���� �ʰ� Ŭ���̾�Ʈ ǥ�ÿ��� ����Ѵ�. 
 *****************************************************************************/

#pragma once

#include "NtlSobActor.h"


class CNtlSobEventObject : public CNtlSobActor
{
	DECLEAR_MEMORY_POOL( CNtlSobEventObject, NTL_DEFAULT_MEMORY_POOL )

public:
	CNtlSobEventObject(VOID);
	virtual ~CNtlSobEventObject(VOID);

	virtual RwBool  Create(VOID);
	virtual void    Destroy(VOID);
	virtual void    Update( RwReal fElapsed );
	virtual void    HandleEvents( RWS::CMsg& pMsg );

protected:	
};
