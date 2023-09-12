/*****************************************************************************
 *
 * File			: NtlSobMonster.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 10. 31	
 * Abstract		: Simulation monster object
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __NTL_SOB_MONSTER_H__
#define __NTL_SOB_MONSTER_H__

#include "NtlSobFeelingActor.h"
#include "NtlBuffContainer.h"

class CNtlBeCharData;

class CNtlSobMonster : public CNtlSobFeelingActor
{
	DECLEAR_MEMORY_POOL(CNtlSobMonster, NTL_DEFAULT_MEMORY_POOL)
	
public:
	CNtlSobMonster();
	virtual ~CNtlSobMonster();

	virtual RwBool			Create(void);
	virtual void			Destroy(void);
	virtual void			Update(RwReal fElapsed);
	virtual CNtlFSMLayer*	CreateFSM(void);
	virtual void			HandleEvents(RWS::CMsg &pMsg);

	// control data station
	virtual void*			GetBehaviorData(void);

protected:
    // �̺�Ʈ ó��
    void    OnEventBotCautionNfy_Handler(RWS::CMsg& pMsg);          ///< �������� ĳ���͸� �߰�������
    void    OnEventBotHelpMeNfy_Handler(RWS::CMsg& pMsg);           ///< ���� ���������� ������ ��û�Ҷ�

protected:
    CNtlBeCharData*         m_pBeData;				/** character behavior data */
};


inline void* CNtlSobMonster::GetBehaviorData(void)
{
	return reinterpret_cast<void*>(m_pBeData); 
}


#endif
