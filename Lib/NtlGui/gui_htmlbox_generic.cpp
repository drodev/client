#include "gui_precomp.h"
#include "gui_htmlbox_generic.h"
#include "gui_html_doc.h"
#include "gui_componentoption.h"
#include "gui_texturemanager.h"
#include "gui_renderer.h"
#include <algorithm>

START_GUI

/**
* \brief Construction
* \param nCurrIdx		(INT) ���� ���� Index
* \param rtClient		(CRectangle) ���� ���� ����
* \param bFixedTopDown	(BOOL)
* \param nLineIntervalY	(INT) ���� �� ������ Y ����
*/
CRowHtml_Item::CRowHtml_Item(INT nCurrIdx, CRectangle rtClient, BOOL bFixedTopDown, INT nLineIntervalY)
{
	m_nCurrIdx			= nCurrIdx;
	m_nLineIntervalY	= nLineIntervalY;	
	m_rtClipping		= rtClient;

	m_bFull				= FALSE;
	m_bFixedTopDown		= bFixedTopDown;
	m_dwWarpAlign		= HTML_WRAP_ALIGN_NONE;

	m_rtArea.left		= m_rtClipping.left;
	m_rtArea.top		= m_rtClipping.top;
	m_rtArea.right		= m_rtClipping.right;
	m_rtArea.bottom		= m_rtClipping.top;

	m_rtCurrArea		= m_rtArea;
}

/**
* \brief Destruction
*/
CRowHtml_Item::~CRowHtml_Item()
{
	// �� �ȿ� ���Ե� �����۵��� ����
	std::list<CHtml_Item*>::iterator it;
	for(it = m_listItems.begin(); it != m_listItems.end(); it++)
	{
		NTL_DELETE( *it );
	}

	// �����۵�� �� ���� �̷���� RowHtml_Item ����
	std::list<CRowHtml_Item*>::iterator rowit;
	for(rowit = m_listRowHtmlItem.begin(); rowit != m_listRowHtmlItem.end(); rowit++)
	{
		NTL_DELETE( *rowit );
	}
}

/**
* \brief �� html item ���� �����Ͽ� RowHtml_Item���� �����.
* \param pItem			(CHtml_Item*) 
* \param nLineIntervalY	(INT)
* \return (CHtml_Item*) ���� ������ Item
*/
CHtml_Item* CRowHtml_Item::ItemDisposition(CHtml_Item *pItem, INT nLineIntervalY)
{
	// ���� ���� ���� á�ٸ� ���� �����۵� �����Ѵ�. ( ���� ���� Disposition ���� �뵵 )
	if(m_bFull)
		return pItem;

	if(m_listRowHtmlItem.size() > 0)
	{
		std::list<CRowHtml_Item*>::reverse_iterator rit = m_listRowHtmlItem.rbegin();
		CRowHtml_Item *pRowHtmlItem = (*rit);
		CHtml_Item *pNextItem = pRowHtmlItem->ItemDisposition(pItem, nLineIntervalY);

		if(pRowHtmlItem->IsFull())
		{
			if(pRowHtmlItem->GetItemCount() == 0)
			{
				if(m_rtCurrArea.bottom >= m_rtArea.bottom)
					m_rtArea.bottom = m_rtCurrArea.bottom;

				m_bFull = TRUE;
				return pNextItem;
			}

			INT nRowHeight = GetChildRowHtmlHeight(m_nLineIntervalY);
			CRectangle rtWrapClipping = m_rtCurrArea;
			rtWrapClipping.top = nRowHeight + nLineIntervalY;

			CRowHtml_Item *pNewRowHtmlItem = NTL_NEW CRowHtml_Item(m_nCurrIdx, rtWrapClipping, TRUE, m_nLineIntervalY);
			m_listRowHtmlItem.push_back(pNewRowHtmlItem);
		}

		return pNextItem;
	}
	else
	{
		m_dwWarpAlign |= pItem->GetWrapAlign();

		CHtml_Item *pNextItem = pItem->ItemDisposition(m_rtCurrArea, m_rtClipping, m_listItems, nLineIntervalY, m_bFixedTopDown, m_bFull);

		if(m_bFull)
		{
			if(m_rtCurrArea.bottom >= m_rtArea.bottom)
				m_rtArea.bottom = m_rtCurrArea.bottom;
		}
		else
		{
			if(m_dwWarpAlign != HTML_WRAP_ALIGN_NONE)
			{
				CRectangle rtWrapClipping = m_rtCurrArea;
				CRowHtml_Item *pWrapRowHtmlItem = NTL_NEW CRowHtml_Item(m_nCurrIdx, rtWrapClipping, TRUE, m_nLineIntervalY);
				m_listRowHtmlItem.push_back(pWrapRowHtmlItem);
			}
		}

		return pNextItem;
	}

}

/**
* \brief ���� RowHtml_Item�� ���� ������ ��ü ���� ���� �����Ѵ�.
*/
VOID CRowHtml_Item::ItemFinishDisposition(VOID)
{
	if(m_rtCurrArea.bottom >= m_rtArea.bottom)
		m_rtArea.bottom = m_rtCurrArea.bottom;
}

VOID CRowHtml_Item::ItemTBCSorting(VOID)
{
	std::list<CHtml_Item*>::iterator it;

	for(it = m_listItems.begin(); it != m_listItems.end(); it++)
	{
		if(m_rtCurrArea.bottom >= m_rtArea.bottom)
			m_rtArea.bottom = m_rtCurrArea.bottom;

		(*it)->ItemLineBottomSorting(m_rtArea.bottom);
	}
}

/**
* \brief Item�� Texture�� �˸°� ����.
* \param nOffsetX
* \param nOffsetY
* \param rtPaint
* \param pTexture
* \param dwAlign
*/
VOID CRowHtml_Item::OnPrePaint(INT nOffsetX, INT nOffsetY, const CRectangle& rtPaint, CTexture *pTexture, DWORD dwAlign)
{
	std::list<CHtml_Item*>::iterator it;

	INT nCurrItemWidth = 0;
	INT nCx, nCy;
	INT nClipWidth = m_rtClipping.GetWidth();
	DWORD dwNewAlign = dwAlign;

	for(it = m_listItems.begin(); it != m_listItems.end(); it++)
	{
		dwNewAlign = (*it)->GetAlign();
		(*it)->GetSize(nCx, nCy);
		if((*it)->GetWrapAlign() == HTML_WRAP_ALIGN_NONE)
			nCurrItemWidth += nCx;
		else
			nClipWidth -= nCx;
	}

	nClipWidth -= GetChildRowHtmlWidth();

	INT nAdjustOffsetX = nOffsetX + GetAlignOffsetX(dwNewAlign, nClipWidth, nCurrItemWidth);

	for(it = m_listItems.begin(); it != m_listItems.end(); it++)
	{
		CHtml_Item *pHtmlItem = (*it);
		if(pHtmlItem->GetWrapAlign() != HTML_WRAP_ALIGN_NONE)
			nAdjustOffsetX = nOffsetX;

		pHtmlItem->OnPrePaint(nAdjustOffsetX, nOffsetY, rtPaint, pTexture);
	}

	dwNewAlign = dwAlign;
	std::list<CRowHtml_Item*>::iterator rowit = m_listRowHtmlItem.begin();
	for(rowit = m_listRowHtmlItem.begin(); rowit != m_listRowHtmlItem.end(); rowit++)
	{
		CRowHtml_Item *pRowHtmlItem = (*rowit);
		pRowHtmlItem->OnPrePaint(nOffsetX, nOffsetY, rtPaint, pTexture, dwNewAlign);
	}
}

/**
* \brief RowHtml�� list�� ������ �ִ� Item���� OnPaint ���� ȣ���Ѵ�.
* \param rtScreen	(CRectangle&) �׷��� ����
*/
VOID CRowHtml_Item::OnPaint(const CRectangle& rtScreen)
{
	std::list<CHtml_Item*>::iterator it;

	for(it = m_listItems.begin(); it != m_listItems.end(); it++)
	{
		(*it)->OnPaint(rtScreen);
	}
}

VOID CRowHtml_Item::OnBackPaint( const CRectangle& rtScreen )
{
	std::list<CHtml_Item*>::iterator it;

	for(it = m_listItems.begin(); it != m_listItems.end(); it++)
	{
		(*it)->OnBackPaint(rtScreen);
	}
}

/**
* \brief ������ �ִ� Item���� SetAlpha�� ȣ�����ش�.
* \param ucAlpha	(BYTE) ���İ� ( 0 ~ 255 )
*/
VOID CRowHtml_Item::OnSetAlpha( BYTE ucAlpha ) 
{
	CHtml_Item* pHtml = NULL;
	CHtml_PictureItem* pPicture = NULL;

	std::list<CHtml_Item*>::iterator it;
	for(it = m_listItems.begin(); it != m_listItems.end(); it++)
	{
		pHtml = (*it);

		if( pHtml->GetType() == HTML_ITEM_PICTURE )
		{
			pPicture = (CHtml_PictureItem*)pHtml;

			pPicture->OnSetAlpha( ucAlpha );
		}
	}
}

VOID CRowHtml_Item::Update( float fElasped )
{
	std::list<CHtml_Item*>::iterator it;
	for(it = m_listItems.begin(); it != m_listItems.end(); it++)
	{
		(*it)->Update( fElasped );
	}
}

/**
* \brief ���� ���� �����۵�� �������� �Ϸ� �Ǿ��°�?
* \return �Ϸ� ����
*/
BOOL CRowHtml_Item::IsFull(VOID)
{
	return m_bFull;
}

/**
* \brief ���� ���� ����°�?
* \return ��������� TRUE, ������� �ʴٸ� FALSE
*/
BOOL CRowHtml_Item::IsEmpty(VOID)
{
	if(m_listItems.size() == 0)
		return TRUE;

	return FALSE;
}

CRectangle CRowHtml_Item::GetArea(VOID)
{
	return m_rtArea;
}

INT CRowHtml_Item::GetAreaHeight(VOID)
{
	return m_rtArea.GetHeight();
}

