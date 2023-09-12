/*****************************************************************************
* File			: TBNewsGui.h
* Author		: Haesung, Cho
* Copyright		: (��)NTL
* Date			: 2008. 10. 21
* Abstract		: DBO õ������ ����ȸ �ҽ��� ������
*****************************************************************************
* Desc         : 
*****************************************************************************/

#ifndef __TBNEWSGUI_H__
#define __TBNEWSGUI_H__

#pragma once

// õ������ ����ȸ GUI ��ũ��Ʈ ����
#define dTBNEWS_SCRIPT_FILE_FOLDER		L"script\\tenkaichibudokai\\"
#define dTBNEWS_GUI_FRAMEWORK_FILE		"gui\\TBNewsGui.frm"
#define dTBNEWS_GUI_SURFACE_FILE		"gui\\TBNewsGui.srf"

// õ������ ����ȸ�� ��ũ�� �Ǵ� ����ƽ �ڽ��� ����
#define dTBNEWS_INFO_BOX_NUMS						2

// õ������ ����ȸ ��ũ�� �ڽ��� �ּ� ũ��
#define dTBNEWS_INFO_BOX_MIN_WIDTH					245

// õ������ ����ȸ ��ũ�� �ڽ��� ����
#define dTBNEWS_INFO_BOX_MARGIN						10

/**
* \ingroup client
* \brief õ������ ����ȸ �ҽ��� GUI
*/
class CTBNewsGui : public CNtlPLGui, public RWS::CEventHandler
{
	enum eNewsType
	{
		TYPE_INDIVIDIAUL = 0,			///< ������ �ҽ���
		TYPE_TEAM,					///< ���� �ҽ���

		TYPE_NUMS,
		INVALID_TYPE = 0xFF
	};

	enum eStaticInfo
	{
		INFO_STATE = 0,					///< ������ ���� ����
		INFO_INDITIME,				///< ������ �ð� ����
		INFO_TEAMTIME,				///< ��Ƽ�� �ð� ����
		
		INFO_NUMS,
		INVALID_INFO = 0xFF
	};

	enum eTextLine
	{
		TL_1 = 0,
		TL_2,
		TL_3,
		TL_4,

		TL_NUMS
	};

	enum eNoticeType
	{
		NIT_STATE_GUIDE,
		NIT_STATE_END,
		
		NIT_NUMS,
		INVALID_NIT = 0xFF
	};

public:
	CTBNewsGui(const RwChar* pName);
	virtual ~CTBNewsGui();

	RwBool	Create();
	void	Destroy();

	void	Update(RwReal fElapsed);

	RwInt32	SwitchDialog(bool bOpen);
	void	HandleEvents(RWS::CMsg& msg);

public:
	void	UpdateInterface();
	void	SetNews( RwUInt8 byIndiMatchState, RwUInt8 byTeamMatchState );
	void	SetMatchNotice( RwUInt8 byIndiMatchState, RwUInt8 byTeamMatchState );
	void	SetPrizeText( eNoticeType eNitType, RwUInt8 byMatchType, gui::CStaticBox* pComponent, const WCHAR* awcWinner, const WCHAR* awcSecondWinner );
	void	UpdateNoticeImage( eNoticeType eNitType );
	void	UpdateButtons();

	void	OnClickedBtnClose( gui::CComponent* pComponent );
	void	OnClickedBtnSoloRequest( gui::CComponent* pComponent );
	void	OnClickedBtnPartyRequest( gui::CComponent* pComponent );
	void	OnClickedBtnLicense( gui::CComponent* pComponent );
	void	OnClickedBtnTournenment( gui::CComponent* pComponent );

	// Info
public:
	void	InitInfoBox();
	WCHAR*	GetNextStepString( RwUInt8 byMatchType );			///< ���� ���¿� ���� �޽��� ���
	void	SetInfoBox( RwUInt8 byInfoBoxNum, gui::CStaticBox* pStbInfoBox );
	void	UpdateInstanceInfo();


protected:
	gui::CStaticBox*	m_pStbTitle;			///< �ҽ����� �̸�
	gui::CStaticBox*	m_pStbHeadLine;			///< �ҽ����� HeadLine
	gui::CStaticBox*	m_pStbNewsMark;			///< �ҽ����� Mark

	gui::CPanel*		m_pPnlImage;			///< �ҽ����� ���ϵ� �̹���
	gui::CHtmlBox*		m_pHtmlNews;			///< �ҽ����� ��µ� Html �ڽ�

	gui::CStaticBox*	m_pStbNoticeText[TL_NUMS];	///< �ҽ����� ��µ� �ؽ�Ʈ��
		
	gui::CButton*	m_pBtnClose;			///< �ݱ� ��ư
	gui::CButton*	m_pBtnSoloRequest;		///< ������ ��û�ϱ� �� ��ư
	gui::CButton*	m_pBtnPartyRequest;		///< ��Ƽ�� ��û�ϱ� �� ��ư
	gui::CButton*	m_pBtnLicense;			///< �������� ��ư
	gui::CButton*	m_pBtnTournement;		///< ����ǥ�� ��ư

	// Scroll infotext
	gui::CDialog*		m_pDlgInfo;			///< Clipping �Ǵ� dialog
	gui::CStaticBox*	m_paStbInfoBox[dTBNEWS_INFO_BOX_NUMS];
	RwUInt8				m_aBoxPresentInfo[dTBNEWS_INFO_BOX_NUMS];
	RwReal				m_fBoxPresentPosX[dTBNEWS_INFO_BOX_NUMS];

	RwUInt8				m_byCurFirstBox;	///< ���� �ռ��� �ִ� �ڽ��� ��ȣ

	// Slot
	gui::CSlot			m_slotClickedBtnClose;
	gui::CSlot			m_slotClickedBtnSoloRequest;
	gui::CSlot			m_slotClickedBtnPartyRequest;
	gui::CSlot			m_slotClickedBtnLicense;
	gui::CSlot			m_slotClickedBtnTournement;

	RwBool				m_bMudosaUpdate;
	RwUInt32			m_uiMudosaReaminTime;
};

#endif//__TBNEWS_GUI_H__