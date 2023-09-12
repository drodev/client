/*****************************************************************************
*
* File			: PetSkillWindowGui.h
* Author		: agebreak
* Copyright	: (��)NTL
* Date			: 2007. 8. 16	
* Abstract		: DBO Pet Skill Window Gui
*****************************************************************************
* Desc         : Summon Pet�� Skill Window GUI�� ǥ���ϴ� Ŭ����
*              : ���� ��� UI�� ���⼭ ���� ǥ���Ѵ�.
*****************************************************************************/

#pragma once

#include "NtlPLGui.h"
#include "ceventhandler.h"
#include "SurfaceGui.h"

class CNtlSobIcon;

#define SUMMON_PET_MAX_SKILL 3

class CPetSkillWindowGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
    /// ��ȯ�� ���� Ÿ���� �����ϱ� ���� ������
    enum EPetType               
    {
        E_PET_TYPE_SUMMON   = 0x00000001,
        E_PET_TYPE_ITEM     = 0x00000002,
        E_TRANSFORM_CANCEL  = 0x00000004,
    };

public:
	CPetSkillWindowGui();
	CPetSkillWindowGui(const RwChar* pName);
	~CPetSkillWindowGui();

	virtual void	Init();
	virtual RwBool	Create();
	virtual void	Destroy();
	virtual void	Update(RwReal fElapsed);	
	virtual RwInt32	SwitchDialog(bool bOpen);	
    virtual void    HandleEvents(RWS::CMsg &pMsg);

    static  CPetSkillWindowGui* GetInstance();
    static  void                DeleteInstance();

    void    AdjustDialog();                                     ///< UI�� ��ġ�� �����Ѵ�.
    void    SetPetID(RwUInt32 uiSerialID, EPetType ePetType);   ///< ��ȯ�� Pet�� Serial ID�� �����Ѵ�.
    void    SetTransformCancel(RwBool bEnable);                 ///< ���� ��� �������� ǥ���Ѵ�.
    void    UpdatePetInfo();                                    ///< pet�� ������ Update�ϰ� ǥ���Ѵ�.

	RwUInt32 GetInfoFlag();

protected:    
    VOID	OnPaint(VOID);
    VOID	OnClickSummonCloseBtn(gui::CComponent* pComponent);
    VOID    OnClickItemCloseBtn(gui::CComponent* pComponent);
    VOID    OnClickSummonAttack(const CKey& key);               ///< �������� ���ù�ư�� Ŭ���� ���
    VOID    OnMouseDownSummonAttack(const CKey& key);           ///< �������� ���ù�ư�� ���� ��ư���� ������� - ��ư�� �̹����� �����Ѵ�.
    VOID    OnClickTransformCancel(gui::CComponent* pComponent);
    VOID    OnMouseEnter(gui::CComponent* pComponent);
	VOID	OnMove( RwInt32 iOldX, RwInt32 iOldY );
    VOID    OnMouseLeave(gui::CComponent* pComponent);
    VOID	OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
    VOID	OnMouseDialogLeave(gui::CComponent* pComponent);

    void    SetSkillIcon();                                     ///< ��ų �������� �ؽ��ĸ� �����Ѵ�.
    void    UpdateSkillIcon(RwReal fElapsedTime);               ///< ��ų �������� ����(��Ÿ��) ����Ʈ�� ������Ʈ�Ѵ�.

protected:
    static CPetSkillWindowGui*  m_pInstance;

    gui::CPanel*    m_pPnlSummonPetBack;
    gui::CPanel*    m_pPnlItemPetBack;
    gui::CPanel*    m_pPnlTransformCancelBack;
    gui::CButton*   m_pBtnSummonClose;
    gui::CButton*   m_pBtnItemClose;
    gui::CButton*   m_pBtnSummonAttack;
    gui::CButton*   m_pBtnTransformCancel;

    gui::CSlot      m_slotPaint;
    gui::CSlot      m_slotClickCloseBtn1;
    gui::CSlot      m_slotClickCloseBtn2;
    gui::CSlot      m_slotClickSummonAttack;
    gui::CSlot      m_slotMouseDownSummonAttack;
    gui::CSlot      m_slotClickTransformCancel;
    gui::CSlot      m_slotMouseEnter;
    gui::CSlot      m_slotMouseLeave;
	gui::CSlot		m_slotMove;
    gui::CSlot      m_slotMouseMove;
    gui::CSlot      m_slotMouseDialogLeave;

    CSurfaceGui     m_surFocus;                               ///< Attack ��ư�� ��Ŀ���� ���������� ǥ�ÿ� �����̽�
    RwBool          m_bVisibeFocus;

    CSurfaceGui     m_surSummonSkill[SUMMON_PET_MAX_SKILL];   ///< Summon Pet�� ��ų ������ �����̽�
    gui::CRadarEffect m_CoolTimeEffect[SUMMON_PET_MAX_SKILL]; ///< Summon Pet ��ų�� ��Ÿ�� �����̽�
    CNtlSobIcon*    m_pSobSkillIcon[SUMMON_PET_MAX_SKILL];    ///< Summon Pet�� ��ų ������ ��ü

    RwUInt32        m_uiSummonPetID;                          ///< Summon Pet�� Serial ID
    RwUInt32        m_uiItemPetID;                            ///< Item Pet�� Serial ID
    RwUInt32        m_uiInfoFlag;                             ///< ���� �������� ǥ�������� �÷���

    gui::CSurface   m_surAttackBtnUp;                         ///< Attack ��ư�� ���� ������ ���ǽ�
    gui::CSurface   m_surAttackBtnDown;                       ///< Attack ��ư�� �ٿ� ������ ���ǽ�
    gui::CSurface   m_surTransformNamek;                      ///< ����ũ ���� ��� ������
    gui::CSurface   m_surTransformSaiya;                      ///< ���̾��� ���� ��� ������
    gui::CSurface   m_surTransformMajin;                      ///< ���� ���� ��� ������

};