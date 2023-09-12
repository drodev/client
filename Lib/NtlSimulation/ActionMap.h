/*****************************************************************************
* File			: ActionMap.h
* Author		: Haesung, Cho
* Copyright		: (��)NTL
* Date			: 2007. 9. 20
* Abstract		: Action Map
*****************************************************************************
* Desc			: �׼Ǹ��� �ڷᱸ���� �����ϰ� �׼Ǹ��� �Ŵ����� �ۼ��Ѵ�.
* History  -----
* 2008.  2. 22	: �����丵, ������ �׼Ǹ� ��Ŀ��� �ڷᱸ���� �Ŵ����� �и�( �Ӽ� �߰� )
*****************************************************************************/

#ifndef __ACTION_MAP_H__
#define __ACTION_MAP_H__

// Simulation
#include "NtlActionMapDef.h"
#include "InputHandler.h"

// shared
#include "NtlCharacter.h"

#include <map>
#include <vector>
#include <set>

class CActionMapManager;

/**
* \ingroup simulation
* \brief NTL ActionMap�� �ڷᱸ��
*/
class CActionMap
{
public:
	// ������ & �Ҹ���
	CActionMap(void);
	CActionMap( CActionMapManager* pManager );
	CActionMap(const CActionMap& rhs);
	~CActionMap(void);

	WORD	FindAction( WORD wKey );			// Key ������ Action�� ã�´�.
	WORD	FindKey( WORD wAction );			// Action ���� Key�� ã�´�.

	BYTE			SetAction( WORD wKey, WORD wAction );	// Ű�� ����
	VOID			SetLastReleaseAction( WORD wOldAction );
	WORD			GetLastReleaseAction();

	VOID			Clear();									// ActionMap�� �ʱ�ȭ�Ѵ�.
	VOID			ClearReleaseAction();

	VOID			CaptureMap( CActionMap* pCaptureMap );
	VOID			RestoreMap( CActionMap* pCaptureMap );
	BOOL			CheckMap( ACTIONMAP& mapCapture );

	ACTIONMAP&		GetActionMap()							{	return m_mapAction;	}
	ACTIONMAP&		GetKeyMap()							{	return m_mapKey;	}

	CActionMap& operator=(const CActionMap& rhs);				// ������ �����ε�

protected:
	ACTIONMAP		m_mapKey;				// �ڷᱸ�� < ACTION , KEY >
	ACTIONMAP		m_mapAction;			// �ڷᱸ�� < KEY, ACTION >
	ACTIONVEC		m_vecReleaseAction;		// ������ �׼��� ����ϱ� ���� �ڷᱸ��
	CActionMapManager*	m_pManager;	
};

/**
* \ingroup simulation
* \brief NTL ActionMap�� Manager
*/
class CActionMapManager
{
public:
	///< Construction & Destruction
	CActionMapManager(void);
	~CActionMapManager(void);

	///< Create & Destroy
	VOID	Create(VOID);
	VOID	Destroy(VOID);

	///< Basic action map settings (hard-coding)
	VOID	InitDefaultActionMap();

	BYTE	SetSingleKey( BYTE byKey, WORD wAction );		///< Single key setting
	BYTE	SetCombineKey( WORD wKey, WORD wAction );		///< Combination key setting

	WORD	FindAction( WORD wKey );
	WORD	FindKey( WORD wAction );

	WORD	GetInputAction()						{ return m_wInputAction; }
	BOOL	SetInputAction( WORD wAction );					///< Specify input mode
	VOID	ClearInputAction()						{ m_wInputAction = ACTION_INVALID; }

	BYTE	GetLastResult();
	VOID	SetLastResult( BYTE byResult );

	VOID	ClearResult();

	WORD	GetLastReleaseAction()					{ return m_pActionMap->GetLastReleaseAction(); }
	VOID			ClearReleaseAction()			{ m_pActionMap->ClearReleaseAction(); }

	std::wstring	GetKeyName( WORD wAction );

	WORD	InputHandlerDown( BYTE byKey );
	WORD	InputHandlerUp( BYTE byKey, std::list< WORD >& listUpAction );
	void	InputActionDown( WORD wAction );
	void	InputActionUp( WORD wAction );

	void	CheckDownActionWithCombineKey( BYTE byKey, std::list< WORD >& listUpAction );

	void	InputClear();

	VOID	CaptureActionMap();
	VOID	RestoreActionMap();

	void	AddUpdateData(BYTE byType, WORD wActionID, WORD wKey);
	RwBool	GetUpdateData(sSHORTCUT_UPDATE_DATA* pData , BYTE& byCount);

	VOID	ClearActionMap();

	VOID	SetActionMapMode( BYTE byActionMapMode );
	BYTE	GetActionMapMode()					{ return m_byActionMapMode; }
protected:
	WORD	MakeKey( BYTE byKey );
	virtual void	MakeComposition( uNtlKey& uMakeKey );

	VOID	RegisterKeyName(VOID);
	
	VOID	RegisterKeyType(VOID);
	VOID	RegisterActionType(VOID);

public:
	BOOL	IsFixedKey( WORD wKey )				{ return IsMapType( TYPE_FIXED, wKey, m_mapKeyType ); }
	BOOL	IsFixedAction( WORD wAction )		{ return IsMapType( TYPE_FIXED, wAction, m_mapActionType ); }
	BOOL	IsCombineKey( WORD wKey )			{ return IsMapType( TYPE_COMBINE, wKey, m_mapKeyType ); }
	BOOL	IsExclusiveAction( WORD wAction )	{ return IsMapType( TYPE_EXCLUSIVE, wAction, m_mapActionType ); }

	BOOL	IsMapType( int nType, WORD wKeyType, TYPEMAP& mapType );

protected:
	KEYNAMEMAP	m_mapKeyName;
	TYPEMAP		m_mapKeyType;
	TYPEMAP		m_mapActionType;

	typedef std::map< unsigned short, unsigned int > mapdef_InputAction;
	mapdef_InputAction	m_mapInputAction;							///< ���� InputHandlerDown���� ����� Action���� ���� ����Ʈ

	RESULTVEC	m_vecResult;

	WORD		m_wInputAction;										///< Ű �Է��� ���� ���� ACTION_INVALID �̿��� ���� ������ �ִ´�.
	
	CActionMap*		m_pActionMap;									///< Ŭ���̾�Ʈ���� ���Ǵ� ActionMap
	CActionMap*		m_pCaptureMap;									///< ������ ����� ���� ������ �ִ´�.
	CActionMap*		m_pDefaultMap;									///< ���� �⺻������ �����Ǵ� ActionMap

	sSHORTCUT_UPDATE_DATA	m_asUpdateData[NTL_SHORTCUT_MAX_COUNT];	///< ����� ������ �����ϴ� �迭
	BYTE					m_byUpdateCount;						///< Ű�� ��������� ������	

	BYTE					m_byActionMapMode;						///< ACTIONMAP�� ��� ���
	
};

#endif // __ACTION_MAP_H__