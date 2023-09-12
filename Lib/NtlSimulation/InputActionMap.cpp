// precomp
#include "precomp_ntlsimulation.h"
#include "InputActionMap.h"

// core
#include "NtlSysEvent.h"
#include "NtlMovement.h"

// simulation
#include "NtlSLLogicDef.h"
#include "NtlSLEvent.h"
#include "NtlSLEventFunc.h"
#include "NtlSLApi.h"
#include "NtlSLGlobal.h"
#include "NtlSLPacketGenerator.h"
#include "NtlCameraManager.h"

// framework
#include "NtlApplication.h"

CInputActionMap* CInputActionMap::m_pInstance = 0;

/**
* \brief Construction
*/
CInputActionMap::CInputActionMap()
:m_hKeyDown(0)
,m_hKeyUp(0)
,m_hMouseDown(0)
,m_hMouseUp(0)
,m_pCallKeyboardMove(0)
,m_pCallKeyboardDashMove(0)
,m_pCallAvatarSelect(0)
,m_pCallJump(0)
,m_pCallCharging(0)
,m_pCallBlocking(0)
,m_pCallSitAndStand(0)
,m_pCallAutoRun(0)
,m_pCallSkillQuickSlotDown(0)
,m_pCallSkillQuickSlotUp(0)
,m_pCallSkillQuickSlotExDown(0)
,m_pCallSkillQuickSlotExUp(0)
,m_pCallSkillQuickSlotEx2Down(0)
,m_pCallSkillQuickSlotEx2Up(0)
,m_pCallSkillQuickSlotChange(0)
,m_pCallExit(0)
,m_pCallLooting(0)
,m_pCallDialogAction(0)
,m_pCallTabKey(0)
,m_pCallAutoTarget(0)
,m_pCallAutoAttack(0)
,m_pCallAutoFollow(0)
,m_pCallPartySelect(0)
,m_pCallPartyAutoSelect(0)
,m_pCallScouterUse(0)
,m_pCallTargetMarking(0)
,m_pCallTargetSelecting(0)
,m_pCallChatPageChange(0)
,m_uiMoveFlags(0)
,m_bRBtnDown(0)
,m_uiServerMoveFlags(0)
,m_bActive(TRUE)
,m_bAcceptServer(TRUE)
{
	NTL_PRE(m_pInstance == 0);
	m_pInstance = this;	

	m_sFrontDashMap.byDown = 0;
	m_sFrontDashMap.fTime = 0.0f;
	m_sFrontDashMap.uiMoveFlags = NTL_MOVE_F;
	m_sLeftDashMap.byDown = 0;
	m_sLeftDashMap.fTime = 0.0f;
	m_sLeftDashMap.uiMoveFlags = NTL_MOVE_L;
	m_sRightDashMap.byDown = 0;
	m_sRightDashMap.fTime = 0.0f;
	m_sRightDashMap.uiMoveFlags = NTL_MOVE_R;
	m_sBackDashMap.byDown = 0;
	m_sBackDashMap.fTime = 0.0f;
	m_sBackDashMap.uiMoveFlags = NTL_MOVE_B;

	m_mapFlag.clear();
}

/**
* \brief Destruction
*/
CInputActionMap::~CInputActionMap()
{
	m_pInstance = 0;
	m_mapFlag.clear();
}

/**
* \brief CInputActionMap�� �ν��Ͻ� ����(�̱���)
*/
CInputActionMap* CInputActionMap::GetInstance(void)
{
	return m_pInstance;
}

/**
* \brief Create
*/
RwBool CInputActionMap::Create(void)
{
	NTL_FUNCTION("CInputActionMap::Create");

	// Link
	LinkMsg(g_EventUpdateTick, 0, SLUPDATE_PRIORITY_INPUT);
	LinkMsg(g_EventActionMapLoadInfo, 0, 0x9000);
	LinkMsg(g_EventActionMapUpdateRes, 0, 0x9000);
	LinkMsg(g_EventTLActionMapBackup, 0 );
	LinkMsg(g_EventTLActionMapRestore, 0 );

	// CallBack
	m_hKeyDown = CInputHandler::GetInstance()->LinkKeyDown( this, &CInputActionMap::KeyDownHandler);
	m_hKeyUp = CInputHandler::GetInstance()->LinkKeyUp( this, &CInputActionMap::KeyUpHandler);
	m_hMouseDown = CInputHandler::GetInstance()->LinkMouseDown( this, &CInputActionMap::MouseDownHandler);
	m_hMouseUp = CInputHandler::GetInstance()->LinkMouseUp( this, &CInputActionMap::MouseUpHandler);

	// ActionMapManager �ʱ�ȭ
	InitDefaultActionMap();
	m_ActionMapManager.ClearInputAction();
	m_ActionMapManager.ClearReleaseAction();
	m_ActionMapManager.ClearResult();

	RegisterFlagMap();	// ����ȸ���� ���� Ű�� ���

	// ���ø����̼ǿ� ��Ű�� ����Ѵ�. print screen/sys rq Ű�� �̿��ϱ� ����
	/*RegisterHotKey( CNtlApplication::GetInstance()->GetHWnd(), NTL_KEY_SNAPSHOT, 0, VK_SNAPSHOT );*/
	
	NTL_RETURN(TRUE);
}

/**
* \brief Destroy
*/
void CInputActionMap::Destroy(void)
{
	NTL_FUNCTION("CInputActionMap::Destroy");

	// UnLink Event
	UnLinkMsg(g_EventTLActionMapBackup);
	UnLinkMsg(g_EventTLActionMapRestore);
	UnLinkMsg(g_EventActionMapUpdateRes);
	UnLinkMsg(g_EventActionMapLoadInfo);
	UnLinkMsg(g_EventUpdateTick);
	

	// UnLink Callback
	CInputHandler::GetInstance()->UnLinkKeyDown(m_hKeyDown); 
	CInputHandler::GetInstance()->UnLinkKeyUp(m_hKeyUp);
	CInputHandler::GetInstance()->UnLinkMouseDown(m_hMouseDown); 
	CInputHandler::GetInstance()->UnLinkMouseUp(m_hMouseUp);

	// UnLink
	UnLinkKeyboardMove();
	UnLinkKeyboardDashMove();
	UnLinkAvatarSelect();
	UnLinkJump();
	UnLinkCharging();
	UnLinkBlocking();
	UnLinkSitAndStand();
	UnLinkAutoRun();
	UnLinkSkillQuickSlotDown();
	UnLinkSkillQuickSlotUp();
	UnLinkSkillQuickSlotExDown();
	UnLinkSkillQuickSlotExUp();
	UnLinkSkillQuickSlotEx2Down();
	UnLinkSkillQuickSlotEx2Up();
	UnLinkSkillQuickSlotChange();
	UnLinkGameExit();
	UnLinkLooting();
	UnLinkDialogHotKey();
	UnLinkTabKey();
	UnLinkAutoTarget();
	UnLinkAutoAttack();
	UnLinkAutoFollow();
	UnLinkPartySelect();
	UnLinkPartyAutoSelect();
	UnLinkScouterUse();
	UnLinkTargetMarking();
	UnLinkTargetSelecting();
	UnLinkChatPageChane();

	NTL_RETURNVOID();
}

/**
* \brief Update
* \param fElapsed	(RwReal) ���� Update���� ����� �ð�
*/
void CInputActionMap::Update(RwReal fElapsed)
{
	// InputActionMap�� ��Ȱ��ȭ ���¶�� Update���� �ʴ´�.
	if(!m_bActive)
		return;

	// dash move update
	if(m_sFrontDashMap.byDown > 0)
		m_sFrontDashMap.fTime += fElapsed;

	if(m_sLeftDashMap.byDown > 0)
		m_sLeftDashMap.fTime += fElapsed;

	if(m_sRightDashMap.byDown > 0)
		m_sRightDashMap.fTime += fElapsed;

	if(m_sBackDashMap.byDown > 0)
		m_sBackDashMap.fTime += fElapsed;

	// keyboard move update
	//	if(m_uiServerMoveFlags > 0 && m_pCallKeyboardMove)
	//		m_pCallKeyboardMove->Call(m_uiServerMoveFlags);
}

/**
* \brief HandleEvents
* \param pMsg	(RWS::CMsg&) �̺�Ʈ�� �޽���
*/
void CInputActionMap::HandleEvents(RWS::CMsg &pMsg)
{
	NTL_FUNCTION("CNtlSobManager::HandleEvents");

	if(pMsg.Id == g_EventUpdateTick)
	{
		float fElapsed = *reinterpret_cast<float*>(pMsg.pData);
		Update(fElapsed);
	}
	// 
	else if( g_EventActionMapLoadInfo == pMsg.Id )
		HandleEventActionmapLoadInfo( pMsg );
	else if( g_EventActionMapUpdateRes == pMsg.Id )
		HandleEventsActionMapUpdateRes( pMsg );
	else if( g_EventTLActionMapBackup == pMsg.Id )
	{
		m_ActionMapManager.SetActionMapMode( ACTIONMAP_MODE_DEFAULT );
	}
	else if( g_EventTLActionMapRestore == pMsg.Id )
	{
		m_ActionMapManager.SetActionMapMode( ACTIONMAP_MODE_USERSETTING );
	}

	NTL_RETURNVOID();
}

