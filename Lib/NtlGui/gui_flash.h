////////////////////////////////////////////////////////////////////////////////
// Name: class gui::CFlash
// Desc: Flash
//
// 2007.07.16 Peessi@hitel.net   - 
//
////////////////////////////////////////////////////////////////////////////////
#ifndef __GUI_FLASH_H__
#define __GUI_FLASH_H__

#include "gui_component.h"

START_GUI

class CFlash_Generic;

//: Flash component
class CFlash : public CComponent
{	
public:
	//: Enumuration
	enum eRESIZETYPE { NOSCALE, SHOWALL, EXACTFIT };
	enum eARRAYTYPE { SA_INT, SA_DOUBLE, SA_FLOAT, SA_STRING, SA_WSTRING };

	//: Flash Constructor
	CFlash( CComponent* pParent, CSurfaceManager* pSurfaceManager );
	CFlash( const CRectangle& rtPos, CComponent* pParent, CSurfaceManager* pSurfaceManager, CONST CHAR* pFlashFIleName,
			BOOL bUseFont = FALSE, BOOL bOriginalSize = FALSE, BOOL bScissor = FALSE );	
			// bOriginalSize : �ε��� �������ҽ��� ũ��� ����.
			// bParentScissor : �θ� ���� ��, �ڱ� ���� ������ ������ Ŭ����.
	
	//: Flash Destructor
	virtual ~CFlash(VOID);

	//! Attributes:
	VOID	AutoRewind( BOOL bAutoRewind );
	VOID	SetResizeType( eRESIZETYPE eResizeType );
	VOID	SetUseFont( BOOL bUseFont );

	CRectangle GetFrameResolution(VOID);		// �÷����� ����(�۾�) ũ��
	INT		GetFrameCount(VOID);
	FLOAT	GetFrameRate(VOID);

	DWORD	GetCurrentFrame(VOID);
	VOID	GotoFrame( DWORD dwFrame );

	BOOL	IsPlayMovie(VOID);
	
	VOID	SetFrameCallback( BOOL bSet );
	BOOL	HasFrameCallback(VOID);	

	// ex: SetVariable( "_root._object.width", "60" );
	BOOL	SetVariable( const CHAR* path, const CHAR* pValue );
	BOOL	SetVariable( const CHAR* path, const WCHAR* pValue );
	BOOL	SetVariableFloat( const CHAR* path, FLOAT fValue );
	BOOL	SetVariableArray( eARRAYTYPE type, const CHAR* path, DWORD index, const VOID* pData, DWORD count );

	// ex: GetVariable( "_root._object.x" ); 
	const CHAR*		GetVariable( const CHAR* path );
	const WCHAR*	GetVariableWideStr( const CHAR* path );
	FLOAT			GetVariableFloat( const CHAR* path );
	BOOL			GetVariableArray( eARRAYTYPE type, const CHAR* path, DWORD index, VOID* pData, DWORD count );

	// ex: Invoke( "_root._object.gotoAndPlay", "%s,%d", "on", 1 ); return Null�� �Լ��� ��ã������, "undefine"�� �Լ��� ã������ ���ϰ��� ������.
	const CHAR*		Invoke( const CHAR* path, const CHAR* parameter, ... );

	//! Operations:
	BOOL	Load( CONST CHAR* pFlashFile, BOOL bOriginalSIze = FALSE );	// bOriginalSize : �ε��� �������ҽ��� ũ��� ����.
	VOID	Unload(VOID);

	VOID	Update( FLOAT fElapsedTime );	

	VOID	PlayMovie( BOOL bPlay );
	VOID	RestartMovie(VOID);

	VOID	Rotate( RwInt32 nDegree );			// + : �ð����, - : �ݽð����

	VOID	Show( bool bShow );

	//! Signals	
	CSignal_v1<gui::CComponent*>&			SigMovieEnd(VOID);
	CSignal_v2<const char*,const char*>&	SigFSCallBack(VOID);
	
private:
	//! Implementation:

protected:
	//! Variables
	CFlash_Generic *m_pImpl;

private:
	//! Etc
	CFlash(const CPanel &copy) : CComponent(NULL,NULL) { return; } // disallow copy construction.

	friend class CFlash_Generic;	
};  

END_GUI

#endif
