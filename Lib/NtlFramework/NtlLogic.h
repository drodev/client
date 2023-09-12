/*****************************************************************************
 *
 * File			: NtlLogic.h
 * Author		: HyungSuk, Jang
 * Copyright	: (��)NTL
 * Date			: 2005. 7. 14	
 * Abstract		: Main Logic.
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/


#ifndef __NTL_LOGIC__
#define __NTL_LOGIC__

#include "ceventhandler.h"
#include "NtlSysEvent.h"


//RWS_DEFINE_EVENT(iMsgUpdateTick, 0, "Sent just before each MsgUpateTick.");

/**
 * \ingroup Client
 * client�� ��� simulation object�� system event�� ������ ��ü�̴�.
 * ���⿡�� free tick, 10 frame sync tick, 20 frame sync tick, 10 frame sync tick�� �����Ѵ�.
 *
 */

class CNtlLogic
{
private:
    
	bool m_bEnabled;			/**< tick�� enable �� disable flag*/

	float m_fFreeElapsed;		/**< free sync tick*/
	float m_fSync30Elapsed;		/**< 30 frame sync tick�� ���Ǵ� delta time ����*/
	float m_fSync20Elapsed;		/**< 20 frame sync tick�� ���Ǵ� delta time ����*/
	float m_fSync10Elapsed;		/**< 10 frame sync tick�� ���Ǵ� delta time ����*/
	
public:

	CNtlLogic();

	bool Create(void);
	void Destroy(void);

	/**
	* \ingroup Client
	* client�� rendering ��ü�� �������� sync�� tick event�� ������.
	* ��� simulation object�� tick event�� �޾Ƽ� update�� �Ѵ�.
	*
	*/
	void Update(float fElapsed);

	// simulation object tick�� enable �� disable
	void SetEnabled(bool bEnabled);
};

inline void CNtlLogic::SetEnabled(bool bEnabled)
{
	m_bEnabled = bEnabled;
}

#endif
