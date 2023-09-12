#include "precomp_dboclient.h"
#include "NetPySideIconGui.h"

// core
#include "NtlDebug.h"

// presentation
#include "NtlPLGuiManager.h"

// dbo
#include "DboEvent.h"
#include "DboEventGenerator.h"
#include "DboPacketGenerator.h"
#include "DialogManager.h"
#include "DboGlobal.h"


CNetPySideIconGui::CNetPySideIconGui(const RwChar* pName)
: CSideIconBase(pName)
{
    m_bNetmarbleMemberShip = FALSE;
}

CNetPySideIconGui::~CNetPySideIconGui(void)
{
}

RwBool CNetPySideIconGui::Create() 
{
    NTL_FUNCTION(__FUNCTION__);

    if(!CNtlPLGui::Create("", "gui\\NetPySideIcon.srf", "gui\\NetPySideIcon.frm"))
        NTL_RETURN(FALSE);

    CNtlPLGui::CreateComponents(CNtlPLGuiManager::GetInstance()->GetGuiManager());

    m_pThis = (gui::CDialog*)GetComponent("dlgMain");
    m_pBtnNetPy = (gui::CButton*)GetComponent("btnNetPySideIcon");
    m_slotNetPyBtn = m_pBtnNetPy->SigClicked().Connect(this, &CNetPySideIconGui::OnIconButtonClicked);
    m_slotNetPyMouseEnter = m_pBtnNetPy->SigMouseEnter().Connect(this, &CNetPySideIconGui::OnMouseEnter);
    m_slotNetPyMouseLeave = m_pBtnNetPy->SigMouseLeave().Connect(this, &CNetPySideIconGui::OnMouseLeave);
    
    LinkMsg(g_EventUpdateNetPy);
    LinkMsg(g_EventNetMarbleMemberShipNfy);

    Show(FALSE);

    NTL_RETURN(TRUE);
}

VOID CNetPySideIconGui::Destroy() 
{
    UnLinkMsg(g_EventUpdateNetPy);
    UnLinkMsg(g_EventNetMarbleMemberShipNfy);

   CNtlPLGui::DestroyComponents();
   CNtlPLGui::Destroy();
   Show(TRUE);
}

VOID CNetPySideIconGui::HandleEvents( RWS::CMsg &msg ) 
{
    if(msg.Id == g_EventUpdateNetPy)
    {
        Show(TRUE);
        CSideIconGui::GetInstance()->OpenSideView(this, SIDEVIEW_NETPY, (VOID*)E_NETPY_NOTIFY);
    }
    else if(msg.Id == g_EventNetMarbleMemberShipNfy)
    {
        m_bNetmarbleMemberShip = TRUE;

        Show(TRUE);
        CSideIconGui::GetInstance()->OpenSideView(this, SIDEVIEW_NETPY, (VOID*)E_NETPY_INFO);        
    }
}

VOID CNetPySideIconGui::OnIconButtonClicked( gui::CComponent* pComponent ) 
{
    CSideIconGui::GetInstance()->CloseSideView(SIDEVIEW_NETPY);

	// ��ȹ������ ��û�ϱ� ������ Ȱ��ȭ ��Ű�� �ʴ´�.
	// 09. 08. 17 ������ ��ȹ�� �����Ͼ��� ��û���� Ŭ���̾�Ʈ�� ���ؼ� �۾���
	/*if( !GetDialogManager()->IsOpenDialog( DIALOG_NETPYSHOP ) )
		GetDboGlobal()->GetGamePacketGenerator()->SendShopNetPyItemStartReq();
	else
		GetDboGlobal()->GetGamePacketGenerator()->SendShopNetPyItemEndReq();*/
}

VOID CNetPySideIconGui::OnSideViewClosed() 
{

}

void CNetPySideIconGui::OnMouseEnter(gui::CComponent* pComponent)
{
    CSideIconGui::GetInstance()->OpenSideView(this, SIDEVIEW_NETPY, (VOID*)E_NETPY_INFO);
}

void CNetPySideIconGui::OnMouseLeave(gui::CComponent* pComponent)
{
    CSideIconGui::GetInstance()->CloseSideView(SIDEVIEW_NETPY);
}

void CNetPySideIconGui::Show( bool bShow ) 
{
    // ���� NetPy�� 0�̸� Side Icon�� ������ �ʴ´�.
    if(!m_bNetmarbleMemberShip && Logic_GetNetPy() <= 0)
    {
        __super::Show(FALSE);
        return;
    }

    __super::Show(bShow);    
}