/**
* \brief ���ӿ� ������ �� �������� �����ִ� ����Ű ������ �޴´�.
*/
void CInputActionMap::HandleEventActionmapLoadInfo( RWS::CMsg& msg ) 
{
	SNtlEventActionMapLoadInfo* pPacket = (SNtlEventActionMapLoadInfo*)msg.pData;

	// pPacket->byCount�� 0 �̸� ������ ����Ǿ� �ִ� ����Ű�� ���ٴ� ���̴�.
	// Ŭ���̾�Ʈ�� �ϵ� �ڵ��Ǿ� �ִ� ����Ű�� �������ְ� ������ �����Ѵ�.
	if( 0 == pPacket->byCount )
	{
		m_ActionMapManager.ClearActionMap();

		// ActionMap�� ���ǵǾ� �ִ� �⺻ �׼Ǹ����� �����Ѵ�.
		m_ActionMapManager.InitDefaultActionMap();

		// ��� Release Action�� ���õ� �����̳� ����� Ŭ����
		m_ActionMapManager.ClearResult();
		m_ActionMapManager.ClearReleaseAction();
		m_ActionMapManager.ClearInputAction();

		// ������ ���� �� ����
		ApplyActionMap();

		// ĸ��( byCount �� 0 �̶�� Ŭ���̾�Ʈ�� ����Ű�� �������� �ŷ� �Ѵ�. )
		m_ActionMapManager.CaptureActionMap();
	}
	else
	{
		m_ActionMapManager.ClearActionMap();

		// �������� ����Ű�� �޾Ƽ� �׼Ǹ��� ����
		for( int i=0; i<pPacket->byCount; ++i )
			m_ActionMapManager.SetCombineKey( pPacket->asData[i].wKey, pPacket->asData[i].wActionID );

		// ĸ��(������ �ִ� ��)
		m_ActionMapManager.CaptureActionMap();

		// ������ ����Ǿ� �ִ� ����Ʈ ������ �ʱ�ȭ
		m_ActionMapManager.InitDefaultActionMap();

		// ����Ʈ �ʱ�ȭ �� �Ϳ� �ٽ� �ѹ� Setting
		for( int i=0; i<pPacket->byCount; ++i )
			m_ActionMapManager.SetCombineKey( pPacket->asData[i].wKey, pPacket->asData[i].wActionID );

		// ��� Release Action�� ���õ� �����̳� ����� Ŭ����
		m_ActionMapManager.ClearResult();
		m_ActionMapManager.ClearReleaseAction();
		m_ActionMapManager.ClearInputAction();

		// �ٽ� ����
		ApplyActionMap();
	}
}

/**
* \breif ������ ����� ����Ű ������ ������ �� ���� ���
*/
void CInputActionMap::HandleEventsActionMapUpdateRes( RWS::CMsg& msg ) 
{
	SNtlEventActionMapUpdateRes* pPacket = (SNtlEventActionMapUpdateRes*)msg.pData;

	// ����
	if( pPacket->bSuccess )
	{
		// �������� ������ �����Ǿ����� �Ϻ��ϰ� ������ �ϰ�
		// ������ ������ �� �ִ� ���·� �����д�.
		m_ActionMapManager.CaptureActionMap();
		m_bAcceptServer = TRUE;
	}
	// ����
	else
	{
		// �����Ͽ��ٸ� ������ ĸ�ĵ� ����Ű�� ����������
		// ���Ӱ� �⺻ ����Ű�� �����Ͽ� �����Ѵ�.

		m_ActionMapManager.InitDefaultActionMap();
		m_bAcceptServer = TRUE;
		
		ApplyActionMap();
	}
}

/**
* \brief Initializes the key information of the InputActionMap.
*/
void CInputActionMap::Reset(void)
{
	if( m_uiServerMoveFlags != NTL_MOVE_NONE )
	{
		if(m_pCallKeyboardMove)
			m_pCallKeyboardMove->Call(NTL_MOVE_NONE);
	}

	// If the pusher is pressed, call 0
	if( IsDownAction(ACTION_AVATAR_CHARGE) && m_pCallCharging)
	{
		m_pCallCharging->Call(0);
	}
	SetFlagAction( ACTION_AVATAR_CHARGE, FALSE );

	// If blocking is pressed, call 0
	if( IsDownAction(ACTION_AVATAR_BLOCKING) && m_pCallBlocking)
	{
		m_pCallBlocking->Call(0);
	}
	SetFlagAction( ACTION_AVATAR_BLOCKING, FALSE );

	// ������ ȸ��
	for( int i = ACTION_QUICK_1; i <= ACTION_QUICK_PLUS; ++i )
	{
		// �������� ������ �־��ٸ�(?)
		if( IsDownAction( i ) )
		{
			// 0 ~ 11 ( 12�� )
			m_pCallSkillQuickSlotUp->Call( i - ACTION_QUICK_1 );
			SetFlagAction( i, FALSE );
		}
	}

	for( int i = ACTION_QUICK_1_EX; i <= ACTION_QUICK_PLUS_EX; ++i )
	{
		if( IsDownAction( i ) )
		{
			m_pCallSkillQuickSlotExUp->Call( i - ACTION_QUICK_1_EX );
			SetFlagAction( i, FALSE );
		}
	}

	for( int i = ACTION_QUICK_1_EX2; i <= ACTION_QUICK_PLUS_EX2; ++i )
	{
		if( IsDownAction( i ) )
		{
			m_pCallSkillQuickSlotEx2Up->Call( i - ACTION_QUICK_1_EX2 );
			SetFlagAction( i, FALSE );
		}
	}

	m_uiKey1MoveValidFlags	= 0;
	m_uiKey2MoveValidFlags	= 0;
	m_uiMoveFlags			= 0;
	m_bRBtnDown				= FALSE;
	m_uiServerMoveFlags		= NTL_MOVE_NONE;

	m_sFrontDashMap.byDown = 0;
	m_sFrontDashMap.fTime = 0.0f;
	m_sFrontDashMap.uiMoveFlags = NTL_MOVE_F;
	m_sLeftDashMap.byDown = 0;
	m_sLeftDashMap.fTime = 0.0f;
	m_sLeftDashMap.uiMoveFlags = NTL_MOVE_L;
	m_sRightDashMap.byDown = 0;
	m_sRightDashMap.fTime = 0.0f;
	m_sRightDashMap.uiMoveFlags = NTL_MOVE_R;
	m_sBackDashMap.byDown = 0;
	m_sBackDashMap.fTime = 0.0f;
	m_sBackDashMap.uiMoveFlags = NTL_MOVE_B;

	// ActionMap Ignore Remove
	//m_cActionMap.RemoveIgnoreKey();
	m_mapUpdownRef.clear();

	// ActionMap�� Up Down Reference�� Ŭ�����Ѵ�.
	m_ActionMapManager.ClearInputAction();
}

/**
* \brief �̵��� ���õ� �ڷḸ Reset
*/
void CInputActionMap::ResetMoveFlags( void ) 
{
	if( m_uiServerMoveFlags != NTL_MOVE_NONE )
	{
		if(m_pCallKeyboardMove)
			m_pCallKeyboardMove->Call(NTL_MOVE_NONE);
	}

	m_uiKey1MoveValidFlags	= 0;
	m_uiKey2MoveValidFlags	= 0;
	m_uiMoveFlags			= 0;

	m_uiServerMoveFlags		= NTL_MOVE_NONE;

	m_sFrontDashMap.byDown = 0;
	m_sFrontDashMap.fTime = 0.0f;
	m_sFrontDashMap.uiMoveFlags = NTL_MOVE_F;
	m_sLeftDashMap.byDown = 0;
	m_sLeftDashMap.fTime = 0.0f;
	m_sLeftDashMap.uiMoveFlags = NTL_MOVE_L;
	m_sRightDashMap.byDown = 0;
	m_sRightDashMap.fTime = 0.0f;
	m_sRightDashMap.uiMoveFlags = NTL_MOVE_R;
	m_sBackDashMap.byDown = 0;
	m_sBackDashMap.fTime = 0.0f;
	m_sBackDashMap.uiMoveFlags = NTL_MOVE_B;

	// ActionMap�� Up Down Reference�� Ŭ�����Ѵ�.
	m_ActionMapManager.ClearInputAction();
}

/**
* \brief Key�� Down�� ���� ������ �ͼ� �׼��� ã�Ƴ���.
*/
int CInputActionMap::KeyDownHandler(unsigned int pKeyData)
{
	SKeyData *pData = reinterpret_cast<SKeyData*>( pKeyData );

	unsigned short usAction = ACTION_INVALID;

	// RepCount�� 1�϶��� �����Ѵٴ� ���� �ѹ��� �����Ѵٴ� ���̴�.
	if(pData->uiRepCount == 1)
	{
		// TODO: The current tab key uses the hardcoded ACTION_TARGET_AUTO action ID
		// This is the code we added for tab handling in the temporary login focus window since it is mapped.
		// Create a way to work out and back out, or make sure that only tab keys are handled as exceptions.
		if( FALSE == m_bActive )
		{
			if( m_pCallTabKey && pData->uiChar == 0x09 )
			{
				m_pCallTabKey->Call();
			}			
			
			unsigned short usPreAction = ACTION_INVALID;
			usPreAction = m_ActionMapManager.InputHandlerDown( (unsigned char)(pData->uiChar & 0xFF) );

			/*if( usPreAction == ACTION_GLOBAL_SNAPSHOT )
			{
				GetNtlGameCameraManager()->SetCaptureScreenShot();
			}
			else */if( usPreAction == ACTION_CHAT_PGUP )
			{
				if( m_pCallChatPageChange )
					m_pCallChatPageChange->Call( 0 );
			}
			else if( usPreAction == ACTION_CHAT_PGDN )
			{
				if( m_pCallChatPageChange )
					m_pCallChatPageChange->Call( 1 );
			}

			return 1;
		}

		int nKey = pData->uiChar & 0xFF;

		// KeyRef ����
		KeyReference( (unsigned char)(pData->uiChar & 0xFF) );

		// Returns if the key is ignored.
		if (IsIgnoreKey((unsigned char)(pData->uiChar & 0xFF)))
			return 1;

		// Checks by sending the current key to the action map manager.
		usAction = m_ActionMapManager.InputHandlerDown( (unsigned char)(pData->uiChar & 0xFF) );

		if (usAction == ACTION_INVALID)
		{
			return 1;
		}

		ActionDownMoveHandler( usAction );
		ActionDownDashMoveHandler( usAction );
		ActionDownBehaviorHandler( usAction );
		ActionDownGuiHandler( usAction );
	}

	return 1;
}

