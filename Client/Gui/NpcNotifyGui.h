/******************************************************************************
* File			: NpcNotifyGui.h
* Author		: Cho HaeSung
* Copyright		: (��)NTL
* Date			: 2008. 2. 11
* Abstract		: 
*****************************************************************************
* Desc			: NPC�� ���ͼ� ������ ������ ����Ѵ�.
*****************************************************************************/

#ifndef __NPC_NOTIFY_GUI_H__
#define __NPC_NOTIFY_GUI_H__

//#include "ceventhandler.h"
//#include "NtlPLGui.h"
//
//#define dNPCNOTIFY_SLIDING_IN_TIME		0.1f			// �����̵� �� �Ǵ� �ð�
//#define dNPCNOTIFY_SLIDING_OUT_TIME		0.1f			// �����̵� �ƿ� �Ǵ� �ð�
//#define dNPCNOTIFY_SHOW_TIME			3.0f			// NPC Notify�� �ؽ�Ʈ�� �����ִ� �ð�
//
//class CNpcNotifyGui : public CNtlPLGui, public RWS::CEventHandler
//{
//public:
//	//! Enum 
//	enum eSTATE { NPC_NONE, NPC_SLIDING_IN, NPC_SHOW, NPC_SLIDING_OUT };	// State
//	enum eTYPE { NPC_LEFT, NPC_CENTER, NPC_RIGHT };
//
//	//! Constructor & Destructor
//	CNpcNotifyGui(VOID);
//	CNpcNotifyGui(const RwChar* pName);
//	virtual ~CNpcNotifyGui(VOID);
//
//	RwBool	Create(VOID);
//	VOID	Destroy(VOID);
//
//	VOID	Init(VOID);
//
//	RwBool	SetNpcNotifyReady(eTYPE eType, eSTATE eState);
//	VOID	SetSlidingPosition(RwInt32 nStartX, RwInt32 nStartY, RwInt32 nEndX, RwInt32 nEndY );
//	VOID	SetCurrentPosition(RwInt32 nCurrentX, RwInt32 nCurrentY);
//
//	VOID	HandleEvents( RWS::CMsg& msg );
//	VOID	Update( RwReal fElapsed );
//
//	//! Operation
//	VOID	SetState(eSTATE eState);
//
//	VOID	OnMove(RwInt32 nOldX, RwInt32 nOldY);
//			
//protected:
//	VOID	NpcUpdateProc( RwReal fElapsed );
//
//	// Updates
//	VOID	NpcUpdate_None(RwReal fElapsed);
//	VOID	NpcUpdate_SlidingIn(RwReal fElapsed);
//	VOID	NpcUpdate_Show(RwReal fElapsed);
//	VOID	NpcUpdate_SlidingOut(RwReal fElapsed);
//
//	VOID	ApplyCurrentPosition(RwReal fTotalTime);
//
//	//! Variables
//	gui::CStaticBox*	m_pStbText;			///< Text
//	gui::CFlash*		m_pFlaBalloon;		///< ��ǳ��
//	gui::CPanel*		m_pPanNpc;			///< NPC
//
//	RwReal		m_fCurrentTime;
//
//	CPos		m_posStart;
//	CPos		m_posCurrent;
//	CPos		m_posEnd;
//	
//	RwInt32		m_eState;
//
//	VOID	(CNpcNotifyGui::*StateUpdate)(RwReal fElapsed);
//};

#endif//__NPC_NOTIFY_GUI_H__	