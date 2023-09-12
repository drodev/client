#include "precomp_dboclient.h"
#include "CautionSideIconGui.h"

// Core
#include "NtlDebug.h"

// Simulation
#include "NtlSLEvent.h"
#include "NtlSLEventFunc.h"

// Presentation
#include "NtlPLGuiManager.h"
#include "NtlPLEvent.h"

// Dbo
#include "DboGlobal.h"
#include "DisplayStringManager.h"


///////////////////////////////////////////////////////////////////////////////////////////
// CCautionSideViewUnit
///////////////////////////////////////////////////////////////////////////////////////////

/**
* \brief Construction
*/
CCautionSideViewUnit::CCautionSideViewUnit( gui::CComponent* pParentGui, std::string& uiStringID, const WCHAR* pwcString, RwReal fLimitTime)
{
	m_bLife = TRUE;
	m_uiStringID = uiStringID;
	m_fLimitTime = fLimitTime;
	m_fCurrentTime = 0.0f;
	
	CRectangle rect( 0, 0, dCAUTION_UNIT_WIDTH, dCAUTION_UNIT_HEIGHT );
	m_pStbSideViewUnit = NTL_NEW gui::CStaticBox( &rect, pParentGui, GetNtlGuiManager()->GetSurfaceManager());
	m_pStbSideViewUnit->SetTextColor( dCAUTION_UNIT_TEXT_COLOR );
	m_pStbSideViewUnit->SetText( pwcString );
}

/**
* \brief Destruction
*/
CCautionSideViewUnit::~CCautionSideViewUnit() 
{
	if( m_pStbSideViewUnit )
	{
		NTL_DELETE( m_pStbSideViewUnit );
		m_pStbSideViewUnit = NULL;
	}
}

/**
* \brief Update
* \param fElapsed	(RwReal) ���� ������Ʈ���� ����� �ð�
*/
void CCautionSideViewUnit::Update( RwReal fElapsed ) 
{
	if( !m_bLife )
		return;

	m_fCurrentTime += fElapsed;
	
	if( m_fCurrentTime > m_fLimitTime )
		m_bLife = FALSE;
}

/**
* \brief �θ� ������Ʈ������ ��ġ�� ���Ѵ�.
* \param nPosX		(RwInt32) X�� ���� ��ǥ
* \param nPosY		(RwInt32) Y�� ���� ��ǥ
*/
void CCautionSideViewUnit::SetPositionFromParent( RwInt32 nPosX, RwInt32 nPosY ) 
{
	if( m_pStbSideViewUnit )
		m_pStbSideViewUnit->SetPosition( nPosX, nPosY );
}

///////////////////////////////////////////////////////////////////////////////////////////
// CCautionSideIconGui
///////////////////////////////////////////////////////////////////////////////////////////

/**
* \brief Construction
*/
CCautionSideIconGui::CCautionSideIconGui( const RwChar* pName )
: CSideIconBase( pName )
{
	m_nSize = 0;
	m_pIconButton = NULL;
}

/**
* \brief Destruction
*/
CCautionSideIconGui::~CCautionSideIconGui() 
{
}

/**
* \brief Caution SideIcon�� �⺻���� ������Ʈ�� �����ϸ� UI�� ����� ������ �����Ѵ�.
* \returns ���� ����
*/
RwBool CCautionSideIconGui::Create() 
{
	NTL_FUNCTION( "CCautionSideIconGui::Create" );

	if( !CNtlPLGui::Create( "", "gui\\CautionSideIcon.srf", "gui\\CautionSideIcon.frm" ) )
		NTL_RETURN( FALSE );

	CNtlPLGui::CreateComponents( GetNtlGuiManager()->GetGuiManager() );

	m_pThis = (gui::CDialog*)GetComponent( "dlgMain" );
	m_pIconButton = (gui::CButton*)GetComponent( "btnIcon" );

	m_slotIconButtonClicked = m_pIconButton->SigClicked().Connect( this, &CCautionSideIconGui::OnIconButtonClicked );
	m_slotMove = m_pThis->SigMove().Connect( this, &CCautionSideIconGui::OnMove );

	// Priority
	SetNumber( dSIDEICON_PRIORITY_CAUTION );

	Show(false);

	NTL_RETURN(TRUE);
}

/**
* \brief Caution SideIcon�� �⺻���� ������Ʈ ���� �� Ŭ�������� ����� �ڿ��� �����Ѵ�.
*/
void CCautionSideIconGui::Destroy() 
{
	CNtlPLGui::DestroyComponents();
	CNtlPLGui::Destroy();
}

