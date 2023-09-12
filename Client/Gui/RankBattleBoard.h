/******************************************************************************
* File			: RankBattleBoard.h
* Author		: Cho Hae sung
* Copyright		: (��)NTL
* Date			: 2007. 12. 14
* Abstract		: 
*****************************************************************************
* Desc			: ��ũ��Ʋ�� ���� �Խ���
*****************************************************************************/

#ifndef __RANKBATTLE_H__
#define __RANKBATTLE_H__

#include "RankBoardCommon.h"

// RankBattle Define

#define dRANKBOARD_RANKBATTLE_ROWITEM_Y				67
#define dRANKBOARD_RANKBATTLE_ROWITEM_NUMS			10
#define dRANKBOARD_RANKBATTLE_ROWITEM_MARGIN_Y		0
#define dRANKBOARD_RANKBATTLE_ROWITEM_FONT_HEIGHT	90

#define dRANKBOARD_RANKBATTLE_FIRST_PAGE			0
#define dRANKBOARD_RANKBATTLE_FIRST_COMPARE			1

#define dRANKBOARD_RANKBATTLE_UNDERLINE_NUMS		9
#define dRANKBOARD_RANKBATTLE_UNDERLINE_WIDTH		612

struct sRANKBATTLE_ITEM
{
	RwInt32		nRank;												///< ����
	WCHAR		awcName[NTL_MAX_SIZE_CHAR_NAME+1];			///< ĳ���� �̸�
	RwInt32		nLevel;												///< ����
	RwUInt8		byClass;											///< Ŭ����
	WCHAR		awcGuildName[NTL_MAX_SIZE_GUILD_NAME+1];	///< ��� �̸�
	RwInt32		nPoint;												///< ����
	RwUInt16	wStraightWin;										///< ����
	RwUInt32	nCompare;											///< �񱳳�¥
};

/**
* \ingroup client
* \brief ��ũ��Ʋ�� �׸��
*/
class CRankBattleRowItem
{
public:
	CRankBattleRowItem();
	virtual ~CRankBattleRowItem();

	VOID Create( gui::CComponent* pParentGui, RwInt32 nTop );
	VOID Destroy();

	VOID Show( RwBool bShow = TRUE );

	// Set Subject
	VOID SetItem( RwInt32 nRank, const WCHAR* pwcName, RwInt32 nLevel, RwUInt8 byClass, const WCHAR* pwcGuildName, RwInt32 nPoint, RwUInt16 nStraightWin, RwUInt32 nCompare , RwBool bHightLight = FALSE);
	VOID SetCompareInfo( RwInt32 nCompare );
	VOID ClearItem();

	// Set ToolTip
	VOID OnMouseEnterFromClass( gui::CComponent* pComponent );
	VOID OnMouseLeaveFromClass( gui::CComponent* pComponent );

protected:
	gui::CStaticBox*	m_pStbRank;				///< ����
	gui::CStaticBox*	m_pStbName;				///< �̸�
	gui::CStaticBox*	m_pStbLevel;			///< ����
	gui::CPanel*		m_pPanClass;			///< ����
	gui::CStaticBox*	m_pStbGuildName;		///< ����̸�
	gui::CStaticBox*	m_pStbPoint;			///< ����
	gui::CStaticBox*	m_pStbStraightWin;		///< ����
	gui::CStaticBox*	m_pStbCompare;			///< ��
	gui::CPanel*		m_pPanCompareMark;		///< �񱳸�ũ
	gui::CDialog*		m_pDlgItem;

	gui::CSlot			m_slotMouseEnterFromClass;
	gui::CSlot			m_slotMouseLeaveFromClass;

	RwInt32				m_nRank;				///< ����

	RwUInt8				m_byClass;				///< ����


};

/**
* \ingroup client
* \brief ��ũ��Ʋ ���� �Խ���
*/
class CRankBattleBoard : public CBoard
{
public:
	// �������� ���� ����Ÿ�� ��ȿ��
	enum eDataResult
	{
		eDATA_OK = 0,
		eDATA_ONLYCOMPARE,
		eDATA_NONE,
		eDATA_NOTPAGE,
		eDATA_NOTFIND,

		eDATA_NUMS,
		eDATA_INVALID = 0xFF
	};

	// �˻� ���
	enum eSearchMode
	{
		eSEARCH_RANK = 0,	// ��ũ�� �˻�
		eSEARCH_NAME,

