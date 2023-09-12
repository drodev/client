////////////////////////////////////////////////////////////////////////////////
// Name: class gui::CGlobalComponent
// Desc: GUI Library���������Ǵ� Component ����. 
//		 Phase�� ������� �������� �����Ǿ��� Component�� ����.	
//			 
// 2006.03.6 Peessi@hitel.net   
//
// To Be Desired: 
////////////////////////////////////////////////////////////////////////////////

#ifndef __GUI_GLOBALCOMPONENT_H__
#define __GUI_GLOBALCOMPONENT_H__

START_GUI

class CGlobalComponent
{
public:
//! Destructor:
	~CGlobalComponent(VOID);

//! Attributes:
	static CGlobalComponent* GetInstance();

//! Operations:
	VOID SetToolTip( CToolTip* pToolTip );	// ����!! : new�� ������ �����͸� �Ѱܾ� �Ѵ�.
	VOID SetToolTip( std::string strName );	// ����!! : CreateComponent�� ����Ǿ�� �Ѵ�.
	CToolTip* GetToolTip() { return m_pToolTip; }
	
	VOID CreateComponent( std::string rsrFile, std::string srfFile, std::string frmFile, 
						  CResourceManager* pRsrMgr, CSurfaceManager* pSrfMgr, CComponentManager* pFrmMgr,
						  CComponent* pGuiMgr );
	VOID DeleteComponent(VOID);

protected:
//! Variables:
	CToolTip*		m_pToolTip;
	COMPPAGE_HANDLE m_hComponentPage;

	CResourceManager*	m_pRsrMgr;
	CSurfaceManager*	m_pSrfMgr;
	CComponentManager*	m_pFrmMgr;
	CComponent*			m_pGuiMgr;

	std::string			m_strRsr;
	std::string			m_strSrf;
	
//! Etc:
	CGlobalComponent(VOID);				
	CGlobalComponent( CGlobalComponent& copy );
};

static CGlobalComponent* GetGlobalComponent(VOID)
{
	return CGlobalComponent::GetInstance();
}

END_GUI

#endif//__GUI_GLOBALCOMPONENT_H__