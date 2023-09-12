#pragma once

// core
#include "ceventhandler.h"
#include "NtlSLEvent.h"

// presentation
#include "NtlPLGui.h"

// dbo
#include "SideIconGui.h"

/**
 * \ingroup Client
 * \brief PC�� NetPy ����/�˸��� ������ ���̵� ������
 *
 * \date 2009-04-20
 * \author agebreak
 */
class CNetPySideIconGui : public CSideIconBase, public RWS::CEventHandler
{
public:
    CNetPySideIconGui(const RwChar* pName);
    virtual ~CNetPySideIconGui(void);

    RwBool		Create();
    VOID		Destroy();

    virtual VOID	OnIconButtonClicked(gui::CComponent* pComponent);
    virtual VOID	OnSideViewClosed();
    virtual void	Show(bool bShow);

protected:
    virtual VOID	HandleEvents( RWS::CMsg &msg );
    void            OnMouseEnter(gui::CComponent* pComponent);
    void            OnMouseLeave(gui::CComponent* pComponent);

protected:
    gui::CSlot      m_slotNetPyBtn;
    gui::CSlot      m_slotNetPyMouseEnter;
    gui::CSlot      m_slotNetPyMouseLeave;
    gui::CButton*   m_pBtnNetPy;
    RwBool          m_bNetmarbleMemberShip;
};
