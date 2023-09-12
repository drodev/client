#include "precomp_dboclient.h"
#include "CautionNotifyGui.h"

// Sound
#include "GUISoundDefine.h"

// shared
#include "NtlBattle.h"

// presentation
#include "NtlPLGuiManager.h"
#include "NtlPLEvent.h"

// simulation
#include "NtlSLGlobal.h"
#include "NtlSLLogic.h"
#include "NtlSobAvatar.h"

// dbo
#include "DboGlobal.h"
#include "DboEvent.h"
#include "DisplayStringManager.h"
#include "DialogPriority.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CNotifyTimer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* \brief Constructions
*/
CNotifyTimer::CNotifyTimer()
: m_pCallTimer(0)
, m_fCurrentTime(0.0f)
, m_fIntervalTime(dDEFAULT_NOTIFY_TIMER_INVERVAL_TIME)
{

}

/**
* \brief Constructions
*/
CNotifyTimer::CNotifyTimer(RwReal fIntervalTime) 
: m_pCallTimer(0)
, m_fCurrentTime(0.0f)
{
	m_fIntervalTime = fIntervalTime;
}

/**
* \brief Destruction
*/
CNotifyTimer::~CNotifyTimer() 
{
	UnLinkIntervalTimer();
}

/**
* \brief Ÿ�̸Ӱ� �ߵ��� ������ �������ش�.
* \param fIntervalTIme	(RwReal) Ÿ�̸Ӱ� �ߵ��� ����
*/
void CNotifyTimer::SetIntervalTime( RwReal fIntervalTime ) 
{
	m_fIntervalTime = fIntervalTime;
}

/**
* \brief Update
* \param fElapsed	(RwReal) ���� ������Ʈ���� ����� �ð�
*/
void CNotifyTimer::Update( RwReal fElapsed ) 
{
	m_fCurrentTime += fElapsed;

	if( m_fCurrentTime > m_fIntervalTime )
	{
		m_fCurrentTime = 0.0f;

		if( m_pCallTimer )
			m_pCallTimer->Call( m_fIntervalTime );
	}
}