INT	CRowHtml_Item::GetCurrentIndex(VOID)
{
	return m_nCurrIdx;
}

INT CRowHtml_Item::GetItemCount(VOID)
{
	return (INT)m_listItems.size();
}

VOID CRowHtml_Item::GetItemRect( std::list<CRectangle>& list ) 
{
	// m_listItem�� ����ִ� �����۵��� ���� ũ�⸦ ������� ��ƿ´�.
	std::list<CHtml_Item*>::iterator itHtmlItem;
	for( itHtmlItem = m_listItems.begin(); itHtmlItem != m_listItems.end(); ++itHtmlItem )
	{
		CHtml_Item* pHtmlItem = (*itHtmlItem);

		// ����Ʈ�� �����ۿ� �־��ش�.
		if( pHtmlItem->GetType() == HTML_ITEM_STRING ||
			pHtmlItem->GetType() == HTML_ITEM_LINK )
			static_cast<CHtml_StringItem*>(pHtmlItem)->GetItemRect( list ); // ����Ʈ�� �ִ� �׸�
	}
}

/**
* \brief ���� �����Ǿ� �ִ� RowHtml Item�� �߿��� ��ũ �Ӽ��� ������ �ִ� ������ ��´�.
*/
VOID CRowHtml_Item::GetLinkRect( std::list<sLinkRect>& list )
{
	std::list<CHtml_Item*>::iterator itHtmlItem;
	for( itHtmlItem = m_listItems.begin(); itHtmlItem != m_listItems.end(); ++itHtmlItem )
	{
		CHtml_Item* pHtmlItem = (*itHtmlItem);

		if( pHtmlItem->GetType() == HTML_ITEM_LINK )
		{
			sLinkRect sLink;
			CHtml_LinkItem* pLinkItem = static_cast<CHtml_LinkItem*>(pHtmlItem);

			sLink.pLinkItem = pLinkItem;
			sLink.rectArea = pLinkItem->GetRect();

			list.push_back( sLink );
		}
	}
}

INT CRowHtml_Item::GetAlignOffsetX(DWORD dwAlign, INT nClipWidth, INT nItemWidth)
{
	INT nOffsetX = 0;

	if(ENABLE_COMPONENT_STYLE(dwAlign,COMP_TEXT_CENTER))
	{
		nOffsetX += (nClipWidth - nItemWidth)/2;
		if(nOffsetX < 0)
			nOffsetX = 0;
	}
	else if(ENABLE_COMPONENT_STYLE(dwAlign,COMP_TEXT_RIGHT))
	{
		nOffsetX += nClipWidth - nItemWidth - 2;
		if(nOffsetX < 0)
			nOffsetX = 0;
	}

	return nOffsetX;
}

INT	CRowHtml_Item::GetChildRowHtmlWidth(VOID)
{
	if(m_listRowHtmlItem.size() == 0)
		return 0;
	else
		return m_rtCurrArea.GetWidth();
}

INT CRowHtml_Item::GetChildRowHtmlHeight(INT nLineIntervalY)
{
	INT nHeight = 0;

	if(m_listRowHtmlItem.size() > 0)
	{
		std::list<CRowHtml_Item*>::reverse_iterator rit = m_listRowHtmlItem.rbegin();
		CRectangle rtArea = (*rit)->GetArea();
		nHeight = rtArea.bottom;
	}

	return nHeight;
}






/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

HtmlLinkTagFunc CHtmlBox_Generic::m_fnHtmlLinkTag = NULL;

CHtmlBox_Generic::CHtmlBox_Generic(CHtmlBox *pSelf, BOOL bDynamic /* = FALSE */)
: m_bDynamic( bDynamic )
{
	m_pHtmlBox		= pSelf;
	m_pHtmlDoc		= NULL;
	m_nLineInterY	= HTML_LINE_INTERVAL;
	m_dwStyle		= 0;
	//m_dwStyle		= COMP_TEXT_LEFT | COMP_TEXT_UP;
	m_nItemCx		= 0;
	m_nItemCy		= 0;
	m_nVScrollPos	= 0;

	m_BgColor		= RGB(0, 0, 0);

	m_TextSurface.m_pTexture = NULL;

	// signals
	m_SlotSetOption = pSelf->SigSetOptions().Connect(this, &CHtmlBox_Generic::OnSetOptions);
	m_SlotPaint = pSelf->SigPaint().Connect(this, &CHtmlBox_Generic::OnPaint);
	m_SlotMove = pSelf->SigMove().Connect(this, &CHtmlBox_Generic::OnMove);
	m_SlotResize = pSelf->SigResize().Connect(this, &CHtmlBox_Generic::OnResize);

	m_SlotSetColor = pSelf->SigSetColor().Connect( this, &CHtmlBox_Generic::OnSetColor );
	m_SlotSetAlpha = pSelf->SigSetAlpha().Connect( this, &CHtmlBox_Generic::OnSetAlpha );
	m_SlotScrollChange = pSelf->m_pScrollBar->SigValueChanged().Connect( this, &CHtmlBox_Generic::OnScrollMove );
	m_SlotSliderMove = pSelf->m_pScrollBar->SigSliderMoved().Connect( this, &CHtmlBox_Generic::OnScrollMove );
	m_SlotMouseMove = pSelf->SigMouseMove().Connect( this, &CHtmlBox_Generic::OnMouseMove );
	m_SlotMouseDown = pSelf->SigMouseDown().Connect( this, &CHtmlBox_Generic::OnMouseDown );
	m_SlotMouseUp = pSelf->SigMouseUp().Connect( this, &CHtmlBox_Generic::OnMouseUp );

	// Intervals Text
	m_bIntervalText = FALSE;
	m_bPause = FALSE;
	m_bDonePage = FALSE;
	m_bImmediate = FALSE;

	m_fIntervalTime = 0.0f;
	m_pListRectangle = NULL;

	m_vecNewLineIdx.clear();
	m_vecNewPageIdx.clear();

	m_nPageCount = 1;		// Default 1 page

	m_fElapsedTime = 0.0f;
	m_nCurrentPage = 0;
	m_nCurrentRow = 0;

	// weight
	m_fRatio = 0.0f;

	// default count
	m_nPresentNum = 1;

	// Dynamic �Ӽ�
	m_nMaxCX = m_pHtmlBox->GetScreenRect().GetWidth();
	m_nMaxCY = m_pHtmlBox->GetScreenRect().GetHeight();
	m_nMinCX = 0;
	m_nMinCY = 0;

	// Dynamic�� �� ����� ������ �Ǵ� Rect( Screen, Client )
	m_rectScreen = m_pHtmlBox->GetScreenRect();
	m_rectClient = m_pHtmlBox->GetClientRect();

	m_nMaxWidth = 0;

	// Link �Ӽ�
	m_itCaptureLink = m_listDuplicateLink.end();
	m_pListLink = NULL;
}

CHtmlBox_Generic::~CHtmlBox_Generic()
{
	DeleteIntervalLink();
	DeleteIntervalText();
	DeleteTextTexture();
	DeleteItem();
}

VOID CHtmlBox_Generic::SetHtmlFromFile(const CHAR *pFileName)
{
	SetVScrollEnable(FALSE);

	DeleteItem();
	m_pHtmlDoc = NTL_NEW CHtmlDoc;
	m_pHtmlDoc->SetDefaultAlign(COMP_TEXT_LEFT | COMP_TEXT_UP);
	if( m_fRatio > 0.0f )
		m_pHtmlDoc->SetFontRatio( m_fRatio );
	m_pHtmlDoc->SetTextBackgroundColor(m_BgColor);
	m_pHtmlDoc->SetHtmlFromFile(m_pHtmlBox, pFileName);

	// ���� ����� �� Item�� ã�Ƽ� �ű⿡ �����.
	if( m_bDynamic )
		AdjustToWidthString();

	ItemDisposition();
	ItemLineSorting();

	if(m_bVScrollEnable)
	{
		ItemDisposition();
		ItemLineSorting();
	}

	SetVScrollPos(0);

	// ���̳��� �Ӽ��� ���� ���̸� �����Ѵ�.
	if( m_bDynamic )
		AdjustToHeightString();
}

VOID CHtmlBox_Generic::SetHtmlFromMemory(const WCHAR *pMemory, INT nSize)
{
	SetVScrollEnable(FALSE);

	DeleteItem();
	m_pHtmlDoc = NTL_NEW CHtmlDoc;
	if( m_fRatio > 0.0f )
		m_pHtmlDoc->SetFontRatio( m_fRatio );
	m_pHtmlDoc->SetTextBackgroundColor(m_BgColor);
	m_pHtmlDoc->SetHtmlFromMemory(m_pHtmlBox, pMemory, nSize);

	if( m_bDynamic )
		AdjustToWidthString();

	ItemDisposition();
	ItemLineSorting();

	if(m_bVScrollEnable)
	{
		ItemDisposition();
		ItemLineSorting();
	}

	SetVScrollPos(0);

	if( m_bDynamic )
		AdjustToHeightString();

//	AdjustVerticalAlign( m_dwStyle );
}

