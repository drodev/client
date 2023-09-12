/*****************************************************************************
*
* File			: NtlPlLensFlare
* Author		: agebreak
* Copyright	: (��)NTL
* Date			: 2007. 4. 19	
* Abstract		: Presentation layer LensFlare entity class
*****************************************************************************
* Desc         : �¾��� ��ġ�� ������ �޴� Lensflare�� ������ Ŭ����
*
*****************************************************************************/

#pragma once

#include "NtlPLAttach.h"
#include "NtlDebug.h"
#include "NtlEffectDefine.h"

#define	LENSFLARE_FADE_VELOCITY		4.0f
#define	LENSFLARE_PICK_TICK			0.3f

///< LensFlare�� �����ϴ� Spot�� ������ ��� �ִ� ����ü
struct SNtlPLLensFlareSpot
{
	RwTexture*	m_pTexture;					///< Spot�� Texture
	RwReal		m_fSize;					///< Spot�� Size (0.0 ~ 1.0)
	RwReal		m_fLinePos;					///< Spot�� ��ġ (1 ~ -1)
	RwRGBAReal	m_color;					///< Spot�� Vertex Color	
	RwIm2DVertex* m_pIm2dBuffer;			///< Spot�� �����ϴ� Vertex ����

	SNtlPLLensFlareSpot()
	{
		m_pTexture = NULL;
		m_fSize = 1.0f;
		m_fLinePos = 0.5f;
		m_color.red = m_color.green = m_color.blue = m_color.alpha = 1.0f;
		m_pIm2dBuffer = NULL;
	}

	SNtlPLLensFlareSpot(RwTexture* pTexture, RwReal fSize, RwReal fLinePos, RwReal red, RwReal green, RwReal blue, RwReal alpha)
	{
		m_pTexture = pTexture;
		m_fSize = fSize;
		m_fLinePos = fLinePos;		
		m_color.red = red;
		m_color.green = green;
		m_color.blue = blue;
		m_color.alpha = alpha;
		m_pIm2dBuffer = NULL;
	}

	~SNtlPLLensFlareSpot()
	{
		if(m_pIm2dBuffer)
		{
			NTL_ARRAY_DELETE(m_pIm2dBuffer);
		}
	}
};

class CNtlPLLensFlare : public CNtlPLAttach
{
public:
	CNtlPLLensFlare(void);
	virtual ~CNtlPLLensFlare(void);

	virtual RwBool	Create( const SPLEntityCreateParam * pParam = NULL );
	virtual RwBool	SetProperty(const CNtlPLProperty *pData);
	virtual void	Destroy(void);
	virtual RwBool	Update(RwReal fElapsed);
	virtual RwBool	Render(void);

	virtual void	SetMatrix(RwMatrix& matWorld);

	void	AddSpot(const SNtlPLLensFlareSpot& spot);				///< Spot�� �߰��Ѵ�.
	void	AddSpotForTest(const std::string& strXMLFileName);		///< XML���Ͽ��� Spot ������ �о�ͼ� �����Ѵ�

	void	SetMaxIntensity(RwReal fMaxIntensity) {m_fIntensity = fMaxIntensity;}	///< �ִ� ������ �����Ѵ�. (0.0 ~ 1.0 ����)
	RwReal  GetMaxIntensity() {return m_fIntensity;}				///<  �ִ� ������ ��ȯ�Ѵ�.

protected:
	void	AddSpots();												///< Spot���� ���Ϳ� �߰��Ѵ�.
	void	UpdateVertices(RwReal fElapsedTime);					///< vertex���� ������ Update�Ѵ�.
	void	SetRhwVertex(RwIm2DVertex* pVertex, RwReal nStartX, RwReal nStartY, RwInt32 width, RwInt32 height, RwRGBAReal color);		///< 2D Vertex���� �����Ѵ�
	RwBool	CalcPicking(const RwV2d& posLight);						///< ������ Object�� Terrain Collision�� üũ�Ͽ� ������ �Ⱥ����� �����Ѵ�.

protected:
	std::vector<SNtlPLLensFlareSpot>		m_vecSpots;
	std::vector<RwTexture*>					m_vecTex;	
	RwReal									m_fIntensity;			///< Flare�� �ִ� ����
	RwReal									m_fIntensityBorder;		///< Flare�� ���� (������ ������ �ش�)	
	RwMatrix								m_matWorld;				///< World Matrix (Pos�� �����ϱ� ���ؼ� ����Ѵ�)
	RwBool									m_bRender;				///< Render ����
	RwReal									m_fFadeIntensity;		///< Fade In/Out�� ����
	EFadeStatus								m_eFadeStatus;

	// Pick Tick ������ ������
	RwBool									m_bPrevPickingResult;	///< ���� Tick���� �����ϰ� �ִ� Picking �����
	RwReal									m_fPickingTickTime;		///< Pick�� Tick�� �����ϱ� ���� Time ����									
};	
