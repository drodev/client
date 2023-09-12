#ifndef __GUI_SURFACEMANAGER_H__
#define __GUI_SURFACEMANAGER_H__

#include "gui_define.h"
#include "gui_componenttype.h"
#include "gui_surface.h"

START_GUI

class CComponentOptions;
class CSurfaceManager_Generic;
class CResourceManager;
class CSurfacePage;

class CSurfaceManager
{
//! Construction:
public:
	
	CSurfaceManager(CResourceManager *pResourceManager);

	//: component manager �Ҹ���...	
	virtual ~CSurfaceManager();

//! Attributes:
public:

	//: Surface page add
	bool AddPage(const std::string& str);

	//: Surface page remove
	VOID RemovePage(const std::string& str);

	//: script ������� �ʰ�, �������� ������ ��.
	CSurface CreateSurface(const std::string& strTex);

	//: script ������� �ʰ�, �������� ������ ��.
	VOID RemoveSurface(CSurface& surface);

	//: strName => surface name
	//: surface name���� surface�� ������ ��´�.
	CSurface GetSurface(const std::string& strPage,const std::string& strName);

	// Append By Peessi 
	CSurfacePage* GetSurfacePage( const std::string& strFilename );
		
//! Implementation:
private:
	
	CResourceManager *m_pResourceManager;
	
	CSurfaceManager_Generic *m_pImpl;
};

END_GUI



#endif