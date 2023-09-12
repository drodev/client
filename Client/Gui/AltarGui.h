#pragma once

#include "NtlPLGui.h"
#include "ceventhandler.h"
#include "SurfaceGui.h"
#include "NtlDragonBall.h"

class CNtlSobItem;
class CNtlWorldConceptDBC;

/// �巡�ﺼ Ÿ��
enum EDragonBallType
{
	E_DRAGONBALL_NONE,
	E_DRAGONBALL_1,
	E_DRAGONBALL_2,
	E_DRAGONBALL_3,
	E_DRAGONBALL_4,
	E_DRAGONBALL_5,
	E_DRAGONBALL_6,
	E_DRAGONBALL_7,
};

/// �巡�ﺼ ���� ����ü
struct DragonBallSlot
{
	CRectangle		 m_rt;		///< �巡�ﺼ ������ ����
	CSurfaceGui		 m_surface;	///< �巡�ﺼ ������ �����̽� (�ؽ��� ������ �ʿ�)
	EDragonBallType	 m_eDBType;	///< ���Կ� �ִ� �巡�ﺼ Ÿ��
	CNtlSobItem*	 m_pSobItem; ///< ���Կ� �ִ� �������� ������

	DragonBallSlot()
	{
		m_eDBType = E_DRAGONBALL_NONE;
		m_pSobItem = NULL;
	}
};


/**
 * \ingroup Client
 * \brief �巡�ﺼ ��� ��ȯ ���� Ŭ���� ������ GUI
 * �巡�ﺼ 7���� �����Ͽ� ����� ��ȯ�ϱ� ���ؼ� ����Ѵ�.
 * \date 2007-06-20
 * \author agebreak
 */
class CAltarGui	: public CNtlPLGui, public RWS::CEventHandler
{
public:
	CAltarGui(void);
	CAltarGui(const RwChar* pName);
	virtual ~CAltarGui(void);

	VOID		Init();
	RwBool		Create();
	VOID		Destroy();
	VOID		Update(RwReal fElapsed);

	RwInt32		SwitchDialog(bool bOpen);

	// Event
	VOID		HandleEvents(RWS::CMsg &pMsg);

	// Singleton create / remove function
// Almost no GUI is generated, so you only need to create it.
	static void		  CreateInstance();
	static void		  DeleteInstance();

protected:
	// CallBack
	VOID	OnClickExitBtn(gui::CComponent* pComponent);
	VOID	OnClickOKBtn(gui::CComponent* pComponent);
	VOID	OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID	OnMouseDown(const CKey& key);
	VOID	OnMouseUp(const CKey& key);
	VOID	OnPaint();
	VOID	OnInputBoxGotFocus();
	VOID	OnInputBoxLostFocus();
    VOID	OnCaptureMouseDown(const CKey& key);


	RwInt32	GetChildSlotIdx(RwInt32 nX, RwInt32 nY);	///< ���콺�� Ŭ���Ҷ� � Slot�� �ش��ϴ��� ����Ѵ�.

	VOID	SetDragonBallSlot(RwInt32 nSlotIdx, EDragonBallType eDragonBallType);	///< �巡�ﺼ�� slot�� �����Ѵ�.
	VOID	RemoveDragonBallSlot(RwInt32 nSlotIdx);									///< ������ �巡�ﺼ�� slot���κ��� �����Ѵ�.
    RwBool  IsExistSameType(EDragonBallType eType);                                 ///< ���� Ÿ��(��ȣ)�� �巡�ﺼ�� �̹� �����ִ��� üũ�Ѵ�.

	VOID	SpawnDragon();								///< ��� ��ȯ ������ �����Ѵ�.

	

protected:
	static CAltarGui*	m_pInstance;			///< �̱��� �ν��Ͻ� ��ü	

	gui::CButton*		m_pBtnExit;				///< Exit ��ư
	gui::CButton*		m_pBtnOK;				///< OK ��ư
	gui::CInputBox*		m_pInKeyword;			///< �ֹ� ��ǲ �ڽ�
	gui::CPanel*		m_pPnlInputBack;		///< ��ǲ �ڽ� ���
	gui::CPanel*		m_apPnlLight[7];		///< �巡�ﺼ�� ���ԵǸ� ����� ���
	gui::CStaticBox*	m_pStaticKeyword;		///< �ֹ� ��ǲ �ڽ��� ���� �ؽ�Ʈ

	gui::CSlot			m_slotClickExitBtn;	
	gui::CSlot			m_slotClickOKBtn;	
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotMouseDown;	
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotGotFocus;
	gui::CSlot			m_slotLostFocus;
    gui::CSlot			m_slotCaptureMouseDown;

    DragonBallSlot      m_DBSlot[DRAGON_BALL_TYPE_COUNT][NTL_ITEM_MAX_DRAGONBALL];          ///< �巡�ﺼ �������� ǥ���� ����
	RwInt32				m_nDBCount;				///< ���� �����Ǿ� �ִ� �巡�ﺼ Count
	RwBool				m_bSpawnDragon;			///< ����� ��ȯ�ߴ��� ����
	RwBool				m_bDelete;

	CNtlWorldConceptDBC*	m_pWorldConceptDBC;	///< �巡�ﺼ �÷��� ��Ʈ�ѷ��� ������

};
