/******************************************************************************
* File			: HintSideIconGui.h
* Author		: Kim Jinsung -> Cho Haesung(2007. 1. 16)
* Copyright		: (��)NTL
* Date			: 2007. 6. 13
* Abstract		: 
*****************************************************************************
* Desc			: PoPo Icon�� ���Ͽ� Html ����Ÿ�� ���
CHelpHintConditionCheck			// Hint�� ���� ������ üũ�ϴ� Ŭ����
CHintSideIconGui				// PoPo Icon�� Side icon
CHelpHintSideViewGui			// PoPo Icon�� ���ؼ� �������� ����(F1)
CGuideHintSideViewGui			// PoPo Icon�� ���ؼ� �������� Html, Flash ����
*****************************************************************************/

#pragma once

#include "NtlSharedType.h"
#include "WindowBy3.h"

//#define dHINTSIDEICON_DEBUG
#define dHINT_HELP_DEFAULT_HEIGHT		60	// HelpHintText�� ������ Component ����
#define dHINT_HELP_OPEN_POS_BY_BOTTOM	35	// HelpHintIcon���� Bottom ��
#define dHINT_HTML_DIRECTORY_GUIDE		"script\\guide\\"

struct sHELP_TBLDAT;
struct sGUIDE_HINT_TBLDAT;
struct SNtlEventRegSideHintIcon; 

class CHint;
class CHelpHintConditionCheck;
class CHintSideIconGui;
class CHelpHintSideViewGui;
class CHelpHintConditionCheck;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class : CHelpHintConditionCheck
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
* \ingroup client
* \brief ���� ��Ʈ�� ������ ��Ȳ�� üũ�ϴ� Ŭ����
*/
class CHelpHintConditionCheck : public RWS::CEventHandler
{
protected:
	enum eHELPHINT_CONDITION_CHECK
	{
		LEVEL_2 = 0,
		LEVEL_3,								/// level 1 ����
		LEVEL_4,
		LEVEL_5,
		LEVEL_6,
		LEVEL_7,
		LEVEL_8,
		LEVEL_9,
		LEVEL_10,
		LEVEL_15,
		LEVEL_20,			// 10
		LEVEL_25,
		LEVEL_30,
		FIRST_BATTLE_FINISH,					/// ó�� ������ ������ ����
		FIRST_FAINT,							///	ó�� �ǽ����� ��
		FIRST_CLICK_WARHOUSENPC,				/// ó�� â��NPC�� Ŭ�� �� ��
		FIRST_LEARN_DASH,						/// ó�� ��ø� ����� ��
		FIRST_CLICK_SHOPNPC,					/// ó�� ���� NPC�� Ŭ���� ��
		FIRST_LEARN_CHARGE,						/// ó�� ������ ����� ��
		FIRST_LEARN_HTB,						/// ó�� HTB�� ����� ��
		FIRST_CLICK_MOB,	// 20				/// ó�� ���� Ŭ������ ��

		FIRST_LOOT_ITEM	,						/// ���� item ����  		
		FIRST_IN_MAINWORLD,						/// ���� ���� ���Խ� NPC dialog�� ���� help hint
		FIRST_LOOT_EQUIP,						/// ���� ���item ����
		FIRST_KILL_MOB,							/// ���� Mob ���	
		FIRST_DOWN_DURABILITY,					/// ���� ��� ������ �ٿ�	
		FIRST_LOOT_HOIPOISTONE,					/// ȣ�����̽��� item ����
		FIRST_OPEN_CAPSULEKIT,					/// ���� open inventory
		FIRST_USE_SCOUTER,						/// ���� use scouter

		FIRST_INTO_TMQ
	};

	typedef std::vector<TBLIDX>				TBLIDXVEC;
	typedef std::map<BYTE, TBLIDXVEC>		HELPMAP;

protected:
	HELPMAP				m_mapHelpHint;
	RwUInt32			m_uiHelpHint;
	RwBool				m_bRegNewHint;

public:
	CHelpHintConditionCheck();
	virtual ~CHelpHintConditionCheck();