/**
* \brief FONT�� ����ġ ����
*
*/
BOOL CHtmlBox_Generic::SetFontRatio(  float fRatio  ) 
{
	// ���� �������� ������̶��.. �����Ѵ�.
	if( m_bIntervalText && !m_bDonePage )
		return FALSE;

	if( m_fRatio <= 0.0f || m_fRatio > 10.0f )
		return FALSE;

	m_fRatio = fRatio;

	// ���� m_pHtmlDoc�� NULL�� �ƴ϶�� �ε� �Ŀ� ����� ���̹Ƿ�
	// ��� String Item�� ���ġ�ϰ� �ٽ� �׷��ش�.
	if( m_pHtmlDoc )
	{
		CHtmlDoc::ListHtmlItem::iterator docit;
		CHtmlDoc::ListHtmlItem listHtmlItem = m_pHtmlDoc->GetItems();

		// ��� HtmlStringItem�� ������ �����ش�.
		for(docit = listHtmlItem.begin(); docit != listHtmlItem.end(); ++docit)
		{
			if( (*docit)->GetType() == HTML_ITEM_STRING )
			{
				CHtml_StringItem* pStringItem = (CHtml_StringItem*)(*docit);
				pStringItem->SetFontRatio( fRatio );
			}
			else if( (*docit)->GetType() == HTML_ITEM_LINK )
			{
				CHtml_LinkItem* pLinkItem = (CHtml_LinkItem*)(*docit);
				pLinkItem->SetFontRatio( fRatio );
			}
		}

		if( m_bDynamic )
			AdjustToWidthString();

		// �ٽ� ��ġ�ϰ� �ٽ� �׷��ش�.
		ItemDisposition();
		ItemLineSorting();

		if(m_bVScrollEnable)
		{
			ItemDisposition();
			ItemLineSorting();
		}

		SetVScrollPos(0);

		if( m_bDynamic )
			AdjustToHeightString();

//		AdjustVerticalAlign( m_dwStyle );
	}

	return TRUE;
}

/**
* \brief Style�� �����Ѵ�. 32bit �ڷ���
* \param dwStyle	(DWORD) bit flag�� �Ǿ� �ִ� �ڷ���
*/
VOID CHtmlBox_Generic::SetStyle(DWORD dwStyle)
{
	m_dwStyle = dwStyle;
}

/**
* \brief HtmlBox�� Item���� ������ �����Ѵ�.
* \param nSpace	(INT) Item���� ���� ������ �ȼ�
*/
VOID CHtmlBox_Generic::SetLineSpace(INT nSpace)
{
	m_nLineInterY = nSpace;
}

/**
* \brief Html�� Text���� ��µ� ��� ������ �����Ѵ�.
* \param color	(COLORREF) 32bit ����
*/
VOID CHtmlBox_Generic::SetTextBackgroundColor(COLORREF color)
{
	m_BgColor = color;
}

VOID CHtmlBox_Generic::Clear(VOID)
{
	DeleteItem();
	DeleteRenderItem();
	m_TextSurface.m_pTexture->FillClear();
}

//: Sets the surface.
VOID CHtmlBox_Generic::AddSurface( CSurface surface )
{
	CRectangle rtSnap = surface.m_SnapShot.rtRect;
	CRectangle rtScreen = m_pHtmlBox->GetScreenRect(); 

	surface.m_SnapShot.rtRect.left = rtScreen.left+rtSnap.left;
	surface.m_SnapShot.rtRect.top = rtScreen.top+rtSnap.top;
	surface.m_SnapShot.rtRect.right = surface.m_SnapShot.rtRect.left+rtSnap.GetWidth();
	surface.m_SnapShot.rtRect.bottom = surface.m_SnapShot.rtRect.top+rtSnap.GetHeight();

	m_stlSurface.push_back(surface);
}

/**
* \brief �ؽ��ĸ� �����Ѵ�.
*/
VOID CHtmlBox_Generic::CreateTextTexture(VOID)
{
	DeleteTextTexture();

	CRectangle rect = m_pHtmlBox->GetScreenRect();

	m_TextSurface.m_pTexture = g_TextureMgr.CreateTexture( rect.GetWidth(), rect.GetHeight() );
	m_TextSurface.m_SnapShot.uRed = 255;
	m_TextSurface.m_SnapShot.uGreen = 255;
	m_TextSurface.m_SnapShot.uBlue = 255;
	m_TextSurface.m_SnapShot.uAlpha = 255;
	m_TextSurface.m_SnapShot.UVs[0] = 0;
	m_TextSurface.m_SnapShot.UVs[1] = 0;
	m_TextSurface.m_SnapShot.UVs[2] = 1;
	m_TextSurface.m_SnapShot.UVs[3] = 1;

	m_TextSurface.m_SnapShot.rtRect.left = rect.left;
	m_TextSurface.m_SnapShot.rtRect.right = rect.left+m_TextSurface.m_pTexture->GetWidth();
	m_TextSurface.m_SnapShot.rtRect.top = rect.top;
	m_TextSurface.m_SnapShot.rtRect.bottom = rect.top+m_TextSurface.m_pTexture->GetHeight();
}

/**
* \brief �ؽ��ĸ� �����Ѵ�.
*/
VOID CHtmlBox_Generic::DeleteTextTexture(VOID)
{
	if(m_TextSurface.m_pTexture)
	{
		g_TextureMgr.DeleteTexture( m_TextSurface.m_pTexture );
		m_TextSurface.m_pTexture = NULL;
	}
}

/**
* \brief IntervalText Mode On
*
* IntervalText ��带 �����ϰ� �ϰ� ���� m_pHtmlDoc�� �ڷḦ ������ �ִ� ���¶��
* �ٽ� �ѹ� �ڷ��� ��ġ�� ����ϰ� �ؽ��ĸ� ������.
*
* \param fIntervalTime (float)�ؽ�Ʈ�� �� ���ڰ� ��µǴ� ������ �ð�_�ʴ���
*/
VOID CHtmlBox_Generic::SetIntervalTextEnable( float fIntervalTime ) 
{
	m_bIntervalText = TRUE;
	m_fIntervalTime = fIntervalTime;

	if( m_pHtmlDoc )
	{
		SetVScrollEnable(FALSE);

		ItemDisposition();
		ItemLineSorting();

		ItemRenderToTexture(0);
	}
}

/**
* \brief IntervalText ��� ����
* ���� ������ ����� CHtmlBox�� ���ư���. ��� IntervalText���� �����۵��� �ʱ�ȭ �����ϰ�
* �ؽ����� ��ǥ�� UV�� ȸ���Ѵ�.
*/
VOID CHtmlBox_Generic::SetIntervalTextDisable() 
{
	// IntervalText ���� Item ���� �� �ʱ�ȭ
	DeleteIntervalText();

	m_bIntervalText = FALSE;
	m_fIntervalTime = 0.0f;

	// ���� m_pHtmlDoc�� Item�� ������ ���� ���
	if( m_pHtmlDoc )
	{
		SetVScrollEnable(FALSE);

		if( m_bDynamic )
			AdjustToWidthString();

		ItemDisposition();
		ItemLineSorting();

		if(m_bVScrollEnable)
		{
			ItemDisposition();
			ItemLineSorting();
		}

		CRectangle rect = m_pHtmlBox->GetScreenRect();

		// �ؽ��� ���� �ʱ�ȭ
		CreateTextTexture();

		// �ٽ� �׸��� :: ItemRenderToTexture
		SetVScrollPos(0);

		if ( m_bDynamic )
			AdjustToHeightString();
	}
}

// ������Ʈ
VOID CHtmlBox_Generic::Update( float fElapsedTime  ) 
{
	if( m_listRowHtml.empty() )
		return;

	// ���͹��ؽ�Ʈ ���, ������ �ϼ�, ��� ���� ���� Update���� �ʾƵ� �ȴ�.
	if( !m_bIntervalText || m_bDonePage || m_bPause )
	{
		std::list<CRowHtml_Item*>::iterator it;
		for( it = m_listRowHtml.begin(); it != m_listRowHtml.end(); ++it )
		{
			(*it)->Update( fElapsedTime );
		}

		return;
	}

	if( !m_pListRectangle )
		return;

	if( m_bImmediate )
		IntervalPageDone(m_nCurrentPage);

	// �������� ������ ������Ʈ�� ���� �ʴ´�.
	if( m_pListRectangle[m_nCurrentPage].empty() )
		return;

	m_fElapsedTime += fElapsedTime;

	// ���� ������ �ð��� m_fIntervalTime ���� ������ Update
	RwReal fRevivalTime = m_fElapsedTime / m_fIntervalTime;
	if( fRevivalTime > 1.0f )
	{
		// �������� ������ �´�.
		RwInt32 nRevivalCount = (RwInt32)fRevivalTime;
		
		// �Ҽ����� ������ �´�.
		RwReal fPercentage = fRevivalTime - (RwReal)nRevivalCount;
		
		// ���� Ÿ���� ����
		m_fElapsedTime = m_fIntervalTime * fPercentage;

		RwBool bDone = FALSE;
		for( RwInt32 j=0; j < nRevivalCount && bDone == FALSE; ++ j )
		{
			for( int i=0; i< m_nPresentNum; ++i)
			{
				// ���� �ݺ��ڿ� ��� �ִ� top�� ������ top�� �ٸ� ��� ������ �Ѿ ��.
				CRectangle rectScr = m_pHtmlBox->GetScreenRect();
				if( (*itListRect).top != m_nCurrentRow &&
					( itListRect != m_pListRectangle[m_nCurrentPage].begin() ) )
				{	
					// ������ top ����
					m_nCurrentRow = (*itListRect).top;

					// ������ �ϼ��Ǿ����� m_TextSurface�� m_SnapShot�� �����ش�.
					m_TextSurface.m_SnapShot.rtRect.top = rectScr.top;
					m_TextSurface.m_SnapShot.rtRect.left = rectScr.left;
					m_TextSurface.m_SnapShot.rtRect.right = rectScr.right;
					m_TextSurface.m_SnapShot.rtRect.bottom = rectScr.top + ((*itListRect).top - m_vecPageRect[m_nCurrentPage].top);

					// m_TextSurface�� UV ������Ʈ
					m_TextSurface.m_SnapShot.UVs[2] = (float)m_TextSurface.m_SnapShot.rtRect.GetWidth() 
						/ (float)m_TextSurface.m_pTexture->GetWidth();
					m_TextSurface.m_SnapShot.UVs[3] = (float)m_TextSurface.m_SnapShot.rtRect.GetHeight() 
						/ (float)m_TextSurface.m_pTexture->GetHeight();

					// ���� Interval�� ��µǴ� Plane ���� ������Ʈ
					m_planeInterval.rtRect.right = m_planeInterval.rtRect.left;
					m_planeInterval.rtRect.top = ((*itListRect).top - m_vecPageRect[m_nCurrentPage].top) + rectScr.top;

					// UV �� ����
					m_planeInterval.UVs[1] = (float)((*itListRect).top - m_vecPageRect[m_nCurrentPage].top)
						/ (float)m_TextSurface.m_pTexture->GetHeight();
				}

				// �� ���ھ� ������Ų��.
				m_planeInterval.rtRect.left = rectScr.left;

				// �̵��� �Ǿ�� �����Ҽ� �ֵ���.
				m_planeInterval.rtRect.top = ((*itListRect).top - m_vecPageRect[m_nCurrentPage].top) + rectScr.top;
				m_planeInterval.rtRect.right += (*itListRect).right;
				m_planeInterval.rtRect.bottom = m_planeInterval.rtRect.top + (*itListRect).bottom;

				// UV��ǥ�� ����ϰ�
				m_planeInterval.UVs[2] = (float)m_planeInterval.rtRect.GetWidth() / (float)m_TextSurface.m_pTexture->GetWidth();
				m_planeInterval.UVs[3] = m_planeInterval.UVs[1] + 
					( (float)m_planeInterval.rtRect.GetHeight() / (float)m_TextSurface.m_pTexture->GetHeight() );

				// ���� �������� ���ڸ� �� ����ߴٸ� �������� �ϼ���Ų��.
				itListRect++;
				if( itListRect == m_pListRectangle[m_nCurrentPage].end() )
				{
					IntervalPageDone( m_nCurrentPage );
					bDone = TRUE;
					break;
				}
			}
		}
	}
}

