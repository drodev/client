////////////////////////////////////////////////////////////////////////////////
// File: TBTournamentGui.h
// Desc: õ�����Ϲ���ȸ ����ǥ
//
// 2008.09.25 Peessi@hitel.net   
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __TB_TOURNAMENT_GUI_H__
#define __TB_TOURNAMENT_GUI_H__

#include "NtlPLGui.h"
#include "SurfaceGui.h"
#include "ceventhandler.h"
#include "NtlBudokai.h"
#include "NtlTimeQuest.h"

// ��������
class CTBTournamentFightInfo
{
public:
	//! Enumuration
	enum CHILDSTATE { LEFT_ANIMATION_END = 0x01, RIGHT_ANIMATION_END = 0x02, ENDOFCHILDANIMATION = 0x03 };

	struct stENTRYINFO
	{
		stENTRYINFO::stENTRYINFO(VOID)
		{
			bEntry = FALSE;
			wJoinID = INVALID_WORD;
			byScore = INVALID_BYTE;			
		}

		RwBool			bEntry;
		RwUInt16		wJoinID;
		RwUInt8			byScore;		
	};

	//! Constructor & Destructor
	CTBTournamentFightInfo( CTBTournamentFightInfo* pAboveNode, RwUInt8 byMatchNumber, RwUInt8 byMatchLevel, RwBool bParty );		
	~CTBTournamentFightInfo(VOID);

	//! Operation
	// 1. ���� ��� �޾����� Line������ ä���, �ѹ� ���� ����� �÷��׸� ���ش�.	�ִϸ��̼� �÷��׵� ��~!!
	VOID	SetFightResult( RwUInt8 byMatchResult, RwUInt16 wWinnerJoinID, RwUInt16 wJoinID1, RwUInt16 wJoinID2, RwUInt8 byScore1, RwUInt8 byScore2 );

	// 2. �� ����������, �ؿ��� �ö�� �����ͷ� ä���ش�. 
	VOID	SetEntryData( RwUInt8 byIdx, RwUInt16 wJoinID );

	// 3. �������� ��ư ������ �� ����
	VOID	ClickFightInfo(VOID);

	// 4. �̸� ���
	VOID	ShowNameToInfoWnd( RwUInt8 byTeamPos );
	
	// 4. �ִϸ��̼��� ��������.
	VOID	EndOfAnimation(VOID);

	//! Attribute
	RwUInt8		GetMatchNumber(VOID) { return m_byMatchNumber; }
	RwUInt8		GetMatchLevel(VOID) { return m_byMatchLevel; }
	RwUInt16	GetWinnerID(VOID) { return m_wWinnerTeamJoinID; }
	RwUInt16	GetLeftEntryID(VOID) { return m_stEntry[0].wJoinID; }
	RwUInt16	GetRightEntryID(VOID) { return m_stEntry[1].wJoinID; }
	RwUInt8		GetWinnerPosition(VOID);
	RwBool		IsPartyData(VOID) { return m_bParty; }
	RwBool		IsEnableToStartAnimation(VOID) { return m_stEntry[0].bEntry && m_stEntry[1].bEntry; }

	CTBTournamentFightInfo* GetAboveFightInfo(VOID) { return m_pAboveFightInfo; }

private:
	//! Variable
	// ��ġ ����( � ���° ��� )
	RwUInt8			m_byMatchNumber;	// ���ʺ��� 0��, �����ѹ�
	RwUInt8			m_byMatchLevel;		// ��º��� 0��, �����ѹ�
	// �ִϸ��̼ǵǾ��ϴ� �÷���( ���� ��� 2���� ���� ���� ��ȣ�� �޾ƾ���. �� 2�� �Ǿ�� ��
	RwInt32			m_nEndOfBelowAnimation;	
	// �� �������� ���� ID
	stENTRYINFO		m_stEntry[2];			
	// ���� ���
	RwUInt8			m_byMatchResult;	// eMATCH_RESULT
	RwUInt16		m_wWinnerTeamJoinID;	
	// ���� ��� 
	CTBTournamentFightInfo* m_pAboveFightInfo;
	// ��Ƽ ����ΰ�
	RwBool			m_bParty;	
};