/**
* \brief ���̵�����ܿ��� ���̵���� ����ִ� ������ ������ �޴´�.
* \param pData	(void*) SCautionSideViewUnits*�� void* ���� ��ȯ�� �ڷ�
*/
void CCautionSideIconGui::OnSideIconReceive( void* pData ) 
{
	SCautionSideViewUnits* pUnitSize = reinterpret_cast<SCautionSideViewUnits*>( pData );

	m_nSize = pUnitSize->nSize;

	// ����� 0�̰ų� �� ������ �ݴ´�.
	if( m_nSize <= 0 )
	{
		Show(false);
	}
	else
	{
		WCHAR awcBuffer[32];
		swprintf_s( awcBuffer, 32, L"%d", m_nSize );
		m_pIconButton->SetText( awcBuffer );

		Show(true);
	}
}

/**
* \brief ����� SideView�� �� �� ��
*/
void CCautionSideIconGui::OnSideViewClosed() 
{
	/*Show(false);*/
}

/**
* \brief SideIcon�� Ŭ������ �� ����ǵ��� ����� �Լ�
*/
void CCautionSideIconGui::OnIconButtonClicked( gui::CComponent* pComponent ) 
{
	CSideIconGui::GetInstance()->OpenSideView( this, SIDEVIEW_CAUTION, NULL );
}

/**
* \brief �⺻ Dialog�� Move�ǰų� Resize ���� �� ȣ��
* \param nOldX	(RwInt32) ���� X ��ǥ
* \param nOldY	(RwInt32) ���� Y ��ǥ
*/
void CCautionSideIconGui::OnMove( RwInt32 nOldX, RwInt32 nOldY ) 
{
	CRectangle rect = m_pIconButton->GetScreenRect();
	CSideIconGui::GetInstance()->OnSideViewSend( SIDEVIEW_CAUTION, (void*)&rect);
}

///////////////////////////////////////////////////////////////////////////////////////////
// CCautionSideViewGui
///////////////////////////////////////////////////////////////////////////////////////////

/**
* \brief Construction
*/
CCautionSideViewGui::CCautionSideViewGui( const RwChar* pName ) 
: CSideViewBase( pName )
{

}

/**
* \brief Destruction
*/
CCautionSideViewGui::~CCautionSideViewGui() 
{

}

/**
* \brief CautionSideView�� ������Ʈ�� ���ҽ��� �����ϰ� �ʿ��� Event�� ����Ѵ�.
* \return	��������
*/
RwBool CCautionSideViewGui::Create() 
{
	NTL_FUNCTION( "CCautionSideViewGui::Create" );

	if( !CNtlPLGui::Create( "", "gui\\CautionSideView.srf", "gui\\CautionSideView.frm" ) )
		NTL_RETURN( FALSE );

	CNtlPLGui::CreateComponents( GetNtlGuiManager()->GetGuiManager() );

	m_pThis = (gui::CDialog*)GetComponent( "dlgMain" );
	m_pStbTitle = (gui::CStaticBox*)GetComponent( "stbTitle" );
	m_pBtnClose = (gui::CButton*)GetComponent( "btnClose" );

	m_winBackPanel.SetType(CWindowby3::WT_HORIZONTAL);
	m_winBackPanel.SetSurface(0, GetNtlGuiManager()->GetSurfaceManager()->GetSurface("CautionSideView.srf", "srfDialogBackUp"));
	m_winBackPanel.SetSurface(1, GetNtlGuiManager()->GetSurfaceManager()->GetSurface("CautionSideView.srf", "srfDialogBackCenter"));
	m_winBackPanel.SetSurface(2, GetNtlGuiManager()->GetSurfaceManager()->GetSurface("CautionSideView.srf", "srfDialogBackDown"));
	m_winBackPanel.SetSize(250, 160);
	m_winBackPanel.SetPositionfromParent(0, 0);

	m_slotMove = m_pThis->SigMove().Connect(this, &CCautionSideViewGui::OnMove);
	m_slotPaint	= m_pThis->SigPaint().Connect(this, &CCautionSideViewGui::OnPaint);
	m_slotClickedClose = m_pBtnClose->SigClicked().Connect( this, &CCautionSideViewGui::OnCloseButtonClicked );

	// Set Text
	m_pStbTitle->SetText( GetDisplayStringManager()->GetString( "DST_CAUTION_SIDEICON_TITLE" ) );

	Show(false);

	LinkMsg( g_EventCautionSideNotify, 0 );

	GetNtlGuiManager()->AddUpdateFunc( this );

	NTL_RETURN( TRUE );
}

