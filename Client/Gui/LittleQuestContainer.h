/******************************************************************************
* File			: LittleQuestContainer.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 2. 20
* Abstract		: 
*****************************************************************************
* Desc			: Ư�� Ÿ���� �ν��Ͻ� ����Ʈ �����̳�
*****************************************************************************/

#pragma once

#include <list>

// core
#include "ceventhandler.h"

// share
#include "NtlTimeQuest.h"

// simulation
#include "NtlSLDef.h"
#include "NtlSLEvent.h"

// dbo
#include "SurfaceGui.h"

class CLittleQuestContainer : public RWS::CEventHandler
{
#define dMAX_QUEST_AIM			4	///< ����Ʈ�� �ִ� ��ǥ ����

	struct sQuestData
	{
		sTS_KEY					sTSKey;				///< TSŰ
		RwUInt32				uiSortType;			///< ����Ʈ Ÿ��
		RwUInt32				uiQuestTitle;		///< ����Ʈ ����
		eSTOC_EVT_DATA_TYPE		eEvtInfoType;		///< ���� �̺�Ʈ ���� - ������ Ÿ��
		uSTOC_EVT_DATA			uEvtInfoData;		///< ���� �̺�Ʈ ���� - ������
		RwUInt32				uiTimeLimit;		///< Ÿ�� ���� ����
	};

public:
	CLittleQuestContainer();
	virtual ~CLittleQuestContainer();

	typedef std::list<sQuestData*>				LIST_QUEST;
	typedef std::list<sQuestData*>::iterator	LIST_QUEST_ITER;

	RwBool		Create(RwUInt32 uiQuestType, gui::CStaticBox* pQuestTitle, gui::CStaticBox* pAim_1, gui::CStaticBox* pAim_2,
					   gui::CStaticBox* pAim_3, gui::CStaticBox* pAim_4);
	VOID		Destroy();

	VOID		NextQuest();

protected:
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			InitQuestData();
	VOID			SetIndicator(sQuestData* pQuestData);
	sQuestData*		FindData(NTL_TS_T_ID tID);
	sQuestData*		NextData(NTL_TS_T_ID tID_current);
	VOID			DelData(NTL_TS_T_ID& tID);

protected:		
	gui::CStaticBox*	m_pQuestTitle;				///< ����Ʈ ����
	gui::CStaticBox*	m_pQuestAim[dMAX_QUEST_AIM];///< ����Ʈ ��ǥ

	RwUInt32			m_uiQuestType;
	NTL_TS_T_ID			m_tID;						///< ���� �������� �ִ� ����Ʈ ID
	LIST_QUEST			m_listQuestData;
};