/**
* \brief �������� ������ ����
* \return ������ ����
*/
INT CHtmlBox_Generic::GetIntervalPageNums( VOID ) 
{
	return m_nPageCount;
}

INT CHtmlBox_Generic::GetCurrentPage(VOID)
{
	return m_nCurrentPage;
}

/**
* \brief ���� ������
* \return ��������
*/
BOOL CHtmlBox_Generic::SetNextPage( VOID ) 
{
	// �� ������������ �۴ٸ� ���� �������� ���� �����ش�.
	// �ƴ϶�� FALSE�� ����
	if( m_nCurrentPage < m_nPageCount-1 )
		++m_nCurrentPage;
	else
		return FALSE;

	// ������ �������� �ʱ�ȭ
	IntervalPageInit( m_nCurrentPage );
	ItemRenderToTexture( m_vecPageRect[m_nCurrentPage].top );

	if( m_bImmediate )
		IntervalPageDone( m_nCurrentPage );

	return TRUE;
}

/**
* \brief ���� ������
* \return ��������
*/
BOOL CHtmlBox_Generic::SetPrevPage( VOID ) 
{
	// ���� �������� �ѱ�
	if( m_nCurrentPage > 0 )
		--m_nCurrentPage;
	else
		return FALSE;

	// ���ҵ� �������� �ʱ�ȭ
	IntervalPageInit( m_nCurrentPage );
	ItemRenderToTexture( m_vecPageRect[m_nCurrentPage].top );

	if( m_bImmediate )
		IntervalPageDone( m_nCurrentPage );

	return TRUE;
}

/**
* \brief ��������ŵ
* \return ��������
*/
BOOL CHtmlBox_Generic::SetSkipPage( VOID ) 
{
	// IntervalText ��尡 �ƴ϶�� ����
	if( m_bIntervalText == FALSE )
		return FALSE;

	// �̹� �������� �ϼ��Ǿ� �ִٸ� ����
	if( m_bDonePage == FALSE )
	{
		IntervalPageDone( m_nCurrentPage );
		return TRUE;
	}
	else
		return FALSE;
}

/**
* \brief ������ �ʱ�ȭ
* �������� ����ϱ� ���� �ʱ�ȭ
* \param nPage (INT)������ ��ȣ
*/
VOID CHtmlBox_Generic::IntervalPageInit( INT nPage ) 
{
	if( nPage >= m_nPageCount || nPage < 0 )
		return;

	// ���� ���� �ִٸ� �÷��� �簳
	if( m_bPause )
		m_bPause = FALSE;

	// �ݺ����� ��ġ �ʱ�ȭ
	itListRect = m_pListRectangle[nPage].begin();
	m_nCurrentRow = (*itListRect).top;

	// ���� ��� ȿ���� ���� Plane�� �ʱ�ȭ�Ѵ�.
	m_planeInterval.rtRect.left = m_TextSurface.m_SnapShot.rtRect.left;
	m_planeInterval.rtRect.top = m_TextSurface.m_SnapShot.rtRect.top;
	m_planeInterval.rtRect.right = m_TextSurface.m_SnapShot.rtRect.left;
	m_planeInterval.rtRect.bottom = m_TextSurface.m_SnapShot.rtRect.top;

	// UV �ʱ�ȭ
	m_planeInterval.UVs[0] = 0.0f;
	m_planeInterval.UVs[1] = 0.0f;
	m_planeInterval.UVs[2] = 0.0f;
	m_planeInterval.UVs[3] = 0.0f;

	// ������ �����ش�. �ʱ�ȭ
	m_planeInterval.uAlpha = m_TextSurface.m_SnapShot.uAlpha;
	m_planeInterval.uBlue = m_TextSurface.m_SnapShot.uBlue;
	m_planeInterval.uRed = m_TextSurface.m_SnapShot.uRed;
	m_planeInterval.uGreen = m_TextSurface.m_SnapShot.uGreen;

	// �ؽ��ĸ� ������ �ִ� �κе� �ʱ�ȭ�Ѵ�.
	m_TextSurface.m_SnapShot.rtRect.right = m_TextSurface.m_SnapShot.rtRect.left;
	m_TextSurface.m_SnapShot.rtRect.bottom = m_TextSurface.m_SnapShot.rtRect.top;

	// UV
	m_TextSurface.m_SnapShot.UVs[0] = 0.0f;
	m_TextSurface.m_SnapShot.UVs[1] = 0.0f;
	m_TextSurface.m_SnapShot.UVs[2] = 0.0f;
	m_TextSurface.m_SnapShot.UVs[3] = 0.0f;

	m_bDonePage = FALSE;

	if( m_bDynamic )
		AdjustToHeightString();
}

/**
* \brief ������ �Ϸ�
* UV ��ǥ ����(�Ϸ�)
* \param nPage (INT)������ ��ȣ
*/
VOID CHtmlBox_Generic::IntervalPageDone( INT nPage ) 
{
	if( nPage >= m_nPageCount )
		return;

	m_bDonePage = TRUE;

	CRectangle rectScr = m_pHtmlBox->GetScreenRect();

	INT nOffsetY = 0;

	//// Interval Text�� ��� �� �������� ��� �ִ� �������� ũ��� Y�� Offset�� �������ְ�
	//if( m_bIntervalText )
	//{
	//	if( !m_vecPageRect.empty() )
	//		nOffsetY = GetAlignOffsetY(m_dwStyle, rectScr.GetHeight(), m_vecPageRect[nPage].GetHeight());
	//}

	m_TextSurface.m_SnapShot.rtRect.left = rectScr.left;
	m_TextSurface.m_SnapShot.rtRect.top = rectScr.top + nOffsetY;
	m_TextSurface.m_SnapShot.rtRect.right = rectScr.left + m_vecPageRect[nPage].GetWidth();
	m_TextSurface.m_SnapShot.rtRect.bottom = rectScr.top + m_vecPageRect[nPage].GetHeight() + nOffsetY;

	m_TextSurface.m_SnapShot.UVs[0] = 0.0f;
	m_TextSurface.m_SnapShot.UVs[1] = 0.0f;
	m_TextSurface.m_SnapShot.UVs[2] = (float)rectScr.GetWidth() / (float)m_TextSurface.m_pTexture->GetWidth();
	m_TextSurface.m_SnapShot.UVs[3] = (float)m_vecPageRect[nPage].GetHeight() / (float)m_TextSurface.m_pTexture->GetHeight();

	// ���� �Ϸ�� �������� Signal�� ������.
	m_SigPageDone( nPage );
}

/**
* \brief IntervalText �޸� ���� �� �ʱ�ȭ
* IntervalText�� ���Ǿ��� �޸𸮿� �������� �����ϰ� �ʱ�ȭ�Ѵ�.
*/
VOID CHtmlBox_Generic::DeleteIntervalText( VOID ) 
{
	// Intervals Text
	if( m_pListRectangle )
	{
		// �迭�� ��ȸ�Ͽ� �� ����Ʈ�� �ʱ�ȭ
		for( int i=0; i < m_nPageCount; ++i )
			m_pListRectangle[i].clear();

		// �迭�� ����
		NTL_ARRAY_DELETE( m_pListRectangle );
	}

	// [br]�±��� ���� ����
	m_vecNewLineIdx.clear();
	m_vecNewPageIdx.clear();

	// �������� ������ ����
	m_vecPageRect.clear();

	m_nPageCount = 1;

	m_fElapsedTime = 0.0f;
	m_nCurrentPage = 0;
	m_nCurrentRow = 0;

	m_bPause = FALSE;
	m_bDonePage = FALSE;
	m_bImmediate = FALSE;
}

/**
* \brief ���� �� �������� ã�� ���� �� �������� ���̿� ���� ���θ� �����Ѵ�. ( Dynamic �� ��� )
*/
VOID CHtmlBox_Generic::AdjustToWidthString( VOID ) 
{
	m_nMaxWidth = FindMaxWidthItem();
	
	CRectangle rectClient = m_pHtmlBox->GetClientRect();

	INT nResizeWidth = m_nMaxWidth;

	if( m_nMinCX > m_nMaxWidth )
	{
		nResizeWidth = m_nMinCX;
	}

	if( m_nMaxCX < m_nMaxWidth )
	{
		nResizeWidth = m_nMaxCX;
	}

	// ���� ����� �����ش�.
	m_pHtmlBox->SetSize( nResizeWidth, rectClient.GetHeight() );
}

