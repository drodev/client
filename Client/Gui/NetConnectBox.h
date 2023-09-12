///******************************************************************************
//* File			: NetConnectBox.h
//* Author		: Hong SungBock
//* Copyright		: (��)NTL
//* Date			: 2007. 1. 4
//* Update		: 2007. 10. 15
//* Abstract		: network connect ���� box
//*****************************************************************************
//* Desc			: CNetConnectBox
//*****************************************************************************/
//
//#pragma once
//
//// core
//#include "ceventhandler.h"
//
//// gui
//#include "gui_button.h"
//
//// presentation
//#include "NtlPLGui.h"
//
//// dbo
//#include "DboDef.h"
//#include "Windowby3.h"
//
//class CNetConnectBox : public CNtlPLGui , public RWS::CEventHandler
//{
//public:
//	CNetConnectBox(const RwChar* pName);
//	virtual ~CNetConnectBox();
//
//	RwBool		Create();
//	VOID		Destroy();
//	VOID		Update(RwReal fElapsed);
//
//protected:
//	CNetConnectBox() {}
//	VOID			HandleEvents( RWS::CMsg &msg );	
//	
//	VOID			CalcBoxSize();				///< �־��� �޼����� �´� �ڽ��� �����
//	VOID			SetText();
//	VOID			ProcessCancel();
//	VOID			SwitchDialog(bool bSwitch);
//
//	VOID			OnClickedOkButton(gui::CComponent* pComponent);
//	VOID			OnClickedCancelButton(gui::CComponent* pComponent);	
//	VOID			OnPaint();	
//
//protected:
//
//	gui::CSlot			m_slotPaint;
//	gui::CSlot			m_slotOk;
//	gui::CSlot			m_slotCencle;
//
//	CWindowby3			m_Backboard;			///< ��� 
//	CWindowby3			m_Panel;				///< ���� ��� Ʋ
//
//	gui::CButton*		m_pOkBtn;
//	gui::CButton*		m_pCancelBtn;
//
//	gui::CStaticBox*	m_pMessage;				///< �޼��� ����
//
//	std::wstring		m_wstrString;			///< ���� �޼���
//	RwUInt8				m_byMsgBoxType;			///< �޼��� �ڽ� ��� Ÿ��
//	RwUInt32			m_uiMsgProcessType;		///< �޼��� ó�� Ÿ��
//	RwReal				m_fRemainTime;			///< ������Ʈ Ÿ��
//	sMsgBoxData			m_ExData;				///< �޼��� Ȯ�� ����Ÿ
//
//	RwBool				m_bRemainTime;			///< �޼��� �ڽ��� �����ִ� ���� �ð��� �ִ��� ����
//	const WCHAR*		m_pwcText;				///< �������� �����־��� ��Ʈ�� ���̺� �ε���
//};