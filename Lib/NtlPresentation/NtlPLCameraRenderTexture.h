/*****************************************************************************
 *
 * File			: NtlPLCameraRenderTexture.h
 * Author		: HongHoDong
 * Copyright	: (��)NTL
 * Date			: 2006. 8. 19.	
 * Abstract		: NtlPLCameraRenderTexture
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

/**
 * \ingroup NtlPresentation
 * RenderWare�� RenderToTexture ����� Wrapping �� Class �̴�.
 * Texture�� �����ؼ� ����� �ϹǷ� ����ϴ��ʿ����� Texture�� �޾Ƽ� Rendering
 * �� �ϸ� �ȴ�.
 * CameraRenderTexture�� ��,�� ������ Camera�� ZBuffer�� ��� ������ �ϱ� ������
 * ZBuffer�� Memory�� ���� ����� �ɰ� ����.
 */

#ifndef __NTL_CAMERA_RENDER_TEXTURE_
#define __NTL_CAMERA_RENDER_TEXTURE_

#include "NtlDebug.h"
#include "NtlPLEntity.h"

//#define RENDER_TEXTURE_ASPECTRATIO (4.0f/3.0f)

class CNtlPLCameraRenderTexture
{
protected:
	RwCamera	*m_pCamera;																///< RenderToTexture�� Camera
	RwTexture	*m_pRenderTexture;														///< RenderToTexture�� Texture
	RwBool		m_IsCamInWorld;
	
protected:
	void SetCalcFov(RwReal fFov, RwInt32 nWidth, RwInt32 nHeight);

public:
	CNtlPLCameraRenderTexture() : m_pCamera(NULL), m_pRenderTexture(NULL) {} ;
	~CNtlPLCameraRenderTexture() {};

	void Create( RwInt32	nTexWidth,														///< RenderTexture�� ����(nWidth:����, nHeight; ����) 
		         RwInt32	nTexHeight, 
				 RwInt32	nRealWidth, 
				 RwInt32	nRealHeight,
				 RwReal		fFov = 45.f,
				 RwBool		IsCamInWorld = FALSE);

	void SetNear(RwReal _Near);
	void SetFar(RwReal _Far);
	RwCamera* GetCamera() { return m_pCamera; }
																						///< Texture Size�ʹ� ������ ��� ������ �ִ� ����?
	void Destroy();
	
	void RenderTexture();																// Render NTL World
	void RenderTexture(CNtlPLEntity *pEntity);											///< Entity�� Texture�� Rendering�� �Ѵ�.
	void RenderTexture(std::list<CNtlPLEntity*>& listEntity);
																						///< Texture�� Rendering�� �ϴ� Timing�� ��� �� ���ΰ�?
																						///< Ui�� Update�� �� �� Rendering�� �� ��� ������ ���� �ϴ�.
	
	void Render(RwCamera *pRenderTarget, RwV2d fPos, RwV2d fSize);	    				///< Test�� m_pRenderTexture�� Rendering
	
	RwTexture *GetTexture() { NTL_ASSERTE(m_pRenderTexture); return m_pRenderTexture; } ///< Texture Return(Reference ������ �ұ� �����)
	void SetCameraPosition(const RwV3d *pCameraPos, const RwV3d *pLookAt);				///< Camera Transform
};

#endif