	RwBool			Create();
	void			Destroy();

	void			HandleEvents(RWS::CMsg& msg);

protected:
	RwBool			RegHelpHint(const BYTE& byID);
	RwBool			IsRegedHelpHint(const BYTE& byID);
	void			SendPacketHintReq();

	RwBool			IsHelpHint_First_Battle_Finish(RWS::CMsg& msg);
	RwBool			IsHelpHint_First_Faint(RWS::CMsg& msg);
	RwBool			IsHelpHint_First_Click_Mob(RWS::CMsg& msg);
	RwBool			IsHelpHint_Learn_HTBSkill(RWS::CMsg& msg);
	RwBool			IsHelpHint_Learn_Skill(RWS::CMsg& msg, const eHELPHINT_CONDITION_CHECK& eHelpHint, const RwUInt32& uiSkill);
	RwBool			IsHelpHint_Level(RWS::CMsg& msg, const eHELPHINT_CONDITION_CHECK& eHelpHint, const RwUInt8& uiLevel);
	RwBool			IsHelpHint_First_Click_NPC(RWS::CMsg& msg, const eHELPHINT_CONDITION_CHECK& eHelpHint, const RwUInt32& uiNPC);
	RwBool			IsHelpHint_First_Into_Tmq(RWS::CMsg& msg);
	RwBool			IsHelpHint_First_TSItemGet(RWS::CMsg& msg);				/// ���� item ����
	RwBool			IsHelpHint_EndterWorldNPCDialog(RWS::CMsg& msg);		/// ���� ���� ���Խ� NPC dialog�� ���� help hint
	RwBool			IsHelpHint_First_TSItemGetEquip(RWS::CMsg& msg);		/// ���� ���item ����
	RwBool			IsHelpHint_First_AvatarKillMob(RWS::CMsg& msg);			/// ���� Mob ���
	RwBool			IsHelpHint_First_SobEquipItemDurDown(RWS::CMsg& msg);	/// ���� ��� ������ �ٿ�
	RwBool			IsHelpHint_First_TSItemGetHoipoiStone(RWS::CMsg& msg);	/// ȣ�����̽��� item ����
	RwBool			IsHelpHint_First_OpenBagGui(RWS::CMsg& msg);			/// ���� open inventory
	RwBool			IsHelpHint_First_OpenScouterBackgroundGui(RWS::CMsg& msg);	/// ���� use scouter
};

class CHintSideIconGui : public CSideIconBase, RWS::CEventHandler
{
public:
	typedef std::vector<CHint*> HINTVEC;

protected:
	gui::CButton*			m_pIconButton;

	gui::CSlot				m_slotIconButtonClicked;

	gui::CSlot				m_slotPaint;
	gui::CSlot				m_slotMove;

	HINTVEC					m_vecHelpHint;
	CHelpHintConditionCheck m_helpHintConditionCheck;
	
	gui::CFlickerEffect		m_feEffect;


public:
	CHintSideIconGui(const RwChar* pName);
	virtual ~CHintSideIconGui();

	RwBool			Create();
	void			Destroy();

	void			Update( RwReal fElapsed );

	void			HandleEvents(RWS::CMsg& msg);

	RwBool			UpdateHint();
	void			ShowHint();
	void			HideHint();
	void			ShowHintView();

	virtual void	OnSideViewClosed();
	virtual void	OnIconButtonClicked(gui::CComponent* pComponent);
	void			OnPaint();
	void			OnMove(RwInt32 nOldX, RwInt32 nOldY);

};

/**
* \ingroup client
* \brief ���� ��Ʈ SideView
*/
class CHelpHintSideViewGui : public CSideViewBase, RWS::CEventHandler
{
protected:
	gui::CStaticBox*	m_pHelpHintTitle;
	gui::CStaticBox*	m_pHelpHintText;
	gui::CButton*		m_pCloseButton;
	gui::CButton*		m_pOpenButton;

	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotOpenButtonClicked;
	gui::CSlot			m_slotCloseButtonClicked;

