#ifndef __GUI_HTMLBOX_GENERIC_H__
#define __GUI_HTMLBOX_GENERIC_H__

#include "gui_htmlbox.h"
#include "gui_htmlbox_item.h"

START_GUI

// HTML ITEM ������ ����
#define MAX_HTML_ITEM			1000
#define MAX_HTML_ITEM_ALIGN		100	
#define HTML_LINE_INTERVAL		5		///< ���δ� ������ Define���� ����(�⺻)

/**
* \brief Link �Ǵ� ������ �����ϰ� �ִ´�.
*/
struct sLinkRect
{
	CHtml_LinkItem* pLinkItem;			///< ��ũ ������
	CRectangle		rectArea;			///< ���� ����( ��ũ��, ������ ���� )
};

// Callback
typedef VOID (*HtmlLinkTagFunc)(gui::CComponent* pComponent, BYTE byType, UINT32 uiIndex, std::wstring& strFilename);

// ���漱��
class CHtmlDoc;

/**
* \ingroup client
* \brief RowHtml_Item Ŭ������ Html���� �� ���� ��� �ִ� Item���̴�.
*/
class CRowHtml_Item
{
public:

	CRowHtml_Item(INT nCurrIdx, CRectangle rtClient, BOOL bFixedTopDown, INT nLineIntervalY);
	~CRowHtml_Item();

	CHtml_Item*	ItemDisposition(CHtml_Item *pItem, INT nLineIntervalY);
	VOID		ItemFinishDisposition(VOID);
	VOID		ItemTBCSorting(VOID);

	VOID		OnPrePaint(INT nOffsetX, INT nOffsetY, const CRectangle& rtPaint, CTexture *pTexture, DWORD dwAlign);
	VOID		OnPaint(const CRectangle& rtScreen);
	VOID		OnBackPaint(const CRectangle& rtScreen);
	VOID		OnSetAlpha( BYTE ucAlpha );

	VOID		Update( float fElasped );

	BOOL		IsFull(VOID);
	BOOL		IsEmpty(VOID);
	CRectangle	GetArea(VOID);
	INT			GetAreaHeight(VOID);
	INT			GetCurrentIndex(VOID);
	INT			GetItemCount(VOID);

	// ����Ʈ�� ���� ������ �ִ� string �������� ��� ���� ũ�⸦ ����Ѵ�.
	VOID		GetItemRect( std::list<CRectangle>& list );
	VOID		GetLinkRect( std::list<sLinkRect>& list );

private:
	INT GetAlignOffsetX(DWORD dwAlign, INT nClipWidth, INT nItemWidth);
	INT	GetChildRowHtmlWidth(VOID);
	INT GetChildRowHtmlHeight(INT nLineIntervalY);

private:
	INT						m_nCurrIdx;				///< ���� Index ( Line Index )
	INT						m_nLineIntervalY;		///< Item �� Y ����
	BOOL					m_bFull;				///< ���� Row�� �� á������ ����
	BOOL					m_bFixedTopDown;
	CRectangle				m_rtClipping;
	CRectangle				m_rtArea;
	CRectangle				m_rtCurrArea;
	DWORD					m_dwWarpAlign;
	std::list<CHtml_Item*>	m_listItems;
	std::list<CRowHtml_Item*> m_listRowHtmlItem;	
};

/**
* \ingroup client
* \brief HtmlBox�� ����� �� �ִ� Generic �Ӽ���
*/
class CHtmlBox_Generic
{
public:
	CHtmlBox_Generic(CHtmlBox *pSelf, BOOL bDynamic = FALSE);
	~CHtmlBox_Generic();

	VOID	SetHtmlFromFile(const CHAR *pFileName);					///< ���Ͽ��� �Ľ�
	VOID	SetHtmlFromMemory(const WCHAR *pMemory, INT nSize);		///< �޸𸮿��� �Ľ�
	
	BOOL	SetFontRatio( float fRatio );							///< �ؽ�Ʈ ���� ����
	VOID	SetStyle(DWORD dwStyle);								///< Style ����
	VOID	SetLineSpace(INT nSpace);								///< ���� ���� ����
	VOID	SetTextBackgroundColor(COLORREF color);					///< �ؽ�Ʈ ������ ����

	VOID	Clear(VOID);									///< Item, Texture �ʱ�ȭ

public:
	//: Sets the surface.
	VOID	AddSurface( CSurface surface );
	
