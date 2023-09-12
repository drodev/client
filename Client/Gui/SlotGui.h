/******************************************************************************
* File			: CSlotGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2006. 8. 1
*****************************************************************************
* Desc			: Slot�� ǥ���ϱ� ���� Ŭ����
*****************************************************************************/

#pragma once

#include "NtlItem.h"
#include "rectangle.h"
#include "SurfaceGui.h"
#include "gui_texture.h"
#include "gui_staticbox.h"
#include "gui_surface.h"
#include "DialogDefine.h"


class CNtlSobItem;
class CNtlSobItemAttr;
class CNtlSobBuff;

struct sTBLDAT;
struct sITEM_TBLDAT;
struct sSKILL_TBLDAT;
struct sHTB_SET_TBLDAT;
struct sITEM_OPTION_TBLDAT;


//////////////////////////////////////////////////////////////////////////
//	CSlotGui : Slot�� Display�� ����
//////////////////////////////////////////////////////////////////////////

// Slot display style
#define SDS_NONE			0x00000000
#define	SDS_COUNT			0x00000001	///< Display number
#define SDS_LOCK			0x00000002	///< Use prohibited image
#define SDS_DISABLE			0x00000004	///< Use images that are not available because the current conditions are not right


class CSlotGui
{
public:
	CSlotGui();
	virtual ~CSlotGui();

	RwBool			Create(gui::CComponent *pParent, RwUInt32 iOwnerDialog, DWORD dwSlotStyle = SDS_NONE);
	VOID			Destroy();
	VOID			Clear();

	RwBool			SetIcon(const RwChar* pcIconName);	
		
	VOID			SetSize(RwInt32 iSize);
	VOID			SetAlpha(RwUInt8 byAlpha);
	VOID			SetParentPosition(int iX, int iY);
	VOID			SetPosition_fromParent(int iX, int iY);
	
	RwInt32			GetX_fromParent();
	RwInt32			GetY_fromParent();
	RwInt32			GetParentX();
	RwInt32			GetParentY();

	RwInt32			GetWidth();
	RwInt32			GetHeight();
	

	VOID			SetClippingRect( CRectangle& rtClipping );
	VOID			SetClippingMode( RwBool bMode );

	gui::CTexture*	GetTexture();
	RwUInt32		GetOwnerDialog();

	VOID			SetCount(RwUInt32 iCount);
	RwUInt32		GetCount();

	VOID			ClickEffect(RwBool bClick);
	VOID			ShowDisable(RwBool bShow);
	VOID			ShowLock(RwBool bShow);

	RwBool			IsShowDisable();
	RwBool			IsShowLock();
	RwBool			IsClippingMode();
	RwBool			PtInRect(RwInt32 iX, RwInt32 iY);

	VOID			Paint(bool bRenderTop = false);

protected:		
	gui::CStaticBox*	m_pCount;

	CSurfaceGui			m_srfIcon;
	CSurfaceGui			m_srfLock;
	CSurfaceGui			m_srfDisable;
	
	DWORD				m_dwSlotStyle;
	RwUInt32			m_uiOwnerDialog;

	RwInt32				m_iParentX;			///< �θ� �������� X ��ġ
	RwInt32				m_iParentY;			///< �θ� �������� Y ��ġ

	RwInt32				m_iX_fromParent;
	RwInt32				m_iY_fromParent;

	RwInt32				m_iWidth;
	RwInt32				m_iHeight;

	RwBool				m_bClipping;
	RwBool				m_bShowLock;
	RwBool				m_bShowDisable;

	RwUInt32			m_uiStackCount;		///< ����
};



//////////////////////////////////////////////////////////////////////////
//	CRegularSlotGui : �Ϲ����� Slot ������ ����
//////////////////////////////////////////////////////////////////////////

enum eREGULAR_SLOT_TYPE
{
	REGULAR_SLOT_ITEM_NOT_IDENTIFICATION,			///< (Sob �������� �ƴ�)��Ȯ�� ������
	REGULAR_SLOT_ITEM_TABLE,						///< Item Table���� ������
	REGULAR_SLOT_ITEM_SOB,							///< Sob Item
	REGULAR_SLOT_ITEM_SOB_NOT_IDENTIFICATION,		///< Sob ��Ȯ�� ������
	REGULAR_SLOT_SKILL_TABLE,						///< Skill table�� ��ų
	REGULAR_SLOT_SIMPLE_ICON,						///< �ܼ��� ������
	REGULAR_SLOT_HTBSKILL_TABLE,					///< HTB table�� HTB��ų

	INVALID_REGULAR_SLOT_TYPE
};


// Slot function flag
#define SFF_NONE							0x00000000
#define SFF_USE_ITEM_OPTION_TABLE			0x00000001	///< Item option table�� ����Ѵ�(REGULAR_SLOT_ITEM_TABLE, REGULAR_SLOT_ITEM_SOB�� ��쿡�� ����)


class CRegularSlotGui : public CSlotGui
{
public:
	CRegularSlotGui();
	virtual ~CRegularSlotGui();

	RwBool			Create(gui::CComponent *pParent, RwInt32 iOwnerDialog, eREGULAR_SLOT_TYPE eSlotType, RwUInt32 uiSlotStyle = SDS_NONE);
	VOID			Destroy();

	VOID			Clear();

	RwBool			SetIcon(RwUInt32 uiSerial, RwUInt32 uiCount = 1);
	RwBool			SetIcon(const RwChar* pcText, RwUInt32 uiCount = 0);
	RwBool			SetIcon(eREGULAR_SLOT_TYPE eSlotType, RwUInt32 uiSerial, RwUInt32 uiCount = 1);
	RwBool			SetIcon(eREGULAR_SLOT_TYPE eSlotType, const RwChar* pcText, RwUInt32 uiCount = 0);

	VOID			SetCount(RwUInt32 uiCount);

	VOID			SetPrice(RwUInt32 uiPrice);
	RwUInt32		GetPrice();

	RwBool			SetSerialType(eREGULAR_SLOT_TYPE eSlotType);
	eREGULAR_SLOT_TYPE	GetSerialType();

	RwUInt32				GetSerial();
	CNtlSobItem*			GetSobItem();						///< SobItem ������ ��ȯ�Ѵ�.(Sob��ȣ�� �ƴ϶�� NULL)
	CNtlSobItemAttr*		GetSobItemAttr();					///< SobItemAttr ������ ��ȯ�Ѵ�.(Sob��ȣ�� �ƴ϶�� NULL)
	sITEM_TBLDAT*			GetItemTable();
	sSKILL_TBLDAT*			GetSkillTable();
	sHTB_SET_TBLDAT*		GetHTBSkillTable();
	sITEM_OPTION_TBLDAT*	GetItemOptionTable();

	RwBool			IsOnlyUsableIcon();

	VOID			Paint(bool bRenderTop = false);

protected:
	eREGULAR_SLOT_TYPE		m_eSlotType;
	DWORD					m_dwFunctionFlag;
	RwUInt32				m_uiSerial;
	RwBool					m_bOnlyUsableIcon;
	RwUInt32				m_uiPrice;

	CNtlSobItem*			m_pSobItem;			///< SobItem Information (NULL if not Sob)
	CNtlSobItemAttr*		m_pSobItemAttr;		///< SobItemAttr ����(Sob��ȣ�� �ƴ϶�� NULL)
	sTBLDAT*				m_pTBLDAT;			
	sITEM_OPTION_TBLDAT*	m_pITEM_OPTION_TBLDAT;
};