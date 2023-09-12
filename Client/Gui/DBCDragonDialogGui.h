#pragma once

#include "NtlDebug.h"
#include "NtlPLGui.h"
#include "ceventhandler.h"

class CTextTable;

// ��ǳ���� �̷�� ����ü
struct SDragonDialog
{
	gui::CPanel*		m_pPanel;
	gui::CStaticBox*	m_pStatic;
	RwReal				m_fLifeTime;

	SDragonDialog()
	{
		m_pPanel = NULL;
		m_pStatic = NULL;
		m_fLifeTime = 0.0f;
	}

	void Show(RwBool bShow)
	{
		m_pPanel->Show(B2b(bShow));
		m_pStatic->Show(B2b(bShow));
	}

	void SetAlpha(RwReal fAlpha)
	{
		BYTE byAlpha = (BYTE)(fAlpha * 255.0f);
		m_pPanel->SetAlpha(byAlpha);
		m_pStatic->SetAlpha((UCHAR)byAlpha);
	}

	void SetPosition(RwInt32 x, RwInt32 y)
	{
		m_pPanel->SetPosition(x, y);
		m_pStatic->SetPosition(x, y);
	}
};

/**
* \ingroup Client
* \brief ����� ��ȭ(��ǳ��)�� ǥ���ϴ� GUI Ŭ����
* \date 2007-07-6
* \author agebreak
*/
class CDBCDragonDialogGUI : public CNtlPLGui, public RWS::CEventHandler
{
public:
	enum EDialogType			///< ���̾�α��� Ÿ��
	{
		E_DIALOG_NORMAL,
		E_DIALOG_WARN,

		DIALOG_COUNT,
	};

public:
	CDBCDragonDialogGUI(void);
	CDBCDragonDialogGUI(const RwChar* pName);
	virtual ~CDBCDragonDialogGUI(void);

	VOID		Init();
	RwBool		Create();
	VOID		Destroy();
	VOID		Update(RwReal fElapsed);	

	// Event
	VOID		HandleEvents(RWS::CMsg &pMsg);

	VOID		SetText(RwInt32 nTblIdx, EDialogType eDialogType = E_DIALOG_NORMAL);					///< ��� ��ȭ ���̺� �ε����� ��ȭ�� ǥ���Ѵ�.
	VOID		SetText(std::wstring& strWString, EDialogType eDialogType = E_DIALOG_NORMAL);		///< �ؽ�Ʈ�� ǥ���Ѵ�.	
	VOID		ShowNormalDialog(RwBool bShow);				///< �Ϲ� ���â ǥ�� ������ �����Ѵ�.

	static		CDBCDragonDialogGUI* GetInstance();			///< �̱��� Instance�� ��ȯ�Ѵ�.
	static		void				 DeleteInstance();		///< �̱��� Instance�� �����Ѵ�.

protected:	
	void		AdjustDialog();								///< UI�� ��ġ�� �����Ѵ�.    

protected:
	static		CDBCDragonDialogGUI* m_pInstance;			///< �̱��� �ν��Ͻ�

	SDragonDialog	m_SDragonDialog[DIALOG_COUNT];			///< ����� ��ȭ�� ǥ���� ��ǳ�� ����ü
	CTextTable*		m_pDragonTextTable;						///< ����� ��ȭ ���̺�		
	RwBool			m_bDelete;
    
};	
