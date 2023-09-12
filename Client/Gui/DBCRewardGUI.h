#pragma once

#include "NtlDebug.h"
#include "NtlPLGui.h"
#include "ceventhandler.h"
#include "ButtonList.h"
#include "DragonBallRewardTable.h"
#include "ItemTable.h"
#include "SkillTable.h"
#include "SurfaceGui.h"
#include "DragonBallTable.h"
#include "DragonBallRewardTable.h"

class CTextTable;
class CNtlWorldConceptDBC;

#define REWARD_LIST_MAX_VISIBLE		4

/// ���� GUI ����
enum ERewardUIStatus
{
	E_REWARD_STATUS_SELECT,			///< ���� ���� �ܰ�
	E_REWARD_STATUS_CONFIRM,		///< ���� Ȯ�� �ܰ�
};


/// ���� �׸���� Ʈ�� ������ �����ϴ� ���
struct SRewardItem
{
	sDRAGONBALL_REWARD_TBLDAT* pData;			///< Reward Table Data
	SRewardItem* pParent;
	std::vector<SRewardItem*> itemChild;	///< �ڽ� �����۵�

	SRewardItem()
	{
		pData = NULL;
		pParent = NULL;
	}
	~SRewardItem()
	{
		for each(SRewardItem* pItem in itemChild)
		{
			NTL_DELETE(pItem);
		}
	}		
};


/**
 * \ingroup Client
 * \brief ��� ��ȯ�� �ҿ����� GUI
 * \date 2007-06-24
 * \author agebreak
 */
class CDBCRewardGUI : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CDBCRewardGUI(void);
	CDBCRewardGUI(const RwChar* pName);
	virtual ~CDBCRewardGUI(void);

	VOID		Init();
	RwBool		Create();
	VOID		Destroy();
	VOID		Update(RwReal fElapsed);
	RwInt32		SwitchDialog(bool bOpen);

	// Event
	VOID		HandleEvents(RWS::CMsg &pMsg);

	// �̱��� ����/���� 
	static	void	CreateInstance();
	static	void	DeleteInstance();

	VOID			AdjustDialog();							///< ���̾�α� ��ġ�� ����

protected:
	// CallBack
	VOID	OnClickBackBtn(gui::CComponent* pComponent);
	VOID	OnClickOkBtn(gui::CComponent* pComponent);
	VOID	OnClickCancelBtn(gui::CComponent* pComponent);
	VOID	OnPaint();
	VOID	OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID	OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID	OnMouseLeave(gui::CComponent* pComponent);
	VOID	OnScrollBarChanged(RwInt32 iValue);
    VOID	OnCaptureMouseDown(const CKey& key);
    VOID	OnCaptureWheelMove( RwInt32 nFlag, RwInt16 sDelta, CPos& pos );

	
	// �׸� ���� CallBack
	gui::CButton*	OnCreateItem();
	void			OnDestroyItem(gui::CButton* pButton);
	void			OnClickedItem(RwInt32 iIndex);


	VOID			SetStatus(ERewardUIStatus eStatus);		///< ����â UI�� ���� ���¸� �����Ѵ�.
	
	void			ShowList(SRewardItem* pItem, RwInt32 nPos);
	void			CreateRewardTree(SRewardItem* pParent, RwInt32 nDepth);						///< ���� �����͵��� Ʈ���� �����Ѵ�.
	void			ShowItemInfo(SRewardItem* pItem);		///< ���� ������ ������ ǥ���Ѵ�.
	void			UnLockDragonBall();						///< Lock���� �巡�ﺼ���� ��� UnLock�Ѵ�.	
	RwBool			IsExistSkill(RwUInt32 nTblIdx);			///< �̹� ������ �ִ� ��ų���� Ȯ���Ѵ�.	

protected:
	static	CDBCRewardGUI*	m_pInstance;			///< �̱��� �ν��Ͻ� ��ü

	WCHAR					m_pBuf[20];
	RwBool					m_bDisplayHurryUp;		///< �ð��� ���ٶ�� �޽����� ǥ���ߴ��� ���� �÷���
	RwBool					m_bDelete;				///< �������� ���� �÷���
	DWORD					m_nDepthIdx;			///< ���� �׸� ������ �ε��� ��	
	DWORD					m_nPrevDepthIdx;		///< ���� �׸� ������ �ε��� ��
    RwInt32                 m_nBtnCount;            ///< ��ư ���� ����
	
	CTextTable*				m_pDBRewardTextTable;	///< ���� ���� �ؽ�Ʈ ���̺�	
	CDragonBallTable*		m_pDragonBallTable;		///< �巡�ﺼ ���̺�
	CDragonBallRewardTable* m_pDragonBallRewardTable; ///< ���� ���̺�

	SRewardItem				m_RewardItemRoot;		///< ���� ������ Ʈ���� ��Ʈ ���
	SRewardItem*			m_pPrevItem;			///< �Ѵܰ����� Ʈ�� ���
	SRewardItem*			m_pRewardItem;			///< ���� ���� ������
	sTBLDAT*				m_pRewardItemTblData;	///< ���� �������� ���̺� ������		

	CNtlWorldConceptDBC*	m_pWorldConceptDBC;		///< DBC Concept ��Ʈ�ѷ�


	// gui
    gui::CPanel*            m_pPnlSelectMenu;
    gui::CPanel*            m_pPnlSelectItem;
	gui::CButton*			m_pBtnBack;
	gui::CButton*			m_pBtnOK;
	gui::CButton*			m_pBtnCancel;	
	gui::CStaticBox*		m_pSttTime;
	gui::CStaticBox*		m_pSttItemName;
	gui::CStaticBox*		m_pSttItemText;	
	gui::CScrollBar*		m_pScrollBar;
	CSurfaceGui				m_sufItem;				///< �������� Icon�� ǥ���� Surface

	CButtonList<CDBCRewardGUI, SRewardItem*>	m_ButtonList;	///< �׸� ��ư ����

	// slot
	gui::CSlot				m_slotClickExitBtn;
	gui::CSlot				m_slotClickBackBtn;
	gui::CSlot				m_slotClickOKBtn;
	gui::CSlot				m_slotClickCancelBtn;
	gui::CSlot				m_slotPaint;
	gui::CSlot				m_slotMove;
	gui::CSlot				m_slotMouseMove;
	gui::CSlot				m_slotMouseLeave;
	gui::CSlot				m_slotSliderMove;
	gui::CSlot				m_slotSliderChanged;
    gui::CSlot  			m_slotCaptureMouseDown;
    gui::CSlot              m_slotListWheelMove[REWARD_LIST_MAX_VISIBLE];
};	