/**
/* \brief ���� ���� Item�鿡 ���缭 ������Ʈ�� ����� �����Ѵ�.
*/
VOID CHtmlBox_Generic::AdjustToHeightString( VOID ) 
{
	INT nHeight = m_pHtmlBox->GetHeight();

	// In the Interval Text Mode, the size is calculated from the calculated page information.
	if( m_bIntervalText )
	{
		if( m_vecPageRect.empty() )
			return;

		nHeight = m_vecPageRect[m_nCurrentPage].GetHeight();
	}
	// Otherwise, it is calculated using the bottom of the Area of CRowHtml_Item at the end.
	else
	{
		if( m_listRowHtml.empty() )
			return;

		CRowHtml_Item* pItem = m_listRowHtml.back();
		CRectangle rectArea = pItem->GetArea();

		nHeight = rectArea.bottom;
	}
	//DBO_WARNING_MESSAGE("nHeight: " << nHeight << " m_nMaxCY: " << m_nMaxCY);
	// disabled by daneos to fix height issue of message box
	//if( nHeight > m_nMaxCY )
	//	nHeight = m_nMaxCY;

	if( nHeight < m_nMinCY )
		nHeight = m_nMinCY;

	m_pHtmlBox->SetSize( m_pHtmlBox->GetWidth(), nHeight);
}

/**
* \brief �������� �÷����Ѵ�.
* \param nPage (INT)�÷����� ������
* \return ��������
*/
BOOL CHtmlBox_Generic::SetPlayPage( INT nPage ) 
{
	if( nPage >= m_nPageCount || nPage < 0 )
		return FALSE;

	if( m_bIntervalText )
	{
		m_nCurrentPage = nPage;
		IntervalPageInit( m_nCurrentPage );
		ItemRenderToTexture( m_nCurrentPage );

		if( m_bImmediate )
			IntervalPageDone( m_nCurrentPage );

		return TRUE;
	}
	else
		return FALSE;
}

/**
* \brief �Ͻø���
* \param bPause (BOOL)�Ͻø���(default = TRUE)
*/
VOID CHtmlBox_Generic::SetPause( BOOL bPause /*= TRUE */ ) 
{
	m_bPause = bPause;
}

/**
* \brief �������
* \param bImmediate (BOOL)�������(default = TRUE)
*/
VOID CHtmlBox_Generic::SetImmediate( BOOL bImmediate /*= TRUE */ ) 
{
	m_bImmediate = bImmediate;
}

/**
* \brief �ѹ��� ����� ������ ������ �����Ѵ�.
* \param nNum	�ѹ��� ����� ����
*/
VOID CHtmlBox_Generic::SetPresentNum( INT nNum ) 
{
	m_nPresentNum = nNum;

	if( m_nPresentNum < 1 )
		m_nPresentNum = 1;

	if( m_nPresentNum > 10 )
		m_nPresentNum = 10;

}

/**
* \brief �ѹ��� ����� ������ ����� ��ȯ�޴´�.
*/
INT gui::CHtmlBox_Generic::GetPresentNum() 
{
	return m_nPresentNum;
}

/**
/* \brief m_pHtmlDoc �� �����ϰ� �������� Item�� �ʱ�ȭ�Ѵ�.
*/
VOID CHtmlBox_Generic::DeleteItem(VOID)
{
	NTL_DELETE( m_pHtmlDoc );

	// rendering item delete
	DeleteRenderItem();
}

/**
/* \brief m_listRowHtml �� ����ִ� �������� Item���� �����ϰ� list�� clear�Ѵ�.
*/
VOID CHtmlBox_Generic::DeleteRenderItem(VOID)
{
	std::list<CRowHtml_Item*>::iterator it;
	for(it = m_listRowHtml.begin(); it != m_listRowHtml.end(); it++)
	{
		NTL_DELETE( *it );
	}

	m_listRowHtml.clear();
}

/**
* \brief �����۵��� �Ӽ��� ������Ʈ�� ����� �˸°� �ֱ� ���Ͽ� �����ؼ�
* CRowHtml_Item���� �����.
*/
VOID CHtmlBox_Generic::ItemDisposition(VOID)
{
	// ���� �ۼ�.
	DeleteIntervalText();	
	DeleteRenderItem();

	// CHtmlDoc�� ��� �ִ� ������ ����Ʈ�� ������ �´�.
	CHtml_Item *pDocHtmlItem;
	CHtmlDoc::ListHtmlItem::iterator docit;
	CHtmlDoc::ListHtmlItem listHtmlItem = m_pHtmlDoc->GetItems();

	// ��� �������� ��ġ�� �ʱ�ȭ���ش�.
	for(docit = listHtmlItem.begin(); docit != listHtmlItem.end(); ++docit)
	{
		pDocHtmlItem = (*docit);
		pDocHtmlItem->ResetItemDisposition();
	}

	// �����۵��� HtmlBox�� �˸°� ���� �ϱ� ���Ͽ� �ʱ��� ����ϴ� ������ ����ش�.
	CRectangle rect = m_pHtmlBox->GetClientRect();

	// ��ũ�ѹٰ� Ȱ��ȭ ���¶�� ScrollBar ��ŭ Width�� ���ش�.
	if(m_bVScrollEnable)
		rect.right -= m_pHtmlBox->m_pScrollBar->GetSliderRect().GetWidth();		

	// �� �����۵��� ��ġ�� �����ϱ� �������� ũ�⸦ �̸� �����Ѵ�.
	m_nItemCx = rect.GetWidth();
	m_nItemCy = rect.GetHeight();

	INT nCurrIdx = 0;

	rect.bottom = INT_MAX;

	CRowHtml_Item *pRowHtml = NTL_NEW CRowHtml_Item(nCurrIdx, rect, FALSE, m_nLineInterY);
	m_listRowHtml.push_back(pRowHtml);

	// CHtmlDoc�� ����ִ� ��� �����۵��� ���� HtmlBox UI�� ũ�⿡ ���缭
	// �� �ึ�� CRowHtml_Item���� ����� ������ �Ѵ�.
	for(docit = listHtmlItem.begin(); docit != listHtmlItem.end(); ++docit)
	{
		pDocHtmlItem = (*docit);
		
		// [br] �±��� �������� ����س��´�.
		if( pDocHtmlItem->GetType() == HTML_ITEM_NEWLINE )
			m_vecNewLineIdx.push_back( nCurrIdx );
		
		while(pDocHtmlItem)
		{
			pDocHtmlItem = pRowHtml->ItemDisposition(pDocHtmlItem, m_nLineInterY);
			if(pRowHtml->IsFull())
			{
				CRectangle rtArea = pRowHtml->GetArea();
				rect.top = rtArea.bottom + m_nLineInterY;
				pRowHtml = NTL_NEW CRowHtml_Item(++nCurrIdx, rect, FALSE, m_nLineInterY);
				m_listRowHtml.push_back(pRowHtml);
			}
		}
	}

	// ���������� ���� pRowHtml �̸� ��ü ������ �������ش�.
	if(pRowHtml)
	{
		pRowHtml->ItemFinishDisposition();		
	}

	// �� ���ھ� ��� ����� ���� ������� RowHtml_Item��� �� ���ھ� �ٽ� �ѹ� ����� ���༭
	// �������� �����Ͽ� �� �� �ֵ��� ���� �ϳ����� ��ġ�� ����ؼ� ������ �ִ´�.
	if( m_bIntervalText )
		IntervalTextPosCalc();

	// Link ������ ����Ѵ�.
	LinkRectCalc();
}

/**
/* \brief Item�� ũ�⸦ ����ϰ� ScrollBar�� Ȱ��ȭ �Ǿ�� �ϴ���, ScrollBar�� Range �������� �Ѵ�.
*/
VOID CHtmlBox_Generic::ItemLineSorting(VOID)
{
	m_nItemCy = 0;

	if(m_listRowHtml.size() > 0)
	{
		std::list<CRowHtml_Item*>::reverse_iterator rit = m_listRowHtml.rbegin();
		CRectangle rtArea = (*rit)->GetArea();
		m_nItemCy = rtArea.bottom;
	}	

	// Interval Text ��带 �����Ҷ��� Scroll�� ������� �ʴ´�.
	if(m_bVScrollEnable == FALSE && m_bIntervalText == FALSE)
	{
		CRectangle rect = m_pHtmlBox->GetClientRect();
		//CRectangle rect = m_rectClient;
		if(m_nItemCy > rect.GetHeight())
			SetVScrollEnable(TRUE);
	}

	if(m_bVScrollEnable)
	{
		CRectangle rect = m_pHtmlBox->GetClientRect();
		if(m_nItemCy > rect.GetHeight())
			SetVScrollRange(m_nItemCy - rect.GetHeight());
	}
}

/**
* \brief CHtml_Item���� Texture�� �������Ѵ�.
* \param nVScrollPos	(INT)	��ũ���� ��ġ
*/
VOID CHtmlBox_Generic::ItemRenderToTexture(INT nVScrollPos)
{
	if(m_TextSurface.m_pTexture == NULL)
		return;

	// texture clear
	m_TextSurface.m_pTexture->FillClear();

	// vertical align
	CRectangle rect = m_pHtmlBox->GetClientRect();

	// Item �� ������ �� ���� ��ũ�� Offset�� �������Ѵ�.
	INT nOffsetX = 0;
	INT nOffsetY = -nVScrollPos;

	std::list<CRowHtml_Item*>::iterator it;
	for(it = m_listRowHtml.begin(); it != m_listRowHtml.end(); it++)
	{
		(*it)->OnPrePaint(nOffsetX, nOffsetY, rect, m_TextSurface.m_pTexture, m_dwStyle);
	}

}

/**
* \brief dwAlign�� ���缭 X�� Offset���� ����Ѵ�.
* \param dwAlign	(DWORD) ���� �Ӽ�
* \param nClipWidth	(INT) ����� X ����
* \param nItemWidth	(INT) ���� �ȿ� �� �ִ� �������� ũ��
* \return Style�� �´� X�� Offset ��
*/
INT CHtmlBox_Generic::GetAlignOffsetX(DWORD dwAlign, INT nClipWidth, INT nItemWidth)
{
	INT nOffsetX = 0;

	if(ENABLE_COMPONENT_STYLE(dwAlign,COMP_TEXT_CENTER))
	{
		nOffsetX = (nClipWidth - nItemWidth)/2;
		if(nOffsetX < 0)
			nOffsetX = 0;
	}
	else if(ENABLE_COMPONENT_STYLE(dwAlign,COMP_TEXT_RIGHT))
	{
		nOffsetX = nClipWidth - nItemWidth - 2;
		if(nOffsetX < 0)
			nOffsetX = 0;
	}

	return nOffsetX;
}

