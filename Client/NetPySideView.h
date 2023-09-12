#pragma once

// core
#include "ceventhandler.h"

// presentation
#include "NtlPLGui.h"

// dbo
#include "Windowby3.h"
#include "SideIconGui.h"
#include "DBOEvent.h"
    
/**
 * \ingroup Client
 * \brief NetPy ������ ǥ���ϴ� Side View
 *
 * \date 2009-04-20
 * \author agebreak
 */
class CNetPySideViewGui : public CSideViewBase, public RWS::CEventHandler
{
public:
    enum ENetPySideViewHeight
    {
        NETPY_SIDEVIEW_HEIGHT_NORMAL = 60,
        NETPY_SIDEVIEW_HEIGHT_PCBANG = 140,
        NETPY_SIDEVIEW_HEIGHT_NFY    = 60,
    };

public:
    CNetPySideViewGui(const RwChar* pName);
    virtual ~CNetPySideViewGui(void);

    RwBool		Create();
    VOID		Destroy();
    VOID		Update(RwReal fElapsed);

    virtual VOID	OnPressESC();
    virtual VOID	OnSideViewOpen(const void* pData);
    virtual VOID	OnSideViewClose();
    virtual VOID	OnSideViewLocate(const CRectangle& rectSideIcon);	

protected:
    virtual VOID	HandleEvents( RWS::CMsg &msg );
    VOID			LocateComponent();
    VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
    VOID			OnResize( RwInt32 iOldW, RwInt32 iOldH );
    VOID			OnPaint();

    VOID            SetState(eNetPySideViewType type);
    VOID            OnShowInfo();           ///< ���� NetPy ������ ����Ѵ�
    VOID            OnShowNotify();         ///< NetPy ���� ������ ����Ѵ�. 

protected:
    CWindowby3			m_BackPanel;		///< ���
    eNetPySideViewType  m_type;             ///< ���� �������� Ÿ��

    gui::CSlot			m_slotPaint;
    gui::CSlot			m_slotMove;
    gui::CSlot			m_slotResize;

    // ���� NetPy ����
    gui::CStaticBox*    m_pstbRemainTimeTitle;
    gui::CStaticBox*    m_pstbRemainTimeData;    
    gui::CStaticBox*    m_pstbGetTitle;
    gui::CStaticBox*    m_pstbGetData;    
    gui::CStaticBox*    m_pstbCurrentTitle;
    gui::CStaticBox*    m_pstbCurrentData;   

    // NetPy ȹ�� ����
    gui::CStaticBox*    m_pstbGetPoint;

    SDboEventUpdateNetPy m_UpdateNetPyInfo;                 ///< ������ ���� ���� NetPy ������Ʈ ����
    DWORD                m_dwUpdateNetPyPoint;              ///< ȹ�� ����Ʈ
    RwReal               m_fRemainTime;                     ///< ���� NetPy ȹ������� ���� �ð�
    RwReal               m_fNotifyShowTime;                 ///< Notify ǥ�� �ð�    
    RwBool               m_bIsPCBang;                       ///< PC�������� �Ǵ��Ѵ�.
};
