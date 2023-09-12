#ifndef __GUI_HYPERTEXTBOX_GENERIC_H__
#define __GUI_HYPERTEXTBOX_GENERIC_H__

#include "gui_hypertextbox.h"
#include "gui_hypertextbox_item.h"

START_GUI

class CHyperTextBox_Generic
{
public:

	CHyperTextBox_Generic(CHyperTextBox *pSelf,
												DWORD dwStyle);

	CHyperTextBox_Generic(CHyperTextBox *pSelf,
												int nRow,
												int nColumn,
												int nInterval,
												DWORD dwStyle);
	~CHyperTextBox_Generic();

	CHyperTextBox *m_pHyperTextBox;

	std::list<CSurface> m_stlSurface;
	CSurface m_TextSurface;

	std::vector<HFONT> m_vecFont;
	HFONT				m_hFont;
	std::string m_strKey;					// 
	DWORD			m_dwStyle;					// scroll bar is vertival ro horizen
	COLORREF		m_dwTextColor;			// default text color
	COLORREF	m_dwTextBkColor;		// default text background color
	int				m_nBkMode;					// default text backgrond mode;
	int				m_nRow,m_nColumn;		// ������ row,colum ��ǥ.
	int				m_nInterval;				// ���� ����.
	int				m_nBlank;						// �Ѷ��ο� blank�� ä���� �� �ִ� blank ����.

	VOID Clear(VOID);
	//-------------------------------------------------------------------------
	//: font Create
	VOID CreateFont(TCHAR * szFaceName, int nHeight, int nAttributes = 0);
	
	VOID SetTextKey(const std::string &key);
	VOID TextOut(VOID);

// signals
public:

	CSignal_v1<CNode*> m_SigNode;

// callback function
private:

	VOID OnSetOptions(const CComponentOptions &options);
	VOID OnScrollValueChange(int nValue);
	VOID OnScrollMove(int nValue);
	VOID OnMove(int nOldX,int nOldY);
	VOID OnResize(int nOldW,int nOldH);
	VOID OnMouseDown(const CKey &key);
	VOID OnMouseWheel(int nFlags,short shDelta,CPos& ptPos);

	CSlot m_SlotSetOptions;
	CSlot m_SlotScrollValueChange;
	CSlot m_SlotScrollMove;
	CSlot m_SlotMove;
	CSlot m_SlotResize;
	CSlot m_SlotMouseDown;
	CSlot m_SlotMouseWheel;
		
private:

	//-------------------------------------------------------------------------

	std::vector<CHyperTextBox_Item> m_vecItem;

	VOID CreatureTexture(int nWidth,int nHeight);
	VOID CascadeTexture(VOID);
	VOID NodePasing(CTextNode *pText); 
	VOID DrawItem(VOID);
};

END_GUI

#endif