		eSEARCH_NUMS,
		eSEARCH_INVALID = 0xFF
	};

public:
	CRankBattleBoard();
	virtual ~CRankBattleBoard();

	// abstract
	virtual void Create( eBoardType eType , CRankBoardGui* pParent );
	virtual void Destroy();

	virtual void Show( RwBool bShow = TRUE );
	virtual void Enable( RwBool bEnable = TRUE );

	virtual void MessageProc( RWS::CMsg& msg );

	virtual void CurrentPage();

	// Interface
	VOID		ApplyData();
	VOID		RowItemClear();
	VOID		SetDataResult( RwUInt8 byDataResult );

	// Callback
	VOID		OnClickedBtnPrev( gui::CComponent* pComponent );
	VOID		OnClickedBtnNext( gui::CComponent* pComponent );
	
	void		OnInputReturnSearch();
	void		OnClickedBtnSearch(gui::CComponent* pComponent);

	// ��ġ ���� �޺��ڽ�
	VOID		OnSearchItemSelect( INT nIndex );
	VOID		OnSearchListToggled( RwBool bToggled, gui::CComponent* pComponent );

	// Compare ���� �޺��ڽ� 
	VOID		OnItemSelect( INT nIndex );
	VOID		OnListToggled( RwBool bToggled, gui::CComponent* pComponent );
	VOID		OnClickedCompare( gui::CComponent* pComponent );

	VOID		OnIpbSearchGotFocus();
	VOID		OnIpbSearchLostFocus();
	
protected:
	CRankBoardGui*		m_pParentGui;

	CRankBattleRowItem	m_RankBattleRowItem[dRANKBOARD_RANKBATTLE_ROWITEM_NUMS];

	gui::CDialog*		m_pRankBattleBoardDlg;
	gui::CPanel*		m_pPanUnderLine[dRANKBOARD_RANKBATTLE_UNDERLINE_NUMS];

	gui::CButton*		m_pBtnPrev;
	gui::CButton*		m_pBtnNext;
	gui::CComboBox*		m_pCbbSearchTitle;

	gui::CSlot			m_slotSearchItemSelect;
	gui::CSlot			m_slotSearchListToggled;

	RwInt32				m_nSearchMode;
	RwBool				m_bSearchRank;				///< ���� �����

	RwInt32				m_nSearchRankPage;			///< ���� ����϶��� ������
	RwInt32				m_nSearchRankIndex;			///< ���� ����϶� ���̶���Ʈ ���� ��ġ

	gui::CInputBox*		m_pIpbSearch;
	gui::CButton*		m_pBtnSearch;

	gui::CSlot			m_slotClickedBtnPrev;
	gui::CSlot			m_slotClickedBtnNext;
	gui::CSlot			m_slotReturnIptSearch;
	gui::CSlot			m_slotClickedBtnSearch;

	gui::CSlot			m_slotIpbSearchGotFocus;
	gui::CSlot			m_slotIpbSearchLostFocus;

	gui::CStaticBox*	m_pStbRank;					///< ����
	gui::CStaticBox*	m_pStbName;					///< �̸�
	gui::CStaticBox*	m_pStbLevel;				///< ����
	gui::CStaticBox*	m_pStbClass;				///< ����
	gui::CStaticBox*	m_pStbGuildName;			///< ����̸�
	gui::CStaticBox*	m_pStbPoint;				///< ����
	gui::CStaticBox*	m_pStbStraightWin;			///< ����
	/*gui::CComboBox*		m_pCbbCompare;				///< �񱳳�¥( �޺��ڽ� )*/
	gui::CStaticBox*	m_pStbRankBattleCompare;		///< ���� ����

	gui::CSlot			m_slotItemSelect;			///< ������ ����Ʈ
	gui::CSlot			m_slotListToggled;			///< ����Ʈ�ڽ� ���
	gui::CSlot			m_slotClickedCompare;		///< ����Ʈ�ڽ��� ����� ��ư Ŭ��

	RwInt32				m_nCurrentPage;
	RwInt32				m_nCurrentCompareDay;

	RwUInt8				m_byDataResult;

	RwInt32				m_nRankBattleItemCount;
	sRANKBATTLE_ITEM	m_sRankBattleItem[dRANKBOARD_RANKBATTLE_ROWITEM_NUMS];
	WCHAR				m_awcSearchName[NTL_MAX_SIZE_CHAR_NAME+1];
};


#endif//__RANKBATTLE_H__