/**
* \brief Ű�� Up �Ǿ��� �� Ű�� ������ �ͼ� �׼Ǹ��� ������ �´�.
*/
int CInputActionMap::KeyUpHandler(unsigned int pKeyData)
{
	SKeyData *pData = reinterpret_cast<SKeyData*>( pKeyData );

	unsigned short usAction = ACTION_INVALID;

	std::list< unsigned short > uiActionUpList;
	if( m_bActive == FALSE )
	{
		unsigned short usPreAction = ACTION_INVALID;
		usPreAction = m_ActionMapManager.InputHandlerUp( (unsigned char)(pData->uiChar & 0xFF), uiActionUpList );

		if( usPreAction == ACTION_GLOBAL_SNAPSHOT )
		{
			GetNtlGameCameraManager()->SetCaptureScreenShot();
		}
	}

	// VK_JUNJA�� ALT�� ���� ���¿��� = �� �Է����� ��� ( �ϵ��ڵ����� ġȯ���ش�. )
	if ((pData->uiChar & 0xFF) == VK_JUNJA)
	{
		pData->uiChar = NTL_KEY_EQUAL;
	}

	// KeyRef ���� : ���� Down �Ǿ��� �ʴ� Ű��� ������ ���� ( Snap Shot ���� ���ܷ� �Ѵ�. )
	if( !KeyReference( (unsigned char)(pData->uiChar & 0xFF), FALSE ) && ( (unsigned char)(pData->uiChar & 0xFF) ) != VK_SNAPSHOT )
		return 1;

	// Return if ignored
	if( IsIgnoreKey( (unsigned char)(pData->uiChar), TRUE ) )
		return 1;

	// If you set the key, it will be parameterized as UP.
	usAction = m_ActionMapManager.InputHandlerUp( (unsigned char)(pData->uiChar & 0xFF), uiActionUpList );

	if( usAction == ACTION_INVALID )
	{
		BYTE byErr = m_ActionMapManager.GetLastResult();

		// If there are no errors, it is the same as a normal INVALID.
		if( byErr == SET_RESULT_INVALID )
		{
			// ���� ��������� �ϴ� Action���� List�� �ִٸ� ��� �������ش�.
			if( !uiActionUpList.empty() )
			{
				for each( unsigned short uiActionUp in uiActionUpList )
				{
					ActionUpMoveHandler( uiActionUp );
					ActionUpDashMoveHandler( uiActionUp );
					ActionUpBehaviorHandler( uiActionUp );
					ActionUpGuiHandler( uiActionUp );
				}
			}

			return 1;
		}

		// ���������� ������ �Ǿ��ٸ� InputActionMap�� ���¸� ȸ�������ش�.
		Reset();
		
		switch( byErr )
		{
			case SET_RESULT_FIXED_KEY:
			{
				CNtlSLEventGenerator::ActionMapClientNotify( SNtlEventActionMapClientNotify::ACTIONMAP_FIXEDKEY );
			}
			break;
			case SET_RESULT_NOT_COMBINE_ACTION:
			{
				CNtlSLEventGenerator::ActionMapClientNotify( SNtlEventActionMapClientNotify::ACTIONMAP_NOTCOMBINE );
			}
			break;
			case SET_RESULT_ALREADY_KEY:			// ������ �ִ� Ű�� ������
			{
				CNtlSLEventGenerator::ActionMapClientNotify( SNtlEventActionMapClientNotify::ACTIONMAP_RELEASE, m_ActionMapManager.GetLastReleaseAction() );
			}
			break;
			case SET_RESULT_SAME_KEY:
			{
				CNtlSLEventGenerator::ActionMapClientNotify( SNtlEventActionMapClientNotify::ACTIONMAP_SAMEKEY );
			}
			break;
			case SET_RESULT_OK:
			{
				CNtlSLEventGenerator::ActionMapClientNotify( SNtlEventActionMapClientNotify::ACTIONMAP_OK );
			}
			break;
		default:
			break;
		}

		return 1;
	}

	ActionUpMoveHandler( usAction );
	ActionUpDashMoveHandler( usAction );
	ActionUpBehaviorHandler( usAction );
	ActionUpGuiHandler( usAction );

	return 1;
}


int CInputActionMap::MouseDownHandler(unsigned int pMouseData)
{

	/*SMouseData *pData = reinterpret_cast<SMouseData*>(pMouseData);*/
	//if(pData->chBtnType == MOUSE_RBTN)  //���콺 �����°� �Ŀ� ����
	//m_bRBtnDown = TRUE;

	//ConvertServerFlags(m_uiServerMoveFlags);

	return 1;
}

int CInputActionMap::MouseUpHandler(unsigned int pMouseData)
{

	/*SMouseData *pData = reinterpret_cast<SMouseData*>(pMouseData);*/
	//if(pData->chBtnType == MOUSE_RBTN)
	//m_bRBtnDown = FALSE;

	//ConvertServerFlags(m_uiServerMoveFlags);

	return 1;
}

void CInputActionMap::SetActive(RwBool bActive)
{ 
	m_bActive = bActive; 

	// ��Ȱ��ȭ��� �̵� Flag�� Reset
	if( bActive == FALSE )
		ResetMoveFlags();
}

void CInputActionMap::InitInputMode() 
{
	m_ActionMapManager.ClearInputAction();
}

RwUInt32 CInputActionMap::GetInputMode() 
{
	return (RwUInt32)m_ActionMapManager.GetInputAction();
}

void CInputActionMap::SetInputMode( RwUInt32 nAction ) 
{
	if( !m_ActionMapManager.SetInputAction( (unsigned short)nAction ) )
	{
		BYTE byErr = m_ActionMapManager.GetLastResult();

		// ���� ����
		if( byErr == SET_RESULT_OK )
			return;
	}
}

std::wstring CInputActionMap::GetKeyName( RwUInt32 nAction ) 
{
	return m_ActionMapManager.GetKeyName( (RwUInt16)nAction );
}

unsigned short CInputActionMap::FindKey( RwUInt32 nAction ) 
{
	return m_ActionMapManager.FindKey( (RwUInt16)nAction );
}

void CInputActionMap::InitDefaultActionMap() 
{
	m_ActionMapManager.InitDefaultActionMap();
}

/**
* \brief �׼Ǹ��� ����
*
* �ڷᱸ���� CActionMap���� ����� ���� üũ�ϰ� �װ��� ����Ͽ�
* ������ ��Ŷ�� �����Ѵ�.
*/
RwBool CInputActionMap::ApplyActionMap()
{
	if( m_bAcceptServer == FALSE )
		return FALSE;

	sSHORTCUT_UPDATE_DATA pData[NTL_SHORTCUT_MAX_COUNT];
	BYTE byCount = 0;
	if( m_ActionMapManager.GetUpdateData( pData , byCount ) )
	{
		// �ٲ� ���� �ִٸ� ��Ŷ�� ������ Result�ڵ尡 �������� ����Ǳ� ������ ������ ������ �� �� ����
		// ���� �����Ѵ�.
		API_GetSLPacketGenerator()->SendCharKeyUpdateReq( pData, byCount );

		m_bAcceptServer = FALSE;

		return TRUE;
	}

	return FALSE;
}

void CInputActionMap::CancleActionMap() 
{
	if( m_bAcceptServer )
		m_ActionMapManager.RestoreActionMap();
}

/**
* \brief ���õ� Ű�� ����Ѵ�.
* \param byKey		(RwUInt8) Ű�� VK_CODE
* \param nRefCount	(int) ���õ� Ƚ��, KeyUpHandler���� ī��Ʈ�� üũ�Ѵ�.
* \return ��������
*/
RwBool CInputActionMap::RegisterIgnoreKey( RwUInt8 byKey, int nRefCount ) 
{
	IGNOREMAP::iterator it = m_mapIgnore.find( byKey );
	// �̹� ������
	if( it != m_mapIgnore.end() )
	{
		return FALSE;
	}

	// �������� �ʴ´ٸ� �߰��Ѵ�.
	m_mapIgnore[byKey] = (RwUInt8)nRefCount;
	
	return TRUE;
}

RwBool CInputActionMap::RemoveIgnoreKey( RwUInt8 byKey ) 
{
	IGNOREMAP::iterator it = m_mapIgnore.find( byKey );

	// �������� ����
	if( it == m_mapIgnore.end() )
	{
		return FALSE;
	}

	// �����ϸ� ����
	m_mapIgnore.erase( it );

	return TRUE;
}

RwBool CInputActionMap::IsIgnoreKey( RwUInt8 byKey, RwBool bRef /*= FALSE */ ) 
{
	IGNOREMAP::iterator it = m_mapIgnore.find( byKey );

	// ���õǴ� Ű�� �ƴ�.
	if( it == m_mapIgnore.end() )
		return FALSE;
	
	// BYTE���� INVALID��� REF�� �������� �ʰ� ����
	if( it->second == 0xFF )
		return TRUE;

	// Ref Count ����
	if( bRef )
		(*it).second--;

	// 0 ���� �۰ų� ������ ����
	if( (*it).second <= 0 )
		m_mapIgnore.erase( it );

	// �����϶�� �˷���
	return TRUE;
}

void CInputActionMap::ClearIgnoreKey() 
{
	m_mapIgnore.clear();
}

RwUInt8 CInputActionMap::GetActionMapMode()
{
	return m_ActionMapManager.GetActionMapMode();
}