/**
* \brief CNtlCallbackParam1float �� Callback�� ��ϵǾ� �ִٸ� �������ش�.
*/
void CNotifyTimer::UnLinkIntervalTimer( void ) 
{
	if( m_pCallTimer )
		NTL_DELETE( m_pCallTimer );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CCautionNotifyContinuance
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* \brief Constructions
*/
CCautionNotifyContinuance::CCautionNotifyContinuance()
: m_pNotifyGui(NULL)
, m_strStringID("")
, m_fRemainTime(0.0f)
{

}

/**
* \brief Constructions
*/
CCautionNotifyContinuance::CCautionNotifyContinuance( CCautionNotifyGui* pNotify, std::string& uiStringID, RwReal fLimitTime, RwReal fIntervalTime ) 
{
	m_pNotifyGui = pNotify;
	m_strStringID = uiStringID;
	m_fRemainTime = fLimitTime;
	
	m_Timer.SetIntervalTime( fIntervalTime );
	m_Timer.LinkIntervalTimer( this, &CCautionNotifyContinuance::OnIntervalTimer );
}

/**
* \brief Destruction
*/
CCautionNotifyContinuance::~CCautionNotifyContinuance() 
{
	m_Timer.UnLinkIntervalTimer();
}

/**
* \brief Update
* \param fElapsed	(RwReal) ���� ������Ʈ���� ����� �ð�
*/
void CCautionNotifyContinuance::Update( RwReal fElapsed ) 
{
	m_Timer.Update( fElapsed );
}

/**
* \brief ���� �ð��� ã�´�.
* \return ���� �ð�
*/
RwReal CCautionNotifyContinuance::IsRemain() 
{
	return m_fRemainTime;
}

/**
* \brief CNotifyTimer�� ��ϵ� Callback
* \param fElapsed	(RwReal) IntervalTime
*/
int CCautionNotifyContinuance::OnIntervalTimer( RwReal fIntervalTime ) 
{
	m_fRemainTime -= fIntervalTime;

	WCHAR awcBuffer[256];
	swprintf_s( awcBuffer, 256, GetDisplayStringManager()->GetString( m_strStringID ), (RwInt32)m_fRemainTime );
	m_pNotifyGui->ShowCautionNotify( TRUE, m_strStringID, awcBuffer );

	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CCautionNotifyGui
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* \brief Constructions
*/
CCautionNotifyGui::CCautionNotifyGui() 
{
	m_pStbOut = NULL;

	m_bFinish = TRUE;
	m_fLifeTime = 0.0f;
	m_fCurrentTime = 0.0f;

	m_bFadeOut = FALSE;
	m_fFadeOutTime = 0.0f;

	m_strStringID = "";

}

/**
* \brief Constructions
*/
CCautionNotifyGui::CCautionNotifyGui( const RwChar* pName )
: CNtlPLGui(pName)
{
	m_pStbOut = NULL;

	m_bFinish = TRUE;
	m_fLifeTime = 0.0f;
	m_fCurrentTime = 0.0f;

	m_bFadeOut = FALSE;
	m_fFadeOutTime = 0.0f;

	m_strStringID = "";
}

/**
* \brief Destruction
*/
CCautionNotifyGui::~CCautionNotifyGui() 
{
	for( CONTINUANCELIST::iterator it = m_listContinuance.begin(); it != m_listContinuance.end(); ++it )
	{
		NTL_DELETE( (*it) );
	}
	m_listContinuance.clear();

}

/**
* \brief Create
* \return ��������
*/
RwBool CCautionNotifyGui::Create( VOID ) 
{
	NTL_FUNCTION("CCautionNotifyGui::Create");

	// Create Components
	if(!CNtlPLGui::Create("", "", "gui\\CautionNotify.frm"))
		NTL_RETURN(FALSE);

	CNtlPLGui::CreateComponents(CNtlPLGuiManager::GetInstance()->GetGuiManager());

	m_pThis = (gui::CDialog*)GetComponent("dlgMain");
	m_pThis->SetPriority( dDIALOGPRIORITY_NOTIFY );

	m_pStbOut = (gui::CStaticBox*)GetComponent("sttOut");


	Enable(FALSE);

	// Add Update
	GetNtlGuiManager()->AddUpdateFunc(this);

	// Link Message
	LinkMsg( g_EventTimeFixedNotify, 0 );
	LinkMsg( g_EventResize, 0 );
	
	// Event�� ����Ѵ�.
	RegisterHandler();

	NTL_RETURN(TRUE);
}

/**
* \brief Destroy
*/
VOID CCautionNotifyGui::Destroy( VOID ) 
{
	NTL_FUNCTION( "CCautionNotifyGui::Destroy");

	UnLinkMsg( g_EventTimeFixedNotify );
	UnLinkMsg( g_EventResize );

	GetNtlGuiManager()->RemoveUpdateFunc(this);

	CNtlPLGui::DestroyComponents();
	CNtlPLGui::Destroy();

	NTL_RETURNVOID();
}

/**
* \brief Update
* \param fElapsed	(RwReal) ���� ������Ʈ���� ����� �ð�
*/
VOID CCautionNotifyGui::Update( RwReal fElapsed ) 
{
	// ���� Continuance �� ����Ʈ�� ��� ���� �ʴٸ� ������Ʈ ���ش�.
	if( !m_listContinuance.empty() )
	{
		CONTINUANCELIST::iterator it = m_listContinuance.begin();

		while( it != m_listContinuance.end() )
		{
			// ������Ʈ�ϰ� RemainTime�� 1.0 �ʺ��� ���ٸ� �������ش�. ( ������ �̹� Callback�� ȣ��� ���� )
			(*it)->Update( fElapsed );
			if( (*it)->IsRemain() <= 1.0f )
			{
				// ����
				CCautionNotifyContinuance *pContinuance = (*it);
				it = m_listContinuance.erase(it);
				NTL_DELETE( pContinuance );

				continue;
			}

			it++;
		}	
	}

	if( m_bFinish )
		return;

	m_fCurrentTime += fElapsed;
	
	// ���ӽð����� ���� �ð��� �� �������� Fade Out��Ų��.
	if( m_fCurrentTime > m_fLifeTime )
	{
		m_bFadeOut = TRUE;
	}

	// FadeOut �ǰ�, FadeOut�� �Ϸᰡ �Ǹ� ��������.
	if(m_bFadeOut)
	{
		m_fFadeOutTime += fElapsed;
		if(m_fFadeOutTime >= CAUTION_NOTIFY_FADEOUT_TIME)
		{
			m_bFinish = TRUE;
			m_fCurrentTime = 0.0f;
			Show(false);

			return;
		}

		RwUInt8 byAlpha = (RwUInt8)((CAUTION_NOTIFY_FADEOUT_TIME - m_fFadeOutTime)*255.0f/CAUTION_NOTIFY_FADEOUT_TIME);
		m_pStbOut->SetAlpha(byAlpha);
	}
}

/**
* \brief HandleEvents
* \param msg	(RWS::CMsg*) �̺�Ʈ �޽��� ����ü
*/
VOID CCautionNotifyGui::HandleEvents( RWS::CMsg& msg ) 
{
	if( msg.Id == g_EventTimeFixedNotify )
	{
		SDboEventTimeFixedNotify* pNotify = reinterpret_cast<SDboEventTimeFixedNotify*>( msg.pData );

		// �ڵ鷯�� ��ϵǾ� �ִٸ� ���� �Լ��� ȣ���ϰ� Return�Ѵ�.
		HANDLEMAP::iterator it = m_mapNotifyHandler.find( pNotify->strStringID );
		if( it != m_mapNotifyHandler.end() )
		{
			(this->*((*it).second))(pNotify->bActive, pNotify->strStringID);
			return;
		}

		ShowCautionNotify( pNotify->bActive, pNotify->strStringID, pNotify->pString );

		// ���� �޼��� �ߺ��� ����� �޼��� ���ö����� ���, �ߺ��� ��ų���  ShowCautionNotify ������ ó���Ұ�,
		Logic_PlayGUISound(GSD_SYSTEM_WARNING_NOTIFY);		
	}
	// �ػ󵵰� ����Ǿ��� �� ������� �̺�Ʈ
	else if( msg.Id == g_EventResize )
	{
		SNtlPLEventResize *pData = reinterpret_cast<SNtlPLEventResize*>( msg.pData );

		// ��������
		PositionAlign( pData->iWidht, pData->iHeight );
	}
}

/**
* \brief ��µ� �ؽ�Ʈ�� ��ġ�� �����Ѵ�.
*/
VOID CCautionNotifyGui::PositionAlign( RwInt32 nScreenWidth, RwInt32 nScreenHeight ) 
{
	m_pThis->SetPosition( (RwInt32)( (nScreenWidth - m_pThis->GetPosition().GetWidth() ) /2 ),
		(RwInt32)( (nScreenHeight * GetDboGlobal()->GetDBOUIConfig()->GetNotifyConfig()->fCautionNotiry_YPosRate ) ) );
}

/**
* \brief ������ Caution �� Text�� �����ϰ� �ʱ�ȭ�Ѵ�.
*/
VOID CCautionNotifyGui::SetCurrentCautionNotify(std::string& strStringID, const WCHAR* pwcString )
{
	m_fCurrentTime = 0.0f;
	m_fFadeOutTime = 0.0f;
	m_fLifeTime = CAUTION_NOTIFY_LIFE_TIME;
	
	m_strStringID = strStringID;
	m_pStbOut->SetText( pwcString );
	m_pStbOut->SetAlpha(CAUTION_NOTIFY_DEFAULT_ALPHA);
	
	PositionAlign( GetDboGlobal()->GetScreenWidth(), GetDboGlobal()->GetScreenHeight() );
	
	m_bFinish = FALSE;
	m_bFadeOut = FALSE;

	Show(true);
}

/**
* \brief ���޽����� ����ϴ� �Լ� ( �̹� ���� ������ ������ �ִ� ���� SideIcon���� ����������. )
*/
VOID CCautionNotifyGui::ShowCautionNotify( RwBool bActive, std::string& strStringID, const WCHAR* pwcString )
{
	if( bActive )
	{
		// �̹� ����ϰ� �ִ� CautionNotify�� ���ٸ� �ٷ� ����Ѵ�.
		if( m_bFinish )
			SetCurrentCautionNotify( strStringID, pwcString );
		else
		{
			// ����ϰ� �ִ� CautionNotify�� �ִٸ� SideIcon���� ������ ��µǰ� �ִ� CautionNotify�� ����������
			// ���ο� CautionNotify�� ����Ѵ�.
			CDboEventGenerator::CautionSideNotify( TRUE, strStringID, m_pStbOut->GetText().c_str(), m_fLifeTime-m_fCurrentTime);

			SetCurrentCautionNotify( strStringID, pwcString );
		}
	}
	else
	{
		// ���� ��µǰ� �ִ� ID�� �����϶�� ����� ID�� ������ ��� �����ش�.
		if( m_bFinish )
		{
			if( m_strStringID == strStringID )
				ClearCurrentCautionNotify();
		}
	}
}

/**
* \brief ������ CautionNotify�� �ʱ�ȭ�Ѵ�.
*/
VOID CCautionNotifyGui::ClearCurrentCautionNotify() 
{
	m_fCurrentTime = 0.0f;
	m_fLifeTime = 0.0f;
	m_fFadeOutTime = 0.0f;

	m_strStringID = "";

	m_pStbOut->SetAlpha(CAUTION_NOTIFY_DEFAULT_ALPHA);
	m_pStbOut->Clear();

	m_bFinish = TRUE;

	Show(false);
}

/**
* \brief Free PVP ��� ó�� �ƿ� �޽����� �ڵ鷯
* \param bActive	(RwBool) ������� ��������
* \param uiStringID	(RwUInt32) ���ڿ� �ε���
*/
VOID CCautionNotifyGui::FreePvpOutSideHandler( RwBool bActive, std::string strStringID)
{
	// bActive �� FALSE�� �����Ѵ�.
	if( bActive )
	{
		if( !m_listContinuance.empty() )
			DeleteContinuance( strStringID );
	
		// ���
		AddContinuance( strStringID, dFREEPVP_OUTSIDE_STAGE_LIMIT_TIME, dDEFAULT_NOTIFY_TIMER_INVERVAL_TIME );

		// �ѹ��� ������ش�.
		WCHAR awcBuffer[256];
		swprintf_s( awcBuffer, 256, GetDisplayStringManager()->GetString( "DST_FREEPVP_OUTSIDE_STAGE" ), (RwInt32)dFREEPVP_OUTSIDE_STAGE_LIMIT_TIME );
		ShowCautionNotify( TRUE, strStringID, awcBuffer );
		
	}
	else
	{
		// ����Ʈ�� �ƹ��͵� �� ��� �ִٸ� �׳� ���Ͻ�Ų��.
		if( !m_listContinuance.empty() )
			DeleteContinuance( strStringID );
	}
}

/**
* \brief �ڵ鷯�� ��ϵ� �͵��� ����Ѵ�.
*/
VOID CCautionNotifyGui::RegisterHandler() 
{
	m_mapNotifyHandler["DST_FREEPVP_OUTSIDE_STAGE"] = &CCautionNotifyGui::FreePvpOutSideHandler;
}

/**
* \brief StringID�� Continuance�� ����Ѵ�.
* \param uiStringID		(RwUInt32) ���ڿ� �ε���
* \param fLimitTime		(RwReal) ���ѽð�
* \param fIntervalTime	(RwReal) ����
*/
VOID CCautionNotifyGui::AddContinuance(std::string& strStringID, RwReal fLimitTime, RwReal fIntervalTime )
{
	CCautionNotifyContinuance* pContinuance = NTL_NEW CCautionNotifyContinuance( this, strStringID, fLimitTime, fIntervalTime );
	m_listContinuance.push_back( pContinuance );
}

/**
* \brief Continuance List�� ��ϵǾ� �ִ� ������ StringID�� ���� Continuance�� �����Ѵ�.
* \param uiStringID		(RwUInt32) ���ڿ� �ε���
*/
VOID CCautionNotifyGui::DeleteContinuance(std::string& strStringID)
{	
	CONTINUANCELIST::iterator it = m_listContinuance.begin();
	while( it != m_listContinuance.end() )
	{
		if( (*it)->GetStringID() == strStringID )
		{
			// ����
			CCautionNotifyContinuance *pContinuance = (*it);
			it = m_listContinuance.erase(it);
			NTL_DELETE( pContinuance );

			continue;
		}

		it++;
	}	
}