	VOID	CreateTextTexture(void);						///< Text Texture ����
	VOID	DeleteTextTexture(void);						///< Text Texture ����

	//: 2007-11-16 �� ���ھ� ������� ����ϴ� ���
public:
	VOID	SetIntervalTextEnable(float fIntervalTime);		///< ��� �� : ��� ���� (��)
	VOID	SetIntervalTextDisable();						///< �� ���ھ� ����ϴ� ��带 ����

	VOID	Update(float fElapsedTime);						///< ������Ʈ

	INT		GetIntervalPageNums(VOID);						///< ��µǴ� �� ������ ����
	INT		GetCurrentPage(VOID);							///< ���� ������

	BOOL	SetNextPage(VOID);								///< ���� ������
	BOOL	SetPrevPage(VOID);								///< ���� ������
	BOOL	SetSkipPage(VOID);								///< ���� ������ SKIP

	BOOL	SetPlayPage(INT nPage);							///< nPage���� �÷���

	VOID	SetPause( BOOL bPause = TRUE );					///< �Ͻø��� ( FALSE�� ������ �簳 )
	VOID	SetImmediate( BOOL bImmediate = TRUE );			///< �������� �ٷ� �����ִ� ���

	VOID	SetPresentNum(INT nNum);						///< �ѹ��� ��µ� ������ ���� ����
	INT		GetPresentNum();								///< ���� ��µǴ� ���� ����

	CSignal_v1<int> m_SigPageDone;							///< �������� �Ϸ� ���� �� ���󰡴� ȣ��Ǵ� Signal

private:
	VOID	DeleteItem(VOID);								///< m_pHtmlDoc ����
	VOID	DeleteRenderItem(VOID);							///< m_listRowHtml �ʱ�ȭ
	
	VOID	ItemDisposition(VOID);							///< HtmlBox ������Ʈ�� ���� Item�� ���
	VOID	ItemLineSorting(VOID);							///< HtmlBox ���� ���
	VOID	ItemRenderToTexture(INT nVScrollPos);			///< ������ �˸°� ������

	INT		GetAlignOffsetX(DWORD dwAlign, INT nClipWidth, INT nItemWidth);
	INT		GetAlignOffsetY(DWORD dwAlign, INT nClipHeight, INT nItemHeight);

	VOID	SetVScrollEnable(BOOL bEnable);
	VOID	SetVScrollRange(INT nRange);
	VOID	SetVScrollPos(INT nPos);

	VOID	IntervalTextPosCalc(VOID);						///< ���� ��ġ�� ���
	VOID	IntervalPagePosCalc(VOID);						///< �������� ũ�� ���

	VOID	IntervalPageInit(INT nPage);					///< ����� ���� ������Ʈ ���� �ʱ�ȭ
	VOID	IntervalPageDone(INT nPage);					///< IntervalText ������ �Ϸ�

	VOID	DeleteIntervalText(VOID);						///< IntervalText�� ��� �ڿ� ����

	// Dynamic ���� �Լ�
	VOID	AdjustToWidthString(VOID);						///< Dynamic �Ӽ� �϶� ������Ʈ�� Width�� �����Ѵ�.
	VOID	AdjustToHeightString(VOID);						///< Dynamic �Ӽ� �϶� ������Ʈ�� Height�� �����Ѵ�.

	INT FindMaxWidthItem(VOID);

	// Link ���� �Լ�
	VOID	LinkRectCalc(VOID);								///< ��ũ�Ǵ� ��ġ�� ���
	VOID	LinkVScrollCalc(INT nPos);						///< ��ũ�Ǵ� ������ ��ũ�ѿ� ���� ������ش�.
	VOID	DeleteIntervalLink(VOID);						///< Interval Text Mode�� �� ��ũ ���� ��� �Ѱ��� �����Ѵ�.

public:
	// Link ���� �ݹ� �Լ�
	static HtmlLinkTagFunc m_fnHtmlLinkTag;

	static VOID LinkHtmlLinkTag(HtmlLinkTagFunc fnLinkTag);

	// signals
public:

	VOID OnSetOptions(const CComponentOptions& options);
	VOID OnPaint(VOID);
	VOID OnMove(int nX,int nY);
	VOID OnResize(int nCx, int nCy);
	VOID OnSetAlpha( BYTE ucAlpha );
	VOID OnSetColor( BYTE ucRed, BYTE ucGreen, BYTE ucBlue );
	VOID OnScrollMove( INT nPos );
	VOID OnMouseMove( INT nKey, INT nXPos, INT nYPos );
	VOID OnMouseDown(const CKey& key);
	VOID OnMouseUp(const CKey& key);