/**
* \brief CautionSideView���� ���� �ڿ��� ���ҽ��� �����Ѵ�.
*/
void CCautionSideViewGui::Destroy() 
{
	NTL_FUNCTION( "CCautionSideViewGui::Destroy" );

	GetNtlGuiManager()->RemoveUpdateFunc( this );

	if( !m_listUnit.empty() )
	{
		ListUnitsIt it = m_listUnit.begin();
		while( it != m_listUnit.end() )
		{
			DestroyUnit( (CCautionSideViewUnit*)(*it) );
			++it;
		}
		
		m_listUnit.clear();
	}

	UnLinkMsg( g_EventCautionSideNotify );

	CNtlPLGui::DestroyComponents();
	CNtlPLGui::Destroy();

	NTL_RETURNVOID();
}

/**
* \brief Update
*/
void CCautionSideViewGui::Update( RwReal fElapsed ) 
{
	// List�� �ƹ��� Unit�� ���ٸ� Update���� �ʴ´�.	
	if( m_listUnit.empty() )
	{
		/*CSideIconGui::GetInstance()->*/
		return;
	}
	
	// ���ŵ� ����� �ִ� �˻��Ѵ�.
	RwBool bIsDelete = FALSE;
	ListUnitsIt it = m_listUnit.begin();
	while( it != m_listUnit.end() )
	{
		(*it)->Update( fElapsed );

		if( !(*it)->IsLive() )
		{
			CCautionSideViewUnit* pUnit = (CCautionSideViewUnit*)(*it);
			m_listUnit.erase( it++ );
			DestroyUnit( pUnit );
			bIsDelete = TRUE;
		}

		if( !bIsDelete )
			it++;
	}

	// ������Ž� �ִٸ� �� ���
	if( bIsDelete )
	{
		// ���̸� �����ϰ� ������ ���ġ
		OnSideViewLocate( m_rectIcon );

		// SideIcon�� ������ �˷��ش�.
		SendUnitSizeToIcon();
	}
}

/**
* \brief OnPaint
*/
void CCautionSideViewGui::OnPaint() 
{
	m_winBackPanel.Render();	
}

/**
* \brief OnMove
*/
void CCautionSideViewGui::OnMove( RwInt32 nOldX, RwInt32 nOldY ) 
{
	m_winBackPanel.SetRect( m_pThis->GetScreenRect() );
}

/**
* \brief �ݱ� ��ư�� Ŭ������ ��
*/
void CCautionSideViewGui::OnCloseButtonClicked( gui::CComponent* pComponent ) 
{
	OnSideViewClose();
}

/**
* \brief HandleEvents
*/
void CCautionSideViewGui::HandleEvents( RWS::CMsg& msg ) 
{
	if( msg.Id == g_EventCautionSideNotify )
	{
		SDboEventCautionSideNotify* pNotify = reinterpret_cast<SDboEventCautionSideNotify*>( msg.pData );

		// bActive �� TRUE�� ���
		// FALSE�� ���� ( �����丮�� ����� ���� �����̱� ������ ���� ������ ���� �ʴ´�.
		if( pNotify->bActive )
		{
			// ������ �ϰ� ������ �����ϸ� ������ ����� �����Ѵ�.
			if( CreateUnit( pNotify->strStringID, pNotify->pString, pNotify->fLifeTime ) )
			{
				SendUnitSizeToIcon();
				OnSideViewLocate( m_rectIcon );
			}
		}
		//else
		//{
		//	// StringID�� �������ְ� ���� ������ ���� �ִٸ� ������ ����� �����Ѵ�.
		//	if ( DestroyUnit( pNotify->uiStringID ) )
		//	{
		//		SendUnitSizeToIcon();
		//		OnSideViewLocate( m_rectIcon );
		//	}
		//}
	}
}

/**
* \brief ESC Ű�� ������ ���
*/
void CCautionSideViewGui::OnPressESC() 
{
	OnSideViewClose();
}

/**
* \brief OnSideViewOpen
*/
void CCautionSideViewGui::OnSideViewOpen( const void* pData ) 
{
	// �������� �ִٰų� List�� �ƹ��͵� ������ ���� �ƴ϶�� �Ҵ�.
	if( m_pThis->IsVisible() || m_listUnit.empty() )
		Show(false);
	else
		Show(true);
}

