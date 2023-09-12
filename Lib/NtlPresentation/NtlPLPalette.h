/*****************************************************************************
*
* File			: NtlPLPalette.h
* Author		: Hong sungbock
* Copyright		: (��)NTL
* Date			: 2008. 3. 13
* Abstract		: Presentation layer palette info
*****************************************************************************
* Desc          : Dbo���� ���̴� �ȷ�Ʈ ������ ������ �ִ�
*****************************************************************************/

#ifndef __NTL_PLPALETTE_H__
#define __NTL_PLPALETTE_H__

#define dEMBLEM_PALETTE_COUNT			32
#define	dPALETTE_EMBLEM_ELEMENT_NAME	"Emblem/element"


#define dINVALID_EMBLEM_PALETTE_INDEX			(0xff)
#define dINVALID_DOGI_PALETTE_INDEX				(0xff)


enum ePaletteType
{
	PALETTETYPE_EMBLEM,
	PALETTETYPE_DOGI,

	NUM_PALETTE
};

enum eLOAD_RESULT
{
	LOAD_RESULT_OK,

	LOAD_RESULT_FAIL_LOAD_FILE,						///< ������ ���� ���ߴ�
	LOAD_RESULT_NOT_EXIST_PALETTE,					///< �ش� �ȷ�Ʈ�� ����
	LOAD_RESULT_LESS_ELEMENT_COUNT,					///< �ȷ�Ʈ�� ���� ������ dEMBLEM_PALETTE_COUNT���� �۴�
	LOAD_RESULT_MORE_ELEMENT_COUNT,					///< �ȷ�Ʈ�� ���� ������ dEMBLEM_PALETTE_COUNT���� ����
};

class CNtlPLPalette
{
public:
	static CNtlPLPalette* GetInstance() { return m_pInstance; }

	CNtlPLPalette();
	virtual ~CNtlPLPalette();

	static VOID	CreateInstance();
	static VOID	DestoryInstance();

	COLORREF		GetColor(ePaletteType eType, RwUInt32 uiColorIndex);
	RwUInt8			GetIndex(ePaletteType eType, const COLORREF* pColor);

	///< �ȷ�Ʈ�� �ٽ� �о���̴� ���߿� �Լ�
	///< �����! ���� ���ӿ��� �ܺ� �����͸� �о� ������� ����.
	///< �ȷ�Ʈ ���� ����ڰ� �ȷ�Ʈ�� �ٲٰ� ���� GUI ���� �ٲ��� ���� ������ �ִ�
	eLOAD_RESULT	LoadPalette_forDeveloper();

protected:
	VOID	InitEmblemPalette();

protected:
	static CNtlPLPalette* m_pInstance;

	COLORREF		m_aEmblemColorPalette[dEMBLEM_PALETTE_COUNT];
};

static CNtlPLPalette* GetNtlPLPalette(VOID)
{
	return CNtlPLPalette::GetInstance();
}

#endif