/**
* \brief dwAlign�� ���缭 Y�� Offset���� ����Ѵ�.
* \param dwAlign		(DWORD) ���� �Ӽ�
* \param nClipHeight	(INT) ����� Y ����
* \param nItemHeight	(INT) ���� �ȿ� �� �ִ� �������� ũ��
* \return Style�� �´� Y�� Offset ��
*/
INT	CHtmlBox_Generic::GetAlignOffsetY(DWORD dwAlign, INT nClipHeight, INT nItemHeight)
{
	INT nOffsetY = 0;

	if(ENABLE_COMPONENT_STYLE(dwAlign,COMP_TEXT_VERTICAL_CENTER))
	{
		nOffsetY = (nClipHeight - nItemHeight)/2;
		if(nOffsetY < 0)
			nOffsetY = 0;
	}
	else if(ENABLE_COMPONENT_STYLE(dwAlign,COMP_TEXT_DOWN))
	{
		nOffsetY = nClipHeight - nItemHeight - 2;
		if(nOffsetY < 0)
			nOffsetY = 0;
	}

	return nOffsetY;
}

/**
* \brief Vertical ScrollBar�� Ȱ��ȭ ����
* \param bEnable	(BOOL) TRUE = Ȱ��ȭ, FALSE = ��Ȱ��ȭ
*/
VOID CHtmlBox_Generic::SetVScrollEnable(BOOL bEnable)
{
	m_bVScrollEnable = bEnable;
	m_pHtmlBox->m_pScrollBar->SetRange( 0, 0 );

	if( bEnable )
		m_pHtmlBox->m_pScrollBar->Show( true );
	else
		m_pHtmlBox->m_pScrollBar->Show( false );
}

/**
* \brief Vertical ScrollBar�� �̵��Ÿ��� �����Ѵ�.
* \param nRange		(INT) ��ũ�� �Ǵ� ������ �ȼ�
*/
VOID CHtmlBox_Generic::SetVScrollRange(INT nRange)
{
	m_nVScrollRange = nRange;

	m_pHtmlBox->m_pScrollBar->SetRange( 0, nRange );
}

/**
* \brief Vertical ScrollBar�� ��ũ�ѵ� ������ ����
* \param nPos	(INT) ��ũ�ѵ� ������ �ȼ�
*/
VOID CHtmlBox_Generic::SetVScrollPos(INT nPos)
{
	m_nVScrollPos = nPos;

	// nPos��ŭ Offset�� �־ Item���� �ؽ��Ŀ� ������ �Ѵ�.
	ItemRenderToTexture(nPos);

	// ScrollBar�� ��ũ�� �� ��ġ�� �����Ѵ�.
	m_pHtmlBox->m_pScrollBar->SetValue( nPos );

	LinkVScrollCalc( nPos );
}

/**
* \brief ������ CRowHtml_Item�� IntervalText Mode�� �� ���
* ���� �����ϰ� �ִ� CRowHtml_Item���� ������ ������ Page�� ���ؿ� ���缭 Interval Text Mode�� ����Ѵ�.
* Component�� Script�� �ʱ⿡ �������� ������ ����� ����� ������ ��Ȯ������.
*/
VOID CHtmlBox_Generic::IntervalTextPosCalc(VOID)
{
	// SetOption���� ������ ��� ��
	CRectangle rect = m_rectClient;

	// �� ���������� �� ���� ���� ���� ����Ͽ� �������� ������ ���� �����Ѵ�.
	// �׸��� �������� �������� ������ ���� ����Ѵ�.
	std::list<CRowHtml_Item*>::iterator itRowHtml;
	int nSumHeightRows = 0, nLastBrRow = 0;
	int nLiveBrRow = 0;
	CRectangle rectPage;

	for( itRowHtml = m_listRowHtml.begin(); itRowHtml != m_listRowHtml.end(); ++itRowHtml )
	{
		CRowHtml_Item* pRowHtml = (*itRowHtml);
		nSumHeightRows += pRowHtml->GetAreaHeight() + m_nLineInterY;	// ������ ���� ���̸� ���Ѵ�.

		// ������� CRowHtml_Item ���� �� ���̰� ���� �������� �����
		// �� �������� �����ϴ� ������ br�±׸� ����Ѵ�.
		if( rect.GetHeight() < nSumHeightRows )
		{
			m_nPageCount++;

			if( nLiveBrRow == nLastBrRow )
				nLastBrRow = (*itRowHtml)->GetCurrentIndex() - 1;

			int nPrevBrOffset = pRowHtml->GetCurrentIndex() - nLastBrRow;
			std::advance( itRowHtml, -nPrevBrOffset );

			nSumHeightRows = 0;

			// �������� �Ѿ�� ���� ��ȣ�� ����Ѵ�.
			m_vecNewPageIdx.push_back( (*itRowHtml)->GetCurrentIndex() );
			nLiveBrRow = (*itRowHtml)->GetCurrentIndex();
		}

		// ���� �������� ������ [br]�±׸� ����س��´�.
		VECINT::iterator itVecNewLine = 
			std::find( m_vecNewLineIdx.begin(), m_vecNewLineIdx.end(), pRowHtml->GetCurrentIndex() );
		if( itVecNewLine != m_vecNewLineIdx.end() )
			nLastBrRow = pRowHtml->GetCurrentIndex();
	}

	// ���� m_pListRectangle�� �̹� ������ ��� �������� ����� �����Ѵ�.
	NTL_ARRAY_DELETE( m_pListRectangle );

	// ������ ������ ���缭 ����Ʈ�� ����� �� ����Ʈ�� ������ ���� ��ġ�� ����Ͽ� ����Ѵ�.

	// ������ �Ҵ�
	if( m_nPageCount > 0 )
		m_pListRectangle = NTL_NEW LISTRECTANGLE[m_nPageCount];

	// ���� ��ġ ���
	int nCurrentPage = 0;
	for( itRowHtml = m_listRowHtml.begin(); itRowHtml != m_listRowHtml.end(); ++itRowHtml )
	{
		CRowHtml_Item* pRowHtml = (*itRowHtml);

		// List�� ������� pRowHtml�� ������ �ִ� String�� ��ġ�� ��´�.
		pRowHtml->GetItemRect( m_pListRectangle[nCurrentPage] );

		// ���� ���� ���� �������� �Ѿ�� ������ ã�ƺ��� ���� �������� �Ѿ�� ���̶��
		// �������� ���������ְ� �������� ������ ����Ѵ�.
		int nCurrentIdx = pRowHtml->GetCurrentIndex();
		VECINT::iterator itVecNewPage = 
			std::find( m_vecNewPageIdx.begin(), m_vecNewPageIdx.end(), nCurrentIdx );

		// �����ϴ� ���� �������� ����
		if( itVecNewPage != m_vecNewPageIdx.end() )
			++nCurrentPage;
	}

	// ������ �������� br�� ��� ���� �� �����Ƿ� �˻����ش�. (�׸��� ������ �������� ������� �ʴ´�.)
	if( m_pListRectangle[m_nPageCount-1].empty() )
		m_nPageCount -= 1;

	// �ʱ�� ù��° �������� �����ְ� �������� ũ�⸦ ����Ѵ�.
	IntervalPagePosCalc();
	IntervalPageInit( 0 );
}

/**
* \brief �������� ��ġ�� ����Ѵ�.
* IntervalMode�� �������� �������� ��ġ�� ����Ѵ�.
*/
VOID CHtmlBox_Generic::IntervalPagePosCalc( VOID ) 
{
	// m_vecPageRect�� ������� �ʴٸ� �� ����ϴ� ���̹Ƿ� ����ش�.
	if( !m_vecPageRect.empty() )
		m_vecPageRect.clear();

	CRectangle rectScr = m_pHtmlBox->GetScreenRect();

	for(int i=0; i<m_nPageCount; ++i)
	{
		CRectangle rect;

		CRectangle rectBegin = (*(m_pListRectangle[i].begin()));
		CRectangle rectEnd = (*(m_pListRectangle[i].rbegin()));

		rect.left = 0;
		rect.top = rectBegin.top;
		rect.right = rectScr.GetWidth();
		rect.bottom = rectEnd.top + rectEnd.bottom;

		m_vecPageRect.push_back( rect );
	}
}