/**
* \brief OnSideViewReceive
* \param pData	(void*) Side Icon�� ũ�⸦ �ޱ� ���ؼ� CRectangle�� ���޹޴´�.
*/
void CCautionSideViewGui::OnSideViewReceive( void* pData ) 
{
	CRectangle* pRect = reinterpret_cast<CRectangle*>(pData);

	m_rectIcon = (*pRect);
}

/**
* \brief OnSideViewClose
*/
void CCautionSideViewGui::OnSideViewClose() 
{
	Show(false);
}

/**
* \brief ���ֵ��� ���̷� ������ View�� ũ�⸦ ���ϰ� Unit���� ��ġ�Ѵ�.
* \param rectSideIcon	(const CRectangle&) Caution SideIcon�� ȭ�� ��ġ �� ũ��
*/
void CCautionSideViewGui::OnSideViewLocate( const CRectangle& rectSideIcon ) 
{
	RwInt32 nHeight = 0;

	ListUnitsIt it = m_listUnit.begin();
	RwInt32 nIndex = (RwInt32)m_listUnit.size();
	while( it != m_listUnit.end() )
	{
		nHeight += (*it)->GetHeight();

		(*it)->SetPositionFromParent( dCAUTION_UNIT_MARGIN_X_FROM_VIEW, (nIndex * dCAUTION_UNIT_HEIGHT) + dCAUTION_UNIT_HEIGHT_OFFSET_TOP );

		--nIndex;
		++it;
	}
	
	nHeight += dCAUTION_UNIT_HEIGHT_OFFSET_TOP + dCAUTION_UNIT_HEIGHT_OFFSET_BOTTOM;
	m_pThis->SetHeight( nHeight );
	m_pThis->SetPosition( rectSideIcon.left - m_pThis->GetWidth() + rectSideIcon.GetWidth(), rectSideIcon.top - nHeight );
}

/**
* \brief Unit�� �����Ѵ�.
* \param uiStringID		(RwUInt32) ���ڿ� �ε��� (DisplayStringManager)
* \param pString		(const WCHAR*) ���ڿ�
* \param fLifeTime		(RwReal) ��� �޽����� ��� �ִ� �ð�
*/
RwBool CCautionSideViewGui::CreateUnit(std::string& uiStringID, const WCHAR* pString, RwReal fLifeTime )
{
	// 10�� �̻��� ��� �ϳ��� �����ش�.
	if( (RwInt32)m_listUnit.size() >= dMAX_CAUTION_SIDE_VIEW_UNIT )
	{
		CCautionSideViewUnit* pUnit = m_listUnit.back();
		m_listUnit.pop_back();
		DestroyUnit( pUnit );
	}
	
	// ���� �� �ֱ�
	CCautionSideViewUnit* pUnit = NTL_NEW CCautionSideViewUnit( m_pThis, uiStringID, pString, fLifeTime );
	m_listUnit.push_front( pUnit );

	return TRUE;
}

/**
* \brief Unit�� �����Ѵ�.
* \param pUnit	(CCautionSideViewUnit*) Unit�� �޸� �����Ѵ�.
*/
RwBool CCautionSideViewGui::DestroyUnit( CCautionSideViewUnit* pUnit ) 
{
	NTL_DELETE( pUnit );

	return TRUE;
}

/**
* \brief uiStringID�� ������ �ִ� Unit�� ��� �����Ѵ�.
* \param uiStringID		(RwUInt32) ���ڿ� �ε���
* \return ��������
*/
RwBool CCautionSideViewGui::DestroyUnit(std::string& uiStringID )
{
	if( (RwInt32)m_listUnit.size() <= 0 )
		return FALSE;

	RwBool bIsDelete = FALSE;
	for( ListUnitsIt it = m_listUnit.begin(); it != m_listUnit.end(); ++it)
	{
		if( (*it)->GetStringID() == uiStringID )
		{
			CCautionSideViewUnit* pUnit = (*it);
			it = m_listUnit.erase( it );
			DestroyUnit( pUnit );
			bIsDelete = TRUE;
		}
	}

	return bIsDelete;
}

/**
* \brief SideIcon�� Unit�� ������ ������.
*/
void CCautionSideViewGui::SendUnitSizeToIcon() 
{
	SCautionSideViewUnits sData;
	sData.nSize = (RwInt32)m_listUnit.size();

	CSideIconGui::GetInstance()->OnSideIconSend( SIDEICON_CAUTION, (void*)&sData ); 
}