RwInt32 CInputActionMap::GetKeyDownCount(RwUInt32 uiFlags)
{
	RwInt32 iCount = 0;
	for(RwInt32 i = 0; i < 4; ++i)
	{
		if( (uiFlags >> i) & 0x01 )
			iCount++;
	}

	return iCount;
}

RwUInt32 CInputActionMap::ConvertServerFlags(RwUInt32 uiFlags)
{
	//The priority of the keyboard is determined.
	if (uiFlags == NTL_BIT_FRONT_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_F;
	}
	else if (uiFlags == NTL_BIT_TURN_LEFT_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_TURN_L;
	}
	else if(uiFlags == NTL_BIT_BACK_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_B;
	}
	else if(uiFlags == NTL_BIT_TURN_RIGHT_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_TURN_R;
	}
	else if (uiFlags == NTL_BIT_LEFT_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_L;
	}
	else if (uiFlags == NTL_BIT_RIGHT_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_R;
	}
	else if(uiFlags == NTL_BIT_LF_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_F_TURN_L;
	}
	else if(uiFlags == NTL_BIT_LB_MOVE )
	{
		m_uiServerMoveFlags = NTL_MOVE_B_TURN_L;
	}
	else if(uiFlags == NTL_BIT_RF_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_F_TURN_R;
	}
	else if(uiFlags == NTL_BIT_RB_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_B_TURN_R;
	}

	else if (uiFlags == NTL_BIT_FL_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_F_TURN_L;
	}
	else if (uiFlags == NTL_BIT_FR_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_F_TURN_R;
	}
	else if (uiFlags == NTL_BIT_BL_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_B_TURN_L;
	}
	else if (uiFlags == NTL_BIT_BR_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_B_TURN_R;
	}
	else if (uiFlags == NTL_BIT_LL_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_L_TURN_L;
	}
	else if (uiFlags == NTL_BIT_LR_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_L_TURN_R;
	}
	else if (uiFlags == NTL_BIT_RL_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_R_TURN_L;
	}
	else if (uiFlags == NTL_BIT_RR_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_R_TURN_R;
	}
	else if (uiFlags == NTL_BIT_DOWN_MOVE)
	{
		m_uiServerMoveFlags = NTL_MOVE_HEIGHT_DOWN;
	}

	else if(uiFlags == NTL_BIT_FB_MOVE)
	{
		ConvertServerFlags(m_uiKey1MoveValidFlags);
	}
	else
		m_uiServerMoveFlags = NTL_MOVE_NONE;

	return m_uiServerMoveFlags;
}

void CInputActionMap::HitTestDownDbClickDashMap(SInputDashMap& sDashMap)
{
	if(sDashMap.byDown % 2 != 0)
		return;

	if(sDashMap.byDown == 0)
		sDashMap.byDown++;
	else
	{
		if(sDashMap.fTime <= NTL_KEYBOARD_DBCLICK_TIME)
			sDashMap.byDown++;
		else
			sDashMap.byDown = 1;
	}

	sDashMap.fTime = 0.0f;
}


void CInputActionMap::HitTestUpDbClickDashMap(SInputDashMap& sDashMap)
{
	if(sDashMap.fTime <= NTL_KEYBOARD_DBCLICK_TIME)
		sDashMap.byDown++;
	else
		sDashMap.byDown = 0;

	if(sDashMap.byDown >= 4)
	{
		CallDashMove(sDashMap.uiMoveFlags);
		sDashMap.byDown = 0;
	}

	sDashMap.fTime = 0.0f;
}

void CInputActionMap::CallDashMove(RwUInt32 uiServerDashMoveFlags)
{
	// dash ������(0.1 �� �ȿ� �� �ٽ� ������). 
	if(!m_bActive || !m_pCallKeyboardDashMove)
		return;

	m_pCallKeyboardDashMove->Call(uiServerDashMoveFlags);
}

/**
* \ brief Handler according to move action
*
* When the key is pressed, the bit of the key is set to the current movement, and the
It converts to * flag.
*
* \ param iAction (unsigned int) Action ID
*/
void CInputActionMap::ActionDownMoveHandler( RwUInt32 uiAction ) 
{
	// old server move flags
	RwUInt32 uiOldServerMoveFlags = m_uiServerMoveFlags;

	// keyboard down count check
	RwInt32 iKeyDownCount = GetKeyDownCount(m_uiMoveFlags); 

	if(iKeyDownCount == 1)
	{
		m_uiKey1MoveValidFlags = m_uiMoveFlags;
	}

	else if(iKeyDownCount == 2)
	{
		m_uiKey2MoveValidFlags = m_uiMoveFlags;
	}

	// ACTION�� ���� �ൿ ����
	switch( uiAction )
	{
	case ACTION_AVATAR_FORWARD:
		m_uiMoveFlags |= NTL_BIT_FRONT_MOVE;
		break;
	case ACTION_AVATAR_BACKWARD:
		m_uiMoveFlags |= NTL_BIT_BACK_MOVE;
		break;
	case ACTION_AVATAR_LEFTTURN:
		m_uiMoveFlags |= NTL_BIT_TURN_LEFT_MOVE;
		break;
	case ACTION_AVATAR_RIGHTTURN:
		m_uiMoveFlags |= NTL_BIT_TURN_RIGHT_MOVE;
		break;
	case ACTION_AVATAR_LEFTSIDE:
		m_uiMoveFlags |= NTL_BIT_LEFT_MOVE;
		break;
	case ACTION_AVATAR_RIGHTSIDE:
		m_uiMoveFlags |= NTL_BIT_RIGHT_MOVE;
		break;

	default:
		break;
	}

	// server flag convert
	if(GetKeyDownCount(m_uiMoveFlags) > 2)
	{
		ConvertServerFlags(m_uiKey2MoveValidFlags);
	}
	else
	{
		ConvertServerFlags(m_uiMoveFlags);
	}

	// If there is a change in the flag that contains the flag to move to the server
	// Send the flag.
	if( m_uiServerMoveFlags != uiOldServerMoveFlags )
	{
		if(m_bActive && m_pCallKeyboardMove)
			m_pCallKeyboardMove->Call(m_uiServerMoveFlags);
	}
}

/**
* \brief �뽬 �̵��� üũ�Ѵ�.
*
* ���� �׼ǿ� �´� �뽬�� �ߵ��� Ȯ���Ͽ� ������ ������ �뽬�� �����Ѵ�.
* \param iAction (unsigned int)�׼�ID
*/
void CInputActionMap::ActionDownDashMoveHandler( RwUInt32 uiAction ) 
{
	switch( uiAction )
	{
	case ACTION_AVATAR_FORWARD:
		HitTestDownDbClickDashMap(m_sFrontDashMap);
		break;
	case ACTION_AVATAR_LEFTTURN:
	case ACTION_AVATAR_LEFTSIDE:
		HitTestDownDbClickDashMap(m_sLeftDashMap);
		break;
	case ACTION_AVATAR_BACKWARD:
		HitTestDownDbClickDashMap(m_sBackDashMap);
		break;
	case ACTION_AVATAR_RIGHTTURN:
	case ACTION_AVATAR_RIGHTSIDE:
		HitTestDownDbClickDashMap(m_sRightDashMap);
		break;
	default:
		break;
	}
}

void CInputActionMap::ActionDownBehaviorHandler( RwUInt32 uiAction ) 
{
	if( FALSE == m_bActive )
		return;

	switch( uiAction )
	{
	case ACTION_AVATAR_SITDOWN:		// sit/standup | fly down
	{
		if (m_pCallJump && IsDownAction(ACTION_AVATAR_SITDOWN) == FALSE)
		{
			SetFlagAction(ACTION_AVATAR_SITDOWN, TRUE);
			m_pCallSitAndStand->Call(TRUE);
		}
		break;
	}
	case ACTION_AVATAR_JUMP:		// jump
		{
			if( m_pCallJump && IsDownAction( ACTION_AVATAR_JUMP ) == FALSE )
			{
				SetFlagAction( ACTION_AVATAR_JUMP, TRUE );
				m_pCallJump->Call(m_uiServerMoveFlags);
			}
			break;
		}
	case ACTION_AVATAR_LOOTING:		// ����
		{
			if( m_pCallLooting )
				m_pCallLooting->Call();
			break;
		}
	case ACTION_AVATAR_CHARGE:		// �� ������
		{
			if( m_pCallCharging && IsDownAction( ACTION_AVATAR_CHARGE ) == FALSE  )
			{
				SetFlagAction( ACTION_AVATAR_CHARGE, TRUE );
				m_pCallCharging->Call( 1 );
			}
			break;
		}
	case ACTION_AVATAR_BLOCKING:
		{
			if( m_pCallBlocking && IsDownAction( ACTION_AVATAR_BLOCKING ) == FALSE )
			{
				SetFlagAction( ACTION_AVATAR_BLOCKING, TRUE );
				m_pCallBlocking->Call( 1 );
			}
			break;
		}
	}
}

