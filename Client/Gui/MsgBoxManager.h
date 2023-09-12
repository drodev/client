////////////////////////////////////////////////////////////////////////////////
// File: MsgBoxManager.h
// Desc: MsgBox
//
// 2006.06.17 Peessi@hitel.net   
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __MSGBOX_MANAGER_H__
#define __MSGBOX_MANAGER_H__

#include "ceventhandler.h"
#include "eventtimer.h"
#include "DboDef.h"

class CMsgBoxGui;
class SDboEventMsgBoxShow;

class CMsgBoxManager : public RWS::CEventHandler
{
public:
	typedef std::list<CMsgBoxGui*>				LIST_MSGBOX;
	typedef std::list<CMsgBoxGui*>::iterator	LIST_MSGBOX_ITER;
private:
	//! Constructor & Destructor
	CMsgBoxManager(VOID);
public:
	~CMsgBoxManager(VOID);
	
	//! Access
	static RwBool CreateInstance(VOID);
	static VOID   DeleteInstance(VOID);

	static CMsgBoxManager* GetInstance(VOID);
	
	// ������ ����� �����Լ����� �̿�.
	VOID DeleteMsgBox(const char* strStringID );
	VOID DeleteMsgBox( CMsgBoxGui* pDeletedMsgBox );
	VOID DeleteAllMsgBoxExceptNetConnectBox(VOID);
	VOID DeleteNetConnectBox(VOID);

	// �������� ���� ���� ����. �׷����� ����Ʈ�����͸� �̿�. ������ ���� ���������� �߰ߵ� ��. 
	CMsgBoxGui* GetMsgBox(char* strStringID, LIST_MSGBOX* pList = NULL );

	// �����̼ǵ� �޽��� �ڽ����� ���� �����ְų� �������� �ʴ� ���.
	VOID ShowAllMsgBox( bool bShow );	

	RwBool IsShowMsgBox(VOID);			// ��ü�޽����ڽ��� ���϶�
	RwBool IsShowPopupMsgBox(VOID);		// �˾��޽����ڽ��� ���϶�

private:
	//! Implementation
	CMsgBoxGui* CreateMsgBox( RwBool bPopup, const char* StringID);
	VOID DeleteAllMsgBox(VOID);

	VOID MsgBoxShowProc( RwBool bPopup, RwBool bHasInput, std::list<sMsgBoxCustomBtn>* plistCustomBtn, const WCHAR* szText, const char* StringID,
						 sMsgBoxData* pData, RwReal fShowTime, RwBool bDuplicate, RwBool bUpdate );

	VOID SetMsgBoxAlpha( RwUInt8 byAlpha );

	//! Event
	VOID HandleEvents( RWS::CMsg &msg );

	VOID LinkEvent(VOID);
	VOID UnLinkEvent(VOID);

	//! CallBack

	//! Variable
	LIST_MSGBOX		m_listMsgBox;
	LIST_MSGBOX		m_listPopupMsgBox;

	static CMsgBoxManager* m_pInstance;
};

static CMsgBoxManager* GetMsgBoxManager(VOID)
{
	return CMsgBoxManager::GetInstance();
}

#endif//__ICON_MOVE_MANAGER_H__