	sHELP_TBLDAT*		m_pHelpHintData;
	CWindowby3			m_BackPanel;

public:
	CHelpHintSideViewGui(const RwChar* pName);
	virtual ~CHelpHintSideViewGui();

	RwBool			Create();
	void			Destroy();

	void			HandleEvents(RWS::CMsg& msg);

	void			OnPaint();
	void			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	void			OnOpenButtonClicked(gui::CComponent* pComponent);
	void			OnCloseButtonClicked(gui::CComponent* pComponent);
	
	virtual void	OnPressESC();
	virtual void	OnSideViewOpen(const void* pData);
	virtual void	OnSideViewClose();
	virtual void	OnSideViewLocate(const CRectangle& rectSideIcon);

	void			ShowHelpHint(sHELP_TBLDAT* pTableData);	
};

/**
* \ingroup client
* \brief Html or Flash ����
*/
class CGuideHintSideViewGui : public CSideViewBase, RWS::CEventHandler
{
protected:
	enum eGUIDE_ALIGN_VERTICAL
	{
		GUIDE_LEFT		= 1,
		GUIDE_CENTER	= 2,
		GUIDE_RIGHT		= 3,
	};

	enum eGUIDE_ALIGN_HORIZONTAL
	{
		GUIDE_TOP		= 1,
		GUIDE_MIDDLE	= 2,
		GUIDE_BOTTOM	= 3,
	};	

	enum eGUIDE_TYPE
	{
		GUIDE_FLASH		= 1,
		GUIDE_HTML		= 2,		
	};

protected:
	gui::CButton*		m_pCloseButton;
	gui::CHtmlBox*		m_pHtmlBox;
	gui::CFlash*		m_pFlash;

	gui::CSlot			m_slotCloseButtonClicked;

	sGUIDE_HINT_TBLDAT*	m_pGuideHintData;

public:
	CGuideHintSideViewGui(const RwChar* pName);
	virtual ~CGuideHintSideViewGui();

	RwBool			Create();
	void			Destroy();
	void			Update(RwReal fElapsed);

	void			HandleEvents(RWS::CMsg& msg);

	void			OnCloseButtonClicked(gui::CComponent* pComponent);

	virtual void	OnPressESC();
	virtual void	OnSideViewOpen(const void* pData);
	virtual void	OnSideViewClose();
	virtual void	OnSideViewLocate(const CRectangle& rectSideIcon);

	void			SetDialog(const eGUIDE_TYPE& eGuideType);
	void			OpenFlashBox(sGUIDE_HINT_TBLDAT* pTableData);
	void			OpenHtmlBox(sGUIDE_HINT_TBLDAT* pTableData);
};

/**
* \ingroup client
* \brief ���ڿ� �˸��� ��Ʈ SideView
*/

// �˸� �޽����� �� ���� �ð�
#define dSTRING_HINT_LIFE_TIME		5.0f

class CStringHintSideViewGui : public CSideViewBase, RWS::CEventHandler
{
protected:
	gui::CStaticBox*	m_pStringHintTitle;
	gui::CStaticBox*	m_pStringHintText;
	gui::CButton*		m_pCloseButton;
	
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotCloseButtonClicked;

	CWindowby3			m_BackPanel;

	RwReal				m_fCurrentTime;
	RwReal				m_fLifeTime;
	RwBool				m_bNotifyShow;

public:
	CStringHintSideViewGui(const RwChar* pName);
	virtual ~CStringHintSideViewGui();

	RwBool			Create();
	void			Destroy();

	void			HandleEvents(RWS::CMsg& msg);
	void			Update(RwReal fElapsed);

	void			OnPaint();
	void			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	void			OnCloseButtonClicked(gui::CComponent* pComponent);

	virtual void	OnPressESC();
	virtual void	OnSideViewOpen(const void* pData);
	virtual void	OnSideViewClose();
	virtual void	OnSideViewLocate(const CRectangle& rectSideIcon);

	void			StartStringHint();
	void			EndStringHint();

	void			ShowStringHint(const WCHAR* pwcTitle, const WCHAR* pwcText);	
};