/**
* \brief Ű�� ������ �� ó���Ǵ� GUI �׼ǵ�
*
* Ű�� ���� ���¿��� �߻��� �� �ִ� GUI�׼ǵ��� �˻��Ͽ� �����ϰ� 
*
* \param iAction (unsigned int)�׼�ID
*/
void CInputActionMap::ActionDownGuiHandler( RwUInt32 uiAction ) 
{
	if( FALSE == m_bActive )
		return;

	switch( uiAction )
	{
	case ACTION_TARGET_SELF:		// �ڱ� �ڽ� ����
		{
			if( m_pCallAvatarSelect )
				m_pCallAvatarSelect->Call();
			break;
		}

	case ACTION_QUICK_1:			// ������
		{
			if( m_pCallSkillQuickSlotDown && IsDownAction( ACTION_QUICK_1 ) == FALSE )
			{
				SetFlagAction( ACTION_QUICK_1, TRUE );
				m_pCallSkillQuickSlotDown->Call( 0 );
			}
			break;
		}
	case ACTION_QUICK_2:
		{
			if( m_pCallSkillQuickSlotDown && IsDownAction( ACTION_QUICK_2 ) == FALSE )
			{
				SetFlagAction( ACTION_QUICK_2, TRUE );
				m_pCallSkillQuickSlotDown->Call( 1 );
			}
			break;
		}
	case ACTION_QUICK_3:
		{
			if( m_pCallSkillQuickSlotDown && IsDownAction( ACTION_QUICK_3 ) == FALSE )
			{
				SetFlagAction( ACTION_QUICK_3, TRUE );
				m_pCallSkillQuickSlotDown->Call( 2 );
			}
			break;
		}
	case ACTION_QUICK_4:
		{
			if( m_pCallSkillQuickSlotDown && IsDownAction( ACTION_QUICK_4 ) == FALSE )
			{
				SetFlagAction( ACTION_QUICK_4, TRUE );
				m_pCallSkillQuickSlotDown->Call( 3 );
			}
			break;
		}
	case ACTION_QUICK_5:
		{
			if( m_pCallSkillQuickSlotDown && IsDownAction( ACTION_QUICK_5 ) == FALSE )
			{
				SetFlagAction( ACTION_QUICK_5, TRUE );
				m_pCallSkillQuickSlotDown->Call( 4 );
			}
			break;
		}
	case ACTION_QUICK_6:
		{
			if( m_pCallSkillQuickSlotDown && IsDownAction( ACTION_QUICK_6 ) == FALSE )
			{
				SetFlagAction( ACTION_QUICK_6, TRUE );
				m_pCallSkillQuickSlotDown->Call( 5 );
			}
			break;
		}
	case ACTION_QUICK_7:
		{
			if( m_pCallSkillQuickSlotDown && IsDownAction( ACTION_QUICK_7 ) == FALSE )
			{
				SetFlagAction( ACTION_QUICK_7, TRUE );
				m_pCallSkillQuickSlotDown->Call( 6 );
			}
			break;
		}
	case ACTION_QUICK_8:
		{
			if( m_pCallSkillQuickSlotDown && IsDownAction( ACTION_QUICK_8 ) == FALSE )
			{
				SetFlagAction( ACTION_QUICK_8, TRUE );
				m_pCallSkillQuickSlotDown->Call( 7 );
			}
			break;
		}
	case ACTION_QUICK_9:
		{
			if( m_pCallSkillQuickSlotDown && IsDownAction( ACTION_QUICK_9 ) == FALSE )
			{
				SetFlagAction( ACTION_QUICK_9, TRUE );
				m_pCallSkillQuickSlotDown->Call( 8 );
			}
			break;
		}
	case ACTION_QUICK_0:
		{
			if( m_pCallSkillQuickSlotDown && IsDownAction( ACTION_QUICK_0 ) == FALSE )
			{
				SetFlagAction( ACTION_QUICK_0, TRUE );
				m_pCallSkillQuickSlotDown->Call( 9 );
			}
			break;
		}
	case ACTION_QUICK_MIN:
		{
			if( m_pCallSkillQuickSlotDown && IsDownAction( ACTION_QUICK_MIN ) == FALSE )
			{
				SetFlagAction( ACTION_QUICK_MIN, TRUE );
				m_pCallSkillQuickSlotDown->Call( 10 );
			}
			break;
		}
	case ACTION_QUICK_PLUS:
		{
			if( m_pCallSkillQuickSlotDown && IsDownAction( ACTION_QUICK_MIN ) == FALSE )
			{
				SetFlagAction( ACTION_QUICK_PLUS, TRUE );
				m_pCallSkillQuickSlotDown->Call( 11 );
			}
			break;
		}

		// Ȯ�� 1��
	case ACTION_QUICK_1_EX:
		{
			if( m_pCallSkillQuickSlotExDown )
			{
				SetFlagAction( ACTION_QUICK_1_EX, FALSE );
				m_pCallSkillQuickSlotExDown->Call( 0 );
			}
			break;
		}
	case ACTION_QUICK_2_EX:
		{
			if( m_pCallSkillQuickSlotExDown )
			{
				SetFlagAction( ACTION_QUICK_2_EX, FALSE );
				m_pCallSkillQuickSlotExDown->Call( 1 );
			}
			break;
		}
	case ACTION_QUICK_3_EX:
		{
			if( m_pCallSkillQuickSlotExDown )
			{
				SetFlagAction( ACTION_QUICK_3_EX, FALSE );
				m_pCallSkillQuickSlotExDown->Call( 2 );
			}
			break;
		}
	case ACTION_QUICK_4_EX:
		{
			if( m_pCallSkillQuickSlotExDown )
			{
				SetFlagAction( ACTION_QUICK_4_EX, FALSE );
				m_pCallSkillQuickSlotExDown->Call( 3 );
			}
			break;
		}
	case ACTION_QUICK_5_EX:
		{
			if( m_pCallSkillQuickSlotExDown )
			{
				SetFlagAction( ACTION_QUICK_5_EX, FALSE );
				m_pCallSkillQuickSlotExDown->Call( 4 );
			}
			break;
		}
	case ACTION_QUICK_6_EX:
		{
			if( m_pCallSkillQuickSlotExDown )
			{
				SetFlagAction( ACTION_QUICK_6_EX, FALSE );
				m_pCallSkillQuickSlotExDown->Call( 5 );
			}
			break;
		}
	case ACTION_QUICK_7_EX:
		{
			if( m_pCallSkillQuickSlotExDown )
			{
				SetFlagAction( ACTION_QUICK_7_EX, FALSE );
				m_pCallSkillQuickSlotExDown->Call( 6 );
			}
			break;
		}
	case ACTION_QUICK_8_EX:
		{
			if( m_pCallSkillQuickSlotExDown )
			{
				SetFlagAction( ACTION_QUICK_8_EX, FALSE );
				m_pCallSkillQuickSlotExDown->Call( 7 );
			}
			break;
		}
	case ACTION_QUICK_9_EX:
		{
			if( m_pCallSkillQuickSlotExDown )
			{
				SetFlagAction( ACTION_QUICK_9_EX, FALSE );
				m_pCallSkillQuickSlotExDown->Call( 8 );
			}
			break;
		}
	case ACTION_QUICK_0_EX:
		{
			if( m_pCallSkillQuickSlotExDown )
			{
				SetFlagAction( ACTION_QUICK_0_EX, FALSE );
				m_pCallSkillQuickSlotExDown->Call( 9 );
			}
			break;
		}
	case ACTION_QUICK_MIN_EX:
		{
			if( m_pCallSkillQuickSlotExDown )
			{
				SetFlagAction( ACTION_QUICK_MIN_EX, FALSE );
				m_pCallSkillQuickSlotExDown->Call( 10 );
			}
			break;
		}
	case ACTION_QUICK_PLUS_EX:
		{
			if( m_pCallSkillQuickSlotExDown )
			{
				SetFlagAction( ACTION_QUICK_PLUS_EX, FALSE );
				m_pCallSkillQuickSlotExDown->Call ( 11 );
			}
			break;
		}

		// Ȯ�� 2��
	case ACTION_QUICK_1_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Down )
			{
				SetFlagAction( ACTION_QUICK_1_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Down->Call( 0 );
			}
			break;
		}
	case ACTION_QUICK_2_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Down )
			{
				SetFlagAction( ACTION_QUICK_2_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Down->Call( 1 );
			}
			break;
		}
	case ACTION_QUICK_3_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Down )
			{
				SetFlagAction( ACTION_QUICK_3_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Down->Call( 2 );
			}
			break;
		}
	case ACTION_QUICK_4_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Down )
			{
				SetFlagAction( ACTION_QUICK_4_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Down->Call( 3 );
			}
			break;
		}
	case ACTION_QUICK_5_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Down )
			{
				SetFlagAction( ACTION_QUICK_5_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Down->Call( 4 );
			}
			break;
		}
	case ACTION_QUICK_6_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Down )
			{
				SetFlagAction( ACTION_QUICK_6_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Down->Call( 5 );
			}
			break;
		}
	case ACTION_QUICK_7_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Down )
			{
				SetFlagAction( ACTION_QUICK_7_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Down->Call( 6 );
			}
			break;
		}
	case ACTION_QUICK_8_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Down )
			{
				SetFlagAction( ACTION_QUICK_8_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Down->Call( 7 );
			}
			break;
		}
	case ACTION_QUICK_9_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Down )
			{
				SetFlagAction( ACTION_QUICK_9_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Down->Call( 8 );
			}
			break;
		}
	case ACTION_QUICK_0_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Down )
			{
				SetFlagAction( ACTION_QUICK_0_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Down->Call( 9 );
			}
			break;
		}
	case ACTION_QUICK_MIN_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Down )
			{
				SetFlagAction( ACTION_QUICK_MIN_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Down->Call( 10 );
			}
			break;
		}
	case ACTION_QUICK_PLUS_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Down )
			{
				SetFlagAction( ACTION_QUICK_PLUS_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Down->Call ( 11 );
			}
			break;
		}

	case ACTION_TARGET_1STPARTY:		// ù��° ��Ƽ�� ����
		{
			if( m_pCallPartySelect )
				m_pCallPartySelect->Call( 0 );

			break;
		}
	case ACTION_TARGET_2NDPARTY:		//  �ι�° ��Ƽ�� ����
		{
			if( m_pCallPartySelect )
				m_pCallPartySelect->Call( 1 );

			break;
		}
	case ACTION_TARGET_3RDPARTY:		// ����°
		{
			if( m_pCallPartySelect )
				m_pCallPartySelect->Call( 2 );

			break;
		}
	case ACTION_TARGET_4THPARTY:		// �׹�°
		{
			if( m_pCallPartySelect )
				m_pCallPartySelect->Call( 3 );

			break;
		}
	case ACTION_TARGET_AUTOTARGET_PARTY:
		{
			if( m_pCallPartyAutoSelect )
				m_pCallPartyAutoSelect->Call();

			break;
		}
	default:
		break;
	}
}