/**
* \brief ��ũ��Ʈ�� �Ӽ��� �о���δ�.
* \param options (CComponentOptions&) ������Ʈ�� ��ũ��Ʈ ���������� �о���� �Ӽ�
*/
VOID CHtmlBox_Generic::OnSetOptions(const CComponentOptions& options)
{
	if(options.Exists("x"))
	{
		m_rectScreen.left = options.GetValueAsInt("x");
		m_rectClient.left = 0;
	}

	if(options.Exists("y"))
	{
		m_rectScreen.top = options.GetValueAsInt("y");
		m_rectClient.left = 0;
	}

	if(options.Exists("width"))
	{
		m_rectScreen.right = m_rectScreen.left + options.GetValueAsInt("width");
		m_rectClient.right = options.GetValueAsInt("width");
	}

	if(options.Exists("height"))
	{
		m_rectScreen.bottom = m_rectScreen.top + options.GetValueAsInt("height");
		m_rectClient.bottom = options.GetValueAsInt("height");
	}

	if(options.Exists("surface_file"))
	{
		std::string file = options.GetValue("surface_file"); 
		CSurfaceManager *pSurfaceManager = m_pHtmlBox->GetSurfaceManager();
		if(pSurfaceManager)
		{
			int nCount = options.Count("surface");
			for(int i=0 ; i<nCount ; i++)
				AddSurface(pSurfaceManager->GetSurface(file,options.GetValue("surface",i))); 
		}
	}
	// ��Ʈ ũ�� ����
	if(options.Exists("font_ratio"))
	{
		// script�� ������ ���� ( 0.0 < float < 10.0 ) ���� �����Ѵ�.
		m_fRatio = options.GetValueAsFloat("font_ratio");
		if( ( m_fRatio <= 0.0f ) | ( m_fRatio > 10.0f ) )
			m_fRatio = 1.0f;
	}
	
	// Dynamic �Ӽ� ��ũ��Ʈ
	if( options.Exists("dynamic") )
	{
		m_bDynamic = options.GetValueAsBool("dynamic");

		// Dynamic �Ӽ��̶�� ����Ʈ�� �ִ� ���� ���� ������Ʈ�� ũ�Ⱑ �ȴ�.
		m_nMaxCX = m_pHtmlBox->GetScreenRect().GetWidth();
		m_nMaxCY = m_pHtmlBox->GetScreenRect().GetHeight();

		if( options.Exists( "max_cx" ) )
			m_nMaxCX = options.GetValueAsInt( "max_cx" );
		if( options.Exists( "max_cy" ) )
			m_nMaxCY = options.GetValueAsInt( "max_cy" );
		if( options.Exists( "min_cx" ) )
			m_nMinCX = options.GetValueAsInt( "min_cx" );
		if( options.Exists( "min_cy" ) )
			m_nMinCY = options.GetValueAsInt( "min_cy" );
	}

	// text style
	if( options.Exists( "text_style" ) )
	{
		INT nCount = options.Count( "text_style" );
		for( INT i = 0; i < nCount; ++i )
		{
			std::string style = options.GetValue( "text_style", i );

			if(style == "left")
			{
				m_dwStyle |= COMP_TEXT_LEFT;
			}
			if(style == "center")
			{
				m_dwStyle |= COMP_TEXT_CENTER;
			}
			if(style == "right")
			{
				m_dwStyle |= COMP_TEXT_RIGHT;
			}
			if( style == "up" )
			{
				m_dwStyle |= COMP_TEXT_UP;
			}
			if( style == "down" )
			{
				m_dwStyle |= COMP_TEXT_DOWN;
			}
			if( style == "verticalcenter" )
			{
				m_dwStyle |= COMP_TEXT_VERTICAL_CENTER;
			}
		}
	}

	CreateTextTexture();
}

/**
* \brief ������� RowHtml_Item���� �������Ѵ�.
*/
VOID CHtmlBox_Generic::OnPaint(VOID)
{
	// HtmlBox�� �� ����� Paint
	std::list<CSurface>::iterator the; 
	for(the=m_stlSurface.begin(); the!=m_stlSurface.end(); the++)
	{
		g_GuiRenderer.RenderQueue(&(*the).m_SnapShot, (*the).m_pTexture);
	}

	// BackPic���� ������
	
	CRectangle rtScreen = m_pHtmlBox->GetScreenRect();

	if( m_pHtmlDoc )
	{
		std::list<CHtml_Item*>::iterator it;
		for(it = m_pHtmlDoc->m_listItem.begin(); it != m_pHtmlDoc->m_listItem.end(); it++)
		{
			(*it)->OnBackPaint(rtScreen);
		}
	}


	INT nOffsetX = 0;
	INT nOffsetY = 0;
	CRectangle rect = m_pHtmlBox->GetClientRect();

	// Interval Text�� ��� �� �������� ��� �ִ� �������� ũ��� Y�� Offset�� �������ְ�
	if( m_bIntervalText )
	{
		if( !m_vecPageRect.empty() )
		{
			nOffsetX = GetAlignOffsetX(m_dwStyle, rect.GetWidth(), m_nMaxWidth);
			nOffsetY = GetAlignOffsetY(m_dwStyle, rect.GetHeight(), m_vecPageRect[m_nCurrentPage].GetHeight());
		}
	}
	// �ƴ� ����� ��ü �������� ���̷� ����Ѵ�.
	else
	{
		nOffsetX = GetAlignOffsetX(m_dwStyle, rect.GetWidth(), m_nMaxWidth);
		nOffsetY = GetAlignOffsetY(m_dwStyle, rect.GetHeight(), m_nItemCy);
	}

	// Offset���� �̿��Ͽ� ���ĵ� ũ�⿡ ���缭 Texture�� ����.
	PlaneSnapShot sOffsetSnapShot = m_TextSurface.m_SnapShot;

	sOffsetSnapShot.rtRect.left += nOffsetX;
	sOffsetSnapShot.rtRect.top += nOffsetY;
	sOffsetSnapShot.rtRect.right += nOffsetX;
	sOffsetSnapShot.rtRect.bottom += nOffsetY;
	
	g_GuiRenderer.RenderQueue( &sOffsetSnapShot, m_TextSurface.m_pTexture );

	sOffsetSnapShot = m_planeInterval;

	sOffsetSnapShot.rtRect.left += nOffsetX;
	sOffsetSnapShot.rtRect.top += nOffsetY;
	sOffsetSnapShot.rtRect.right += nOffsetX;
	sOffsetSnapShot.rtRect.bottom += nOffsetY;

	// IntervalText Mode���� �ѱ��ھ� ��µǴ� ����
	if( m_bIntervalText && !m_bDonePage )
		g_GuiRenderer.RenderQueue( &sOffsetSnapShot, m_TextSurface.m_pTexture );

	// �׸��� �ʿ��� �κ��� Paint
	std::list<CRowHtml_Item*>::iterator itPic;
	for(itPic = m_listRowHtml.begin(); itPic != m_listRowHtml.end(); itPic++)
	{
		(*itPic)->OnPaint(rtScreen);
	}
}



/**
* \brief Component�� Move �Ǿ��� �� ȣ��Ǵ� �Լ�
* \param nX		(int) nX
* \param nY		(int) nY
*/
VOID CHtmlBox_Generic::OnMove(int nX,int nY)
{

	CRectangle rtScreen = m_pHtmlBox->GetScreenRect();
	CRectangle rtRect;

	rtRect = m_TextSurface.m_SnapShot.rtRect;

	m_TextSurface.m_SnapShot.rtRect.left	= rtScreen.left;
	m_TextSurface.m_SnapShot.rtRect.top		= rtScreen.top;
	m_TextSurface.m_SnapShot.rtRect.right	= rtScreen.left + rtRect.GetWidth();
	m_TextSurface.m_SnapShot.rtRect.bottom	= rtScreen.top + rtRect.GetHeight();

	std::list<CSurface>::iterator the;
	for(the=m_stlSurface.begin(); the!=m_stlSurface.end(); the++)
	{
		rtRect = (*the).m_Original.rtRect;

		(*the).m_SnapShot.rtRect.left	= rtRect.left + rtScreen.left;
		(*the).m_SnapShot.rtRect.top	= rtRect.top + rtScreen.top;
		(*the).m_SnapShot.rtRect.right	= rtRect.right + rtScreen.left;
		(*the).m_SnapShot.rtRect.bottom	= rtRect.bottom + rtScreen.top;
	}
}

VOID CHtmlBox_Generic::OnResize(int nCx, int nCy)
{
	// IntervalText Mode�� Dynamic �Ӽ��ε�
	// ���� �������� ù �������� �ƴ� ���
	// ����
	if( m_bIntervalText && m_bDynamic )
	{
		if( m_nCurrentPage != 0 )
		{
			return;
		}
	}

	CRectangle rtClient = m_pHtmlBox->GetClientRect();

	if(rtClient.GetWidth() != nCx || rtClient.GetHeight() != nCy)
	{
		CreateTextTexture();

		SetVScrollEnable(FALSE);

		if(m_pHtmlDoc)
		{
			ItemDisposition();
			ItemLineSorting();

			if(m_bVScrollEnable)
			{
				ItemDisposition();
				ItemLineSorting();
			}

			SetVScrollPos(0);
		}
	}
}

VOID CHtmlBox_Generic::OnSetAlpha( BYTE ucAlpha )
{
	CSurface* pSurface = NULL;

	std::list<CSurface>::iterator it;
	for( it = m_stlSurface.begin() ; it != m_stlSurface.end() ; ++it )
	{
		pSurface = &(*it);

		pSurface->m_SnapShot.uAlpha = ucAlpha;
	}

	m_TextSurface.m_SnapShot.uAlpha = ucAlpha;

	// ��µǰ� �ִ� ����
	if( m_bIntervalText )
		m_planeInterval.uAlpha = m_TextSurface.m_SnapShot.uAlpha;

	CRowHtml_Item* pRowHtml = NULL;
	std::list<CRowHtml_Item*>::iterator itRow;
	for( itRow = m_listRowHtml.begin(); itRow != m_listRowHtml.end(); ++itRow )
	{
		pRowHtml = (*itRow);

		pRowHtml->OnSetAlpha( ucAlpha );
	}
}

/**
* \brief ������ �����Ѵ�.
* \param ucRed		(BYTE) Red(0~255)
* \param ucGreen	(BYTE) Green(0~255)
* \param ucBlue		(BYTE) Blue(0~255)
*/
VOID CHtmlBox_Generic::OnSetColor( BYTE ucRed, BYTE ucGreen, BYTE ucBlue )
{
	CSurface* pSurface = NULL;

	std::list<CSurface>::iterator it;
	for( it = m_stlSurface.begin() ; it != m_stlSurface.end() ; ++it )
	{
		pSurface = &(*it);

		pSurface->m_SnapShot.uRed = ucRed;
		pSurface->m_SnapShot.uGreen = ucGreen;
		pSurface->m_SnapShot.uBlue = ucBlue;
	}

	m_TextSurface.m_SnapShot.uRed = ucRed;
	m_TextSurface.m_SnapShot.uGreen = ucGreen;
	m_TextSurface.m_SnapShot.uBlue = ucBlue;

	if( m_bIntervalText )
	{
		m_planeInterval.uRed = m_TextSurface.m_SnapShot.uRed = ucRed;
		m_planeInterval.uGreen = m_TextSurface.m_SnapShot.uGreen = ucGreen;
		m_planeInterval.uBlue = m_TextSurface.m_SnapShot.uBlue = ucBlue;
	}
}

