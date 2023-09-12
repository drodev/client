/******************************************************************************
* File			: PortalGui.h
* Author		: agebreak
* Copyright		: (��)NTL
* Date			: 2007. 10. 22
* Abstract		: 
*****************************************************************************
* Desc			: CPortalGui
*                 ��Ż NPC�� Ŭ���ϸ� ������ Portal GUI
*                 ��Ż�ʿ��� ���� ���� ��Ҹ� Ŭ���ϸ� �����̵� �ȴ�.
*				  
*****************************************************************************/

#pragma once

#include "ceventhandler.h"
#include "surfaceGui.h"


class SNtlEventPortalInfoRes;


//The type of icon to be used in the Portal UI
enum EPortalIconType
{
    E_PORTAL_ICON_START_POINT,                      ///< Icon to display the current point
    E_PORTAL_ICON_START_POINT_FOCUS,

    E_PORTAL_ICON_CAMP_ENABLE,                           ///< Currently movable icon (camp)  
    E_PORTAL_ICON_CAMP_ENABLE_FOCUS,

	E_PORTAL_ICON_TOWN_ENABLE,                           ///< Currently movable icon (town)  
	E_PORTAL_ICON_TOWN_ENABLE_FOCUS,

    MAX_ICON_TYPE_CNT,

	MAX_ICON_TYPE_NOT,
};

/// Structure to pass when displaying portal tooltips
struct SPortalTooltip
{
    RwUInt32 nPortalID;
    RwInt32  ePortalIconType;
    DWORD    nZenny;
};

// Status by Portal (The ID of the portal is the key value of the map.)
struct SPortalInfo
{
    RwInt32             m_nIndex;           ///< ID of Portal
    CSurfaceGui         m_surIcon;          ///< Surface to display ICon
    EPortalIconType     m_eIconType;        ///< Current portal status and icon type
    DWORD               m_nZenny;           ///< Consumer zeni (0 if you can not go)  
    RwBool              m_bRegist;          ///< Whether it is registered
	bool				m_bCamp;		// true = camp, false = town
	RwUInt32			worldId;
};

class CPortalGui : public CNtlPLGui, public RWS::CEventHandler
{
	#define FEARLAND_ID 14

	enum EPortalSearch
	{
		E_PORTAL_SEARCH_WORLD,
		E_PORTAL_SEARCH_FEARLAND,

		E_PORTAL_SEARCH_COUNT,
	};

	enum EPortalGrade
	{
		E_PORTAL_GRADE_CAMP = 1,
		E_PORTAL_GRADE_TOWN,
	};

public:
    CPortalGui(const RwChar* pName);
    ~CPortalGui();

    RwBool      Create();
    VOID        Destroy();
    RwInt32     SwitchDialog(bool bOpen);                   ///< DialogManager������ Open/Close

protected:
    VOID        HandleEvents(RWS::CMsg &pMsg);
    VOID        Init();    
    
    VOID        SetupPortalInfo();                          ///< ��Ż���� �������� �����Ѵ� (���ʿ� �ѹ��� ȣ��)
    VOID        UpdatePortalInfo();                         ///< ��Ż���� �������� ������Ʈ�Ѵ�.
    RwBool      CheckRegist(RwUInt32 hNPCSerialID);         ///< ���� ��Ż ����Ʈ�� ��ϵǾ� �ִ� �������� üũ�ϰ�, ��ϵǾ� ���������� ����Ѵ�.    
    RwBool      IsConnect(RwUInt32 nPortalID, DWORD& nZenny);    ///< ���� ����Ʈ�� ����Ǿ� �ִ� ����Ʈ���� Ȯ���Ѵ�. (��ϵǾ� ������ True�� �ʿ� Zenny�� ��ȯ�Ѵ�)

    RwInt32     FindPointIndex(RwUInt32 nCurrPortalID, RwUInt32 nTargetPortalID); ///< Ÿ�� ��Ż�� ��������Ʈ������ �ε����� ã�Ƽ� ��ȯ�Ѵ�. 

	void		SetCurrentPortalIndex(RwUInt32 hNPCSerialID);
	void		SetWorldMapSurface();

	bool		HasPortalRegistered(BYTE portalid); // if avatar has portal registered

	void		UpdatePortalIcon(); // shows portal icons from current selected map

    inline RwBool      IsRegist(RwUInt32 nPortalID);               ///< ���� ��ϵǾ� �ִ��� Ȯ���Ѵ�.;

    // CallBack
    VOID        OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
    VOID        OnMouseUp(const CKey& key);    
    VOID	    OnPaint();
    VOID	    OnClickExitBtn(gui::CComponent* pComponent);    

	VOID		OnSearchWorldSelect(INT nIndex);
	VOID		OnSearchWorldToggled(RwBool bToggled, gui::CComponent* pComponent);

protected:
    typedef     std::map<RwUInt32, SPortalInfo*>  MAPPortalInfo;    
    typedef     std::pair<RwUInt32, SPortalInfo*> PAIRPortalInfo;

    MAPPortalInfo m_mapPortalInfo;                          ///< Maps with information on portals

	int			m_nCurrentWorldSearch;

    RwInt32     m_nCurrIdx;                                 ///< Index of current portal
    RwInt32     m_nSelectIdx;                               ///< The index of the portal currently selected (with the cursor at the top).
    RwUInt32    m_hNPCSerialID;                             ///< NPC handle 
    RwBool      m_bTeleportSuccess;                         ///< Successful Teleport

	RwUInt32    m_hNPCPortalAddSerialID;
    
    gui::CSurface	m_aSurIcon[MAX_ICON_TYPE_CNT];        ///<Surfaces to be used for icons

    // Control
    gui::CButton*	m_pBtnExit; 


	gui::CSurface	m_srfPortalMap[E_PORTAL_SEARCH_COUNT];


    // Icon Legend Text
	gui::CStaticBox* m_pSttStartPoint;
	gui::CPanel*	m_ppnlStartPoint;

	gui::CPanel*	m_ppnlTownPoint;
	gui::CPanel*	m_ppnlCampPoint;

	gui::CStaticBox* m_pSttEnablePoint;

	gui::CComboBox* m_pcbbSearchWorld;

    // slot
    gui::CSlot  m_slotMouseMove;
    gui::CSlot  m_slotMouseUp;
    gui::CSlot  m_slotPaint;
    gui::CSlot  m_slotBtnExit;

	gui::CSlot  m_slotSearchWorldSelect;
	gui::CSlot  m_slotSearchWorldToggled;
};