/**
* \brief Ű���� ���� �̵��׼� �ڵ鷯
*
* Ű ���� ���� �߻��ϴ� �̵� �׼��� ó���Ѵ�.
*
* \param iAction (unsigned int)�׼�ID
*/
void CInputActionMap::ActionUpMoveHandler( RwUInt32 uiAction ) 
{
	switch( uiAction )
	{
		case ACTION_AVATAR_FORWARD:	// ����
		{
			m_uiMoveFlags &= (~NTL_BIT_FRONT_MOVE);

			if (GetKeyDownCount(m_uiMoveFlags) > 2)
			{
				ConvertServerFlags(m_uiKey2MoveValidFlags);
			}
			else
			{
				ConvertServerFlags(m_uiMoveFlags);
			}

			if(m_bActive && m_pCallKeyboardMove)
				m_pCallKeyboardMove->Call(m_uiServerMoveFlags);

			break;
		}
		case ACTION_AVATAR_LEFTTURN: // ��ȸ��
		{
			m_uiMoveFlags &= (~NTL_BIT_TURN_LEFT_MOVE);

			if(GetKeyDownCount(m_uiMoveFlags) > 2)
				ConvertServerFlags(m_uiKey2MoveValidFlags);
			else
				ConvertServerFlags(m_uiMoveFlags);

			if(m_bActive && m_pCallKeyboardMove)
				m_pCallKeyboardMove->Call(m_uiServerMoveFlags);

			break;
		}
		case ACTION_AVATAR_BACKWARD: // ����
		{
			m_uiMoveFlags &= (~NTL_BIT_BACK_MOVE);

			if(GetKeyDownCount(m_uiMoveFlags) > 2)
				ConvertServerFlags(m_uiKey2MoveValidFlags);
			else
				ConvertServerFlags(m_uiMoveFlags);

			if(m_bActive && m_pCallKeyboardMove)
				m_pCallKeyboardMove->Call(m_uiServerMoveFlags);
		}
		break;
		case ACTION_AVATAR_RIGHTTURN: // ��ȸ��
		{
			m_uiMoveFlags &= (~NTL_BIT_TURN_RIGHT_MOVE);

			if(GetKeyDownCount(m_uiMoveFlags) > 2)
				ConvertServerFlags(m_uiKey2MoveValidFlags);
			else
				ConvertServerFlags(m_uiMoveFlags);

			if(m_bActive && m_pCallKeyboardMove)
				m_pCallKeyboardMove->Call(m_uiServerMoveFlags);
		}
		break;
		case ACTION_AVATAR_LEFTSIDE:
		{
			m_uiMoveFlags &= (~NTL_BIT_LEFT_MOVE);

			if (GetKeyDownCount(m_uiMoveFlags) > 2)
				ConvertServerFlags(m_uiKey2MoveValidFlags);
			else
				ConvertServerFlags(m_uiMoveFlags);

			if (m_bActive && m_pCallKeyboardMove)
				m_pCallKeyboardMove->Call(m_uiServerMoveFlags);
		}
		break;
		case ACTION_AVATAR_RIGHTSIDE:
		{
			m_uiMoveFlags &= (~NTL_BIT_RIGHT_MOVE);

			if (GetKeyDownCount(m_uiMoveFlags) > 2)
				ConvertServerFlags(m_uiKey2MoveValidFlags);
			else
				ConvertServerFlags(m_uiMoveFlags);

			if (m_bActive && m_pCallKeyboardMove)
				m_pCallKeyboardMove->Call(m_uiServerMoveFlags);
		}
		break;

	default:
		break;
	}
}

/**
* \brief Ű���� ���� �̵� �׼��� �뽬 �ڵ鷯
*
* Ű���� ���� �̵� �׼ǿ� �뽬�� ó���ؾ� �ϴ� �κ����� Ȯ���ϰ� �����Ѵ�.
*
* \param iAction (unsigned int)�׼�ID
*/
void CInputActionMap::ActionUpDashMoveHandler( RwUInt32 uiAction ) 
{
	switch( uiAction )
	{
	case ACTION_AVATAR_FORWARD:
		HitTestUpDbClickDashMap(m_sFrontDashMap);
		break;
	case ACTION_AVATAR_LEFTTURN:
	case ACTION_AVATAR_LEFTSIDE:
		HitTestUpDbClickDashMap(m_sLeftDashMap);
		break;
	case ACTION_AVATAR_BACKWARD:
		HitTestUpDbClickDashMap(m_sBackDashMap);
		break;
	case ACTION_AVATAR_RIGHTTURN:
	case ACTION_AVATAR_RIGHTSIDE:
		HitTestUpDbClickDashMap(m_sRightDashMap);
		break;
	default:
		break;
	}
}

void CInputActionMap::ActionUpBehaviorHandler( RwUInt32 uiAction ) 
{
	if( FALSE == m_bActive )
		return;

	switch( uiAction )
	{
	case ACTION_AVATAR_SITDOWN:
		{
			if (m_pCallSitAndStand)
			{
				SetFlagAction(ACTION_AVATAR_SITDOWN, FALSE);
				m_pCallSitAndStand->Call(FALSE);
			}
		}
		break;
	case ACTION_AVATAR_AUTORUN:
		{
			if( m_pCallAutoRun )
				m_pCallAutoRun->Call();

			break;
		}
	case ACTION_TARGET_AUTO:			// ����� �� ����
		{
			if( m_pCallAutoTarget )
				m_pCallAutoTarget->Call();
			break;
		}
	case ACTION_TARGET_AUTOATK:			// �ڵ� ����
		{
			if( m_pCallAutoAttack )
				m_pCallAutoAttack->Call();
			break;
		}
	case ACTION_TARGET_AUTOFOLLOW:
		{
			if( m_pCallAutoFollow )
				m_pCallAutoFollow->Call();
			break;
		}
	case ACTION_AVATAR_CHARGE:
		{
			if( m_pCallCharging )
			{
				SetFlagAction( ACTION_AVATAR_CHARGE, FALSE );
				m_pCallCharging->Call(0);
			}
			break;
		}
	case ACTION_AVATAR_JUMP:		// ���� Flag ȸ��
		{
			if( m_pCallJump )
			{
				SetFlagAction( ACTION_AVATAR_JUMP, FALSE );
				m_pCallJump->Call(NTL_MOVE_UNKNOWN);
			}
			
		}
		break;
	case ACTION_AVATAR_BLOCKING:
		{
			if( m_pCallBlocking )
			{
				SetFlagAction( ACTION_AVATAR_BLOCKING, FALSE );
				m_pCallBlocking->Call(0);
			}
			break;
		}
	case ACTION_AVATAR_SCOUTER:
		{
			if(m_pCallScouterUse)
				m_pCallScouterUse->Call();
			break;
		}
	case ACTION_TARGET_MARKING_1:
		{
			if(m_pCallTargetMarking)
			{
				m_pCallTargetMarking->Call(0);
			}
			break;
		}
	case ACTION_TARGET_MARKING_2:
		{
			if(m_pCallTargetMarking)
			{
				m_pCallTargetMarking->Call(1);
			}
			break;
		}
	case ACTION_TARGET_MARKING_3:
		{
			if(m_pCallTargetMarking)
			{
				m_pCallTargetMarking->Call(2);
			}
			break;
		}
	case ACTION_TARGET_MARKING_4:
		{
			if(m_pCallTargetMarking)
			{
				m_pCallTargetMarking->Call(3);
			}
			break;
		}
	case ACTION_TARGET_MARKING_5:
		{
			if(m_pCallTargetMarking)
			{
				m_pCallTargetMarking->Call(4);
			}
			break;
		}
	case ACTION_TARGET_SELECTING_1:
		{
			if(m_pCallTargetSelecting)
			{
				m_pCallTargetSelecting->Call(0);
			}
			break;
		}
	case ACTION_TARGET_SELECTING_2:
		{
			if(m_pCallTargetSelecting)
			{
				m_pCallTargetSelecting->Call(1);
			}
			break;
		}
	case ACTION_TARGET_SELECTING_3:
		{
			if(m_pCallTargetSelecting)
			{
				m_pCallTargetSelecting->Call(2);
			}
			break;
		}
	case ACTION_TARGET_SELECTING_4:
		{
			if(m_pCallTargetSelecting)
			{
				m_pCallTargetSelecting->Call(3);
			}
			break;
		}
	case ACTION_TARGET_SELECTING_5:
		{
			if(m_pCallTargetSelecting)
			{
				m_pCallTargetSelecting->Call(4);
			}
			break;
		}
	default:
		break;
	}
}

