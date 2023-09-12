#pragma once

#include "NtlPLGui.h"
#include "ceventhandler.h"
#include "NtlSLEvent.h"

/**
 * \ingroup Client
 * \brief Ŀ�´�Ƽ Ÿ�� ������ GUI
 * \date 2007-12-26
 * \author agebreak
 */
class CCommuTargetGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	CCommuTargetGui(void);
	CCommuTargetGui(const RwChar* pName);
	virtual ~CCommuTargetGui(void);

	VOID		Init();
	RwBool		Create();
	VOID		Destroy();	
	RwInt32		SwitchDialog(bool bOpen);

	// Event
	VOID		HandleEvents(RWS::CMsg &pMsg);

protected:
    VOID        OnEventTargetSelect(SNtlEventCommuTargetSelect* data);
    VOID        OnEventTargetRelease();

protected:
    gui::CStaticBox*    m_pSttName;                     ///< Ÿ�� �̸� ǥ�� 
    gui::CStaticBox*    m_pSttType;                     ///< Ÿ�� ���� ǥ�� (ģ��,���...)

    SNtlEventCommuTargetSelect     m_currTarget;

};	
