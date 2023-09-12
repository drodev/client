/******************************************************************************
* File			: BroadCastGui.h
* Author		: Haesung Cho
* Copyright		: (��)NTL
* Date			: 2008. 10. 27
* Abstract		: 
*****************************************************************************
* Desc			: ���� TS message, Server emergency, Mini narration�� ����ϴ� GUI
*****************************************************************************/

#ifndef __BROAD_CAST_GUI_H__
#define __BROAD_CAST_GUI_H__

#pragma once

// core
#include "ceventhandler.h"

// presentation
#include "NtlPLGui.h"

// Client UI Config
#include "DBOUIConfig.h"

// BroadCast
#include "BroadCastUnit.h"
#include "NtlPLAccelController.h"

// Client gui
#include "SurfaceGui.h"

#define dBROAD_BALLOON_SHAPE_NUMS		3
#define dBROAD_BALLOON_BTS_DEFAULT_IMG	"BTS_Default.png"
#define dBROAD_BALLOON_BE_DEFAULT_IMG	"BE_Default.png"
#define dBROAD_HTML_TEXT_STANDARD		33
#define dBROAD_HTML_TEXT_LARGE_WIDTH	286
#define dBROAD_HTML_TEXT_SMALL_WIDTH	143
#define dBROAD_HTML_TEXT_HEIGHT			55
#define dBROAD_HTML_TEXT_LARGE_POSITION_X	-325
#define dBROAD_HTML_TEXT_SMALL_POSITION_X	-185
#define dBROAD_HTML_TEXT_POSITION_Y			60

// ���� ����
class CNtlPLAccelController;
class CBroadCastUnit;

// unit deque define
typedef std::deque< CBroadCastUnit > deqBroadUnit;

/**
* \ingroup client
*/
class CBroadCastGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	// ��ε�ĳ��Ʈ GUI�� ����
	enum eBroadState
	{
		STATE_DIRECTION_IN_START,	// ��ź���� ���� ����
		STATE_DIRECTION_IN,			// ��Ÿ���� ���� ��
		STATE_DIRECTION_IN_END,		// ��Ÿ���� ���� ��			- �����̵��� ��� ��ǳ���� ����ش�.
		STATE_OPEN,					// ���� ����
		STATE_DIRECTION_OUT_START,	// ������� ���� ����		- �����̵��� ��� ��ǳ���� �ݴ´�.
		STATE_DIRECTION_OUT,		// ������� ���� ��
		STATE_DIRECTION_OUT_END,	// ������� ���� ��
		STATE_CLOSE,				// ���� ����

		STATE_NUMS,
		INVALID_STATE = 0xFF
	};

	CBroadCastGui(const RwChar* pName);
	virtual ~CBroadCastGui();

	RwBool		Create();
	VOID		Destroy();

	// Updates
	VOID		Update( RwReal fElapsed );
	VOID		UpdateDirectionInStart( RwReal fElapsed );
	VOID		UpdateDirectionIn( RwReal fElapsed );
	VOID		UpdateDirectionInEnd( RwReal fElapsed );
	VOID		UpdateOpen( RwReal fElapsed );
	VOID		UpdateDirectionOutStart( RwReal fElapsed );
	VOID		UpdateDirectionOut( RwReal fElapsed );
	VOID		UpdateDirectionOutEnd( RwReal fElapsed );
	VOID		UpdateClose( RwReal fElapsed );

	// HandleEvents
	VOID		HandleEvents( RWS::CMsg &msg );
	RwInt32		SwitchDialog( bool bOpen );

	// Interfaces
	VOID		SetState( RwUInt8 byState );
	VOID		SetCurUnitData( RwUInt8 byMsgType, vecdef_BroadMsgDataList& vecList );
	VOID		SetCurMsgData( CBroadCastUnit& unit );
	VOID		SetHtmlString( const WCHAR* pString, RwInt32 nSize );
	VOID		SaveCurUnitData();
	VOID		DeleteDeqUnit( RwInt8 byMsgType );
	VOID		DeleteDeqUnitAll();
	VOID		ShowBalloon( RwUInt8 byBalloonShape, RwBool bSmall = FALSE, RwBool bShow = TRUE);
	VOID		HideAllBalloon();

	VOID		SetIllust( const RwChar* pIllustName );
	VOID		SetIllust( RwUInt32 uiOwnerTblIdx, RwUInt32 uiOwnerCondition );
	VOID		SetillustPos( RwInt32 nX, RwInt32 nY );

	VOID		Play( RwBool bPlay );
	RwBool		IsPlay();

	// Signal back
	VOID		OnPaint();
	VOID		OnMove( RwInt32 nOldX, RwInt32 nOldY );


	// Gui
protected:
	gui::CPanel*		m_pPnlBack;
	gui::CStaticBox*	m_pStbName;
	gui::CFlash*		m_paFlaBalloon[dBROAD_BALLOON_SHAPE_NUMS];
	gui::CFlash*		m_paFlaBalloonSmall[dBROAD_BALLOON_SHAPE_NUMS];
	gui::CHtmlBox*		m_pHtmlText;
	gui::CPanel*		m_pPnlIllust;
	CSurfaceGui			m_surIllust;

	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotMove;

protected:
	// ������Ʈ �Լ��� �Լ� ������
	typedef				VOID (CBroadCastGui::*UpdateState)( RwReal );
	UpdateState			m_aCallUpdateState[STATE_NUMS];	///< Update �Լ� ������

	RwUInt8				m_byState;			///< UI�� ���� ����
	deqBroadUnit		m_deqUnit;			///< Unit�� ��⿭
	
	CBroadCastUnit		m_CurUnit;			///< ���� ������� Unit�� Data
	RwBool				m_bCurUnit;			///< ���� ������� Unit�� ����Ÿ ��ȿ/��ȿ ����

	sBROAD_MSG_DATA		m_sCurData;			///< ���� ��µǰ� �ִ� Data ( Setting )	
	RwUInt8				m_uSlidingFadeAlpha;		///< ������ Alpha ( Sliding/Fade �� ���� ���� )
	RwBool				m_bSmallText;		///< ���� ��µǰ� �ִ� Text�� Large������ ����

	RwReal				m_fElapsed;			///< ���� GUI���� �Ҹ�ǰ� �ִ� time

	RwReal				m_fShakeTime;		///< Illust Shake�� ���̴� Ÿ�� ����
	CRectangle			m_rectBackIllust;	///< �Ϸ���Ʈ�� ��鸲 �߽� ��ǥ

	CNtlPLAccelController	m_conAccel;		///< AccelController
	CNtlPLAccelController	m_conAlpha;		///< Alpha AccelController

	RwBool				m_bPlay;			///< ���� �÷��� �ǰ� �ִ°�?

	SUIConfigBroadCast*	m_pBroadCastConfig;	///< Broad Cast ���� ���� �ɼǵ�
};

#endif//__BROAD_CAST_GUI_H__