/**
* \brief Ű���� ���� GUI �׼��� �ڵ鷯
*
* \param iAction (unsigned int)�׼�ID
*/
void CInputActionMap::ActionUpGuiHandler( RwUInt32 uiAction ) 
{
	if( FALSE == m_bActive )
		return;

	switch( uiAction )
	{
	case ACTION_GLOBAL_CANCLE:
		{
			if( m_pCallExit )
				m_pCallExit->Call();
			break;
		}
	case ACTION_QUICK_1:
		{
			if( m_pCallSkillQuickSlotUp )
			{
				SetFlagAction( ACTION_QUICK_1, FALSE );
				m_pCallSkillQuickSlotUp->Call( 0 );
			}
			break;
		}
	case ACTION_QUICK_2:
		{
			if( m_pCallSkillQuickSlotUp )
			{
				SetFlagAction( ACTION_QUICK_2, FALSE );
				m_pCallSkillQuickSlotUp->Call( 1 );
			}
			break;
		}
	case ACTION_QUICK_3:
		{
			if( m_pCallSkillQuickSlotUp )
			{
				SetFlagAction( ACTION_QUICK_3, FALSE );
				m_pCallSkillQuickSlotUp->Call( 2 );
			}
			break;
		}
	case ACTION_QUICK_4:
		{
			if( m_pCallSkillQuickSlotUp )
			{
				SetFlagAction( ACTION_QUICK_4, FALSE );
				m_pCallSkillQuickSlotUp->Call( 3 );
			}
			break;
		}
	case ACTION_QUICK_5:
		{
			if( m_pCallSkillQuickSlotUp )
			{
				SetFlagAction( ACTION_QUICK_5, FALSE );
				m_pCallSkillQuickSlotUp->Call( 4 );
			}
			break;
		}
	case ACTION_QUICK_6:
		{
			if( m_pCallSkillQuickSlotUp )
			{
				SetFlagAction( ACTION_QUICK_6, FALSE );
				m_pCallSkillQuickSlotUp->Call( 5 );
			}
			break;
		}
	case ACTION_QUICK_7:
		{
			if( m_pCallSkillQuickSlotUp )
			{
				SetFlagAction( ACTION_QUICK_7, FALSE );
				m_pCallSkillQuickSlotUp->Call( 6 );
			}
			break;
		}
	case ACTION_QUICK_8:
		{
			if( m_pCallSkillQuickSlotUp )
			{
				SetFlagAction( ACTION_QUICK_8, FALSE );
				m_pCallSkillQuickSlotUp->Call( 7 );
			}
			break;
		}
	case ACTION_QUICK_9:
		{
			if( m_pCallSkillQuickSlotUp )
			{
				SetFlagAction( ACTION_QUICK_9, FALSE );
				m_pCallSkillQuickSlotUp->Call( 8 );
			}
			break;
		}
	case ACTION_QUICK_0:
		{
			if( m_pCallSkillQuickSlotUp )
			{
				SetFlagAction( ACTION_QUICK_0, FALSE );
				m_pCallSkillQuickSlotUp->Call( 9 );
			}
			break;
		}
	case ACTION_QUICK_MIN:
		{
			if( m_pCallSkillQuickSlotUp )
			{
				SetFlagAction( ACTION_QUICK_MIN, FALSE );
				m_pCallSkillQuickSlotUp->Call( 10 );
			}
			break;
		}
	case ACTION_QUICK_PLUS:
		{
			if( m_pCallSkillQuickSlotUp )
			{
				SetFlagAction( ACTION_QUICK_PLUS, FALSE );
				m_pCallSkillQuickSlotUp->Call ( 11 );
			}
			break;
		}

		// Ȯ�� 1��
	case ACTION_QUICK_1_EX:
		{
			if( m_pCallSkillQuickSlotExUp )
			{
				SetFlagAction( ACTION_QUICK_1_EX, FALSE );
				m_pCallSkillQuickSlotExUp->Call( 0 );
			}
			break;
		}
	case ACTION_QUICK_2_EX:
		{
			if( m_pCallSkillQuickSlotExUp )
			{
				SetFlagAction( ACTION_QUICK_2_EX, FALSE );
				m_pCallSkillQuickSlotExUp->Call( 1 );
			}
			break;
		}
	case ACTION_QUICK_3_EX:
		{
			if( m_pCallSkillQuickSlotExUp )
			{
				SetFlagAction( ACTION_QUICK_3_EX, FALSE );
				m_pCallSkillQuickSlotExUp->Call( 2 );
			}
			break;
		}
	case ACTION_QUICK_4_EX:
		{
			if( m_pCallSkillQuickSlotExUp )
			{
				SetFlagAction( ACTION_QUICK_4_EX, FALSE );
				m_pCallSkillQuickSlotExUp->Call( 3 );
			}
			break;
		}
	case ACTION_QUICK_5_EX:
		{
			if( m_pCallSkillQuickSlotExUp )
			{
				SetFlagAction( ACTION_QUICK_5_EX, FALSE );
				m_pCallSkillQuickSlotExUp->Call( 4 );
			}
			break;
		}
	case ACTION_QUICK_6_EX:
		{
			if( m_pCallSkillQuickSlotExUp )
			{
				SetFlagAction( ACTION_QUICK_6_EX, FALSE );
				m_pCallSkillQuickSlotExUp->Call( 5 );
			}
			break;
		}
	case ACTION_QUICK_7_EX:
		{
			if( m_pCallSkillQuickSlotExUp )
			{
				SetFlagAction( ACTION_QUICK_7_EX, FALSE );
				m_pCallSkillQuickSlotExUp->Call( 6 );
			}
			break;
		}
	case ACTION_QUICK_8_EX:
		{
			if( m_pCallSkillQuickSlotExUp )
			{
				SetFlagAction( ACTION_QUICK_8_EX, FALSE );
				m_pCallSkillQuickSlotExUp->Call( 7 );
			}
			break;
		}
	case ACTION_QUICK_9_EX:
		{
			if( m_pCallSkillQuickSlotExUp )
			{
				SetFlagAction( ACTION_QUICK_9_EX, FALSE );
				m_pCallSkillQuickSlotExUp->Call( 8 );
			}
			break;
		}
	case ACTION_QUICK_0_EX:
		{
			if( m_pCallSkillQuickSlotExUp )
			{
				SetFlagAction( ACTION_QUICK_0_EX, FALSE );
				m_pCallSkillQuickSlotExUp->Call( 9 );
			}
			break;
		}
	case ACTION_QUICK_MIN_EX:
		{
			if( m_pCallSkillQuickSlotExUp )
			{
				SetFlagAction( ACTION_QUICK_MIN_EX, FALSE );
				m_pCallSkillQuickSlotExUp->Call( 10 );
			}
			break;
		}
	case ACTION_QUICK_PLUS_EX:
		{
			if( m_pCallSkillQuickSlotExUp )
			{
				SetFlagAction( ACTION_QUICK_PLUS_EX, FALSE );
				m_pCallSkillQuickSlotExUp->Call ( 11 );
			}
			break;
		}

	// Ȯ�� 2��
	case ACTION_QUICK_1_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Up )
			{
				SetFlagAction( ACTION_QUICK_1_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Up->Call( 0 );
			}
			break;
		}
	case ACTION_QUICK_2_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Up )
			{
				SetFlagAction( ACTION_QUICK_2_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Up->Call( 1 );
			}
			break;
		}
	case ACTION_QUICK_3_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Up )
			{
				SetFlagAction( ACTION_QUICK_3_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Up->Call( 2 );
			}
			break;
		}
	case ACTION_QUICK_4_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Up )
			{
				SetFlagAction( ACTION_QUICK_4_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Up->Call( 3 );
			}
			break;
		}
	case ACTION_QUICK_5_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Up )
			{
				SetFlagAction( ACTION_QUICK_5_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Up->Call( 4 );
			}
			break;
		}
	case ACTION_QUICK_6_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Up )
			{
				SetFlagAction( ACTION_QUICK_6_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Up->Call( 5 );
			}
			break;
		}
	case ACTION_QUICK_7_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Up )
			{
				SetFlagAction( ACTION_QUICK_7_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Up->Call( 6 );
			}
			break;
		}
	case ACTION_QUICK_8_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Up )
			{
				SetFlagAction( ACTION_QUICK_8_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Up->Call( 7 );
			}
			break;
		}
	case ACTION_QUICK_9_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Up )
			{
				SetFlagAction( ACTION_QUICK_9_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Up->Call( 8 );
			}
			break;
		}
	case ACTION_QUICK_0_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Up )
			{
				SetFlagAction( ACTION_QUICK_0_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Up->Call( 9 );
			}
			break;
		}
	case ACTION_QUICK_MIN_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Up )
			{
				SetFlagAction( ACTION_QUICK_MIN_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Up->Call( 10 );
			}
			break;
		}
	case ACTION_QUICK_PLUS_EX2:
		{
			if( m_pCallSkillQuickSlotEx2Up )
			{
				SetFlagAction( ACTION_QUICK_PLUS_EX2, FALSE );
				m_pCallSkillQuickSlotEx2Up->Call ( 11 );
			}
			break;
		}

	case ACTION_QUICK_PREV:
		{
			if( m_pCallSkillQuickSlotChange )
			{
				m_pCallSkillQuickSlotChange->Call( 0 );
			}
			break;
		}
	case ACTION_QUICK_NEXT:
		{
			if( m_pCallSkillQuickSlotChange )
			{
				m_pCallSkillQuickSlotChange->Call( 1 );
			}
			break;
		}
	case ACTION_CHAT_PGUP:
		{
			if( m_pCallChatPageChange )
				m_pCallChatPageChange->Call( 0 );
		}
		break;
	case ACTION_CHAT_PGDN:
		{
			if( m_pCallChatPageChange )
				m_pCallChatPageChange->Call( 1 );
		}
		break;
	case ACTION_GLOBAL_SNAPSHOT:		// ��ũ�� ĸ�� ���
		{
			GetNtlGameCameraManager()->SetCaptureScreenShot();
			break;
		}
	default:
		break;
	}

	// ���̾�α� �׼� ó��
	if( m_pCallDialogAction )
		m_pCallDialogAction->Call( uiAction );
}