class CTBTournamentInfoGroup
{
public:
	CTBTournamentInfoGroup( RwUInt8 byPosOffset, RwInt32 nEntryCount, RwUInt8 byTopOfDepth, RwUInt8 byEndOfDepth, RwBool bParty, gui::CFlash* pFlash, gui::CStaticBox* pWinnerName, gui::CStaticBox* pWinnerEmblem );
	virtual ~CTBTournamentInfoGroup(VOID);

	VOID	Update( RwReal fElapsed );
	VOID	Show( bool bShow );
	
	virtual	VOID	CreateFightData( RwUInt8 byIndex, CTBTournamentFightInfo* pAboveFightInfo, RwUInt8 byMatchLevel, RwUInt8 byMatchNumber );	
	virtual VOID	SetEntryData( RwUInt8 byIndex, RwUInt16 wJoinID );
	virtual RwBool	SetFightResultData( RwUInt8 byMatchLevel, RwUInt8 byMatchNumber, RwUInt16 wJoinID1, RwUInt16 wJoinID2, 
										RwUInt8 byMatchResult, RwUInt16 wWinnerTeam, RwUInt8 byScore1, RwUInt8 byScore2 );

	CTBTournamentFightInfo*	FindFightInfo( RwUInt8 byMatchLevel, RwUInt8 byMatchNumber );	
	
	CTBTournamentFightInfo*	GetDepthNumberFromFlashArgs( const RwChar* szArgs, RwUInt8* pDepth, RwUInt8* pNumber );
	CTBTournamentFightInfo*	GetDepthNumberTeamFromFlashArgs( const RwChar* szArgs, RwUInt8* pDepth, RwUInt8* pNumber, RwUInt8* pTeam );
	RwBool	IsMyTeamInThisGroup( RwUInt16 wjoinID );
	VOID	DrawLine( RwUInt8 byDepth, RwUInt8 byNumber, RwUInt8 byPos );
	VOID	FocusMyEntry( RwUInt8 byDepth, RwUInt8 byNumber, RwUInt8 byPos );

protected:
	//! CallBack
	VOID	OnFSCallBack( const RwChar* szCommand, const RwChar* szArgs );

	gui::CSlot				m_slotFSCallBack;

	//! Variable
	CTBTournamentFightInfo**	m_ppFightInfo;
	RwInt32						m_nFightInfoCount;	
	RwInt32						m_nEntryCount;

	RwUInt8						m_byPosOffset;			
	RwUInt8						m_byEndOfDepth;
	RwUInt8						m_byTopOfDepth;
	RwBool						m_bParty;

	gui::CFlash*				m_pFlash;
	gui::CStaticBox*			m_pWinnerName;
	gui::CStaticBox*			m_pWinnerEmblem;
};

class CTBTournamentFinalInfoGroup : public CTBTournamentInfoGroup
{
public:
	enum NAMEINDEX { SEMIFINAL1_LEFT, SEMIFINAL1_RIGHT, SEMIFINAL2_LEFT, SEMIFINAL2_RIGHT, FINAL_LEFT, FINAL_RIGHT, NUM_NAME };
	CTBTournamentFinalInfoGroup( RwUInt8 byPosOffset, RwInt32 nEntryCount, RwUInt8 byTopOfDepth, RwUInt8 byEndOfDepth, RwBool bParty, gui::CFlash* pFlash, gui::CStaticBox* pWinnerName, gui::CStaticBox* pWinnerEmblem );
	virtual ~CTBTournamentFinalInfoGroup(VOID);

	virtual VOID	CreateFightData( RwUInt8 byIndex, CTBTournamentFightInfo* pAboveFightInfo, RwUInt8 byMatchLevel, RwUInt8 byMatchNumber );
	virtual VOID	SetEntryData( RwUInt8 byIndex, RwUInt16 wJoinID ) { /* Do Nothing */ }
	virtual RwBool	SetFightResultData( RwUInt8 byMatchLevel, RwUInt8 byMatchNumber, RwUInt16 wJoinID1, RwUInt16 wJoinID2, 
										RwUInt8 byMatchResult, RwUInt16 wWinnerTeam, RwUInt8 byScore1, RwUInt8 byScore2 );
	VOID	SetFinalEntryData( NAMEINDEX eNameIndex, const WCHAR* szName );

protected:
	//! CallBack
	VOID	OnFinalFSCallBack( const RwChar* szCommand, const RwChar* szArgs );

	gui::CSlot			m_slotFinalFSCallBack;