	CSlot m_SlotSetOption;
	CSlot m_SlotPaint;
	CSlot m_SlotMove;
	CSlot m_SlotResize;
	CSlot m_SlotSetAlpha;
	CSlot m_SlotSetColor;
	CSlot m_SlotScrollChange;
	CSlot m_SlotSliderMove;
	CSlot m_SlotMouseMove;
	CSlot m_SlotMouseDown;
	CSlot m_SlotMouseUp;

private:
	CHtmlBox			*m_pHtmlBox;
	std::list<CSurface> m_stlSurface;
	CSurface			m_TextSurface;

	// html document
	CHtmlDoc			*m_pHtmlDoc;

	// rendering HTML item : �ӵ��� ���Ͽ� ���� �ڷᱸ���� �����Ͽ���.
	std::list<CRowHtml_Item*> m_listRowHtml;

	// component attribute
	DWORD		m_dwStyle;
	INT			m_nLineInterY;				///< line ����.
	INT			m_nItemCx;					///< ��ü item�� width
	INT			m_nItemCy;					///< ��ü item�� height
	BOOL		m_bVScrollEnable;			///< vertical scroll enable
	INT			m_nVScrollRange;			///< vertical scroll range
	COLORREF	m_BgColor;					///< ��� ����
	INT			m_nVScrollPos;

	float m_fRatio;

	BOOL		m_bIntervalText;			///< ������ ��� default = FALSE
	BOOL		m_bDonePage;				///< ������ �������� ��� ��� �Ϸ�
	BOOL		m_bPause;					///< �Ͻø���
	BOOL		m_bImmediate;				///< �������� �ٷ� ������

	float		m_fIntervalTime;			///< ������ �ð�
	float		m_fElapsedTime;				///< ������ �ð�
	
	INT			m_nCurrentRow;				///< ����ϴ� ���� ������ ��ġ�� ����
	INT			m_nCurrentPage;				///< ����ϴ� ���� ������

	PlaneSnapShot	m_planeInterval;		///< ���� �������� ���� rect
	INT				m_nPageCount;			///< �������� ����

	INT				m_nPresentNum;			///< �ѹ��� ������ ������ ���� ( 1 ~ 10 , default 1 )
	
	typedef std::list<CRectangle> LISTRECTANGLE;
	LISTRECTANGLE *m_pListRectangle;		///< ������ ���� ������ ũ�⸦ ���� ����Ʈ
	LISTRECTANGLE::iterator itListRect;		///< ������ �ݺ���

	typedef std::vector<INT> VECINT;
	VECINT m_vecNewLineIdx;					///< CRowHtml_Item�� [br]�±��� index
	VECINT m_vecNewPageIdx; 				///< �������� �����ϴ� [br]�±��� index

	typedef std::vector<CRectangle> VECRECTANGLE;
	VECRECTANGLE m_vecPageRect;				///< �� �������� ũ��

	// Dynamic �Ӽ�
	BOOL	m_bDynamic;						///< Dynamic �Ӽ�
	INT		m_nMaxCX;						///< �ִ� Ȯ���� �� �ִ� X
	INT		m_nMaxCY;						///< �ִ� Ȯ���� �� �ִ� Y
	INT		m_nMinCX;						///< �ִ� ���� �� �ִ� X
	INT		m_nMinCY;						///< �ִ� ���� �� �ִ� Y

	CRectangle	m_rectScreen;				///< �ʱ� ������Ʈ�� ���� ( Dynamic �Ӽ��϶� ����� ������ �ȴ� )
	CRectangle	m_rectClient;				///< �ʱ� ������Ʈ�� ����

	INT		m_nMaxWidth;					///< ���� ������ �߿��� ���� ū ����� �����ϴ� ����

	// Link �Ӽ�
	typedef std::list<sLinkRect> LISTLINK;
	LISTLINK			m_listOriginLink;					///< Link ������ ��� ���� ����Ʈ
	LISTLINK			m_listDuplicateLink;				///< Scroll�� Page ������ ��ģ ��ũ ���� ����Ʈ(���� ���� ����)
	LISTLINK*			m_pListLink;						///< Link ������ ������ ���� ��� �ִ� ����Ʈ(IntervalText ����)
	LISTLINK::iterator	m_itCaptureLink;

};

END_GUI

#endif