/**
* \brief Register actions that require state recovery.
*/
void CInputActionMap::RegisterFlagMap() 
{
	m_mapFlag[ACTION_AVATAR_CHARGE] = FALSE;		// �� ������
	m_mapFlag[ACTION_AVATAR_BLOCKING] = FALSE;		// ���ŷ
	m_mapFlag[ACTION_AVATAR_SITDOWN] = FALSE;		// sit/stand up & fly down
	m_mapFlag[ACTION_AVATAR_JUMP] = FALSE;			// ����
	m_mapFlag[ACTION_QUICK_1] = FALSE;				// ������ ����Ű��
	m_mapFlag[ACTION_QUICK_2] = FALSE;
	m_mapFlag[ACTION_QUICK_3] = FALSE;
	m_mapFlag[ACTION_QUICK_4] = FALSE;
	m_mapFlag[ACTION_QUICK_5] = FALSE;
	m_mapFlag[ACTION_QUICK_6] = FALSE;
	m_mapFlag[ACTION_QUICK_7] = FALSE;
	m_mapFlag[ACTION_QUICK_8] = FALSE;
	m_mapFlag[ACTION_QUICK_9] = FALSE;
	m_mapFlag[ACTION_QUICK_0] = FALSE;
	m_mapFlag[ACTION_QUICK_MIN] = FALSE;
	m_mapFlag[ACTION_QUICK_PLUS] = FALSE;
	m_mapFlag[ACTION_QUICK_1_EX] = FALSE;
	m_mapFlag[ACTION_QUICK_2_EX] = FALSE;
	m_mapFlag[ACTION_QUICK_3_EX] = FALSE;
	m_mapFlag[ACTION_QUICK_4_EX] = FALSE;
	m_mapFlag[ACTION_QUICK_5_EX] = FALSE;
	m_mapFlag[ACTION_QUICK_6_EX] = FALSE;
	m_mapFlag[ACTION_QUICK_7_EX] = FALSE;
	m_mapFlag[ACTION_QUICK_8_EX] = FALSE;
	m_mapFlag[ACTION_QUICK_9_EX] = FALSE;
	m_mapFlag[ACTION_QUICK_0_EX] = FALSE;
	m_mapFlag[ACTION_QUICK_MIN_EX] = FALSE;
	m_mapFlag[ACTION_QUICK_PLUS_EX] = FALSE;
	m_mapFlag[ACTION_QUICK_1_EX2] = FALSE;
	m_mapFlag[ACTION_QUICK_2_EX2] = FALSE;
	m_mapFlag[ACTION_QUICK_3_EX2] = FALSE;
	m_mapFlag[ACTION_QUICK_4_EX2] = FALSE;
	m_mapFlag[ACTION_QUICK_5_EX2] = FALSE;
	m_mapFlag[ACTION_QUICK_6_EX2] = FALSE;
	m_mapFlag[ACTION_QUICK_7_EX2] = FALSE;
	m_mapFlag[ACTION_QUICK_8_EX2] = FALSE;
	m_mapFlag[ACTION_QUICK_9_EX2] = FALSE;
	m_mapFlag[ACTION_QUICK_0_EX2] = FALSE;
	m_mapFlag[ACTION_QUICK_MIN_EX2] = FALSE;
	m_mapFlag[ACTION_QUICK_PLUS_EX2] = FALSE;
}

/**
* \brief ���� �׼��� ���¸� ������ �´�.
* \param iAction	�׼�
* \return �׼��� ���� ( ������ FALSE )
*/
RwBool CInputActionMap::IsDownAction( RwUInt32 uiAction ) 
{
	FLAGMAP::iterator it = m_mapFlag.find( uiAction );
	if( it == m_mapFlag.end() )
	{
		return FALSE;
	}

	return (*it).second;
}

/**
* \brief �׼��� �÷��׸� �����Ѵ�.
* \param iAction	�׼��� NUMBER
* \param bDown		�ٿ��� ����
* \return ��������
*/
RwBool CInputActionMap::SetFlagAction( RwUInt32 uiAction, RwBool bDown ) 
{
	FLAGMAP::iterator it = m_mapFlag.find( uiAction );
	if ( it == m_mapFlag.end() )
	{
		return FALSE;
	}

	(*it).second = bDown;
	return TRUE;
}

void CInputActionMap::UnLinkKeyboardMove(void)
{
	if(m_pCallKeyboardMove)
		NTL_DELETE(m_pCallKeyboardMove);
}

void CInputActionMap::UnLinkKeyboardDashMove(void)
{
	if(m_pCallKeyboardDashMove)
		NTL_DELETE(m_pCallKeyboardDashMove);
}

void CInputActionMap::UnLinkAvatarSelect(void)
{
	if(m_pCallAvatarSelect)
		NTL_DELETE(m_pCallAvatarSelect);
}

void CInputActionMap::UnLinkJump(void)
{
	if(m_pCallJump)
		NTL_DELETE(m_pCallJump);
}

void CInputActionMap::UnLinkCharging(void)
{
	if(m_pCallCharging)
		NTL_DELETE(m_pCallCharging);
}

void CInputActionMap::UnLinkBlocking(void)
{
	if(m_pCallBlocking)
		NTL_DELETE(m_pCallBlocking);
}

void CInputActionMap::UnLinkSitAndStand(void)
{
	if(m_pCallSitAndStand)
		NTL_DELETE(m_pCallSitAndStand);
}

void CInputActionMap::UnLinkAutoRun(void)
{
	if(m_pCallAutoRun)
		NTL_DELETE(m_pCallAutoRun);
}

void CInputActionMap::UnLinkSkillQuickSlotDown(void)
{
	if(m_pCallSkillQuickSlotDown)
		NTL_DELETE(m_pCallSkillQuickSlotDown);
}

void CInputActionMap::UnLinkSkillQuickSlotUp(void)
{
	if(m_pCallSkillQuickSlotUp)
		NTL_DELETE(m_pCallSkillQuickSlotUp);
}

void CInputActionMap::UnLinkSkillQuickSlotExDown(void)
{
	if(m_pCallSkillQuickSlotExDown)
		NTL_DELETE(m_pCallSkillQuickSlotExDown);
}

void CInputActionMap::UnLinkSkillQuickSlotExUp(void)
{
	if(m_pCallSkillQuickSlotExUp)
		NTL_DELETE(m_pCallSkillQuickSlotExUp);
}

void CInputActionMap::UnLinkSkillQuickSlotEx2Down(void)
{
	if(m_pCallSkillQuickSlotEx2Down)
		NTL_DELETE(m_pCallSkillQuickSlotEx2Down);
}

void CInputActionMap::UnLinkSkillQuickSlotEx2Up(void)
{
	if(m_pCallSkillQuickSlotEx2Up)
		NTL_DELETE(m_pCallSkillQuickSlotEx2Up);
}

void CInputActionMap::UnLinkSkillQuickSlotChange(void)
{
	if(m_pCallSkillQuickSlotChange)
		NTL_DELETE(m_pCallSkillQuickSlotChange);
}

void CInputActionMap::UnLinkGameExit(void)
{
	if(m_pCallExit)
		NTL_DELETE(m_pCallExit);
}

void CInputActionMap::UnLinkLooting(void)
{
	if(m_pCallLooting)
		NTL_DELETE(m_pCallLooting);
}

void CInputActionMap::UnLinkDialogHotKey()
{
	if(m_pCallDialogAction)
		NTL_DELETE(m_pCallDialogAction);
}

void CInputActionMap::UnLinkTabKey(void)
{
	if(m_pCallTabKey)
		NTL_DELETE(m_pCallTabKey);
}

void CInputActionMap::UnLinkAutoTarget(void)
{
	if(m_pCallAutoTarget)
		NTL_DELETE(m_pCallAutoTarget);
}

void CInputActionMap::UnLinkAutoAttack(void)
{
	if(m_pCallAutoAttack)
		NTL_DELETE(m_pCallAutoAttack);
}

void CInputActionMap::UnLinkAutoFollow(void)
{
	if(m_pCallAutoFollow)
		NTL_DELETE(m_pCallAutoFollow);
}

void CInputActionMap::UnLinkPartySelect(void)
{
	if(m_pCallPartySelect)
		NTL_DELETE(m_pCallPartySelect);
}

void CInputActionMap::UnLinkPartyAutoSelect(void)
{
	if(m_pCallPartyAutoSelect)
		NTL_DELETE(m_pCallPartyAutoSelect);
}

void CInputActionMap::UnLinkScouterUse(void) 
{
    if(m_pCallScouterUse)
        NTL_DELETE(m_pCallScouterUse);
}

void CInputActionMap::UnLinkTargetMarking(void)
{
	if(m_pCallTargetMarking)
		NTL_DELETE(m_pCallTargetMarking);
}

void CInputActionMap::UnLinkTargetSelecting(void)
{
	if(m_pCallTargetSelecting)
		NTL_DELETE(m_pCallTargetSelecting);
}

void CInputActionMap::UnLinkChatPageChane( void )
{
	if(m_pCallChatPageChange )
		NTL_DELETE(m_pCallChatPageChange);
}

/**
* \brief Ű�� Up/Down Ƚ���� ����Ѵ�.
* \param byChar		(RwUInt8) Ű�� ������
* \param bDown		(RwBool) Ű�� Up/Down ����
* \return Ű�� �̹� �ʿ� �����ؼ� Ref ��/���� �Ͼ�� ��� TRUE
*/
RwBool CInputActionMap::KeyReference( RwUInt8 byChar, RwBool bDown /* = TRUE */)
{
	// �̹� Ű�� ������ ���
	UPDOWNREF::iterator it = m_mapUpdownRef.find( byChar );
	if( it != m_mapUpdownRef.end() )
	{
		// Ref ����
		if( bDown )
		{
			(*it).second++;
		}
		else
		{
			// Ref ����
			(*it).second--;
			if( (*it).second <= 0 )
				m_mapUpdownRef.erase( it );
		}

		return TRUE;
	}
	// Ű�� �������� ���� ���
	else
	{
		if( bDown )
			m_mapUpdownRef[byChar] = 1;

		return FALSE;
	}
}