/**
* \brief ��ũ���� �������� �� ȣ��Ǵ� �Լ�
* \param nPos	(INT) �̵��� �ȼ�
*/
VOID CHtmlBox_Generic::OnScrollMove( INT nPos )
{
	SetVScrollPos( nPos );
}

/**
* \brief Mouse Focusing�� ���Ͽ�
* \param key	(CKey&)
*/
VOID CHtmlBox_Generic::OnMouseMove( INT nKey, INT nXPos, INT nYPos )
{
	if( m_listDuplicateLink.empty() )
		return;

	LISTLINK::iterator itLink;
	for( itLink = m_listDuplicateLink.begin(); itLink != m_listDuplicateLink.end(); ++itLink )
	{
		if( (*itLink).rectArea.PtInRect( nXPos, nYPos ) )
		{
			if( (*itLink).pLinkItem->SetInverseColor( TRUE ) )
				ItemRenderToTexture(m_nVScrollPos);
			
			break;
		}
		else
		{
			if( (*itLink).pLinkItem->SetInverseColor( FALSE ) )
				ItemRenderToTexture( m_nVScrollPos);
		}
	}
}

/**
* \brief HtmlBox���� MouseDown�� ���� �� ó���Ǵ� �Լ�
*/
VOID CHtmlBox_Generic::OnMouseDown( const CKey& key )
{
	if( m_bIntervalText )
	{
		// Interval Text Mode�� ��� �������� �ϼ����� �ʾҴٸ� ó������ �ʴ´�.
		if( !m_bDonePage )
			return;

		if( m_pListLink[m_nCurrentPage].empty() )
			return;

		LISTLINK::iterator itLink;
		for( itLink = m_pListLink[m_nCurrentPage].begin(); itLink != m_pListLink[m_nCurrentPage].end(); ++itLink )
		{
			if( (*itLink).rectArea.PtInRect( (INT)key.m_fX, (INT)key.m_fY ) )
			{
				m_itCaptureLink = itLink;
			}
		}
	}
	else
	{
		if( m_listDuplicateLink.empty() )
			return;

		LISTLINK::iterator itLink;
		for( itLink = m_listDuplicateLink.begin(); itLink != m_listDuplicateLink.end(); ++itLink )
		{
			if( (*itLink).rectArea.PtInRect( (INT)key.m_fX, (INT)key.m_fY ) )
			{
				m_itCaptureLink = itLink;
				break;
			}
		}
	}
}

/**
* \brief HtmlBox���� Mouse Up�� ���� �� ó���Ǵ� �Լ�
* \param key		(CKey&) ���콺�� ��ǥ
*/
VOID CHtmlBox_Generic::OnMouseUp(const CKey& key)
{
	if( m_bIntervalText )
	{
		// Interval Text Mode�� ��� �������� �ϼ����� �ʾҴٸ� ó������ �ʴ´�.
		if( !m_bDonePage )
		{
			m_itCaptureLink = m_listDuplicateLink.end();
			return;
		}

		if( m_pListLink[m_nCurrentPage].empty() )
		{
			m_itCaptureLink = m_listDuplicateLink.end();
			return;
		}

		LISTLINK::iterator itLink;
		for( itLink = m_pListLink[m_nCurrentPage].begin(); itLink != m_pListLink[m_nCurrentPage].end(); ++itLink )
		{
			if( (*itLink).rectArea.PtInRect( (INT)key.m_fX, (INT)key.m_fY ) )
			{
				if( m_itCaptureLink == itLink )
				{
					sLinkRect sLink = (*itLink);

					// ������ ���Դٸ� Callback ȣ��
					if( m_fnHtmlLinkTag )
						(*m_fnHtmlLinkTag)(m_pHtmlBox, 
						sLink.pLinkItem->GetLinkType(), 
						sLink.pLinkItem->GetLinkIndex(),
						sLink.pLinkItem->GetLinkFilename());

					break;
				}
			}
		}
	}
	else
	{
		// Link ������ ���ų� Down�� ���� �ʾҴ���� ����
		if( m_listDuplicateLink.empty() ||
			m_itCaptureLink == m_listDuplicateLink.end() )
			return;

		LISTLINK::iterator itLink;
		for( itLink = m_listDuplicateLink.begin(); itLink != m_listDuplicateLink.end(); ++itLink )
		{
			if( (*itLink).rectArea.PtInRect( (INT)key.m_fX, (INT)key.m_fY ) )
			{
				if( m_itCaptureLink == itLink )
				{
					sLinkRect sLink = (*itLink);

					// ������ ���Դٸ� Callback ȣ��
					if( m_fnHtmlLinkTag )
						(*m_fnHtmlLinkTag)(m_pHtmlBox,
						sLink.pLinkItem->GetLinkType(), 
						sLink.pLinkItem->GetLinkIndex(),
						sLink.pLinkItem->GetLinkFilename());

					break;
				}
			}
		}

		m_itCaptureLink = m_listDuplicateLink.end();
	}
}

/**
* \brief �������� ���� ���� ���� ���� �������� ���Ѵ�.
* \return ���� ���� ���� ���� �������� ������
*/
INT CHtmlBox_Generic::FindMaxWidthItem( VOID ) 
{
	CHtmlDoc::ListHtmlItem listItems = m_pHtmlDoc->GetItems();

	if( listItems.empty() )
		return NULL;

	INT nMaxWidth = 0;
	INT nRealWidth = 0; // ��Ÿ �±׸� �����ؾ��Ѵ�.
	INT nWidth = 0;
	CHtml_Item* pHtmlItem = NULL;
	for( CHtmlDoc::ListHtmlItem::iterator it = listItems.begin(); it != listItems.end(); ++it )
	{
		if( (*it)->GetType() == HTML_ITEM_STRING ||
			(*it)->GetType() == HTML_ITEM_LINK )
			nWidth += (*it)->GetWidth();

		if( (*it)->GetType() == HTML_ITEM_NEWLINE )
			nWidth = 0;

		if( nMaxWidth < nWidth )
		{
			nMaxWidth = nWidth;
			pHtmlItem = (CHtml_Item*)(*it);
		}
	}

	return nMaxWidth;
}

/**
* \brief �����۸�ũ�� ������ ����Ѵ�.
*/
VOID gui::CHtmlBox_Generic::LinkRectCalc( VOID )
{
	if( m_listRowHtml.empty() )
		return;

	if( !m_listOriginLink.empty() )
		m_listOriginLink.clear();

	std::list<CRowHtml_Item*>::iterator itRowHtml;

	for( itRowHtml = m_listRowHtml.begin(); itRowHtml != m_listRowHtml.end(); ++itRowHtml )
	{
		(*itRowHtml)->GetLinkRect( m_listOriginLink );
	}

	m_listDuplicateLink = m_listOriginLink;

	// Interval Text Mode��� ���������� ��ũ ������ ��������� �Ѵ�.
	if( m_bIntervalText )
	{
		DeleteIntervalLink();

		if( m_listOriginLink.empty() )
			return;
		
		// ������ �� ���� ����Ʈ�� ����
		if( m_nPageCount > 0 )
			m_pListLink = NTL_NEW LISTLINK[m_nPageCount];
		
		// �� ���������� ������ ����Ͽ� �� ������ �ȿ� ���� �͵鳢�� ��Ƴ��´�.
		LISTLINK::iterator itOriginLink = m_listOriginLink.begin();
		int nPage = 0;
		while( itOriginLink != m_listOriginLink.end() )
		{
			if( m_vecPageRect[nPage].bottom >= (*itOriginLink).rectArea.bottom )
			{
				sLinkRect sRect;
				sRect.pLinkItem = (*itOriginLink).pLinkItem;
				if( nPage != 0 )
				{
					sRect.rectArea.top = (*itOriginLink).rectArea.top - m_vecPageRect[nPage-1].bottom;
					sRect.rectArea.bottom = (*itOriginLink).rectArea.bottom - m_vecPageRect[nPage-1].bottom;
				}
				else
				{
					sRect.rectArea.top = (*itOriginLink).rectArea.top;
					sRect.rectArea.bottom = (*itOriginLink).rectArea.bottom;
				}
				sRect.rectArea.left = (*itOriginLink).rectArea.left;
				sRect.rectArea.right = (*itOriginLink).rectArea.right;

				m_pListLink[nPage].push_back( sRect );
				++itOriginLink;
			}
			else
			{
				++nPage;
				if( nPage >= m_nPageCount )
					break;
			}
		}
	}
}

/**
* \brief ��ũ���� �����ӿ� ���� ��ũ�Ǵ� ������ �� ������ش�.
*/
VOID CHtmlBox_Generic::LinkVScrollCalc( INT nPos )
{
	// IntervalText Mode�� ���� ������� �ʴ´�.
	if( m_bIntervalText )
		return;

	if( m_listOriginLink.empty() )
		return;

	LISTLINK::iterator itLink;
	LISTLINK::iterator itDuplicateLink = m_listDuplicateLink.begin();
	for( itLink = m_listOriginLink.begin(); itLink != m_listOriginLink.end(); ++itLink )
	{
		(*itDuplicateLink).rectArea.top = (*itLink).rectArea.top - nPos;
		(*itDuplicateLink).rectArea.bottom = (*itLink).rectArea.bottom - nPos;
		++itDuplicateLink;
	}
}

/**
* \brief Interval Text Mode�� �� ����س��� �������� ��ũ ������ �����Ѵ�.
*/
VOID CHtmlBox_Generic::DeleteIntervalLink( VOID )
{
	if( m_pListLink )
	{
		for( int i = 0; i < m_nPageCount-1; ++i )
		{
			m_pListLink[i].clear();
		}

		NTL_ARRAY_DELETE( m_pListLink );
	}
}

VOID CHtmlBox_Generic::LinkHtmlLinkTag( HtmlLinkTagFunc fnLinkTag )
{
	m_fnHtmlLinkTag = fnLinkTag;
}


END_GUI