	//! Variable
	gui::CStaticBox*	m_pName[NUM_NAME];	
	gui::CStaticBox*	m_pEmblem[NUM_NAME];
};

class CTBTournamentGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	//! Enumuration
	enum ePage { TOURNAMENT_INDIVIDUAL_A, TOURNAMENT_INDIVIDUAL_B, TOURNAMENT_INDIVIDUAL_FINAL, TOURNAMENT_PARTY, NUM_PAGE, INVALID_PAGE = 0xFFFFFFFF };

	//! Constructor & Destructor
	CTBTournamentGui( const RwChar* pName );
	~CTBTournamentGui(VOID);

	//! Operation
	VOID	Init(VOID);

	RwBool	Create(VOID);
	VOID	Destroy(VOID);

	VOID	Update( RwReal fElapsed );

	RwInt32	SwitchDialog( bool bOpen );

	//! Event
	VOID	HandleEvents( RWS::CMsg& msg );	
private:	
	//! Implements
	VOID	CreateFightDataGroup(VOID);
	VOID	DeleteFightDataGroup(VOID);
	VOID	SetPage( ePage ePageType );

	//! Callback
	gui::CSlot		m_slotClickClose;
	gui::CSlot		m_slotClickRightArrow;
	gui::CSlot		m_slotClickLeftArrow;
	gui::CSlot		m_slotClickPartyBtn;
	gui::CSlot		m_slotClickIndividualBtn;

	VOID	OnClickClose( gui::CComponent* pComponent );
	VOID	OnClickRightArrow( gui::CComponent* pComponent );
	VOID	OnClickLeftArrow( gui::CComponent* pComponent );
	VOID	OnClickPartyBtn( gui::CComponent* pComponent );
	VOID	OnClickIndividualBtn( gui::CComponent* pComponent );

	//! Variable
	CTBTournamentInfoGroup*			m_pInfoGroup[NUM_PAGE];

	RwUInt8							m_byMaxEntry;							// �ִ� �. 
	ePage							m_eCurrentPage;							// ���� ���̴� ������.
	RwUInt8							m_byIndividualFightInfoInputDoneCount;	// ���� �Էµ� FightInfo ����.(���� ������Ʈ ��) ������
	RwUInt8							m_byTeamFightInfoInputDoneCount;		// ���� �Էµ� FightInfo ����.(���� ������Ʈ ��) ��Ƽ��		

	gui::CButton*					m_pbtnRightArrow;
	gui::CButton*					m_pbtnLeftArrow;
	gui::CStaticBox*				m_pstbIndividualGroupType;

	gui::CButton*					m_pbtnParty;			// Toggle���� ��ư. ��Ƽ�� ���� �� ������Ʈ�� ������ų�, ��Ȱ��ȭ
	gui::CButton*					m_pbtnIndividual;

	gui::CStaticBox*				m_pstbTitle;			
	gui::CStaticBox*				m_pstbInfomation;		// ����.	
	gui::CButton*					m_pbtnNextInfomation;	// ���� ���� ��ư.

	gui::CButton*					m_pbtnClose;

public:
	static std::map<RwUInt16,sBUDOKAI_TOURNAMENT_ENTRY_TEAM_INFO> m_mapIndividualEntryInfo;
	static std::map<RwUInt16,sBUDOKAI_TOURNAMENT_ENTRY_TEAM_INFO> m_mapTeamEntryInfo;
	static std::map<RwUInt16,sBUDOKAI_TOURNAMENT_INDIVIDUAL_ENTRY_DATA> m_mapIndividualEntryData;
	static std::map<RwUInt16,sBUDOKAI_TOURNAMENT_TEAM_ENTRY_DATA> m_mapTeamEntryData;

	static sBUDOKAI_TOURNAMENT_ENTRY_TEAM_INFO* FindIndividualEntryInfo( RwUInt16 wJoinID );
	static sBUDOKAI_TOURNAMENT_ENTRY_TEAM_INFO* FindTeamEntryInfo( RwUInt16 wJoinID );
	static sBUDOKAI_TOURNAMENT_INDIVIDUAL_ENTRY_DATA* FindIndividualEntryData( RwUInt16 wJoinID );
	static sBUDOKAI_TOURNAMENT_TEAM_ENTRY_DATA* FindTeamEntryData( RwUInt16 wJoinID );
};


#endif//__BUDOKAI_TOURNAMENT_GUI_H__